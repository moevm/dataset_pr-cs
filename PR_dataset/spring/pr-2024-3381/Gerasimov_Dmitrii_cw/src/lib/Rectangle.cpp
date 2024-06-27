#include "../include/Rectangle.hpp"

Rectangle::Rectangle(Vector2i left_up, Vector2i right_down, Color color,
                     int64_t thickness, bool fill, Color f_color)
    : left_up(left_up), right_down(right_down), fill(fill),
      Shape(color, thickness, f_color)
{
}

void Rectangle::draw(ImageReader &image) const
{
    draw_rect(image, left_up - Vector2i{thickness, thickness},
              {right_down.x + thickness, left_up.y}, color);
    draw_rect(image, {right_down.x, left_up.y - thickness},
              right_down + Vector2i{thickness, thickness}, color);
    draw_rect(image, {left_up.x - thickness, right_down.y},
              right_down + Vector2i{thickness, thickness}, color);
    draw_rect(image, left_up - Vector2i{thickness, thickness},
              {left_up.x, right_down.y + thickness}, color);
    if (fill)
    {
        draw_rect(image, left_up, right_down, fill_color);
    }
}

void Rectangle::draw_rect(ImageReader &image, Vector2i p1, Vector2i p2,
                          Color col) const
{
    auto [x, y] = p1;
    for (; x < p2.x; x++)
    {
        for (y = p1.y; y < p2.y; y++)
        {
            image.put_pixel({x, y}, col);
        }
    }
}

void Rectangle::set_left_up(Vector2i p)
{
    left_up = p;
}

void Rectangle::set_right_down(Vector2i p)
{
    right_down = p;
}

void Rectangle::set_fill(bool f)
{
    fill = f;
}

Vector2i Rectangle::get_left_up() const
{
    return left_up;
}

Vector2i Rectangle::get_right_down() const
{
    return right_down;
}

bool Rectangle::get_fill() const
{
    return fill;
}