#pragma once

#include "main.h"

void set_pixel(image *img, int x, int y, int color[3]);
int check_colors(char** parts);
bool is_png_file(const char *path);
char** split_string(char* str);
int is_num(char *n);
bool has_dot(char* str);
void sort(int arr[], int n);
int draw_line(image *img, int x00, int y00, int x11, int y11, int color[3], int width);
void draw_circle(image *img, int center_x, int center_y, int radius, int color[3]);
int compare_colors(int color1[3], int color2[3]);
void get_pixel(image *img, int x, int y, int color[3]);
void flood_fill(image *img, int x, int y, int fill_color[3], int boundary_color[3]);
int draw_line2(image *img, int x00, int y00, int x11, int y11, int color[3], int width);