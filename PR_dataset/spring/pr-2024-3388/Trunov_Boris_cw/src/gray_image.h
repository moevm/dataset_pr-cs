#ifndef GRAY_IMAGE_HEADER
#define GRAY_IMAGE_HEADER

#include "bmp.h"
#include <math.h>
#include <stdlib.h>
#include "set_pixel.h"

#define COEFF_RED 0.299
#define COEFF_GREEN 0.587
#define COEFF_BLUE 0.114

void gray_image(image_bmp * img, int x_start, int y_start, int x_end, int y_end);

#endif
