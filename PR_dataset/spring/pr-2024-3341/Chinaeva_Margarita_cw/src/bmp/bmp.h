#pragma once

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

void check_bmp(const char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif);
Rgb** read_bmp(const char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);
void write_bmp(const char new_file[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr);
