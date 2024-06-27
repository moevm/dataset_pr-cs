#pragma once

#include "input_output.h"
#include "toolkit.h"

void print_help();
void change_color(Image* image, Rgb old_color, Rgb new_color);
void apply_rgb_filter(Image *image, int component, int value);
void set_circle_pixels(Image *image, int x_center, int y_center, int x, int y, Rgb color);
void set_circle_dot_pixels(Image *image, int x_center, int y_center, Rgb color);
void set_circle_two_dot_pixels(Image *image, int x_center, int y_center, Rgb color);
void draw_field_circle(Image* input, int x_center, int y_center, int radius, Rgb color);
void draw_line(Image* input,
               Rgb color,
               int thickness,
               int x_start,
               int y_start,
               int x_end,
               int y_end);
void draw_rectangle(Image* input,
                    int left,
                    int up,
                    int width,
                    int height,
                    Rgb color,
                    int thickness,
                    int fill,
                    Rgb fill_color);
void draw_split(Image* input,
                  int count_x,
                  int count_y,
                  int thickness,
                  Rgb color);
void draw_circle_pixel(Image* input,
                   int x,
                   int y,
                   int size,
                   Rgb color,
                   Rgb circle_color);
void draw_circle_pixels(Image* input,
                   int size,
                   Rgb color,
                   Rgb circle_color);
