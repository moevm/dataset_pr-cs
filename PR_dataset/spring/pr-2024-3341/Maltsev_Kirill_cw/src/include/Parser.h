/**
 * @file Parser.h
 * @brief Header with a description of Parser class
 * @version 0.1
 * @date 2024-05-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PARSER_H
#define PARSER_H

#include "ImageEditor.h"

#include <string>
#include <functional>

#define PARSER_ERROR 46

/**
 * @brief class for parsing program launch options
 * 
 */
class Parser
{
public:

    /**
     * @brief Construct a new Parser object
     * 
     */
    Parser() = delete;


    /**
     * @brief Destroy the Parser object
     * 
     */
    ~Parser() = delete;


    /**
     * @brief Parsing coordinates function, in case of an incorrect format, terminates the program
     * 
     * @param[out] x the X coordinate of point (the result of parsing will be recorded here)
     * @param[out] y the Y coordinate of point (the result of parsing will be recorded here)
     * @param[in] str parse string (should be in format: "X.Y")
     */
    static void parseCoords(int& x, int& y, std::string& str);

    /**
     * @brief Parsing number function, in case of an incorrect format, terminates the program
     * 
     * @param[out] number the result of parsing will be recorded here
     * @param[in] str parse string (should be in format: NUMBER)
     */
    static void parseNumber(int& number, std::string& str);

    /**
     * @brief Parsing color function, in case of an incorrect format, terminates the program
     * 
     * @param[out] color the result of parsing will be recorded here
     * @param[in] str parse string (should be in format: "r.g.b")
     */
    static void parseColorRGBA(ie::ColorRGBA& color, std::string& str);

    /**
     * @brief Parsing component name function, in case of an incorrect format, terminates the program
     * 
     * @param[out] parameter he result of parsing will be recorded here
     * @param[in] str parse string (should be in format: {"red", "green", "blue"})
     */
    static void parseComponentName(int& parameter, std::string& str);

    /**
     * @brief Parsing value function, in case of an incorrect format, terminates the program
     * 
     * @param[in] value number to check
     * @param[in] check_func lambda function to check the number
     */
    static void checkValueValidity(int value, std::function<bool(int)> check_func);

private:
    /**
     * @brief Outputs errors to the out stream when processing images
     * 
     * @param[in] error_message the error message that will be displayed in the out stream
     * @param[in] exit_code the error code with which the program will terminate
     */
    static void throwError(const char *error_message, int exit_code);
};

#endif