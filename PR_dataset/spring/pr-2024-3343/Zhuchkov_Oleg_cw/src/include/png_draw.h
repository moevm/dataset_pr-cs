#ifndef draw
#define draw
#include <structs.h>
#include <png.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <png_edit.h>
#include <structs.h>
void draw_line(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb, int thickness);
void fill_circle(png_t* image, int x0, int y0, rgb_t rgb, int radius);
void draw_circle(png_t* image, int x0, int y0, rgb_t rgb, int radius);
void draw_rectangle(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb, int thickness, bool fill, rgb_t fillrgb);
void fill_rectangle(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb);
void draw_hexagon(png_t* image, int x0, int y0, rgb_t rgb, int radius, int thickness, bool fill, rgb_t rgbfill);
void fill_hexagon(png_t* image, int x0, int y0, rgb_t rgb, int radius);
void copy_area_to(png_t* image, int x0, int y0, int x1, int y1, int x2, int y2);
#endif