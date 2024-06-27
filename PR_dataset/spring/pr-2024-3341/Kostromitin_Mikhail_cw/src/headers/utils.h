#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"


int check_if_bmp(BitmapFileHeader* bmfh);
int color_cmp(Rgb f, Rgb s);
int color_validator(Rgb color);
int coord_validator(int max, int coord0, int coord1);
unsigned int padding(unsigned int w);
unsigned int row_len(unsigned int w);
Rgb parse_color(char color_string[]);
void help();
void info(BitmapInfoHeader info_header, BitmapFileHeader file_header);
void print_file_header(BitmapFileHeader header);
void print_info_header(BitmapInfoHeader header);