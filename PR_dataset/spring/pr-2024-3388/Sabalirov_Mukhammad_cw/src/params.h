#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <regex.h>
#include <ctype.h>
#include "args.h"
#include "utils.h"
#include "consts.h"
#include "structs.h"

regmatch_t* get_args_for_regex(char* str, char* regex_template);
void set_axis(func_param_args_t args, func_params_t* params);
int get_nums_from_dot_format(char* str, int match_pos, char* regex_template);
void set_coords(func_param_args_t args, func_params_t* params);
void set_natural_num(func_param_args_t args, func_params_t* params);
void set_colors(func_param_args_t args, func_params_t* params);
func_params_t* set_and_get_func_params(func_param_args_t args);