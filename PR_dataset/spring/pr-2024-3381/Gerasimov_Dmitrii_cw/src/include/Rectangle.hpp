#pragma once

#include "Color.hpp"
#include "Shape.hpp"
#include "Vector2i.hpp"

class Rectangle : public Shape
{
private:
    void draw_rect(ImageReader &image, Vector2i p1, Vector2i p2,
                   Color col) const;
    Vector2i left_up;
    Vector2i right_down;
    bool fill;

protected:
    void draw(ImageReader &image) const override;

public:
    Rectangle(Vector2i left_up, Vector2i right_down, Color color,
              int64_t thickness, bool fill = 0, Color f_color = {});
    void set_left_up(Vector2i p);
    void set_right_down(Vector2i p);
    void set_fill(bool f);
    Vector2i get_left_up() const;
    Vector2i get_right_down() const;
    bool get_fill() const;
};
