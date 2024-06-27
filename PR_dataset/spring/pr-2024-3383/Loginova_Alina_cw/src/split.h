#ifndef CW_SPLIT_H
#define CW_SPLIT_H

#include <png.h>
#include "image_data.h"
png_bytepp split(long x, long y, pixel RGB, long thickness, image_data image);

#endif
