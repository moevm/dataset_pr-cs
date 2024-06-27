/**
 * @file FlagsHandler.h
 * @brief Header with a description of the FlagsHandler class and other structures to work with launch flags
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef FLAGS_HANDLER_H
#define FLAGS_HANDLER_H

#include "ImagePNGHandler.h"
#include <getopt.h>
#include <map>
#include <string>
#include <set>

#define HANDLER_ERROR           45

#define FLAGS_NUMBER            22

#define HELP_IDX                'h'
#define INPUT_IDX               'i'
#define OUTPUT_IDX              'o'
#define INFO_IDX                1001

#define THICKNESS_IDX           1002
#define COLOR_IDX               1003
#define FILL_IDX                1004
#define FILL_COLOR_IDX          1005

#define CIRCLE_IDX              1006
#define CENTER_IDX              1007
#define RADIUS_IDX              1008

#define RGBFILTER_IDX           1009
#define COMPONENT_NAME_IDX      1010
#define COMPONENT_VALUE_IDX     1011

#define SPLIT_IDX               1012
#define NUMBER_X_IDX            1013
#define NUMBER_Y_IDX            1014

#define SQUARED_LINES_IDX       1015
#define LEFT_UP_IDX             1016
#define SIDE_SIZE_IDX           1017

#define OUTSIDE_ORNAMENT_IDX    1018



/**
 * @brief Class for working with input flags
 * 
 */
class FlagsHandler
{

public:
    
    /**
     * @brief Construct a new FlagsHandler object
     * 
     */
    FlagsHandler();

    /**
     * @brief Destroy the FlagsHandler object
     * 
     */
    ~FlagsHandler();

    /**
     * @brief Get the flags and write them to the map (flags_)
     * 
     * @param[in] argc 
     * @param[in] argv 
     */
    void getFlags(int argc, char **argv);
    
    /**
     * @brief Handling flags and calling the appropriate function
     * 
     */
    void handleFlags();

private:

    /**
     * @brief Structure for representing input flags
     * 
     */
    struct Flag
    {
        bool entered;
        std::string parameter;
    };


    std::map<int, Flag>    flags_;                         // map of flags, contains pairs (FLAG_IDX, Flag)
    const char             *short_options_;                // flags with a short format
    const struct option    long_options_[FLAGS_NUMBER];    // flags with a long format
    std::string            last_argument_;                 // the name of the input file can be passed as the last argument
    ImagePNGHandler        image_png_handler_;             // handler for processing PNG image
    
    /**
     * @brief Outputs errors to the out stream when processing images
     * 
     * @param[in] error_message the error message that will be displayed in the out stream
     * @param[in] exit_code the error code with which the program will terminate
     */
    void throwError(const char *error_message, int exit_code);


    /**
     * @brief Get the redundant flags that must not be entered
     * 
     * @param[in] required_flags flags that must be entered
     * @param[in] optional_flags flags that may not be entered
     * @return std::set<int> - set of redudant flags
     */
    std::set<int> getRedundantFlags(std::set<int>& required_flags, 
        std::set<int>& optional_flags);


    /**
     * @brief used by isFunctions to check if all required_flags are entered and all redundant_flags are not entered
     * 
     * @param[in] required_flags flags that must be entered
     * @param[in] redundant_flags flags that must not be entered
     * @return true 
     * @return false 
     */
    bool checkFlagCompliance(std::set<int>& required_flags, 
        std::set<int>& redundant_flags);
    
    /**
     * @brief Get names of input and output files
     * 
     * @param[out] input_file_name 
     * @param[out] output_file_name 
     */
    void getFinFoutNames(std::string &input_file_name, std::string &output_file_name);

    
    // isFunctions check if the required set of flags has been entered
    bool isHelp();
    bool isInfo();
    bool isCircle();
    bool isRGBFilter();
    bool isSplit();
    bool isSquaredLines();
    bool isOutsideOrnament();
    

    // doFunctions parse arguments and execute method from image_handler_ deppending on the flags entered
    void doHelp();
    void doInfo();
    void doCircle();
    void doRGBFilter();
    void doSplit();
    void doSquaredLines();
    void doOutsideOrnament();
};

#endif