#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#pragma pack(push, 1)

typedef struct BMP_FileHeader{
    unsigned short signature; 
    unsigned int filesize;
    unsigned short reserved1; 
    unsigned short reserved2; 
    unsigned int pixelArrOffset;
} BMP_FileHeader;

typedef struct BMP_InfoHeader{
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
} BMP_InfoHeader;

typedef struct{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;
#pragma pack(pop)

typedef struct BMP{
    RGB** pixels;
    BMP_FileHeader* bmfh;
    BMP_InfoHeader* bmih;
} BMP;

typedef struct {
    int left;
    int up;
    int right;
    int down;
    int thickness;
    int side_size;
    RGB* color;
    RGB* fill_color;
    int fill;
    char* input_name;
    char* output_name;
    char component_name;
    int component_value;
    int angle;
    int rotate;
    int squared_lines;
    int rgb_filter;
    int info;
    int square_rhombus;
    int upper_vertex;
    int size;
} Parameters;
#endif
