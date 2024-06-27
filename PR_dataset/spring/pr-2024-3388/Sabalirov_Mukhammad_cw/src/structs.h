#pragma once
#include "png.h"

typedef struct func_param_args{
	int mirror;
	int pentagram;
	int rect;
	int hexagon;
	int fill;
	int info;
	int paving;
	char* axis;
	char* left_up;
	char* right_down;
	char* center;
	char* radius;
	char* thickness;
	char* color;
	char* fill_color;
	char* input;
	char* output;
} func_param_args_t;

typedef struct func_params{
	int mirror;
	int pentagram;
	int rect;
	int hexagon;
	int fill;
	int info;
	int paving;
	int axis;
	int left_up_x;
	int left_up_y;
	int right_down_x;
	int right_down_y;
	int center_x;
	int center_y;
	int radius;
	int thickness;
	int color_r;
	int color_g;
	int color_b;
	int fill_color_r;
	int fill_color_g;
	int fill_color_b;
	char* input;
	char* output;
} func_params_t;

typedef struct png{
	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep *row_pointers;
} png_t; 