#ifndef CWBMP_H
#define CWBMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../cwstructures/cwstructures.h"
#include "../cwerror/cwerror.h"

#define BMP_SIGNATURE 0x4D42
#define BITS_PER_PIXEL 24
#define COMPRESSION 0
#define BLUE 2
#define GREEN 1
#define RED 0


void info(const char *filename);

Bitmap_image_t *load_bmp(const char *file_name);

void save_bmp(const Bitmap_image_t *bitmap_image, const char *file_name);

void free_bmp(Bitmap_image_t *bitmap_file);

bool valid_rgb(RGB_t rgb_color);

bool valid_coordinate(Coord_t coordinate, int width, int height);

bool valid_header(const Bitmap_image_t *bitmap_image); //static

int get_padding(int width);

int get_row_size(int width);

int get_position(Coord_t coordinate, int width, int height);

RGB_t get_pixel(const Bitmap_image_t *bitmap_image, Coord_t coordinate);

void set_pixel(Bitmap_image_t *bitmap_image, Coord_t coordinate, RGB_t color);


#endif