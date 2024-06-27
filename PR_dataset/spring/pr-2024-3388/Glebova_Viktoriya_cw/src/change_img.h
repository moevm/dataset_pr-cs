#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>
#include <png.h>

#include "utils.h"
#include "defines.h"
#include "structs.h"

void set_pixel(png_t* img, int x, int y, rgb_t color);
void draw_line(png_t* img, params_t* params, int start_x, int start_y, int end_x, int end_y);
void draw_circle(png_t* img, params_t* params);
void do_split(png_t* img, params_t* params);
void do_rgb_filter(png_t* img, params_t* params);
void draw_circle(png_t* img, params_t* params);
void draw_field_circle(png_t* img, int center_x, int center_y, int radius, rgb_t color);
void draw_accurate_filed_circle(png_t* img, params_t* params, int center_x, int center_y, int radius);
void change_img(png_t* img, params_t* params);
void set_pixels_for_circle(png_t* img, int center_x, int center_y, int delta_x, int delta_y, rgb_t color);
void set_pixels_for_thickness_circle(png_t* img, int center_x, int center_y, int x, int y, int thickness, rgb_t color);