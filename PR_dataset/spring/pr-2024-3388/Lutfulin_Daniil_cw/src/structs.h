#pragma once

#pragma pack(push,1)
typedef struct BitmapFileHeader{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} bmp_file_header_t;

typedef struct BitmapInfoHeader{
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
} bmp_info_header_t ;

typedef struct Rgb{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}rgb_t;

#pragma pack(pop)

typedef struct Bitmap{
    rgb_t **arr;
    unsigned int width;
    unsigned int height;
}pixels_t;

typedef struct Point{
    int x;
    int y;
}point_t;

typedef struct Args{
    int help;
    int info;
    char* input_file;
    char* output_file;

    int mirror;
    char* mirror_axis;
    char* left_up;
    char* right_down;

    int copy;
    char* dest_left_up;

    int color_replace;
    char* old_color;
    char* new_color;

    int split;
    char* number_x;
    char* number_y;
    char* thickness;
    char* color;

    int ornament;
}args_t;

typedef struct Processed_arguments{
    int info;
    char* input_file;
    char* output_file;

    int mirror;
    char mirror_axis;
    point_t left_up;
    point_t right_down;

    int copy;
    point_t dest_left_up;

    int color_replace;
    rgb_t old_color;
    rgb_t new_color;

    int split;
    size_t number_x;
    size_t number_y;
    size_t thickness;
    rgb_t color;

    int ornament;
}pargs_t;