#include "../include/Circle.hpp"
#include <iostream>

Circle::Circle(Vector2i center, int64_t radius, Color color, int64_t thickness,
               bool fill, Color f_color)
    : center(center), radius(radius), fill(fill),
      Shape(color, thickness, f_color)
{
}

void Circle::draw(ImageReader &image) const
{
    int64_t r = thickness % 2 == 0 ? (thickness) / 2 : (thickness - 1) / 2;

    auto p0 = Vector2i{(-1) * (radius + r), (-1) * (radius + r)};
    auto r2 = (radius + r + 1) * (radius + r + 1);
    auto r3 = (radius - r) * (radius - r);
    for (; p0.x <= (radius + r); p0.x++)
    {
        auto xx = p0.x * p0.x;
        for (p0.y = (-1) * (radius + r); p0.y <= (radius + r); p0.y++)
        {
            auto t = xx + p0.y * p0.y;
            if (t < r2)
            {
                if (fill && t < r3)
                {
                    image.put_pixel(p0 + center, fill_color);
                }
                else if (t >= r3)
                {
                    image.put_pixel(p0 + center, color);
                }
            }
        }
    }
}

void Circle::set_center(Vector2i c)
{
    center = c;
}

void Circle::set_radius(int64_t r)
{
    radius = r;
}

void Circle::set_fill(bool f)
{
    fill = f;
}

Vector2i Circle::get_center() const
{
    return center;
}

int64_t Circle::get_radius() const
{
    return radius;
}

bool Circle::get_fill() const
{
    return fill;
}