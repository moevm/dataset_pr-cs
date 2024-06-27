#ifndef PROCESSING_H
#define PROCESSING_H

#include "bmp.h"

Rgb** drawRectangle(FunctionParams* fp, BMPFile* bmpf);

Rgb** drawOrnament(FunctionParams* fp, BMPFile* bmpf);

Rgb** rotateImage(FunctionParams* fp,BMPFile* bmpf);

Rgb** rotate(FunctionParams* fp,BMPFile* bmpf);

Rgb** binarization(FunctionParams* fp,BMPFile* bmpf);

Rgb** shifting(FunctionParams* fp,BMPFile* bmpf);

void swapPixels(Rgb* a, Rgb* b);

void setPixel(BMPFile* bmpf,int x,int y,Rgb color);

int check(int x, int y, int W, int H);

#endif