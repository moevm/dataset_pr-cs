
#ifndef STRUCTS_H 
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>

#define PI 3.14159265

#pragma pack(push, 1)

typedef struct BitmapFileHeader{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
}BitmapFileHeader;

typedef struct BitmapInfoHeader{
    unsigned int headerSize;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
}BitmapInfoHeader; 

typedef struct RGB {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}rgb;

typedef struct BMPFile {
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    rgb** data;
}BMPFile;

typedef struct coordinates{
    int x, y;
}coords;

typedef struct rect{
    coords start;
    coords end;
    unsigned int thickness;
    rgb color;
    int filled;
    rgb fill_color;
}rectangle;

typedef struct hex{
    //coords start, sec, thrd, fourth, fifth, end;
    unsigned int thickness;
    rgb color;
    int filled;
    rgb fill_color;
    coords centre;
    unsigned int radius;
}hexagon;

#pragma pack(pop)
#endif