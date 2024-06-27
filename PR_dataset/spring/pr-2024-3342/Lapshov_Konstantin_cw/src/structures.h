#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short bfSign;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned short biPlanes;
    unsigned short biBitSize;
    unsigned int biCompression;
    unsigned int biImageSize;
    unsigned int biXPixelsPerMeter;
    unsigned int biYPixelsPerMeter;
    unsigned int biClrTotal;
    unsigned int biClrImportant;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
}RGB;
#pragma pack(pop)

typedef struct{
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB **img;
}BMP;

typedef struct {
    int x;
    int y;
}Point;

typedef struct {
    char* inputFileName;
    char* outputFileName;

    bool hasHelpOpt;
    bool hasInputOpt;
    bool hasOutputOpt;
    bool hasInverseCircleOpt;
    bool hasTrimOpt;
    bool hasTriangleOpt;
    bool hasLineOpt;
    bool hasRhombusOpt;
    bool hasCenterOpt;
    bool hasRadiusOpt;
    bool hasLeftUpOpt;
    bool hasRightDownOpt;
    bool hasPointsOpt;
    bool hasThicknessOpt;
    bool hasColorOpt;
    bool hasFillOpt;
    bool hasFillColorOpt;
    bool hasStartOpt;
    bool hasEndOpt;
    bool hasInfoOpt;

    int radius;
    int thickness;

    Point center;
    Point leftUp;
    Point rightDown;
    Point* points;
    Point start;
    Point end;

    RGB color;
    RGB fillColor;
}Option;