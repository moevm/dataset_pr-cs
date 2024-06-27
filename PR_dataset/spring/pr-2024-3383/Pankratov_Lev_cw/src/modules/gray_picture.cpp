#include "gray_picture.hpp"

void BmpSystem::Bmp::blackAndWhite(const char* outputPathFile, Coordinates coord)
{
    for (int32_t y = coord.leftY; y < coord.rightY && y < infoHeader->height; y++)
    {
        for (int32_t x = coord.leftX; x < coord.rightX && x < infoHeader->width; x++)
        {
            uint8_t gray = round(dataPixels[infoHeader->height - y - 1][x].rgbRed * 0.299 + dataPixels[infoHeader->height - y - 1][x].rgbGreen * 0.587 + dataPixels[infoHeader->height - y - 1][x].rgbBlue * 0.114);
            BmpSystem::Rgb color = {gray, gray, gray};
            setPixel(x, y, color);
        }
    }

    writeBmp(outputPathFile);
}