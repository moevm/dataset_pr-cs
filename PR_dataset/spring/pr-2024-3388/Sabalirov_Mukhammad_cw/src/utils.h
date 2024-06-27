#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "consts.h"
#include "structs.h"

#define MAX(a, b) a >= b ? a : b
#define MIN(a, b) a <= b ? a : b

void panic(char* message);
void print_params(func_params_t* params);
void free_args(func_param_args_t* args);
void free_all(func_param_args_t* args, func_params_t* params, png_t* img);
