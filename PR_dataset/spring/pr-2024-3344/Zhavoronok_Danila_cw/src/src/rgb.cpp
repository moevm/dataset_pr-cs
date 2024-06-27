#include "../include/rgb.h"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b){};
RGB::RGB(const std::vector<int> &vec)
{
    if (vec.size() != 3)
        return;
    *this = RGB(vec[0], vec[1], vec[2]);
}

bool RGB::operator==(const RGB &color)
{
    return this->r == color.r && this->g == color.g && this->b == color.b;
}

bool RGB::operator!=(const RGB &color)
{
    return !(*this == color);
}

std::ostream &
operator<<(std::ostream &os, const RGB &color)
{
    os << unsigned(color.r) << '.' << unsigned(color.g) << '.' << unsigned(color.b);
    return os;
}
