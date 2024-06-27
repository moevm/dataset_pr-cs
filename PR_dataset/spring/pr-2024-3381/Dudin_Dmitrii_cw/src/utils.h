#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "structs.h"

#define MAX(a, b) a >= b ? a : b
#define MIN(a, b) a <= b ? a : b

void panic(char* message);
void print_file_header(bmp_file_header_t header);
void print_info_header(bmp_info_header_t header);
void free_args(args_t* args);
void free_image(img_t* image);