#pragma once

#include <math.h>
#include "structures.h"
#include "errors.h"
#include "bmpInteraction.h"

void swapInt(int* first, int* second);
void setPixel(BMP *bmp, Point point, RGB color);
bool pointInImage(BitmapInfoHeader bmif, Point point);
RGB getInvertPixelColor(BMP *bmp, Point point);

void fillCircle(BMP *bmp, Point center, int radius, RGB color, bool invert);
void trim(BMP* bmp, Point leftUp, Point rightDown);
void line(BMP *bmp, Point start, Point end, int thickness, RGB color);
void triangle(BMP *bmp, Point* points, int thickness, RGB color, int fill, RGB fill_color);
void rhomb(BMP *bmp, RGB color);
void choiceTask(BMP *bmp, Option option);