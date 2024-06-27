#include "checkers.h"

void coordschecker(char * cords){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+\\.\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, cords, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "incorrect coordinates were submitted\n");
        exit(41);
    }

}

void distancechecker(char * distance){
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "could not compile regex\n");
        exit(1);
    };
    reti = regexec(&regex, distance, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "incorrect distance were submitted\n");
        exit(41);
    }
}

int *parse_color(char *color) {
    int *colors = malloc(3 * sizeof(int));
    char *copy_color = strdup(color);
    char *pch = strtok(copy_color, ".");
    for(int i = 0; i < 3; i++){
        colors[i] = atoi(pch);
        pch = strtok(NULL, ".");
    }
    free(copy_color);
    return colors;
}

void colorchecker(char *color) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+\\.[0-9]+\\.[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, color, 0, NULL, 0);
    if (reti){
        fprintf(stderr, "incorrect color were submitted\n");
        exit(41);
    }

    int *color_rgb = parse_color(color);
    if (color_rgb[0] > 255 || color_rgb[1] > 255 || color_rgb[2] > 255 || color_rgb[0] < 0 || color_rgb[1] < 0 ||color_rgb[2] < 0) {
        free(color_rgb);
        fprintf(stderr, "incorrect color were submitted\n");
        exit(41);
    }
    free(color_rgb);
}

void thickchecker(char *thickness) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, thickness, 0, NULL, 0);
    if (reti || atoi(thickness) < 1) {
        fprintf(stderr, "incorrect thickness were submitted\n");
        exit(41);
    }
}

void nameschecker(char* inputname, char* outputname){
    if (strcmp(inputname,outputname)==0){
        fprintf(stderr,"the same input and output names have been submitted\n");
        exit(41);
    }
}


void count_argscheck(char * arg1,char * arg2,char * arg3, char * name){
    if (arg2 != NULL){
        if(strstr(arg1,"--")){
            fprintf(stderr,"there are no arguments for %s\n",name);
            exit(41);
        }else if (!strstr(arg2,"--") && arg3 != NULL){
            fprintf(stderr,"there are too many arguments for %s\n",name);
            exit(41);
        }
    }
}

void no_argschecker(char* arg1, char* arg2, char *name){
    if(arg1 != NULL){
        if(!strstr(arg1,"--") && arg2 != NULL){
            fprintf(stderr,"%s should not have arguments\n",name);
            exit(41);
        }
    }
}
