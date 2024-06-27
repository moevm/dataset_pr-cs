#ifndef BMPFUNC_H
#define BMPFUNC_H

#include "structurs.h"

void print_imageinfo(BitmapInfoHeader bmih, BitmapFileHeader bmfh);

void read_bmp(char file_name[], Image *img);

void write_bmp(char file_name[],Image img);

#endif