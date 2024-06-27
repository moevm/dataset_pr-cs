#ifndef TASKS_H
#define TASKS_H

#include "pngfile.h"
#include "image.h"
#include "drawing.h"
#include "errors.h"


int task_print_file_info(char *path);

int task_draw_triangle(char *input, char *output, int64_t *coords,
                       uint32_t thickness, Pixel color, uint8_t fill,
                       Pixel fill_color, uint8_t compression_level);

int task_create_collage(char *input, char *output, uint32_t number_x,
                        uint32_t number_y, uint8_t compression_level);

int task_rect_search(char *input, char *output, Pixel old_color,
                     Pixel new_color, uint8_t compression_level);

int task_draw_line(char *input, char *output, int64_t *coords,
                   uint32_t thickness, Pixel color,
                   uint8_t compression_level);

int task_draw_outside_ornament(char *input, char *output,
                   uint32_t thickness, Pixel color,
                   uint8_t compression_level);

#endif
