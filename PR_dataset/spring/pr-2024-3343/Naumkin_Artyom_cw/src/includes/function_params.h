#ifndef FUNCTION_PARAMS_H
#define FUNCTION_PARAMS_H

#include "pixels.h"

typedef struct {
    char* input_file;
    char* output_file;

    unsigned char inverse_circle;
    unsigned char trim;
    unsigned char triangle;
    unsigned char line;
    unsigned char fill;
    unsigned char info;
    unsigned char help;

    int thickness;
    int circle_r;

    point_t p0;
    point_t p1;
    point_t p2;

    rgb_t color;
    rgb_t fill_color;

    unsigned char circle_pixel;
    int size;
    rgb_t circle_color;
} params_t;

params_t* init_functionl_params();

params_t* parse_command_line(int argc, char* argv[]);

#endif