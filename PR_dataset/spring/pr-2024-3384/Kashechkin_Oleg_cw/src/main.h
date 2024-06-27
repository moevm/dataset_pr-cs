#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <png.h>
#include <ctype.h>
#include <math.h>

#define PI 3.1415926
#define coordinates_error "Invalid coordinates\n"
#define axis_error "Wrong axis\n"
#define coordinates_center_error "Invalid center coordinates\n"
#define radius_error "Invalid radius\n"
#define width_error "Invalid thickness\n"
#define color_error "Invalid color\n"
#define input_file_error "Failed to open input file: invalid file\n"
#define deepth "Failed to open file: RGB-color deepth was exceeded\n"
#define is_PNG "Not a PNG file\n"
#define drop_file "Error file\n"
#define drop_struct "Error struct\n"
#define outside_hexagon "Hexagon is partially or fully outside the image boundaries. Clipping the hexagon.\n"
#define outside_pentagram "Pentagram is partially or fully outside the image boundaries. Clipping the pentagram.\n"

typedef struct
{
    int start[2];
    int end[2];
    char axis[1];
    int center[2];
    int radius;
    int width;
    int color[3];
    bool fill;
    int color_for_fill[3];
} args;

typedef struct
{
    char *path;
    int width, height;
    int color_type;
    int bit_depth;
    png_bytep *data;
} image;

#include "utils.h"
#include "command.h"
#include "image.h"

int main(int argc, char **argv);
int trigger_option(image *img, args argum, int flag);
int process_option(char opt, char *optarg, char **parts, args *argum, int *flag, char **output_file, char **input_file);
void NewFunction();
void print_help();