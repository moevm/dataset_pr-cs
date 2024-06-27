//
// Created by zoomie on 5/22/24.
//

#ifndef PR_TILES_H
#define PR_TILES_H
#include <png.h>
#include "image_data.h"

png_bytepp tiles(image_data image, long left_up_x, long left_up_y, long right_down_x, long right_down_y);
#endif //PR_TILES_H
