#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "structs.h"

void panic(char* message);
void print_img_info(png_t* img);
void free_args(args_t* args);
void free_img(png_t* img);