#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <regex.h>
#include <ctype.h>
#include "consts.h"
#include "structs.h"
#include "utils.h"

int validate_for_regex(char* str, char* regex_template);
int validate_axis_arg(func_param_args_t params);
int validate_coords_arg(func_param_args_t params);
int validate_natural_num_arg(func_param_args_t params);
int validate_color_arg(func_param_args_t params);
void validate_func_param_args(func_param_args_t params);