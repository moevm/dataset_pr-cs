#ifndef INPUT_H
#define INPUT_H

#include "structs.h"

void print_usage();

bool is_integer(const string &str);

Rgb create_Rgb(int b_in, int g_in, int r_in);

Config get_config(int argc, char *argv[]);

#endif