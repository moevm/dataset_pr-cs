#pragma once

#include "input_output.h"
#include "toolkit.h"

void print_help();
void change_color(Image* image, Rgb old_color, Rgb new_color);
void blur_image(Image* image, int size);
void find_and_border_rectangle(Image* image, int thickness, Rgb color, Rgb border_color);
void rectangle_ornament(Image* image, int ornament_count, Rgb color_values, int thickness);
void circle_ornament(Image* image, Rgb color_values);
void semicircles_ornament(Image* image, int thickness, int ornament_count, Rgb color);
