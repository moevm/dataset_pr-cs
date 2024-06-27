#pragma once

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Rgb check_color(int r, int g, int b);
void check_coord(BitmapInfoHeader *bmif, int *left_x, int *up_y, int *right_x, int *down_y);
void inverse_color(Rgb *color);
void inverse(Rgb **arr, BitmapInfoHeader bmif, int left_x, int up_y, int right_x, int down_y);
void gray_color(Rgb *color);
void gray(Rgb **arr, BitmapInfoHeader bmif, int left_x, int up_y, int right_x, int down_y);
void color_pixel(Rgb *pixel, Rgb color);
void color_bmp (Rgb **arr, BitmapInfoHeader* bmif, Rgb new_color);
Rgb** resize(Rgb **arr, BitmapInfoHeader* bmif, int left, int right, int below, int above, Rgb color);
void color_pixel_check(Rgb** arr, BitmapInfoHeader* bmif, int y, int x, Rgb color);
void fill_wide_circle(Rgb** arr, BitmapInfoHeader* bmif, int x_center, int y_center, int radius, Rgb color);
void draw_line(Rgb **arr, BitmapInfoHeader* bmif, int start_x, int start_y, int end_x, int end_y, int thickness, Rgb color);
Rgb comp_color (Rgb ** arr, int N, int x, int y);
Rgb** compress(Rgb** arr, int N, BitmapInfoHeader* bmif);
