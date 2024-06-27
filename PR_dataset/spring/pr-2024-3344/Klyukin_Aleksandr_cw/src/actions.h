#ifndef COURSE_WORK_DRAWING_LINE_FUNCTIONS_H
#define COURSE_WORK_DRAWING_LINE_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void draw_circle(Rgb **arr, int H, int W, int dot_x, int dot_y, int thickness, int* color);

Rgb **def_task(Rgb **arr, float alpha, int beta, int H, int W);
Rgb **change_red_chanel(Rgb **arr, int H, int W, int r);
Rgb **change_green_chanel(Rgb **arr, int H, int W, int g);
Rgb **change_blue_chanel(Rgb **arr, int H, int W, int b);
void swap_int(int *a, int *b);
void draw_line(Rgb **arr, int H, int W, int x0, int y0, int x1, int y1, int thickness, int *color, int flag);
void fill_sq(Rgb **arr, int start_x, int start_y, int lenght_line, int *colors, int H, int W);
void draw_diags(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int thickness, int *color);
void draw_sq(Rgb **arr, int start_x, int start_y, int lenght_line, int H, int W, int thickness, int *color, int fill, int *fill_color, int thick);
Rgb** turned_copy(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int angle);
void replace_part(Rgb **arr, Rgb **arr_t, int start_x, int start_y, int end_x, int end_y, int H, int W);
void turn(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int angle);

#endif //COURSE_WORK_DRAWING_LINE_FUNCTIONS_H
