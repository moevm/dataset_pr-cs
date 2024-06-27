#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "png.h"
#include "utils.h"
#include "consts.h"
#include "structs.h"

png_t* process_img(png_t* img, func_params_t* params, int* write_flag);
void draw_line(png_t* img, func_params_t* params,int first_x, int first_y, int second_x, int second_y);
void print_png_info(png_t* img);
void mirror_img(png_t* img, func_params_t* params);
void rect_img(png_t* img, func_params_t* params);
void pentagram_img(png_t* img, func_params_t* params);
double line_equation(int x, int x1, int y1, int x2, int y2);
void hexagon_img(png_t* img, func_params_t* params);
void fill_rect(png_t* img, func_params_t* params);
void circle_img(png_t* img, func_params_t* params);
png_t* process_img(png_t* img, func_params_t* params, int* write_flag);
void set_pixel(png_t* img, int x, int y, int* color);
void draw_field_circle(png_t* img,const int x0, const int y0, int radius, int* color);