#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"
#ifndef PRINT_FUNC_H
#define PRINT_FUNC_H

void printBMPHeaders(BMPfile* bmpf);
void printBMPPixels(BMPfile* bmp_file);
void printInfo();

#endif
