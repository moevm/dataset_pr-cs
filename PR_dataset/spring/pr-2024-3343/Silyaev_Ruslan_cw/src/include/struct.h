#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <png.h>
#include <stdbool.h>

typedef struct{
    int height, width;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

typedef struct{
    int r;
    int g;
    int b;
} RGB;

typedef struct {
    int x0;
    int y0;
    int x1;
    int y1;
} Rectangle;

typedef struct {
    char* input;
    char* output;
    bool info;

    bool square;
    int left;
    int up;
    int side_size;
    int thickness;
    bool fill;
    RGB fill_color;

    bool exchange;
    int right;
    int down;
    int exchange_type;

    bool freq_color;

    bool contrast;
    double alpha;
    int beta;

    RGB color;
} Parametrs;

#endif