#pragma once

#include <array>
#include <string>
#include <cstdint>




#pragma pack(push, 1)

struct FileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reversed1;
    uint16_t reversed2;
    uint32_t Offset;
};

struct InfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t colorPlanes;
    uint16_t bytesPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colorsUsed;
    uint32_t importantColors;
};

struct Color
{
    uint8_t r, g, b;

    Color()
        : b(0), g(0), r(0) {}
    Color(uint8_t, uint8_t g, uint8_t b)
        : b(b), g(g), r(r) {}
    int operator!= (Color& other)
    {
        if (r != other.r || b != other.b || g != other.g)
        {
            return 1;
        }
        return 0;
    }
    int operator== (Color& other)
    {
        if (r == other.r && b == other.b && g == other.g)
        {
            return 1;
        }
        return 0;
    }
    void operator= (Color& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
    }
};

#pragma pack(pop)



struct Rectangle
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int thickness;
    Color color;
    bool fill;
    Color fill_color;
};

struct Ornament
{
    std::string pattern; //изменить в дальнейшем
    Color color;
    int thickness;
    int count;
};

struct Rotate
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int angle;
};

struct Circle
{
    std::array<int, 2> center;
    int radius;
    int thickness;
    Color color;
    bool fill;
    Color fill_color;
    Circle(std::array<int, 2> center, int radius, int thickness, Color color, bool fill, Color fill_color)
    : center(center), thickness(thickness), radius(radius), color(color), fill(fill), fill_color(fill_color) {}
    Circle()
    : center({0, 0}), thickness(0), radius(0), color({0,0,0}), fill(0), fill_color({0,0,0}) {}
};

struct Smth
{
    int thickness;
    Color color;
};