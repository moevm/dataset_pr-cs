#include "inverse.hpp"


void BmpSystem::Bmp::inverseColorInArea(const char* outputPathFile, Coordinates coord)
{
    for (int32_t y = coord.leftY; y < coord.rightY && y < infoHeader->height; y++)
    {
        for (int32_t x = coord.leftX; x < coord.rightX && x < infoHeader->width; x++)
        {
            dataPixels[infoHeader->height - y - 1][x].rgbBlue = 255 - dataPixels[infoHeader->height - y - 1][x].rgbBlue;
            dataPixels[infoHeader->height - y - 1][x].rgbGreen = 255 - dataPixels[infoHeader->height - y - 1][x].rgbGreen;
            dataPixels[infoHeader->height - y - 1][x].rgbRed = 255 - dataPixels[infoHeader->height - y - 1][x].rgbRed;
        }
    }

    writeBmp(outputPathFile);
}
