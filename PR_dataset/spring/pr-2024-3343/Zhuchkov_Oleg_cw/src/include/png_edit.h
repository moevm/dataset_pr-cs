#ifndef pngedit
#define pngedit
#include <png.h>
#include <structs.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
rgb_t int_to_rgb(int r, int g, int b);
rgb_t png_byte_to_rgb(png_byte r, png_byte g, png_byte b);
bool check_coords(png_t* image, int x, int y);
void set_pixel(png_t* image, int x, int y, rgb_t rgb);
rgb_t get_pixel(png_t* image,int x, int y);
void copy_pixel_to(png_t* image, int x0, int y0, int x1, int y1);
rgb_t get_blurred_pixel(png_t* image, int x, int y, int size);
void blur(png_t* image, int size);
#endif