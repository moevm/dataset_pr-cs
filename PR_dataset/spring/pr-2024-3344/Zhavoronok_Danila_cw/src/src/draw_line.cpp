#include "../include/draw_line.h"

position::position(int x, int y) : x(x), y(y) {}
position::position(const std::vector<int> &vec)
{
    if (vec.size() != 2)
        return;
    *this = position(vec[0], vec[1]);
}

Circle::Circle(position pos, int r) : pos(pos), r(r) {}

std::ostream &operator<<(std::ostream &os, const position &point)
{
    std::cout << '(' << point.x << ',' << point.y << ')';

    return os;
}

void draw_pixel(RGB *image, int width, int height, position pos, RGB color)
{
    if (pos.x < 0 || pos.x >= width)
        return;
    if (pos.y < 0 || pos.y >= height)
        return;
    // std::cout << pos << '\n';
    image[pos.y * width + pos.x] = color;
}

void draw_circle_line(RGB *image, int width, int height, Circle c, RGB color)
{
    int x = 0;
    int y = c.r;
    int d = 3 - 2 * y;
    while (y >= x)
    {
        draw_pixel(image, width, height, {c.pos.x + x, c.pos.y + y}, color);
        draw_pixel(image, width, height, {c.pos.x - x, c.pos.y + y}, color);
        draw_pixel(image, width, height, {c.pos.x + x, c.pos.y - y}, color);
        draw_pixel(image, width, height, {c.pos.x - x, c.pos.y - y}, color);
        draw_pixel(image, width, height, {c.pos.x + y, c.pos.y + x}, color);
        draw_pixel(image, width, height, {c.pos.x - y, c.pos.y + x}, color);
        draw_pixel(image, width, height, {c.pos.x + y, c.pos.y - x}, color);
        draw_pixel(image, width, height, {c.pos.x - y, c.pos.y - x}, color);
        x++;
        if (d < 0)
        {
            d += (4 * x) + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
    }
}

void draw_circle_filled(RGB *image, int width, int height, Circle c, RGB color)
{
    draw_circle_line(image, width, height, c, color);

    for (int y = -c.r; y <= c.r; y++)
    {
        for (int x = -c.r; x <= c.r; x++)
        {
            if (x * x + y * y <= c.r * c.r)
                draw_pixel(image, width, height, {c.pos.x + x, c.pos.y}, color);
        }
    }
}
struct Rectangle
{
    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

Rectangle get_line_bounding_box(position a, position b, int thickness)
{
    int half_thickness = thickness / 2;

    int x_min = std::min(a.x, b.x) - half_thickness;
    int y_min = std::min(a.y, b.y) - half_thickness;
    int x_max = std::max(a.x, b.x) + half_thickness;
    int y_max = std::max(a.y, b.y) + half_thickness;

    return {x_min, y_min, x_max, y_max};
}

bool rectangles_intersect(const Rectangle &r1, const Rectangle &r2)
{
    return !(r1.x_min > r2.x_max || r1.x_max < r2.x_min || r1.y_min > r2.y_max || r1.y_max < r2.y_min);
}

void draw_line(RGB *image, int width, int height, position a, position b, int thickness, RGB color)
{
    Rectangle image_rect = {0, 0, width - 1, height - 1};
    Rectangle line_rect = get_line_bounding_box(a, b, thickness);

    if (!rectangles_intersect(line_rect, image_rect))
        return;

    int skip = 200;

    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = (a.x < b.x ? 1 : -1) * (thickness / skip + 1);
    int sy = (a.y < b.y ? 1 : -1) * (thickness / skip + 1);
    int err = dx - dy;

    while (abs(a.x - b.x) > thickness / skip && abs(a.y - b.y) > thickness / skip)
    {
        draw_circle_filled(image, width, height, {a, thickness / 2}, color);
        if (2 * err > -dy)
        {
            err -= dy;
            a.x += sx;
        }
        if (2 * err < dx)
        {
            err += dx;
            a.y += sy;
        }

        line_rect = get_line_bounding_box(a, b, thickness);
        if (!rectangles_intersect(line_rect, image_rect))
            return;
    }
}
