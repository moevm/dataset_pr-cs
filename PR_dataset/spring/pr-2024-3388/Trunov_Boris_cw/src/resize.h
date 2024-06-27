#ifndef RESIZE_IMAGE_HEADER
#define RESIZE_IMAGE_HEADER

#include <stdlib.h>
#include "bmp.h"
#include "save_bmp.h"
#include "failure.h"

void resize(image_bmp * image, int left, int right, int up, int down, char * output_file_name, rgb color);

#endif
