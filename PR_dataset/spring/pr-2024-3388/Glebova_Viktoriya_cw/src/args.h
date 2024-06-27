#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>

#include "structs.h"
#include "defines.h"
#include "utils.h"

args_t get_args(int argc, char* argv[]);
int check_for_regex(char* str, char* regex_template);
int check_color( int optional, char* color);
void check_args(args_t args);
void process_long_args(char* optarg, struct option* long_opts, int long_idx, args_t* args);