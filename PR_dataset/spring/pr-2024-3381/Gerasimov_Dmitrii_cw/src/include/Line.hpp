#pragma once

#include <vector>

#include "Circle.hpp"
#include "Color.hpp"
#include "Shape.hpp"
#include "Vector2i.hpp"

class Line : public Shape
{
private:
    void drawX(ImageReader &image, Vector2i coord, size_t r) const;
    Vector2i p1;
    Vector2i p2;

protected:
    void draw(ImageReader &image) const override;

public:
    Line(Vector2i p1, Vector2i p2, Color color, int64_t thickness);
    void set_start(Vector2i p);
    void set_destination(Vector2i p);
    Vector2i get_start() const;
    Vector2i get_destination() const;
};
