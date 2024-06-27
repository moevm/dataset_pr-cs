#ifndef BMP_OPTIONS_HPP
#define BMP_OPTIONS_HPP

#include <memory>
#include <getopt.h>
#include "../include/bmp/RGB.hpp"
#include "../include/bmp/Point2D.hpp"
#include "../include/bmp/Axis.hpp"

struct DrawOptions {
    std::unique_ptr<Axis> axis;
    std::unique_ptr<Point2D> left_up;
    std::unique_ptr<Point2D> right_down;
    std::unique_ptr<Point2D> dest_left_up;
    std::unique_ptr<RGB> old_color;
    std::unique_ptr<RGB> new_color;
    std::unique_ptr<uint64_t> number_x;
    std::unique_ptr<uint64_t> number_y;
    std::unique_ptr<uint64_t> thickness;
    std::unique_ptr<RGB> color;
};

enum class Function {
    HELP,
    INFO,
    MIRROR,
    COPY,
    COLOR_REPLACE,
    SPLIT,
    OUTSIDE_ORNAMENT
};

const char *short_options = ":hIi:o:MCRSOa:f:s:d:p:n:x:y:t:c:";

const struct option long_options[] = {
        {"help",             no_argument,       nullptr, 'h'},
        {"info",             no_argument,       nullptr, 'I'},
        {"input",            required_argument, nullptr, 'i'},
        {"output",           required_argument, nullptr, 'o'},
        {"mirror",           no_argument,       nullptr, 'M'},
        {"copy",             no_argument,       nullptr, 'C'},
        {"color_replace",    no_argument,       nullptr, 'R'},
        {"split",            no_argument,       nullptr, 'S'},
        {"outside_ornament", no_argument,       nullptr, 'O'},
        {"axis",             required_argument, nullptr, 'a'},
        {"left_up",          required_argument, nullptr, 'f'},
        {"right_down",       required_argument, nullptr, 's'},
        {"dest_left_up",     required_argument, nullptr, 'd'},
        {"old_color",        required_argument, nullptr, 'p'},
        {"new_color",        required_argument, nullptr, 'n'},
        {"number_x",         required_argument, nullptr, 'x'},
        {"number_y",         required_argument, nullptr, 'y'},
        {"thickness",        required_argument, nullptr, 't'},
        {"color",            required_argument, nullptr, 'c'},
        {nullptr,            no_argument,       nullptr, 0}
};

#endif //BMP_OPTIONS_HPP
