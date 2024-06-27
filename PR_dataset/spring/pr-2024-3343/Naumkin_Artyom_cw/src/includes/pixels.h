#ifndef PIXELS_H
#define PIXELS_H

#include "bmp.h"

typedef struct {
    int x;
    int y;
} point_t;

int check(point_t point, int w, int h);

void set_pixel(bmp_file_t* bmpf, point_t point, rgb_t color);

void inverse_pixel(bmp_file_t* image, point_t point, rgb_t color);

int point_inside_triangle(point_t p, point_t v0, point_t v1, point_t v2);

#endif