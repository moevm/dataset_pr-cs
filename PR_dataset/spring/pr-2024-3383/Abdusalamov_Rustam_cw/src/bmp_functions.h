#ifndef BMP_FUNCTIONS_H
#define BMP_FUNCTIONS_H

#include "structures.h"

void free_BMP(BMP* bmp);
BMP* read_BMP(const char* input_name);
void write_BMP(const char* output_name, BMP* bmp);
void rgb_filter(char component, int value, BMP* picture);
RGB** copy_area(BMP* bmp, int left, int up, int right, int down);
void rotate(BMP *bmp , int left, int up, int right, int down, int angle);
void set_pixel(BMP *bmp, int x, int y, RGB color);
void set_circle(BMP* bmp, int xc, int yc, int radius, RGB color);
void draw_line(BMP* bmp, int x0, int y0, int x1, int y1, RGB color, int thickness);
void squared_lines(BMP *bmp, int left, int up, int side_size, int thickness, RGB color, int fill, RGB* fill_color);
BMP* create_BMP(int height, int width, RGB fill_color);
void square_rhombus(BMP* bmp, int x0, int y0, int side_size, RGB* fill_color);
#endif

