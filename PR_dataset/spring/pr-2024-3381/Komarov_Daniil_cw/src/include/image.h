#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdint.h>
#include "errors.h"
#include "set.h"

#pragma pack(push, 1)
typedef struct PngPixel_struct {
        uint16_t r;
        uint16_t g;
        uint16_t b;
        uint16_t a;
} Pixel;
#pragma pack(pop)

typedef struct Image_struct {
        Pixel **arr;
        uint32_t width;
        uint32_t height;
} Image;

void image_create(Image **img, uint32_t width, uint32_t height,
                  Pixel *color, int *status_code);

void image_paste(Image **dest, Image *src, uint32_t pos_x,
                 uint32_t pos_y);

void image_destroy(Image *img);

void image_find_largest_rect(Image *img, uint32_t *x0, uint32_t *y0,
                             uint32_t *x1, uint32_t *y1, Pixel color, 
                             int *status_code);

#endif
