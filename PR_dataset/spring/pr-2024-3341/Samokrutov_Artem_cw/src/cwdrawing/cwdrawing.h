#ifndef CWDRAWING_H
#define CWDRAWING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../cwbmp/cwbmp.h"
#include "../cwerror/cwerror.h"


void draw_dot(Bitmap_image_t *image, Coord_t coordinate, RGB_t color);

void fill_circle(Bitmap_image_t *image, Coord_t center, int radius, RGB_t color); //!!

void draw_circle(Bitmap_image_t *image, Coord_t center, int radius, RGB_t color, int rim);

void draw_line(Bitmap_image_t *image, Coord_t start, Coord_t end, RGB_t color, int thickness);

void invert_dot(Bitmap_image_t *image, Coord_t coordinate);

void invert_circle(Bitmap_image_t *image, Coord_t center, int radius);

void crop(Bitmap_image_t *image, Coord_t left_up, Coord_t right_down); 

void contrast(Bitmap_image_t *image, float alpha, int beta);

void blur(Bitmap_image_t *image, int size);

#endif