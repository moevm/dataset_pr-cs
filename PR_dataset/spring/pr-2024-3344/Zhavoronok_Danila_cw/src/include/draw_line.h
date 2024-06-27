#pragma once
#include "../include/rgb.h"
#include <vector>

struct position
{
    int x = 0;
    int y = 0;

    position(int x, int y);
    position(const std::vector<int> &vec);
};

std::ostream &operator<<(std::ostream &os, const position &point);
struct Circle
{
    position pos;
    int r = 0;

    Circle(position pos, int r);
};

void draw_pixel(RGB *image, int width, int height, position pos, RGB color);

void fill_circle(RGB *image, int width, int height, Circle c, RGB color);

void draw_line(RGB *image, int width, int height, position a, position b, int thickness, RGB color);
