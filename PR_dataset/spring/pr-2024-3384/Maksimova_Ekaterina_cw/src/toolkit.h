#pragma once

#include "input_output.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

int cmp_color(Rgb first, Rgb second);
Rgb get_color(Rgb** image, int x, int y, int width, int height, int* count);
void set_pixel(Image* image, int x, int y, Rgb color);
void border_rectangle(Image* image, int start_x, int start_y, int end_x, int end_y, int thick, Rgb color);
int cmp_color_on_area(Image* image, int x1, int y1, int x2, int y2, Rgb old);
void draw_circle(Image* image, Rgb color, int center_x, int center_y, int thickness,int radius);
int get_number(char* ptr);
Rgb get_color_arg(char* str);


