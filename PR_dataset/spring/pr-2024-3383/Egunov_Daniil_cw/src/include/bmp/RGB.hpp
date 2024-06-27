#ifndef BMP_RGB_HPP
#define BMP_RGB_HPP

#include <cstdint>
#include <string>

struct RGB {
    uint8_t r, g, b;

    RGB(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {};

    RGB() : r(255), g(255), b(255) {};

    ~RGB() = default;

    explicit operator std::string() const;

    bool operator==(const RGB &rhs) const;

    bool operator!=(const RGB &rhs) const;
};


#endif //BMP_RGB_HPP
