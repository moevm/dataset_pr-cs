#include "../../include/bmp/RGB.hpp"

RGB::operator std::string() const {
    return "RGB {" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + "}";
}

bool RGB::operator==(const RGB &rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b;
}

bool RGB::operator!=(const RGB &rhs) const {
    return !(*this == rhs);
}
