#ifndef BMP_PARSERS_HPP
#define BMP_PARSERS_HPP

#include <cstdint>
#include "../include/bmp/Axis.hpp"
#include "../include/bmp/Point2D.hpp"
#include "../include/bmp/RGB.hpp"

std::unique_ptr<Axis> parseAxis(const std::string &input);

std::unique_ptr<Point2D> parsePoint2D(const std::string &input);

std::unique_ptr<RGB> parseRGB(const std::string &input);

std::unique_ptr<uint64_t> parseSplitNumber(const std::string &input);

std::unique_ptr<uint64_t> parseThickness(const std::string &input);

#endif //BMP_PARSERS_HPP
