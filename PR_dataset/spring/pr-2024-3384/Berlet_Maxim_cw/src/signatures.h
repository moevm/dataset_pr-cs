#ifndef SIGNATURES_H
#define SIGNATURES_H
#include "structs.h"

bool check_colors(color_t color);
bool check_if_png(const char* file_name);
void read_png_file(const char* file_name, png_t* image);
bool check_if_rgb(png_t* image);
void write_png_file (const char* file_name, png_t* image);
bool check_coords(png_t* image, ipoint_t point);
void set_pixel(png_t* image, ipoint_t point, color_t color);
void draw_line(png_t* image, ipoint_t point1, ipoint_t point2, color_t color);
void draw_smooth_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t color, int thickness);
void draw_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t border_color, color_t fill_color, int thickness);
void flood_fill(png_t* image, ipoint_t point, color_t fill_color, color_t borders_color);
void draw_filled_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t border_color, color_t fill_color, int thickness);
void draw_circle(png_t* image, ipoint_t center, int radius, color_t color);
void draw_thick_line(png_t* image, ipoint_t point1, ipoint_t point2, color_t color, int thickness);
color_t get_pixel(png_t* image, ipoint_t point);
bool color_cmp (color_t c1, color_t c2);
void draw_filled_hexagon(png_t* image, ipoint_t center, float radius, color_t border_color, color_t fill_color, int thickness);
void draw_hexagon(png_t* image, ipoint_t center, float radius, color_t color, int thickness);
void put_pixel_arr(png_t* image, ipoint_t left_up, ipoint_t right_down, color_t** pix_arr);
void copy(png_t* image, ipoint_t left_up, ipoint_t right_down, ipoint_t dest);

#endif