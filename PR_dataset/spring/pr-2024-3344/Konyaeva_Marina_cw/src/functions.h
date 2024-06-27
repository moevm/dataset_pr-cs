#pragma once
#include "library.h"


int is_pixel_part_of_img(struct Png *img, int x, int y);
void set_pixel(struct Png *img, int x, int  y, int* arr_color);
void fill_circle(struct Png *img, int xc, int yc, int r, int *color_arr);
void draw_thick_circle(struct Png *img, int xc, int yc, int r, int th, int *color_arr);
void draw_in_octants(struct Png *img, int xc, int yc, int x, int y, int *color_arr);
void draw_contour_circle(struct Png *img, int xc, int yc, int r, int *color_arr);
void draw_line(struct Png *img, int x1, int y1, int x2, int y2,  int *arr_color);
void draw_thick_line(struct Png *img, int x1, int y1, int x2, int y2, int thick, int *arr_color);
void draw_circle(struct Png* img, int* center, int r, int thick, int* th_color, int flag_fill, int* fill_color);
void switch_filter(struct Png* img, char* comp_name, int comp_value);
void divide_image(struct Png* img, int N, int M, int thick, int* color_arr);
void draw_square(struct Png* img, int* center, int side, int thick, int* color_arr, int fill, int* fill_color);

void test(struct Png* img, int x1, int y1, int x2, int y2, int x3, int y3, int* color);
int is_point_in_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x0, int y0) ;


