#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "data_types.h"

PICInfo read(const string& file_name);
Pixel get_pixel(PICInfo& info, int row, int column);
void write(PICInfo& info, const string& file_name);
void color_replace(PICInfo& info, int* old_colors, int* new_colors);
void ornament(PICInfo& info, string& type, int* colors, int thickness, int count);
void find_rectangle(PICInfo& info, int* rect_color, int thickness, int* border_color);
void cli_parse(int argc, char* argv[]);
void print_info(PICInfo& info, const string& file_name);
void hsv(PICInfo& info);

#endif
