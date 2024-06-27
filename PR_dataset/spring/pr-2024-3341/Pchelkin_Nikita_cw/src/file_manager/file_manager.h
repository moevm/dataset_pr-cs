#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "struct.h"
#include "help.h"

#define PNG_DEBUG 3

char* find_input_file(int argc, char* argv[]);
void read_png_file(char* file_name, Png* image);
void write_png_file(char *file_name, Png* image);