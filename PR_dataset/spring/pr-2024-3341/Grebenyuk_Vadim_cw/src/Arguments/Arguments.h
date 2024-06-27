#pragma once
#include "../Image/Image.h"

#include <map>
#include <string>

class Arguments {
public:
    Arguments(int argc, char *argv[]);
    void process();

private:
    union {
        struct {
            Rgb color;
            int val;
        } filter;
        struct {
            Coords coords[2]; // left_up, right_down
            int angle;
        } rotate;
        struct {
            Coords coords;
            int side_size;
            int thickness;
            Color color;
            bool fill;
            Color fill_color;
        } sqared;
    } p_;

    std::map<std::string_view, std::string_view> raw_;
    void parse_rotate();
    void parse_filter();
    void parse_sqared();
    // replace std::vector for std::span when using C++20
    void check_missing_args(std::vector<std::string_view> arr);
    int parse_int_arg(std::string_view arg);
    void parse_color_arg(std::string_view arg, Color &color);
    void parse_coords_arg(std::string_view arg, Coords &coords);
};
