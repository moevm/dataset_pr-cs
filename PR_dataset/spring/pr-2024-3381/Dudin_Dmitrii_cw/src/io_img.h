#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "defines.h"
#include "utils.h"

img_t* read_img(params_t* params);
void write_img(img_t* img, params_t* params);