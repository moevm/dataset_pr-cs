#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <regex.h>
#include <ctype.h>
#include "png.h"
#include "utils.h"
#include "consts.h"
#include "structs.h"

png_t* read_png_file(func_params_t* params);
void write_png_file(png_t* img, func_params_t* params);