#ifndef ADD_OPERATIONS_H
#define ADD_OPERATIONS_H

#include "../include/png_objects.h"

int is_digit(char *line);

void free_png(Png *png);

void set_pixel(int x, int y, RGB color, Png *png);

RGB get_color(int x, int y, Png *png);

int get_size_pixel(Png *png);

#endif