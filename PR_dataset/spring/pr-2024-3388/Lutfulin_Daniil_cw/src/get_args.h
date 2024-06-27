#pragma once

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "defines.h"
#include "structs.h"
#include "help_functions.h"

args_t get_args(int argc, char **argv);
point_t get_coords_from_string(char* coords_arg);
rgb_t get_color_from_string(char* color_arg);
int get_int_from_string(char* num_string);
void check_args(args_t input_args);
pargs_t process_arguments(args_t input_args);