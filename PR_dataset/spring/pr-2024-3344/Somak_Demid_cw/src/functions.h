#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structurs.h"

void description(void);

void inverse(Image * img,int lu_x, int lu_y, int rd_x, int rd_y);

void black_white(Image *img,int lu_x, int lu_y, int rd_x, int rd_y);

void resize(Image * img, char side[], int distance,Rgb color);

void drawThickLine(Image *img, int x1, int y1, int x2, int y2, int thickness, Rgb color);

void drawRhombus(Image *img, Rgb color);
#endif