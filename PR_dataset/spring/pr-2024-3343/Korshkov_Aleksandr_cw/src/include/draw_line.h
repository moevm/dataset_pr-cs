#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include "../include/png_objects.h"
#include "../include/add_operations.h"

void draw_line(int x0, int y0, int x1, int y1, int thickness, RGB color, Png *png);

int check_line(info_line *line);

void set_start_cords(char *xy, info_line *line);

void set_end_cords(char *xy, info_line *line);

void set_color_line(char *rgb, info_line *line);

void set_thickness_line(char *thickness, info_line *line);

void draw_circle(int x0, int y0, int radius, int thickness, RGB color, Png *png);

void draw_fill_circle(int x0, int y0, int radius, RGB color, Png *png);

void set_square(int x0, int y0, int size, RGB color, Png *png);

#endif