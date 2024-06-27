#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <strings.h>
#include <regex.h>
#include <ctype.h>
#include "consts.h"
#include "structs.h"
#include "validate.h"
#include "utils.h"

void panic(char* message);
char* get_optional_arg(char* arg);
func_param_args_t get_args(int argc, char *argv[]);
void process_long_options(func_param_args_t* args, int code_of_arg, char* optarg);