#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>
#include <math.h>

#pragma pack (push, 1) 
typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb; 

typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader; 
#pragma pack(pop)

typedef struct {
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb **pixels;
} Image;

typedef struct coordinates{
    int x, y;
} coords;

typedef struct image_resize{
    int left_dist;
    int right_dist;
    int above_dist;
    int below_dist;
} image_resize;


typedef struct line{
    coords start, end;
    int thickness;
} line;

#endif
