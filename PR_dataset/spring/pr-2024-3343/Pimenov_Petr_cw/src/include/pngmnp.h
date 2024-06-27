#ifndef PNGMNP_H
#define PNGMNP_H

#include "pngdata.h"

int is_on_canvas(canvas_t* canvas, int x, int y);
int set_pixel(canvas_t* canvas, color_t* color, int x, int y);
color_t* get_pixel(canvas_t* canvas, int x, int y);
canvas_t* copy(canvas_t* canvas, int x0, int y0, int x1, int y1);
int paste(canvas_t* canvas, canvas_t* pasted, color_t* void_color, int x0, int y0);
int draw_line(canvas_t* canvas, color_t* color, int x0, int y0, int x1, int y1, int thickness);
int draw_circumference(canvas_t* canvas, color_t* color, int x0, int y0, int radius, int thickness);
int draw_circle(canvas_t* canvas, color_t* color, int x0, int y0, int radius, int thickness);
int draw_rectangle(canvas_t* canvas, color_t* color, color_t* fill_color, int x0, int y0, int x1, int y1,
                   int thickness);
int split(canvas_t* canvas, color_t* color, int number_x, int number_y, int thickness);
int ornament(canvas_t* canvas, color_t* color, int function, int count, int thickness);
int rotate(canvas_t* canvas, int x0, int y0, int x1, int y1, int angle);
int outside_ornament(image_t* image, color_t* color, int thickness);

#endif