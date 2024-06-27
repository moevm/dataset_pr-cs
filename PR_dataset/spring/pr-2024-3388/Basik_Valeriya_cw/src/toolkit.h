#pragma once

#include "input_output.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ERROR_REQUIRED_PARAMETER "error: no required parameter"
#define ERROR_CODE 40
#define ERROR_INVAlID_COLOR "error: color must be 0-255"
int cmp_color(Rgb first, Rgb second);
void set_pixel(Image* image, int x, int y, Rgb color);
int get_number(char* ptr);
Rgb get_color_arg(char* str);
void print_error_and_exit(const char *error_message);