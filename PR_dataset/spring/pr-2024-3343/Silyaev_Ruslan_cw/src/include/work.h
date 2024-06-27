#ifndef WORK_H
#define WORK_H

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <png.h>

void read_png_file(char *file_name, Png *image);
void write_png_file(char *file_name, Png *image);
void changeColor(png_byte* ptr, RGB color);
void Square(Png* image, Parametrs* par);
int check(int x, int y, int W, int H);
void drawLine(Png* image, int x1, int y1, int x2, int y2, int line_thickness, RGB color);
void drawCircle(Png* image ,int x0, int y0, int radius, RGB color);
void Exchange(Png* image, Parametrs* par);
void swapAreas(Png* image, Rectangle* first, Rectangle* second);
void FreqColor(Png* image, Parametrs* par);
void Contrast(Png* image, Parametrs* par);

#endif