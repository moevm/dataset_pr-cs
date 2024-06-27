#pragma once

#include "ImageReader.hpp"
#include "Vector2i.hpp"

class ImageRedactor;

class Drawable
{
    friend class ImageRedactor;

protected:
    Drawable() = default;
    virtual void draw(ImageReader &image) const = 0;
    virtual ~Drawable() = default;
};