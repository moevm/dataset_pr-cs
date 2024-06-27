#pragma once

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <png.h>

#include "help.h"
#include "struct.h"

#define BLANK_STRING "\0"
#define MAX_STRING 256

void get_points(char* string, int* x1, int* y1, int* x2, int* y2, int* x3, int* y3, regmatch_t groupArray[]);
int get_color(char* string, int buffer[3], regmatch_t groupArray[]);
int point_is_in(Png* image, int x, int y);
void set_pixel(Png* image, int x, int y, int color[3]);
void draw_thin_line(Png* image, int x1, int y1, int x2, int y2, int color[3]);
void draw_line(Png* image, int x1, int y1, int x2, int y2, int color[3], int thickness);
Png* create_new_image(Png* image, int width, int height);
int is_in_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
void draw_triangle(Png* image, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int color[3], int fill, int fill_color[3]);
int check_color(Png* image, int x, int y, int color[3]);
int* find_biggest_rect(Png* image, int color[3]);
void recolor_biggest_rect(Png* image, int old_color[3], int new_color[3]);
void make_collage(Png* image, int number_x, int number_y);
void image_processing(int argc, char* argv[], Png* image, char** output_file, char* input_file);