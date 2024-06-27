#pragma once

Rgb** read_bmp(char* file_name, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);
void write_bmp(char* file_name, Rgb** arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif);