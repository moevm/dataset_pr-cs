#include "change_size.hpp"

void BmpSystem::Bmp::resize(const char* outputPathFile, Side side, BmpSystem::Rgb color)
{
    if (isCorrectSize(side))
    {
        int16_t temp = side.above;
        side.above = side.below;
        side.below = temp;
        
        int32_t oldWidth = infoHeader->width;
        int32_t oldHeight = infoHeader->height;

        int32_t newWidth = oldWidth + side.left + side.right;
        int32_t newHeight = oldHeight + side.above + side.below;

        BmpSystem::Rgb** newPixels = new BmpSystem::Rgb*[newHeight];
        for (int32_t y = 0; y < newHeight; y++)
        {
            newPixels[y] = new BmpSystem::Rgb[newWidth];
        }

        for (int32_t y = 0; y < newHeight; y++)
        {
            for (int32_t x = 0; x < newWidth; x++)
            {
                newPixels[y][x] = color;
            }
        }

        int32_t copyStartY = side.above < 0 ? -side.above : 0;
        int32_t copyStartX = side.left < 0 ? -side.left : 0;
        int32_t copyEndY = oldHeight + (side.below < 0 ? side.below : 0);
        int32_t copyEndX = oldWidth + (side.right < 0 ? side.right : 0);

        for (int32_t y = copyStartY; y < copyEndY; y++)
        {
            for (int32_t x = copyStartX; x < copyEndX; x++)
            {
                int32_t newY = y + side.above;
                int32_t newX = x + side.left;
                if (newY >= 0 && newY < newHeight && newX >= 0 && newX < newWidth)
                {
                    newPixels[newY][newX] = dataPixels[y][x];
                }
            }
        }

        infoHeader->width = newWidth;
        infoHeader->height = newHeight;

        for (int32_t y = 0; y < oldHeight; y++)
        {
            delete[] dataPixels[y];
        }
        delete[] dataPixels;

        dataPixels = newPixels;
    }

    writeBmp(outputPathFile);
}
