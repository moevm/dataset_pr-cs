#pragma once
#include <getopt.h>
#include <stdio.h>

#ifndef STRUCTURE
#define STRUCTURE



#pragma pack (push, 1)
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


int is_replace = -1;
int is_filter = -1;
int is_split = -1;
int is_gamma = -1;


struct option longopts[] = {
            {"help", no_argument, NULL, 'h'},
            {"output", required_argument, NULL, 'o'},
            {"input", required_argument, NULL, 'p'},
            {"info", no_argument, NULL, 'i'},
            {"color_replace", no_argument, &is_replace, 'r'},
            {"old_color", required_argument, NULL, 'a'},
            {"new_color", required_argument, NULL, 'w'},
            {"rgbfilter", no_argument, &is_filter, 'f'},
            {"component_name", required_argument, NULL, 'n'},
            {"component_value", required_argument, NULL, 'v'},
            {"split", no_argument, &is_split, 's'},
            {"number_x", required_argument, NULL, 'x'},
            {"number_y", required_argument, NULL, 'y'},
            {"thickness", required_argument, NULL, 't'},
            {"color", required_argument, NULL, 'c'},
            {"gamma", no_argument, &is_gamma, 'g'},
            {"value", required_argument, NULL, 'j'},
            {0, 0, 0, 0}
};

#endif