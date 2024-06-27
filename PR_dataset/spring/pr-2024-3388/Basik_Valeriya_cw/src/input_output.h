#pragma once

#include <stdio.h>
#include <stdlib.h>
#ifndef STRUCTS
#define STRUCTS
#pragma pack(push, 1)
typedef struct
{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
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

typedef struct
{
    unsigned char b ;
    unsigned char g ;
    unsigned char r;
} Rgb;

typedef struct
{
    int width, height;
    Rgb** pix;
} Image;

typedef struct
{
    Rgb old_color;
    Rgb new_color;

    int component_name;
    int component_value;

    int number_x;
    int number_y;
    int thickness;
    Rgb color;

    int size;
    Rgb circle_color;
} Config;

#pragma pack(pop)
#endif

Image read_bmp(char file_name[], BitmapFileHeader*bmfh, BitmapInfoHeader* bmif);
void print_file_header(BitmapFileHeader header);
void print_info_header(BitmapInfoHeader header);
void write_bmp(char file_name[], Image* image, BitmapFileHeader bmfh, BitmapInfoHeader bmif);
