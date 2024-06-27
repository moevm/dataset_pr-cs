#include "check.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void check(Rgb_i *old ,Rgb_i  *new,char comand,char *new_col,char *old_col,char *value,float *number){
    if (old_col == NULL && comand == 'r') {
        printf("missing color\n");
        exit(47);
    } else if (comand == 'r') {
        if (sscanf(old_col, "%d.%d.%d", &(*old).r, &(*old).g, &(*old).b) != 3) {
            printf("color error1\n");
            exit(47);
        }
        if ((*old).r < 0 ||(*old).r > 255 || (*old).g < 0 || (*old).g > 255 || (*old).b < 0 || (*old).b > 255) {
            printf("color error2\n");
            exit(47);
        }
    }
    if (new_col == NULL && comand == 'r') {
        printf("missing color\n");
        exit(47);
    } else if (comand == 'r') {
        if (sscanf(new_col, "%d.%d.%d", &(*new).r, &(*new).g, &(*new).b) != 3) {
            printf("color error3\n");
            exit(47);
        }
        if ((*new).r < 0 || (*new).r > 255 || (*new).g < 0 || (*new).g > 255 || (*new).b < 0 ||(*new).b > 255) {
            printf("color error4\n");
            exit(47);
        }
    }
    if (value == NULL && comand == 'g') {
        printf("missing value\n");
        exit(47);
    } else if (comand == 'g') {
        if (sscanf(value, "%f", &(*number)) != 1) {
            printf("value error\n");
            exit(47);
        }
        if (number<=0){
            printf("value error\n");
            exit(47);}
    }
}