#include "../include/draw_triangle.h"
#include <algorithm>

triangle::triangle(position a, position b, position c)
{
    this->points.push_back(a);
    this->points.push_back(b);
    this->points.push_back(c);
}

triangle::triangle(const std::vector<int> &vec)
{
    if (vec.size() != 6)
        return;

    for (int i = 0; i < vec.size(); i += 2)
    {
        this->points.push_back({vec[i], vec[i + 1]});
    }
}

triangle::triangle(const std::vector<position> &vec)
{
    if (vec.size() != 3)
        return;

    for (int i = 0; i < vec.size(); i++)
    {
        this->points.push_back(vec[i]);
    }
}

std::ostream &operator<<(std::ostream &os, const std::vector<position> &points)
{
    for (const auto &it : points)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';

    return os;
}

void draw_flat_horizontal_line(RGB *image, int width, int height, position a, position b, RGB color)
{
    if (a.x > b.x)
        std::swap(a, b);
    for (int i = a.x; i <= b.x; i++)
    {
        draw_pixel(image, width, height, {i, a.y}, color);
    }
}

void fill_bottom_flat_triangle(RGB *image, int width, int height, triangle tri, RGB fill_color)
{
    float curx1 = tri.points[0].x;
    float curx2 = tri.points[0].x;

    for (int y = tri.points[0].y; y <= tri.points[1].y; y++)
    {
        draw_flat_horizontal_line(image, width, height, {int(curx1), y}, {int(curx2), y}, fill_color);
        curx1 += float(tri.points[1].x - tri.points[0].x) / (tri.points[1].y - tri.points[0].y); // Add slope val
        curx2 += float(tri.points[2].x - tri.points[0].x) / (tri.points[2].y - tri.points[0].y); // Add slope val
    }
}

void fill_top_flat_triangle(RGB *image, int width, int height, triangle tri, RGB fill_color)
{
    float curx1 = tri.points[2].x;
    float curx2 = tri.points[2].x;

    for (int y = tri.points[2].y; y > tri.points[0].y; y--)
    {
        draw_flat_horizontal_line(image, width, height, {int(curx1), y}, {int(curx2), y}, fill_color);
        curx1 -= float(tri.points[2].x - tri.points[0].x) / float(tri.points[2].y - tri.points[0].y); // Add slope val
        curx2 -= float(tri.points[2].x - tri.points[1].x) / float(tri.points[2].y - tri.points[0].y); // Add slope val
    }
}

bool position_y_sorter(position const &lhs, position const &rhs)
{
    return lhs.y < rhs.y;
}

void draw_triangle(RGB *image, int width, int height, triangle tri, int thickness, RGB color, bool fill, RGB fill_color)
{
    if (fill)
    {
        std::sort(tri.points.begin(), tri.points.end(), &position_y_sorter);
        if (tri.points[1].y == tri.points[2].y)
        {
            fill_bottom_flat_triangle(image, width, height, tri, fill_color);
        }
        else if (tri.points[0].y == tri.points[1].y)
        {
            fill_top_flat_triangle(image, width, height, tri, fill_color);
        }
        else
        {
            position side_point = {(int)(tri.points[0].x + ((float)(tri.points[1].y - tri.points[0].y) /
                                                            (float)(tri.points[2].y - tri.points[0].y)) *
                                                               (tri.points[2].x - tri.points[0].x)),
                                   tri.points[1].y};
            fill_bottom_flat_triangle(image, width, height, {tri.points[0], tri.points[1], side_point}, fill_color);
            fill_top_flat_triangle(image, width, height, {tri.points[1], side_point, tri.points[2]}, fill_color);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        position a = tri.points[i];
        position b = tri.points[(i + 1) % 3];
        draw_line(image, width, height, a, b, thickness, color);
    }
}
