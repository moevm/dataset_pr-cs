
#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>
class Arguments
{
public:
    int x0;
    int x1;
    int x2;
    int y0;
    int y1;
    int y2;
    int opt_number;
    float thickness;
    int number_x;
    int number_y;
    int* old_color;
    int* new_color;
    int* fill_color;
    int* color;
    bool is_fill;
    bool is_help;
    bool is_info;
    std::string input_img_path;
    std::string output_img_path;


    Arguments();
    ~Arguments();

};

Arguments* readArguments(int argc, char** argv);
#endif