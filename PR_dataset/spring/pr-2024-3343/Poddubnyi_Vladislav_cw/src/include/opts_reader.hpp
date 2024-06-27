#pragma once

#include <iostream>
#include <getopt.h>
#include <vector>
#include <sstream>

struct Coordinate{
    int32_t x;
    int32_t y;
    Coordinate(int x=0, int y=0){
        this->x=x;
        this->y=y;
    }
};

struct Color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0){
        this->red=red;
        this->green=green;
        this->blue=blue;
    }
};

struct Opts{
    std::string input_file;
    bool inverse;
    Coordinate left_up;
    Coordinate right_down;
    bool gray;
    bool resize;
    int32_t left;
    int32_t right;
    int32_t above;
    int32_t below;
    Color color;
    bool line;
    Coordinate start;
    Coordinate end;
    int32_t thickness;
    bool help;
    bool info;
    std::string output_file;
    bool outside_ornament;
};

class OptsReader {
public:
    static Opts getOpts(int argc, char* argv[]);
private:
    static Color getColor(std::string arg);
    static Coordinate getCoordinate(std::string arg);
    static std::vector<int32_t> getValues(std::string arg);
    const static struct option long_opts[];
};