#include "checker.h"

void coords_checker(char* coords){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+\\.\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        printf("Error in coords_checker function: Could not compile regex.\n");
        exit(41);
    }
    reti = regexec(&regex, coords, 0, NULL, 0);
    if (reti) {
        printf("Error in coords_checker function: Coords are not correct.\n");
        exit(41);
    }

}

void distance_checker(char * distance){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        printf("Error in distance_checker function: Could not compile regex.\n");
        exit(41);
    };
    reti = regexec(&regex, distance, 0, NULL, 0);
    if (reti) {
        printf("Error in distance_checker function: distance is not correct\n");
        exit(41);
    }
    int digit = atoi(distance);
    if (digit < 1){
        printf("Error in distance_checker: digit is incorrect\n");
        exit(41);
    }
}

int *parse_color(char *color) {
    int *result = malloc(3 * sizeof(int));
    char *copy_color = malloc(sizeof(char) * 100);
    strcpy(copy_color, color);
    char *token = strtok(copy_color, ".");
    for(int i = 0; i < 3; i++){
        result[i] = atoi(token);
        token = strtok(NULL, ".");
    }
    free(copy_color);
    return result;
}

void color_checker(char *color) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+\\.[0-9]+\\.[0-9]+$", REG_EXTENDED);
    if (reti) {
        printf("Error in color_checker function: color is not correct\n");
        exit(41);
    }

    reti = regexec(&regex, color, 0, NULL, 0);
    if (reti){
        printf("The entered color is incorrect.\n");
        exit(41);
    }

    int *color_rgb = parse_color(color);
    if (color_rgb[0] > 255 || color_rgb[1] > 255 || color_rgb[2] > 255 || color_rgb[0] < 0 || color_rgb[1] < 0 ||color_rgb[2] < 0) {
        free(color_rgb);
        printf("The entered color is incorrect.\n");
        exit(41);
    }
    free(color_rgb);
}

void names_checker(char* inputname, char* outputname){
    if (strcmp(inputname, outputname)==0){
        printf("Error in names_checker: Input and output files are the same\n");
        exit(41);
    }
}

void no_argschecker(char* arg,char *name){
    if(arg != NULL){
        if(!strstr(arg,"--")){
            printf("%s doesn't have arguments\n", name);
            exit(42);
        }
    }
}
