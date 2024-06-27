#pragma once

#include <math.h>
#include "args_parsing.h"

#define PX_SIZE 3
#define RED 0
#define GREEN 1
#define BLUE 2

void set_color(Png *image, int x, int y, RGB color);
RGB get_color(Png *image, int x, int y);
int max(int a, int b);
int min(int a, int b);
void change_coords(COORD* left_up, COORD* right_down);
int check_in_pic(Png* image, int x, int y);
int valid_circle(int radius, int thickness, bool fill_flag, RGB* color, bool fill, int circle);
int check_on_circle_line(int x, int y, int x0, int y0, int radius, int thickness);
void draw_circle(Png* image, COORD center_coords, int radius, int thickness, int fill_flag, RGB color, RGB fill_color);
void swap(Png* image, int x1, int y1, int x2, int y2);
void set_area(int height, int width, COORD* left_up, COORD* right_down);
void mirror_x(Png* image, COORD left_up, COORD right_down);
void mirror_y(Png* image, COORD left_up, COORD right_down);
void copy_pic(Png* image, COORD left_up, COORD right_down, COORD dest_left_up);
void contrast(Png* image, float alpha, int beta);
void info(Png* image);
void choose_func(Png image, int flag, OPTS* options);