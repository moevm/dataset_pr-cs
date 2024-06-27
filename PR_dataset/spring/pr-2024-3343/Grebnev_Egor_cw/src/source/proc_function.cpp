#include "proc_function.hpp"
#include <iostream>
BMP ornament(BMP image, int thickness, const RGB& color)
{
    BMP new_image(image);
    new_image.initialize(image.header.width + thickness * 2, image.header.height + thickness * 2);

    for (int32_t y = 0; y < new_image.header.height; y++)
    {
        for (int32_t x = 0; x < new_image.header.width; x++) { new_image.set_color(x,  y, color); }
    }

    for (int32_t y = 0; y < image.header.height; y++)
    {
        for (int32_t x = 0; x < image.header.width; x++) { new_image.set_color(thickness + x, thickness + y, image.get_color(x, y)); }
    }

    return new_image;
}