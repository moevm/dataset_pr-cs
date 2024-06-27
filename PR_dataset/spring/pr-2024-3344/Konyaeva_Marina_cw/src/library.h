#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <png.h>
#include <getopt.h>
#include <regex.h>
#include <string.h> 

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

struct Configs{
	int x_y[2];
    int radius;
    int thickness;

    int* color;
    int fill;
    int* fill_color;

    char* component_name;
    int component_value;
    
    int number_x;
    int number_y;

    int side_size;
};

struct Flags{
    int x_y;
    int radius;
    int thickness;
    int color;

    int component_name;
    int component_value;
    
    int number_x;
    int number_y;

    int side_size;
};
