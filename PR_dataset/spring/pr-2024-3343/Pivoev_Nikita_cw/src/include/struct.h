#ifndef STRUCT_H
#define STRUCT_H

#include <png.h>
#include <stdbool.h>

typedef struct {
    int r;
    int g;
    int b;
} RGB;

typedef struct {
    char* input;
    char* output;
    bool info;
    
    bool copy;
    int copy_left;
    int copy_up;
    int copy_right;
    int copy_down;
    int copy_dest_left;
    int copy_dest_up;

    bool color_replace;
    RGB old_color;
    RGB new_color;

    bool ornament;
    int ornament_pattern;
    int ornament_count;

    bool filled_rects;
    RGB rects_border_color;

    RGB color;
    int thickness;

    bool outside_ornament;
} OptParams;

typedef struct {
    int height, width;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

#endif