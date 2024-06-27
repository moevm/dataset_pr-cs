#ifndef READ_BMP_HEADER
#define READ_BMP_HEADER
#include "bmp.h"

#define PADDING_BMP_SIZE 4

void read_image_bmp(const char* path, image_bmp * img);

#endif
