#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "structs.h"
#include "defines.h"
#include "utils.h"

regmatch_t* get_capture_groups(char* str, char* regex_template);
int* get_nums_from_regex(char* str, int count, char* regex_template);
void set_points(args_t args, params_t* params);
void set_triangle_color(args_t args, params_t* params);
void set_rect_colors(args_t args, params_t* params);
params_t get_params(args_t args);