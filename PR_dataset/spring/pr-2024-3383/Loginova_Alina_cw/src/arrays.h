#ifndef CW_ARRAYS_H
#define CW_ARRAYS_H

#include "array_macros.h"
#include <png.h>
#include "image_data.h"

ArrayDecl(char)
ArrayDecl(png_bytep)
ArrayDecl(png_byte)
ArrayDecl(pixel)
ArrayDecl(Array_pixel)
ArrayDecl(pixel_point)
void pixel_columns_deleter(Array_pixel *column);

#endif
