#pragma once
#include "defines.h"

Rgb** drawSquare(BitmapInfoHeader* BMPInfo, Rgb** arr, SquareProperty sp);
void fillingSquare(BitmapInfoHeader* BMPInfo, Rgb** arr, SquareProperty sp);
void drawLineByBrezenhem(Rgb** pixels, int x0, int y0, int x1, int y1, BitmapInfoHeader* bifh, int thick, Rgb color);
void drawCircle(int x0, int y0, int radius, Rgb color, Rgb** pixels, int width, int height);
void drawPoint(int x0, int y0, Rgb color, Rgb** pixels, int width, int height);
Rgb** exchangeAreas(BitmapInfoHeader* BMPinfo, char* typeExchange, int left, int up, int right, int down, Rgb** pixels);
void pasteArea(Rgb** area, Rgb** pixels, const int width, const int height, const int left, const int up);
void copyArea(Rgb** area, const int widthArea, const int heightArea, const int left, const int up, Rgb** pixels);
Rgb** findAndReplaceColor(BitmapInfoHeader *BMPInfo, Rgb** pixels, Rgb color, char* img);
Rgb getPrimeColor(char *FILE_NAME);
int isColorEqual(Rgb firColor, Rgb secColor);
Rgb** gammedPixels(BitmapInfoHeader *BMPInfo,Rgb** pixels,double value);