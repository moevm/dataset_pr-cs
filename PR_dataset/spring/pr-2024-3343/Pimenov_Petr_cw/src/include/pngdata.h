#ifndef PNGDATA_H
#define PNGDATA_H

#include <png.h>

#define BYTES_PER_PIXEL 3

typedef struct {
    int width, height;
    png_bytepp grid;
} canvas_t;

typedef struct {
    int number_of_passes;
    png_byte color_type, bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    canvas_t* canvas;
} image_t;

typedef struct {
    png_byte r, g, b;
} color_t;

int color_cmp(color_t* a, color_t* b);
color_t* create_color(png_byte r, png_byte g, png_byte b);
color_t* create_void_color(color_t* color);
canvas_t* create_canvas(int width, int height);
void free_canvas(canvas_t* canvas);

#endif