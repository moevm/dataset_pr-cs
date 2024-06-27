#ifndef PNGIO_H
#define PNGIO_H

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <png.h>


void read_png_file(char *file_name, Png *image);
void write_png_file(char *file_name, struct Png *image);

#endif
