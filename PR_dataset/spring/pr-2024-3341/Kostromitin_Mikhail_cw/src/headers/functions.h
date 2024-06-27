#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include "utils.h"
#include "readwrite.h"


void parse_CLI(Rgb*** arr, BitmapFileHeader* file_header, BitmapInfoHeader* file_info, int argc, char* argv[]);
void color_replace(Rgb** arr, int H, int W, Rgb old_color, Rgb new_color);
void color_change(Rgb* dest, Rgb src);
void rgb_filter(Rgb** arr, int H, int W, char component[], int value);
void draw_line(Rgb** arr, int H, int W, int x0, int x1, int y0, int y1, Rgb color);
void split(Rgb** arr, int horizontal, int vertical, int H, int W, int thickness, Rgb color);
void gamma_func(Rgb** arr, int H, int W, float gamma_value);
