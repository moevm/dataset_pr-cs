#include "../include/functions.h"

Pixel get_pixel(PICInfo& info, int row, int column){
    int bytesPerPixel = info.header.BitCount / 8;
    int bytesPerRow = (bytesPerPixel * info.header.Width + 3) & ~3;
    int index = ((info.header.Height - 1 - row) * bytesPerRow) + (column * bytesPerPixel);
    return Pixel{&(info.pixels.at(index + 2)), &(info.pixels.at(index + 1)), &(info.pixels.at(index))};
}
