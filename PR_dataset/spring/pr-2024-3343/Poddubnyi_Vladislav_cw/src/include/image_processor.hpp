#pragma once

#include <iostream>
#include <cmath>
#include "opts_reader.hpp"
#include "picture.hpp"


class ImageProcessor{
public:
    static void gray(Picture &picture, Coordinate leftUp, Coordinate rightDown);
    static void inverse(Picture &picture, Coordinate leftUp, Coordinate rightDown);
    static void resize(Picture &picture, int32_t left, int32_t above, int32_t right, int32_t below, Color color);
    static void line(Picture &picture, Coordinate start, Coordinate end, Color color, int32_t thickness);
    static void ornament(Picture &picture, int32_t thickness, Color color);
};