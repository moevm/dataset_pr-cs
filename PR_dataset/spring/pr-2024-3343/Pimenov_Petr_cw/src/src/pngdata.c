#include <stdlib.h>

#include "pngdata.h"

int
color_cmp(color_t* a, color_t* b) {
    if (a == NULL) {
        return 0;
    }
    if (b == NULL) {
        return 0;
    }
    return a->r == b->r && a->g == b->g && a->b == b->b;
}

color_t*
create_color(png_byte r, png_byte g, png_byte b) {
    color_t* color = (color_t*)malloc(1 * sizeof(color_t));
    color->r = r;
    color->g = g;
    color->b = b;
    return color;
}

color_t*
create_void_color(color_t* color) {
    if (color == NULL) {
        return NULL;
    }
    return create_color(abs(255 - color->r), abs(255 - color->g), abs(255 - color->b));
}

canvas_t*
create_canvas(int width, int height) {
    if (width <= 0) {
        return NULL;
    }
    if (height <= 0) {
        return NULL;
    }
    canvas_t* canvas = (canvas_t*)malloc(1 * sizeof(canvas_t));
    canvas->width = width;
    canvas->height = height;
    canvas->grid = (png_bytepp)malloc(height * sizeof(png_bytep));
    for (size_t row = 0; row < height; row++) {
        canvas->grid[row] = (png_bytep)calloc(width * BYTES_PER_PIXEL, sizeof(png_byte));
    }
    return canvas;
}

void
free_canvas(canvas_t* canvas) {
    for (int row = 0; row < canvas->height; ++row) {
        free(canvas->grid[row]);
    }
    free(canvas->grid);
    free(canvas);
}