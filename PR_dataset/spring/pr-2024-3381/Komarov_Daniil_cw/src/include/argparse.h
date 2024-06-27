#ifndef ARGPARSE_H
#define ARGPARSE_H
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <regex.h>
#include "argdict.h"
#include "image.h"
#include "errors.h"

int argparse_parse(int argc, char **argv, ArgDict **argdict_ptr,
                   enum Mode *mode_ptr);

void argparse_show_help();

int argparse_mode_triangle(ArgDict *argdict, int64_t *coords_ptr,
                           uint32_t *thickness_ptr, Pixel *color_ptr,
                           uint8_t *fill_ptr, Pixel *fill_color_ptr);

int argparse_mode_collage(ArgDict *argdict, uint32_t *number_x,
                          uint32_t *number_y);

int argparse_mode_line(ArgDict *argdict, int64_t *coords_ptr,
                       uint32_t *thickness_ptr, Pixel *color_ptr);

int argparse_mode_ornament(ArgDict *argdict, uint32_t *thickness_ptr,
                           Pixel *color_ptr);

int argparse_mode_rect(ArgDict *argdict, Pixel *old_color, Pixel *new_color);

int argparse_point_coords(char *s, int64_t *coords);

int argparse_triangle_coords(char *s, int64_t *coords_ptr);

int argparse_pos_int(char *s, uint32_t *pos_int);

int argparse_int(char *s, int64_t *pos_int);

int argparse_color(char *s, Pixel *color);

#endif
