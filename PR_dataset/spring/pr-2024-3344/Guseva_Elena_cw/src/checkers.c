#include "checkers.h"

void coordschecker(char * coords){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+\\.\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, coords, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "Coords are not correct\n");
        exit(41);
    }

}

void distancechecker(char * distance){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    };
    reti = regexec(&regex, distance, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "distance is not correct\n");
        exit(41);
    }
}

int *parse_color(char *color) {
    int *result = malloc(3 * sizeof(int));
    char *copy_color = strdup(color);
    char *token = strtok(copy_color, ".");
    for(int i = 0; i < 3; i++){
        result[i] = atoi(token);
        token = strtok(NULL, ".");
    }
    free(copy_color);
    return result;
}

void colorchecker(char *color) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+\\.[0-9]+\\.[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, color, 0, NULL, 0);
    if (reti){
        fprintf(stderr, "Color is not correct\n");
        exit(41);
    }

    int *color_rgb = parse_color(color);
    if (color_rgb[0] > 255 || color_rgb[1] > 255 || color_rgb[2] > 255 || color_rgb[0] < 0 || color_rgb[1] < 0 ||color_rgb[2] < 0) {
        free(color_rgb);
        fprintf(stderr, "Color is not correct\n");
        exit(41);
    }
    free(color_rgb);
}

void thickchecker(char *thickness) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, thickness, 0, NULL, 0);
    if (reti || atoi(thickness) < 1) {
        fprintf(stderr, "This is not correct\n");
        exit(41);
    }
}

void nameschecker(char* inputname, char* outputname){
    if (strcmp(inputname,outputname)==0){
        fprintf(stderr,"Input and output files are the same\n");
        exit(41);
    }
}

void bmp_namechecker(char * name){
    regex_t regex;
    int reti = regcomp(&regex, "^\\S+\\.?[A-Za-z]*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    };
    reti = regexec(&regex, name, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "file is not correct or not given\n");
        exit(41);
    }
}

void count_argscheck(char * first,char * second,char * third, char * name){
    if (second != NULL){
        if(strstr(first,"--")){
            fprintf(stderr,"Not enaught arguments for %s\n",name);
            exit(44);
        }else if (!strstr(second,"--") && third != NULL){
            fprintf(stderr,"Too many arguments for %s\n",name);
            exit(44);
        }
    }
}

void no_argschecker(char* arg,char *name){
    if(arg != NULL){
        if(!strstr(arg,"--")){
            fprintf(stderr,"%s dont have arguments\n",name);
            exit(44);
        }
    }
}