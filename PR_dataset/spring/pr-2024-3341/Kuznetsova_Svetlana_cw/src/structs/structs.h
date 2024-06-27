#pragma once
#include <png.h>
#include <stdbool.h>

typedef struct{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

typedef struct {
    int r;
    int g;
    int b;
} RGB;

typedef struct {
    int x;
    int y;
} COORD;

typedef struct{
    int flag;
    int circle;
    int copy;
    int mirror;
    int contr;

    int radius;
    int thickness;
    float alpha;
    int beta;

    bool fill_flag;
    bool fill;
    bool input_flag;
    bool info_flag;

    char* axis;

    COORD center_coords;
    COORD left_up_coords;
    COORD right_down_coords;
    COORD dest_left_up_coords;

    RGB color;
    RGB fill_color;
} OPTS;
