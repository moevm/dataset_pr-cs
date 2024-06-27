#ifndef PNG_OBJECTS
#define PNG_OBJECTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <png.h>
#include <math.h>
#include <getopt.h>

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;

typedef struct Png {
    int width;
    int height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;


typedef struct info_file {
    int info;
    char *input_file;
    char *output_file;
} info_file;

typedef struct info_line {
    Point p0;
    Point p1;
    RGB color;
    int p;
    int thickness;
} info_line;

typedef struct info_mirror {
    Point p0;
    Point p1;
    int p;
    char axis;
} info_mirror;

typedef struct info_pentagram {
    Point center;
    RGB color;
    int p;
    int radius;
    int thickness;
} info_pentagram;

typedef struct info_contrast {
    int p;
    int beta;
    float alpha;
} info_contrast;

#endif