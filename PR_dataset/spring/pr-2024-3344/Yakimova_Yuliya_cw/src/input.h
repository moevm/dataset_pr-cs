#pragma once
#include "library.h"
#include "structures.h"

void read_png_file(char *file_name, struct Png *image);
void write_png_file(char *file_name, struct Png *image);
void free_image_data(struct Png *image);
