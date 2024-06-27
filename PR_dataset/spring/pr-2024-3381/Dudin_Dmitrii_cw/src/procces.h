#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "structs.h"
#include "defines.h"
#include "io_img.h"

int color_cmp(rgb_t first, rgb_t second);
void paint_biggest_rect(img_t *img, params_t* params);
void edit_image(img_t *img, params_t* params);
void set_pixel(img_t* img, int x, int y, rgb_t color);
void draw_field_circle(img_t* img, int x0, int y0, int radius, rgb_t color);
void draw_line(img_t* img, rgb_t color, int thickness, int first_x, int first_y, int second_x, int second_y);
void paint_triangle(img_t* img, params_t* params);
void make_collage(img_t* img, params_t* params);
