#include "draw_romb.hpp"


int BmpSystem::Bmp::edge(Coord p0, Coord p1, Coord p)
{
    return (p.x - p0.x) * (p1.y - p0.y) - (p.y - p0.y) * (p1.x - p0.x);
}

void BmpSystem::Bmp::drawRomb(const char* outputPathFile, Coord coord, BmpSystem::Rgb rgb, int size)
{
    Coord below = {coord.x, static_cast<int16_t>(coord.y + sqrt(2) * size)};
    Coord right = {static_cast<int16_t>(coord.x + (1 / sqrt(2)) * size), static_cast<int16_t>(coord.y + (1 / sqrt(2)) * size)};
    Coord left = {static_cast<int16_t>(coord.x - (1 / sqrt(2)) * size), static_cast<int16_t>(coord.y + (1 / sqrt(2)) * size)};
    
    int x_min = left.x;
    int x_max = right.x;
    int y_min = coord.y;
    int y_max = below.y;

    for (int16_t y = y_min ; y <= y_max; y++)
    {
        for (int16_t x = x_min; x <= x_max; x++)
        {
            if (x < 0 || x >= infoHeader->width || y < 0 || y >= infoHeader->height)
                continue;
            Coord point{x, y};
            int e1 = edge(coord, right, point);
            int e2 = edge(right, below, point);
            int e3 = edge(below, left, point);
            int e4 = edge(left, coord, point);

            if (e1 >= 0 && e2 >= 0 && e3 >= 0 && e4 >= 0 || e1 <= 0 && e2 <= 0 && e3 <= 0 && e4 <= 0)
            {
                setPixel(x, y, rgb);
            }

        }
    }


    writeBmp(outputPathFile);
}