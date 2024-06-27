/**
 * @file doFuncs.cpp
 * @brief Implementation of methods (doFunctions) for FlagsHandler class
 * @version 0.1.0
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ImageEditor.h"
#include "FlagsHandler.h"
#include "Output.h"
#include "Parser.h"


void FlagsHandler::doHelp()
{
    Output::help();
}

void FlagsHandler::doInfo()
{
    std::string input_file_name;
    
    if (flags_[INPUT_IDX].entered) {
        input_file_name = flags_[INPUT_IDX].parameter;
    } else {
        input_file_name = last_argument_;
    }

    image_png_handler_.showImageInfo(input_file_name);
}

void FlagsHandler::doCircle()
{
    int x0, y0, radius, thickness;
    bool fill;
    ie::ColorRGBA color, fill_color;
    std::string input_file_name;
    std::string output_file_name = "out.png";

    Parser::parseCoords(x0, y0, flags_[CENTER_IDX].parameter);
    Parser::parseNumber(radius, flags_[RADIUS_IDX].parameter);
    Parser::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    Parser::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    fill = flags_[FILL_IDX].entered;
    if (fill) {
        Parser::parseColorRGBA(fill_color, flags_[FILL_COLOR_IDX].parameter);
    }
    getFinFoutNames(input_file_name, output_file_name);
    

    Parser::checkValueValidity(radius, [](int radius) { return (radius > 0); });
    Parser::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    image_png_handler_.drawCircle(input_file_name, output_file_name, x0, y0, radius, thickness, color, fill, fill_color);
}

void FlagsHandler::doRGBFilter()
{
    int component_idx, component_value;
    std::string input_file_name;
    std::string output_file_name = "out.png";

    Parser::parseComponentName(component_idx, flags_[COMPONENT_NAME_IDX].parameter);
    Parser::parseNumber(component_value, flags_[COMPONENT_VALUE_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    Parser::checkValueValidity(component_value, [](int component_value) { return (component_value >= 0 && component_value <= 255); });    

    image_png_handler_.aplyRGBFilterOnImage(input_file_name, output_file_name, component_idx, component_value);    
}

void FlagsHandler::doSplit()
{
    int number_x, number_y, thickness;
    ie::ColorRGBA color;
    std::string input_file_name;
    std::string output_file_name = "out.png";
    
    Parser::parseNumber(number_x, flags_[NUMBER_X_IDX].parameter);
    Parser::parseNumber(number_y, flags_[NUMBER_Y_IDX].parameter);
    Parser::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    Parser::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);


    Parser::checkValueValidity(number_x, [](int number_x) { return (number_x > 1); });
    Parser::checkValueValidity(number_y, [](int number_y) { return (number_y > 1); });
    Parser::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });


    image_png_handler_.SplitImage(input_file_name, output_file_name, number_x, number_y, thickness, color);
}

void FlagsHandler::doSquaredLines()
{
    int left, up, side_size, thickness;
    bool fill;
    ie::ColorRGBA color, fill_color;

    std::string input_file_name;
    std::string output_file_name = "out.png";

    Parser::parseCoords(left, up, flags_[LEFT_UP_IDX].parameter);
    Parser::parseNumber(side_size, flags_[SIDE_SIZE_IDX].parameter);
    Parser::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    Parser::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    fill = flags_[FILL_IDX].entered;
    if (fill) {
        Parser::parseColorRGBA(fill_color, flags_[FILL_COLOR_IDX].parameter);
    }
    getFinFoutNames(input_file_name, output_file_name);

    Parser::checkValueValidity(side_size, [](int side_size) { return (side_size > 0); });
    Parser::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    image_png_handler_.drawSquaredLines(input_file_name, output_file_name, left, up, side_size, thickness, color, fill, fill_color);

}

void FlagsHandler::doOutsideOrnament()
{
    int thickness;
    ie::ColorRGBA color;

    std::string input_file_name;
    std::string output_file_name = "out.png";

    Parser::parseNumber(thickness, flags_[THICKNESS_IDX].parameter);
    Parser::parseColorRGBA(color, flags_[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    Parser::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    image_png_handler_.drawOutsideOrnament(input_file_name, output_file_name, thickness, color);
}