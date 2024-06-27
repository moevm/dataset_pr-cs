#include <cstdint>
#include <sstream>
#include <memory>
#include <iostream>
#include "parsers.hpp"

std::unique_ptr<Axis> parseAxis(const std::string &input) {
    if (input == "x") {
        return std::make_unique<Axis>(Axis::X);
    } else if (input == "y") {
        return std::make_unique<Axis>(Axis::Y);
    } else {
        throw std::invalid_argument("Invalid argument for axis: " + input);
    }
}

std::unique_ptr<Point2D> parsePoint2D(const std::string &input) {
    std::istringstream iss(input);
    int64_t x, y;
    char dot;
    iss >> x >> dot >> y;
    if (iss.fail() || !iss.eof() || dot != '.') {
        throw std::invalid_argument("Invalid argument for point: " + input);
    }
    return std::make_unique<Point2D>(x, y);
}

std::unique_ptr<RGB> parseRGB(const std::string &input) {
    std::istringstream iss(input);
    int16_t r, g, b;
    char dot1, dot2;
    iss >> r >> dot1 >> g >> dot2 >> b;
    if (iss.fail() || !iss.eof() ||
        r < 0 || r > 255 ||
        g < 0 || g > 255 ||
        b < 0 || b > 255 ||
        dot1 != '.' || dot2 != '.') {
        throw std::invalid_argument("Invalid argument for color: " + input);
    }
    return std::make_unique<RGB>(static_cast<uint8_t>(r),
                                 static_cast<uint8_t>(g),
                                 static_cast<uint8_t>(b)
    );
}

std::unique_ptr<uint64_t> parseSplitNumber(const std::string &input) {
    std::istringstream iss(input);
    int64_t n;
    iss >> n;
    if (iss.fail() || !iss.eof() || n <= 1) {
        throw std::invalid_argument("Invalid argument for split number: " + input);
    }
    return std::make_unique<uint64_t>(n);
}

std::unique_ptr<uint64_t> parseThickness(const std::string &input) {
    std::istringstream iss(input);
    int64_t n;
    iss >> n;
    if (iss.fail() || !iss.eof() || n <= 0) {
        throw std::invalid_argument("Invalid argument for thickness: " + input);
    }
    return std::make_unique<uint64_t>(n);
}
