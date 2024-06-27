#include "../../include/bmp/Axis.hpp"

std::string axisToString(const Axis &axis) {
    switch (axis) {
        case Axis::X:
            return "X";
        case Axis::Y:
            return "Y";
    }
    return "";
}
