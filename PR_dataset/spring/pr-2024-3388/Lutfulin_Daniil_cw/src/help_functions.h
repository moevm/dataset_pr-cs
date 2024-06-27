#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include "structs.h"
#include "defines.h"

#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
#define min(a, b)  (((a) < (b)) ? (a) : (b)) 

void leave(char* err_message, int error_code);
void swap_int(int* first, int* second);
void swap_rgb(rgb_t* first_pixel, rgb_t* second_pixel);
void set_pixel(pixels_t* pixels, int y, int x, rgb_t color);
void print_args(args_t args);
void print_pargs(pargs_t pargs);
void print_info_header(bmp_info_header_t info_header);
void print_file_header(bmp_file_header_t header);
void print_help();
void free_picture(pixels_t *pixels);