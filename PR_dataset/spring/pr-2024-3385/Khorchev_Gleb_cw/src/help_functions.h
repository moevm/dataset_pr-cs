#pragma once

#include "bmp_structs.h"

void free_memory(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels);

void error(const char* message, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb** pixels);

void short_error(const char* message);

void print_help();

void print_file_header(BitmapFileHeader header);

void print_info_header(BitmapInfoHeader header);

void print_info(BitmapFileHeader* bmfh, BitmapInfoHeader* bmfi);

int check_digit(char* string);