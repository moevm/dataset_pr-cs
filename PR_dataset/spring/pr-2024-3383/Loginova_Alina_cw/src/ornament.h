#ifndef CW_ORNAMENT_H
#define CW_ORNAMENT_H

#include <png.h>
#include "image_data.h"
png_bytepp ornament(char *pattern, long count, pixel RGB, long thickness, image_data image);
png_bytepp print_circle(long center_x, long center_y, long radius, long thickness, pixel color, image_data image);
#endif
