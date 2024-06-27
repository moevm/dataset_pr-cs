#ifndef STRUCTS_H
#define STRUCTS_H

#include <png.h>

typedef struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
}Png;

typedef struct Color{
	size_t r;
	size_t g;
	size_t b;
}Color;

typedef struct Squared_lines{
	int n;
	int coordinates;
	int left, up;
	int size;
	int thickness;
	Color* thickness_color;
	size_t fill;
	Color* fill_color;
}Squared_lines;

typedef struct Rgbfilter{
	int n;
	char component_name;
	size_t component_value;
}Rgbfilter;

typedef struct Rotate{
	int n;
	int coordinates;
	int left, up, right, down;
	size_t angle;
}Rotate;

typedef struct Rhombus{
	int n;
	int coordinates;
	int left, up;
	int size;
	Color* fill_color;
}Rhombus;

typedef struct Configs{
	int info;
	char* input;
	Squared_lines* squared_lines;
	Rgbfilter* rgbfilter;
	Rotate* rotate; 
	Rhombus* rhombus;
	char* output;
}Configs;


#endif
