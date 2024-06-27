#pragma once

#pragma pack(push,1)

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

typedef struct {
    int inverse;
    int gray;
    int resize;
    int line;
    int input;
    int output;
    int left_up;
    int right_down;
    int left;
    int right;
    int above;
    int below;
    int color;
    int start;
    int end;
    int thickness;
    int info;
    int compress;
    int num;
} check_option;

typedef struct{
    char* input_file;
    char* output_file;
    int left;
    int right;
    int down;
    int up;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    Rgb color;
    int thickness;
    int num;
} value;
