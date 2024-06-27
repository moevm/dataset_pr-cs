#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>


#pragma pack(push, 1)

typedef struct bmp_file_header_t {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct bmp_info_header_t {
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

typedef struct rgb_t {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;

typedef struct bmp_t {
    char* fileName;
    BitmapFileHeader bmfhdr;
    BitmapInfoHeader bmihdr;
    RGB** pixel_array;
} BMP;

typedef struct command_line_options_t {
    char* input;
    char* output;
    bool info;
    bool help;

    bool colorReplace;
    char* oldColor;
    char* newColor;

    bool rgbFilter;
    char* componentName;
    unsigned char componentValue;

    bool split;
    int numberX;
    int numberY;
    int thickness;
    char* color;

    bool binarization;
    int threshold;
} CommandLineOptions;


#endif
