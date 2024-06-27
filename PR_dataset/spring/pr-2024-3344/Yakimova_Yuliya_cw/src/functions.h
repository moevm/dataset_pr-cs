#pragma once
#include "library.h"
#include "structures.h"

void no_argschecker(char* arg, char* name);
void print_png_info(struct Png *image);
void fill_rect(struct Png *image, int x1, int y1, int x2, int y2, int* rgb);
void create_border(struct Png *image, int x1, int y1, int x2, int y2, int* rgb, int thickness);
int* check_str_format(char* str, int tok_num, struct Png *image);
void replace_color(struct Png *image, char* new_color, char* old_color);
void copy_img(struct Png *image, char* left_up, char* right_down, char* dest_left_up);
void create_rect_ornam(struct Png *image, char* color, char* thickness_str, char* count_str);
void create_circle_ornam(struct Png *image, char* color);
void create_semicircle (struct Png *image, int x0, int y0, int r1, int thickness, int* rgb);
void create_semicir_ornam(struct Png *image, char* color, char* thickness_str, char* count_str);
int compare_colors(png_byte* ptr, int* color);
int** free_border_data(struct Png *image, int* color);
void trace_rects(struct Png *image, char* color_ch, char* border_color_ch, char* thickness_str);
void print_help();
void fill_circled(struct Png *image, int x1, int y1, int x2, int y2, int* rgb, int* exc_rgb);
void circle_pix(struct Png *image, char* circle_color_str, char* color_str, char* size_str);