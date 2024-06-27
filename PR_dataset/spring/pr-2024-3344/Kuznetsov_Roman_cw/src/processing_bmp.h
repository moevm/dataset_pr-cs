#ifndef PROCESSING_BMP_H
#define PROCESSING_BMP_H
#include "bmp_reader.h"
#include "processing_data.h"

void romb(BMPfile* bmp, rgb color);
void check_boundary(int* x_min, int* x_max, int* y_min, int* y_max, int W, int H);
void mirror(BMPfile* bmp, int axis, coord left_up, coord right_down);
void collage(BMPfile* bmp, int count_y, int count_x);
void drawPixel(BMPfile* bmp, int x, int y, rgb color);
void drawThickness(BMPfile *bmp, int x, int y, int thickness, rgb color);
void drawingLine(BMPfile* bmp, coord start, coord end, int thickness, rgb color);
void drawRectangle(BMPfile* bmp, coord left_up, coord right_down, int thickness, rgb color, int fill, rgb fill_color);
void drawCircle(BMPfile* bmp, int x, int y, int r, int thickness, rgb color);
void drawPentagram(BMPfile* bmp, int x, int y, int r, int thickness, rgb color);

#endif
