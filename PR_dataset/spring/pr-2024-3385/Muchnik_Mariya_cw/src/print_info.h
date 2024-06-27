#pragma once

void print_file_header(BitmapFileHeader bmfh);
void print_info_header(BitmapInfoHeader bmif);
void print_info(BitmapInfoHeader* bmfh, BitmapFileHeader* bmif);