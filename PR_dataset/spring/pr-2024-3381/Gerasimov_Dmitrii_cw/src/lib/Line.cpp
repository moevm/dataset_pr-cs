#include "../include/Line.hpp"

Line::Line(Vector2i p1, Vector2i p2, Color color, int64_t thickness)
    : p1(p1), p2(p2), Shape(color, thickness)
{
}

void Line::drawX(ImageReader &image, Vector2i coord, size_t r) const
{
    std::vector<Vector2i> v = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    image.put_pixel(coord, color);
    for (auto &i : v)
    {
        for (size_t j = 1; j <= r; j++)
        {
            image.put_pixel(coord + i * j, color);
        }
    }
}

void Line::draw(ImageReader &image) const
{
    auto [x0, y0] = p1;
    auto [x1, y1] = p2;
    int64_t r = thickness % 2 == 0 ? (thickness) / 2 : (thickness - 1) / 2;
    int64_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        image.put_pixel({steep ? y : x, steep ? x : y}, color);
        drawX(image, {steep ? y : x, steep ? x : y}, r);
        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
    Circle(p1, r, color, 1, 1, color).draw(image);
    Circle(p2, r, color, 1, 1, color).draw(image);
}

void Line::set_start(Vector2i p)
{
    p1 = p;
}

void Line::set_destination(Vector2i p)
{
    p2 = p;
}

Vector2i Line::get_start() const
{
    return p1;
}

Vector2i Line::get_destination() const
{
    return p2;
}