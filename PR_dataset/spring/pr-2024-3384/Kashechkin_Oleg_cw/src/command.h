#pragma once

#include "main.h"

int rect(image *img, int start_x, int start_y, int end_x, int end_y, int width, int color[3], bool fill, int color_for_fill[3]);
int hexagon(image *img, int center_x, int center_y, int radius, int width, int color[3], bool fill, int color_for_fill[3]);
int mirror(image *img, char* axis, int start_x, int start_y, int end_x, int end_y);
int pentagram(image *img, int center_x, int center_y, int radius, int width, int color[3]);
int paving(image *img, int start_y, int start_x, int end_y, int end_x);
int outside_rect(image *img, int start_y, int start_x, int end_y, int end_x,int color[3]);