#ifndef DRAW_LINE_HEADER
#define DRAW_LINE_HEADER

#include "bmp.h"
#include "draw_filled_circle.h"
#include "set_pixel.h"
#include <math.h>
#include <stdlib.h>

void draw_line(image_bmp * image,int x_start, int y_start, int x_end, int y_end, rgb color, int thickness);

#endif
