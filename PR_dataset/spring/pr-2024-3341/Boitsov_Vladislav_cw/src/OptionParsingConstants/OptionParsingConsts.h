#ifndef OPTION_PARSING_CONSTANTS
#define OPTION_PARSING_CONSTANTS

#include <getopt.h>
#include <iostream>

#define HELP_INDEX          'h' //short versions
#define OUTPUT_INDEX        'o'
#define INPUT_INDEX         'i'

#define INFO_INDEX          1001 //modes as string args have 1xxx index
#define RECT_INDEX          1002
#define ORNAMENT_INDEX      1003
#define ROTATE_INDEX        1004
#define RHOMBUS_INDEX       1005

#define PATTERN_INDEX       2001 //string args have 2xxx index

#define LEFT_UP_INDEX       3001 //coord args have 3xxx index
#define RIGHT_DOWN_INDEX    3002
#define UPPER_VERTEX_INDEX  3003

#define THICKNESS_INDEX     4001 //int args have 4xxx index
#define COUNT_INDEX         4002
#define ANGLE_INDEX         4003
#define SIZE_INDEX          4004

#define FILL_INDEX          5000 

#define COLOR_INDEX         5001 //Rgb args have 5xxx index
#define FILL_COLOR_INDEX    5002


extern const struct option long_options[];
extern const char* short_options;

#endif