#ifndef CW_ROTATE_H
#define CW_ROTATE_H

#include <png.h>
#include "image_data.h"
png_bytepp rotate(long left_up_x, long left_up_y, long right_down_x, long right_down_y, long angle, image_data image);

#endif
