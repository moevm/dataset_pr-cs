#pragma once

#include "Color.hpp"
#include "Vector2i.hpp"
#include <stdint.h>
#include <string>

class ImageReader
{
protected:
    Vector2i size;

    virtual bool check(Vector2i x) const
    {
        return x.x >= 0 && x.y >= 0 && x.x < size.x && x.y < size.y;
    }

    std::string inputFile;
    std::string outputFile;

public:
    ImageReader(std::string input, std::string output)
    {
        this->inputFile = input;
        this->outputFile = output;
    }

    ImageReader() = default;

    virtual void load(std::string path) = 0;
    virtual void save(std::string path) = 0;
    virtual void load() = 0;
    virtual void save() = 0;
    virtual Vector2i get_size() const = 0;
    virtual void put_pixel(Vector2i coord, Color col) = 0;
    virtual Color get_pixel(Vector2i coord, Color def = Color{}) const = 0;
    virtual ~ImageReader(){};
};