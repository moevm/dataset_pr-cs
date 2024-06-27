#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "../file_handling/file_handling.h"

Rgb check_color(int r, int g, int b);
void color_pixel(int x, int y, Rgb **arr, Rgb color, unsigned int H, unsigned int W);
void draw_thick(int x, int y, Rgb **arr, int width, unsigned int H, unsigned int W, Rgb color);
void draw_line(int x1, int y1, int x2, int y2, int width, unsigned int H, unsigned int W, Rgb **arr, Rgb color);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int width, unsigned int H, unsigned int W, Rgb **arr, Rgb color);
int check_tr(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);
void fill_tr(Rgb **arr, Rgb color, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int H, unsigned int W);
void find_color_max_rect(unsigned int H, unsigned int W, Rgb **arr, Rgb color_find, Rgb color_fill);
Rgb** collage(int x, int y, unsigned int H, unsigned int W, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr);  
void do_bin(Rgb **arr, unsigned int H, unsigned int W, int porog);
void shift(Rgb **arr, unsigned int H, unsigned int W, int shift_x, int shift_y);

#endif 
