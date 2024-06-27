#include "mirror.h"
#include <png.h>
//#include "/opt/homebrew/include/png.h"
#include "struct_png.h"
#include <iostream>

using namespace std;

int* pre(int* cor, int w, int h){
    int* k = new int [2];
    k[0] = cor[0];
    k[1] = cor[1];
    if (k[0] < 0) k[0] = 0;
    if (k[1] < 0) k[1] = 0;
    if (k[0] > w) k[0] = w;
    if (k[1] > h) k[1] = h;
    return k;
}

void mirror(struct Png *image, char axis, int* k1, int* k2) {
    int x,y;
    int* cor1 = pre(k1, image->width, image->height);
    int* cor2 = pre(k2, image->width, image->height);
    switch (axis) {
        case 'x':
            for (y = min(cor1[1], cor2[1]); y < max(cor1[1], cor2[1]); y++) {
                png_byte *row = image->row_pointers[y];
                for (x = min(cor1[0], cor2[0]); x < min(cor1[0], cor2[0]) + abs(cor2[0] - cor1[0]) / 2; x++) {
                    png_byte r = row[x * 3];
                    row[x * 3] = row[(cor2[0] + cor1[0]) * 3 - x * 3];
                    row[(cor2[0] + cor1[0]) * 3 - x * 3] = r;
                    png_byte g = row[x * 3 + 1];
                    row[x * 3 + 1] = row[(cor2[0] + cor1[0]) * 3 - x * 3 + 1];
                    row[(cor2[0] + cor1[0]) * 3 - x * 3 + 1] = g;
                    png_byte b = row[x * 3 + 2];
                    row[x * 3 + 2] = row[(cor2[0] + cor1[0]) * 3 - x * 3 + 2];
                    row[(cor2[0] + cor1[0]) * 3 - x * 3 + 2] = b;
                }
            }
            break;
        case 'y':
            for (y = min(cor1[1], cor2[1]); y < min(cor1[1], cor2[1]) + abs(cor2[1] - cor1[1])/2; y++) {
                png_byte *row = image->row_pointers[y];
                png_byte *row_2 = image->row_pointers[max(cor1[1], cor2[1]) - (y - min(cor1[1], cor2[1]))];
                for (x = min(cor1[0], cor2[0]); x < max(cor1[0], cor2[0]); x++) {
                    png_byte r = row[x * 3];
                    row[x * 3] = row_2[x * 3];
                    row_2[x * 3] = r;
                    png_byte g = row[x * 3 + 1];
                    row[x * 3 + 1] = row_2[x * 3 + 1];
                    row_2[x * 3 + 1] = g;
                    png_byte b = row[x * 3 + 2];
                    row[x * 3 + 2] = row_2[x * 3 + 2];
                    row_2[x * 3 + 2] = b;
                }
            }
            break;
    }
}