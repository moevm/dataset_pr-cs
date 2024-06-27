#ifndef PNGIO_H
#define PNGIO_H

#include "pngdata.h"

int read_png_file(char* path, image_t* image);
int write_png_file(char* path, image_t* image);

#endif