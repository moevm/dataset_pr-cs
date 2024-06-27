#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "structs.h"
#include "defines.h"
#include "utils.h"

int check_for_regex(char* str, char* regex_template);
int check_natural_nums(args_t args);
int check_coordinates(args_t args);
int check_colors(args_t args);
int check_args(args_t args);