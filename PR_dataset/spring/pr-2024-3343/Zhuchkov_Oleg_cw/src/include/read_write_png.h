#ifndef read_write
#define read_write
#include <png.h>
#include <structs.h>
#include <stdlib.h>
#include <stdio.h>


void read_png(char* file_name, png_t* image);
void write_png(char* file_name, png_t* image);
#endif