#pragma once

#include <stdint.h>

struct Vector2i
{
    int64_t x{0};
    int64_t y{0};

    constexpr Vector2i operator+(const Vector2i &v) const
    {
        return Vector2i{x + v.x, y + v.y};
    }

    constexpr Vector2i operator*(const int &v) const
    {
        return Vector2i{x * v, y * v};
    }

    constexpr Vector2i operator-(const Vector2i &v) const
    {
        return Vector2i{x - v.x, y - v.y};
    }

    constexpr bool operator==(const Vector2i &v) const
    {
        return x == v.x && y == v.y;
    }

    constexpr bool operator>(const Vector2i &v) const
    {
        return x > v.x && y > v.y;
    }

    constexpr bool operator<(const Vector2i &v) const
    {
        return x < v.x && y < v.y;
    }
};