/**
 * @file Parser.cpp
 * @brief Implementation of functions for parsing data
 * @version 0.1.0
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ImageEditor.h"
#include "Parser.h"

#include <string>
#include <regex>
#include <functional>


void Parser::throwError(const char *error_message, int exit_code)
{
    printf("%s\n", error_message);
    exit(exit_code);
}

void Parser::parseCoords(int& x, int& y, std::string& str)
{
    std::cmatch groups;
    std::regex pattern("(-?[0-9]+)\\.(-?[0-9]+)");

    if ( !std::regex_match(str.c_str(), groups, pattern) ) {
        throwError("Error: coords parsing failed.", PARSER_ERROR);
    }
    
    x = stoi(groups[1]);
    y = stoi(groups[2]);
}

void Parser::parseNumber(int& number, std::string& str)
{
    std::cmatch groups;
    std::regex pattern("-?[0-9]+");

    if ( !std::regex_match(str.c_str(), groups, pattern) ) {
        throwError("Error: number parsing failed.", PARSER_ERROR);
    }

    number = stoi(groups[0]);
}


void Parser::parseColorRGBA(ie::ColorRGBA& color, std::string& str)
{
    std::cmatch groups;
    std::regex pattern("([0-9]+)\\.([0-9]+)\\.([0-9]+)");

    if ( !std::regex_match(str.c_str(), groups, pattern) ) {
        throwError("Error: color parsing failed.", PARSER_ERROR);
    }

    color.r = stoi(groups[1]);
    color.g = stoi(groups[2]);
    color.b = stoi(groups[3]);
    color.a = 255;

    if (color.r < 0 || color.r > 255) {
        throwError("Error: color parsing failed.", PARSER_ERROR);
    }
    if (color.g < 0 || color.g > 255) {
        throwError("Error: color parsing failed.", PARSER_ERROR);
    }
    if (color.b < 0 || color.b > 255) {
        throwError("Error: color parsing failed.", PARSER_ERROR);
    }
}

void Parser::parseComponentName(int& parameter, std::string& str)
{
    if (str == "red") {
        parameter = R_IDX;
        return;
    }
    if (str == "green") {
        parameter = G_IDX;
        return;
    }
    if (str == "blue") {
        parameter = B_IDX;
        return;
    }
    throwError("Error: component parsing failed.", PARSER_ERROR);    
}

void Parser::checkValueValidity(int value, std::function<bool(int)> check_func)
{
    if (!check_func(value)) {
        throwError("Error: value parsing failed.", PARSER_ERROR);
    }
}