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

void copy_pixel(Image* source, png_byte** dest_rows,
                int64_t src_x, int64_t src_y,
                int64_t dest_x, int64_t dest_y);

Image* copy_area(Image* input,
                 int64_t source_up_x, int64_t source_up_y,
                 int64_t source_down_x, int64_t source_down_y,
                 int64_t destination_up_x, int64_t destination_up_y);

uint32_t get_pixel(Image* img, int64_t x, int64_t y);

void set_pixel(Image* img,
               int64_t x,
               int64_t y,
               uint32_t color);

uint32_t rgb_to_rgba(uint8_t r, uint8_t g, uint8_t b);

Image* color_replace(Image* input, uint32_t old, uint32_t new);

Image* border_rectangle(Image* input,
                        uint32_t color,
                        uint16_t thickness,
                        uint16_t index);

Image* border_circle(Image* input,
                     uint32_t color);

Image* draw_circle(Image* input,
                   uint32_t color,
                   int64_t center_x,
                   int64_t center_y,
                   uint32_t thickness,
                   uint32_t radius);

Image* border_semicircles(Image* input,
                          uint32_t color,
                          uint16_t thickness,
                          uint16_t count);

Image* make_border(Image* input,
                   char* pattern,
                   uint32_t color,
                   uint16_t thickness,
                   uint16_t count);

bool find_rectangle(Image* input,
                    uint32_t color,
                    int64_t left,
                    int64_t up,
                    int64_t width,
                    int64_t height);

Image* draw_rectangle(Image* input,
                      uint32_t color,
                      int64_t left,
                      int64_t up,
                      int64_t width,
                      int64_t height,
                      uint32_t thickness);

void set_box_mark(bool** buffer,
                  int64_t left,
                  int64_t up,
                  int64_t width,
                  int64_t height);

Image* frame_rectangles(Image* input,
                        uint32_t color,
                        uint32_t border_color,
                        uint16_t thickness);

Image* outline_image(Image* input,
                     uint32_t color,
                     uint16_t thickness);

#endif /* IMAGE_H */
