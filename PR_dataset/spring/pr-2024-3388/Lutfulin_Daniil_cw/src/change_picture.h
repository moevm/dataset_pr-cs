#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "help_functions.h"

void get_right_coords(pixels_t *pixels, point_t* left_up, point_t* right_down);
void mirror_field(pixels_t* pixels, point_t left_up, point_t right_down, char axis);
rgb_t** get_copy_arr(rgb_t **source, point_t left_up, int copy_height, int copy_width);
void copy_field(pixels_t *pixels, point_t left_up, point_t right_down, point_t dest_left_up);

void draw_horisontal_strip(pixels_t *pixels, int y, int x, size_t thickness, rgb_t color);
void draw_vertical_strip(pixels_t *pixels, int y, int x, size_t thickness, rgb_t color);
void draw_horisontal_line(pixels_t *pixels, int y, int x_start, int x_end, size_t thickness, rgb_t color);
void draw_vertical_line(pixels_t *pixels, int y_start, int y_end, int x, size_t thickness, rgb_t color);
void split_image(pixels_t *pixels, size_t number_x, size_t number_y, size_t thickness, rgb_t color);

void replace_color(pixels_t* pixels, rgb_t old_color, rgb_t new_color);
void binarization(pixels_t *pixels, int treshold);
void make_ornament(pixels_t *pixels, rgb_t color, int thickness, bmp_info_header_t* info_header, bmp_file_header_t* file_header);
void change_picture(pixels_t *pixels, pargs_t *pargs, bmp_info_header_t* info_header, bmp_file_header_t* file_header);