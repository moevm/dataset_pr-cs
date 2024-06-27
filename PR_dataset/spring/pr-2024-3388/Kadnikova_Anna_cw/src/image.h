#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include <png.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"


#define SET_ERROR_FLAG(cond, flag_value) if (cond) {img->error_flag = flag_value; return img;}


typedef struct {
    uint32_t width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;

    png_struct* data;
    png_info* info;
    png_byte** rows;

    uint8_t error_flag;
} Image;


Image* img_from_file(FILE* fstream);

Image* img_from_data(png_byte** buffer,
                     uint32_t width,
                     uint32_t height,
                     png_byte channels);

Image* img_to_file(Image* img, FILE* fstream);

uint32_t get_pixel(Image* img, int64_t x, int64_t y);

void set_pixel(Image* img,
               int64_t x,
               int64_t y,
               uint32_t color);

uint32_t rgb_to_rgba(uint8_t r, uint8_t g, uint8_t b);

Image* draw_circle(Image* input,
                   uint32_t color,
                   int64_t center_x,
                   int64_t center_y,
                   int32_t thickness,
                   int32_t radius,
                   bool fill,
                   uint32_t fill_color);

Image* color_replace(Image* input, uint32_t mask, uint32_t new);

Image* component_set(Image* input, char* cname, uint16_t cvalue);

Image* draw_field_circle(Image* input, int64_t x0, int64_t y0, uint32_t radius, uint32_t color);

Image* draw_line(Image* input,
                 uint32_t color,
                 uint16_t thickness,
                 int64_t x1,
                 int64_t y1,
                 int64_t x2,
                 int64_t y2);

Image* draw_split(Image* input,
                  uint16_t count_x,
                  uint16_t count_y,
                  uint16_t thickness,
                  uint32_t color);

Image* draw_rectangle(Image* input,
                      int64_t left,
                      int64_t up,
                      int64_t width,
                      int64_t height,
                      uint32_t color,
                      uint16_t thickness,
                      bool fill,
                      uint32_t fill_color);

Image* draw_square(Image* input,
                   int64_t left,
                   int64_t up,
                   int64_t side,
                   uint32_t color,
                   uint16_t thickness,
                   bool fill,
                   uint32_t fill_color);

Image* draw_rhombus(Image* input,
                    uint32_t color);

#endif /* IMAGE_H */
