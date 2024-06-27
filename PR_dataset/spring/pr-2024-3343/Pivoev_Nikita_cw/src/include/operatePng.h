#ifndef OPERATEPNG_H
#define OPERATEPNG_H

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <png.h>

void read_png_file(char *file_name, Png *image);
void write_png_file(char *file_name, Png *image);
void setColor(png_byte* ptr, RGB color);

void copyArea(Png* image, OptParams* opt);
void replaceColor(Png *image, OptParams* opt);
void createOrnament(Png* image, OptParams* opt);
void fillRects(Png* image, OptParams* opt);
void fillOutside(Png* image, OptParams* opt);

#endif