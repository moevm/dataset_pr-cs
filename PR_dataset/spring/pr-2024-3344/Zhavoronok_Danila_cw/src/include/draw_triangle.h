#pragma once
#include <vector>
#include "draw_line.h"

struct triangle
{
    std::vector<position> points;
    triangle(const std::vector<int> &vec);
    triangle(const std::vector<position> &vec);
    triangle(position a, position b, position c);
};

void draw_triangle(RGB *image, int width, int height, triangle tri, int thickness, RGB color, bool fill, RGB fill_color);
