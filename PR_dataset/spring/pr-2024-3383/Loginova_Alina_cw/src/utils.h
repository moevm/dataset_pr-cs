#ifndef CW_PR_2024_UTILS_H
#define CW_PR_2024_UTILS_H
#include <png.h>
#include "arrays.h"
#include <math.h>

long abs_negative(long value);
Array_Array_pixel get_columns_raw(image_data image, long loc_width, long loc_height, long init_x, long init_y, _Bool cut, _Bool clockwise);
Array_Array_pixel get_columns(Array_Array_pixel rows, long init_x, long init_y, _Bool cut, _Bool clockwise);
long clamp_positive(long value);
long min(long a, long b);
pixel parse_color(char *color);
long round_num(double num);
void color_row(pixel* row, pixel RGB, long stop, long width);

#endif
