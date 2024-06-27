#include "OptionParsingConsts.h"

const struct option long_options[]={
        {"help",        no_argument,       NULL, HELP_INDEX},
        {"output",      required_argument, NULL, OUTPUT_INDEX},
        {"input",       required_argument, NULL, INPUT_INDEX},
        {"info",        no_argument,       NULL, INFO_INDEX},
        {"rect",        no_argument,       NULL, RECT_INDEX},
        {"ornament",    no_argument,       NULL, ORNAMENT_INDEX},
        {"rotate",      no_argument,       NULL, ROTATE_INDEX},
        {"square_rhombus", no_argument,     NULL, RHOMBUS_INDEX},
        {"pattern",     required_argument, NULL, PATTERN_INDEX},
        {"left_up",     required_argument, NULL, LEFT_UP_INDEX},
        {"right_down",  required_argument, NULL, RIGHT_DOWN_INDEX},
        {"upper_vertex", required_argument, NULL, UPPER_VERTEX_INDEX},
        {"thickness",   required_argument, NULL, THICKNESS_INDEX},
        {"count",       required_argument, NULL, COUNT_INDEX},
        {"angle",       required_argument, NULL, ANGLE_INDEX},
        {"size",    required_argument, NULL, SIZE_INDEX},
        {"fill",        no_argument,       NULL, FILL_INDEX},
        {"color",       required_argument, NULL, COLOR_INDEX},
        {"fill_color",  required_argument, NULL, FILL_COLOR_INDEX},
        {NULL,          0,                 NULL, 0}
    };

const char* short_options = "hi:o:";