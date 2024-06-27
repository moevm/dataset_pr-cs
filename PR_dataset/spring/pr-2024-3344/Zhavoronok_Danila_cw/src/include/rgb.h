#pragma once
#include <iostream>
#include <vector>

struct RGB
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    RGB(uint8_t r, uint8_t g, uint8_t b);
    RGB(const std::vector<int> &vec);
    RGB() = default;
    ~RGB() = default;

    bool operator==(const RGB &rgb);
    bool operator!=(const RGB &rgb);
    friend std::ostream &operator<<(std::ostream &os, const RGB &rgb);
};
