#include "arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ArrayDef(char)
ArrayDef(png_bytep)
ArrayDef(png_byte)
ArrayDef(pixel)
ArrayDef(Array_pixel)
ArrayDef(pixel_point)

void pixel_columns_deleter(Array_pixel *column) {
    clear_pixel_array(column);
}