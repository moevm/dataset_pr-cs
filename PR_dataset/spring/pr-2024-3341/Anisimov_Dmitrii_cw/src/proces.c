#include "proces.h"
#include <math.h>
#include "print.h"
#include <stdlib.h>

#define MIN(x,y) (((x)<(y))? (x) : (y))

void color_replace(unsigned char *a, unsigned char *b, unsigned char *c, unsigned char d, unsigned char f, unsigned char s, unsigned char i, unsigned char g, unsigned char p) {
    if (*a == d && *b == f && *c == s) {
        *a = i;
        *b = g;
        *c = p;
    }
}

void max_color(unsigned char *a, unsigned char *b, unsigned char *c) {
    if (*a >= *b && *a >= *c) {
        char t = *a;
        *b = t;
        *c = t;
    } else if (*b >= *a && *b >= *c) {
        char t = *b;
        *c = t;
        *a = t;
    } else {
        char t = *c;
        *a = t;
        *b = t;
    }
}
void proces(char comand,Rgb_i old ,Rgb_i new, float number,Rgb **arr,BitmapFileHeader bmfh, BitmapInfoHeader bmif){
    unsigned int H = bmif.height;
    unsigned int W = bmif.width;
    if (comand == 'i') {
        printFileHeader(bmfh);
        printInfoHeader(bmif);
        exit(0);
    }
    if (comand == 'r') {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
                color_replace(&arr[i][j].r, &arr[i][j].g, &arr[i][j].b, old.r, old.g, old.b, new.r, new.g, new.b);
        }
    } else if (comand == 'm') {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                max_color(&arr[i][j].r, &arr[i][j].g, &arr[i][j].b);
            }
        }
    } else if (comand == 'g') {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                arr[i][j].r=MIN(floor(pow(arr[i][j].r/255.0, number)*255),255);
                arr[i][j].g=MIN(floor(pow(arr[i][j].g/255.0, number)*255),255);
                arr[i][j].b=MIN(floor(pow(arr[i][j].b/255.0, number)*255),255);
            }
        }
    }
}
