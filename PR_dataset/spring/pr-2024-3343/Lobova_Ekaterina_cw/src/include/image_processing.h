#ifndef PROCESSING_H
#define PROCESSING_H

#define INFO "height: %d;\nwidth: %d;\ncolor_type: %d;\nbit_depth: %d\n"

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>
#include <math.h> 

void rgbfilter(Png *image, char component_name, int component_value);
void squared_lines(Configs* config, Png* image);
void rotate(Configs* config, Png* image);
void draw_line(Png* image, int left, int up, int right, int down, int thickness, Color* color, int num_color);
void set_pixel(Png* image, int y, int x, int num_color, Color* color);
int RGB_or_RGBA(Png *image);
void process_file(Configs* config, Png* image);
void rhombus(Configs* config, Png* image);
#endif 
