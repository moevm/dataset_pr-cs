#pragma once

#include <png.h>

typedef struct Arguments{
    int info_flag;
    char* input_file;
    char* output_file;

    int circle;
    int rgb_filter;
    int split;
    int fill;

    char* center;

    char* radius;
    char* thickness;
    char* component_value;
    char* number_x;
    char* number_y;

    char* component_name;

    char* color;
    char* fill_color;
    int gamma;
    char* value;
} args_t;

typedef struct Coordinates{
    int x;
    int y;
} coords_t;

typedef struct Color{
    int r;
    int g;
    int b;
} rgb_t;

typedef struct FunctionParameters{
    char* input_file;
    char* output_file;
    int info_flag;

    int circle;
    int rgb_filter;
    int split;
    int fill;

    int radius;
    int thickness;
    int component_value;
    int number_x;
    int number_y;

    char* component_name;

    coords_t center;

    rgb_t color;
    rgb_t fill_color;
    int gamma;
    float value;
} params_t;

typedef struct png{
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep *row_pointers;
} png_t; 