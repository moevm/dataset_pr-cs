#pragma once

void freeMemory(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb **arr);
void print_error(char* message, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb **arr);