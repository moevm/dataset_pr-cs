/**
 * @file Output.h
 * @brief Header with a description of the Output class
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TEST_H
#define TEST_H

#include <string>

/**
 * @brief Class used for output data in out stream
 * 
 */
class Output
{
public:

    /**
     * @brief Construct a new Output object
     * 
     */
    Output() = delete;

    /**
     * @brief Destroy the Output object
     * 
     */
    ~Output() = delete;

    /**
     * @brief Displays information about the variant and the author of the course
     * 
     * @param[in] option the number of the course work variant
     * @param[in] name author name
     * @param[in] surname author surname
     */
    static void showAuthorInfo(const char *option, const char *name, const char *surname);

    /**
     * @brief Shows help with information about launch flags
     * 
     */
    static void help();
};

#endif