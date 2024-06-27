#ifndef PROCESSING_H
#define PROCESSING_H

#include "bmp.h"
#include "pixels.h"

int max(int a, int b);

int min(int a, int b);

void crop_image(bmp_file_t* image, point_t left_up, point_t right_down);

void process_circle(bmp_file_t* image, point_t center, int radius, rgb_t color, void (*process_pixel)(bmp_file_t*, point_t, rgb_t));

void inverse_inside_circle(bmp_file_t* image, point_t point, int radius);

void draw_line(bmp_file_t* bmp, point_t start, point_t end, int thickness, rgb_t color);

void draw_triangle(bmp_file_t* image, point_t p0, point_t p1, point_t p2, rgb_t color, int thickness, unsigned char fill, rgb_t color_fill);

void circle_pixel(bmp_file_t* image, int w, int h, rgb_t color, rgb_t circle_color, int size);

#endif