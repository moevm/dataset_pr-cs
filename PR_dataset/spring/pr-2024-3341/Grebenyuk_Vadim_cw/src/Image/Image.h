#pragma once
#include <array>
#include <iostream>
#include <png.h>
#include <string>
#include <vector>

enum Rgb { Red = 0,
           Green = 1,
           Blue = 2 };

using Color = std::array<int, 3>;
using Coords = std::array<int, 2>;

class Image {
private:
    png_structp png_ptr;
    png_infop info_ptr;
    std::vector<png_bytep> row_pointers;
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

public:
    Image(const std::string_view filename);
    ~Image();
    void write(const std::string_view filename);
    void info();
    bool is_valid();
    void rotate(Coords coords[2], int angle);
    void rgbfilter(enum Rgb component, int value);
    void squared_lines(Coords coords, int side_size, int thickness, Color color, bool fill, Color fill_color);
};
