#ifndef PNGFILL_H
#define PNGFILL_H

#include "pngdata.h"

int fill_canvas(canvas_t* canvas, color_t* color);
int fill(canvas_t* canvas, color_t* color, color_t* border_color, int x, int y);

#endif