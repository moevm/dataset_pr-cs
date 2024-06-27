#pragma once

#include <stdlib.h>
#include <png.h>

#include "structs.h"
#include "defines.h"
#include "utils.h"

png_t* read_png(params_t* params);
void write_png(png_t* img, params_t* params);