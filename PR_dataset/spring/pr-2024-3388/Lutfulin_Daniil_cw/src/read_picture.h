#pragma once

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "defines.h"
#include "help_functions.h"

pixels_t* read_bmp_file(char file_name[], bmp_file_header_t* file_header, bmp_info_header_t* info_header);
void write_bmp_file(char file_name[], rgb_t** pixel_array, bmp_file_header_t* file_header, bmp_info_header_t* info_header);