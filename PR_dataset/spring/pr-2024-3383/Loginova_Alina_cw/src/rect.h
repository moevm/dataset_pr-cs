#ifndef CW_RECT_H
#define CW_RECT_H
#include <png.h>
#include "image_data.h"

png_bytepp rect(long left_up_x, long left_up_y, long right_down_x, long right_down_y, long int_thickness, pixel RGB,
                char* fill, pixel RGB_f, image_data image, _Bool ornament);

#endif
