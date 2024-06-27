#ifndef COURSE_MY_LIB_H
#define COURSE_MY_LIB_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <stdexcept>
#include <vector>
#include <map>
#include <clocale>

using namespace std;

#define ARG_ERR 40
#define NO_ARG_ERR 41
#define INCOR_TYPE_ERR 42

#pragma pack(push, 1)
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

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack(pop)

#endif //COURSE_MY_LIB_H
