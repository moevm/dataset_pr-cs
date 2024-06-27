#pragma once

#include "Color.hpp"
#include "Shape.hpp"
#include "Vector2i.hpp"

class Circle : public Shape
{
    friend class Line;

protected:
    void draw(ImageReader &image) const override;
    Vector2i center;
    int64_t radius;
    bool fill;

public:
    Circle(Vector2i center, int64_t radius, Color color, int64_t thickness,
           bool fill = 0, Color f_color = {});
    void set_center(Vector2i c);
    void set_radius(int64_t r);
    void set_fill(bool f);
    Vector2i get_center() const;
    int64_t get_radius() const;
    bool get_fill() const;
};