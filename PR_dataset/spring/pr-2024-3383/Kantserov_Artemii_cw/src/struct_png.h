#ifndef CW_START_STRUCT_PNG_H
#define CW_START_STRUCT_PNG_H

#include <png.h>
//#include "/opt/homebrew/include/png.h"

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

#endif //CW_START_STRUCT_PNG_H
