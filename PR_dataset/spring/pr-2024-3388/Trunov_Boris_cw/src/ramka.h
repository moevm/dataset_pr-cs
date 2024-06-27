#ifndef RAMKA_HEADER
#define RAMKA_HEADER

#include <stdlib.h>
#include "bmp.h"
#include "save_bmp.h"
#include "failure.h"

#define PADDING_BMP_SIZE 4

void draw_ramka(image_bmp * img, int thick, rgb color, char * output_file_name);

#endif
