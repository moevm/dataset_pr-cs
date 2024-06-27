#include "checkers.h"

int *parse_coords(char *coords) {
    int *result = malloc(sizeof(int) * 2);
    char *copy_coords = strdup(coords);
    char *token = strtok(copy_coords, ".");
    result[0] = atoi(token);
    token = strtok(NULL, ".");
    result[1] = atoi(token);
    free(copy_coords);
    return result;
}

int *parse_color(char *color) {
    int *result = malloc(sizeof(int) * 3);
    char *copy_color = strdup(color);
    char *token = strtok(copy_color, ".");
    for (int i = 0; i < 3; i++) {
        result[i] = atoi(token);
        token = strtok(NULL, ".");
    }
    free(copy_color);
    return result;
}

void check_one_coords(char *coords) {
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+\\.[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(41);
    }
    reti = regexec(&regex, coords, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "Coords are not correct\n");
        exit(41);
    }
}

void check_size(char *radius) {
    regex_t regex;
    int reti = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, radius, 0, NULL, 0);
    if (reti || atoi(radius) < 0) {
        fprintf(stderr, "Value is not correct\n");
        exit(41);
    }
}

void check_thickness(char *thickness) {
    regex_t regex;
    int reti = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(41);
    }
    reti = regexec(&regex, thickness, 0, NULL, 0);
    if (reti || atoi(thickness) < 0) {
        fprintf(stderr, "Thickness is not correct\n");
        exit(41);
    }
}

void check_flo(char *thickness) {
    regex_t regex;
    int reti = regcomp(&regex, "[+-]?([0-9]*[.])?[0-9]+", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(41);
    }
    reti = regexec(&regex, thickness, 0, NULL, 0);
    if (reti || atoi(thickness) < 0) {
        fprintf(stderr, "Thickness is not correct\n");
        exit(41);
    }
}


void check_color(char *color) {
    regex_t regex;
    int reti = regcomp(&regex, "[0-9]+\\.[0-9]+\\.[0-9]+", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    int *color_rgb = parse_color(color);
    reti = regexec(&regex, color, 0, NULL, 0);
    if (reti || color_rgb[0] > 255 || color_rgb[1] > 255 || color_rgb[2] > 255 || color_rgb[0] < 0 || color_rgb[1] < 0 ||color_rgb[2] < 0) {
        free(color_rgb);
        fprintf(stderr, "Color is not correct\n");
        exit(41);
    }
    free(color_rgb);
}

void check_component_name(char *color){
    if(strcmp(color, "red") == 0 || strcmp(color, "green") == 0 || strcmp(color, "blue") == 0){
       int c = 0; 
    }else{
        fprintf(stderr, "Component_name is not correct\n");
        exit(41);
    }
}

void check_angle(char *angle){
    if(strcmp(angle, "90") == 0 || strcmp(angle, "180") == 0 || strcmp(angle, "270") == 0){
       int c = 0; 
    }else{
        fprintf(stderr, "Angle is not correct\n");
        exit(41);
    }
}
