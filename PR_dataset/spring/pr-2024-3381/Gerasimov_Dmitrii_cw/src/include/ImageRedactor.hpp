#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Circle.hpp"
#include "Drawable.hpp"
#include "ImageReader.hpp"
#include "Rectangle.hpp"
#include "Vector2i.hpp"
#include "Line.hpp"

class ImageRedactor
{
private:
    ImageReader &image;
    void draw_semicircles(int64_t count, int64_t thickness, Color color);
    void draw_rect(int64_t count, int64_t thickness, Color color);
    void draw_circle(Color color);
    int64_t check_line(Vector2i pos, Vector2i offset, Vector2i offset_to_c,
                       Color color);

public:
    enum class OrnametType
    {
        rectangle,
        circle,
        semicircles
    };
    void copy(Vector2i left_up, Vector2i right_down, Vector2i dest);
    void replace(Color color_old, Color color_new);
    void draw(Drawable &obj);
    void ornament(OrnametType t, int64_t count, int64_t thickness, Color color);
    void filled_rects(Color color, Color b_color, int64_t thickness);
    void rhombus(Color color);
    ImageRedactor(ImageReader &image);
};
