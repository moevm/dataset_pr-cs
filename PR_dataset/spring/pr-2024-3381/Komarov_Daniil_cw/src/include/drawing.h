#ifndef PROCESS_IMG_H
#define PROCESS_IMG_H
#include "image.h"
#include "coord_queue.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Used for scan-line fill (refer to draw_polygon())
struct edge_node {
    int64_t y_min, y_max;
    double x_val;
    double m; // (1/m)*x + b
    uint8_t active;
};

// Draw functions
void draw_polygon(Image *img, int64_t *coords, size_t vertices_count,
                  int64_t outline_thickness, Pixel color,
                  uint8_t fill, Pixel fill_color);

void draw_line(Image *img, int64_t x0_arg, int64_t x1_arg, int64_t y0_arg,
               int64_t y1_arg, int64_t thickness, Pixel color);

void draw_circle(Image *img, int64_t x0, int64_t y0,
                 int64_t r, Pixel outline_color, int64_t thickness,
                 uint8_t fill, Pixel fill_color);

void flood_fill_region(Image *img, uint32_t x_start, uint32_t y_start,
                       Pixel color);

void draw_rectangle(Image *img, int64_t x0, int64_t y0, int64_t x1,
                    int64_t y1, Pixel color);

// Low-level functions (don't use directly)
int edge_node_cmp(const void *a_ptr, const void *b_ptr);
void interpolate_line(Image *img, double a, double b, int64_t x_start,
                      int64_t x_end, Pixel color);


#endif
