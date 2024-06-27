#ifndef BMP_AXIS_HPP
#define BMP_AXIS_HPP

#include <string>

enum class Axis {
    X, Y
};

std::string axisToString(const Axis &axis);

#endif //BMP_AXIS_HPP
