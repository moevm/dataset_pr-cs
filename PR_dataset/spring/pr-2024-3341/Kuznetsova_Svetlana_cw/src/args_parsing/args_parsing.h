#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include <math.h>
#include <stdbool.h>

#include "structs.h"

#define Too_many_args 40
#define Invalid_file 41
#define Error_read_png 42
#define Error_write_png 43
#define Error_args 44
#define Invalid_flag 45

OPTS init_options();
bool is_correct_component(int val);
int count_dots(char* arg);
void are_coordinates(char *arg, COORD* coords);
int to_number(char* arg);
void to_color(char* arg, RGB* color);
bool is_axis(char* arg);
bool invalid_file(char* path_i, char* path_o);
void help();
void args_parsing(int argc, char** argv, char* path_i, char* path_o, OPTS* options, int* flag);