#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "print.h"
#include "Bitmapstruct.h"
#include "option.h"
#include "picture.h"
#include "check.h"
#include "proces.h"

int main(int argc, char *argv[]) {
    char *output = NULL;
    char *input = NULL; 
    char *old_col = NULL;
    char *new_col = NULL;
    char *value=NULL;
    float number=0;
    printf("Course work for option 3.1, created by Dmitrii Anisimov.\n");
    char comand =option(&output,&input,&old_col,&new_col,&value,argc, argv);
    Rgb_i old, new;
    check(&old ,&new, comand, new_col, old_col,value, &number);
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;
    Rgb **arr = read_bmp(input, &bmfh, &bmif);
    unsigned int H = bmif.height;
    unsigned int W = bmif.width;
    proces(comand,old ,new, number,arr,bmfh, bmif);
    write_bmp(output, arr, bmif.height, bmif.width, bmfh, bmif);
    return 0;
}