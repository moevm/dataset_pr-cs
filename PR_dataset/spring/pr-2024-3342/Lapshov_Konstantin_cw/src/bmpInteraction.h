#pragma once

#include "structures.h"
#include "errors.h"

int getOffset(size_t width);
BMP readBMP(const char *filename);
void saveBMP(const char *filename, BMP bmp);

RGB** createArrayOfPixels(int height, int width);
void freeArrayOfPixels(BMP* bmp);

void printInfo(BMP header);