#pragma once

#include <stdint.h>

#pragma pack(push, 1)

class Color
{
public:
    constexpr Color() = default;

    constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;

    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
};

#pragma pack(pop)

constexpr Color Color::Black(0, 0, 0);
constexpr Color Color::White(255, 255, 255);
constexpr Color Color::Red(255, 0, 0);
constexpr Color Color::Green(0, 255, 0);
constexpr Color Color::Blue(0, 0, 255);
constexpr Color Color::Yellow(255, 255, 0);
constexpr Color Color::Magenta(255, 0, 255);
constexpr Color Color::Cyan(0, 255, 255);

constexpr bool operator==(const Color &left, const Color &right)
{
    return (left.r == right.r) && (left.g == right.g) && (left.b == right.b);
}

constexpr bool operator!=(const Color &left, const Color &right)
{
    return !((left.r == right.r) && (left.g == right.g) && (left.b == right.b));
}