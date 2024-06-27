#pragma once
#include "Color.hpp"
#include "Drawable.hpp"
#include "ImageReader.hpp"
#include "Vector2i.hpp"

class Shape : public Drawable
{
protected:
    Color color;
    int64_t thickness;
    Color fill_color;

public:
    Shape(Color color, int64_t th = 1, Color fill = {})
        : color(color), thickness(th), fill_color(fill){};

    void set_color(Color col)
    {
        color = col;
    }

    Color get_color() const
    {
        return color;
    }

    void set_thikness(int64_t th)
    {
        thickness = th;
    }

    int64_t get_thikness() const
    {
        return thickness;
    }

    void set_fill_color(Color col)
    {
        fill_color = col;
    }

    Color get_fill_color() const
    {
        return fill_color;
    }
};