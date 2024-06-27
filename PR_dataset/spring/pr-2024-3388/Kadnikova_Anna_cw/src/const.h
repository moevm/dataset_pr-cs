#ifndef CONST_H
#define CONST_H

#include <stdint.h>


/* CLI flags */

#define ARGNAME_INPUT "input"
#define ARGNAME_SHORT_INPUT 'i'
#define ARGNAME_OUTPUT "output"
#define ARGNAME_SHORT_OUTPUT 'o'
#define DEFAULT_OUTPUT "out.png"

#define ARGNAME_HELP "help"
#define ARGNAME_SHORT_HELP 'h'
#define ARGNAME_INFO "info"
#define ARGNAME_CIRC "circle"
#define ARGNAME_RGBF "rgbfilter"
#define ARGNAME_SPLT "split"
#define ARGNAME_SQRL "squared_lines"
#define ARGNAME_RMBS "rhombus"
#define ARGNAME_CENTER "center"
#define ARGNAME_RADIUS "radius"
#define ARGNAME_FILL_COLOR "fill_color"
#define ARGNAME_FILL "fill"
#define ARGNAME_COLOR "color"
#define ARGNAME_THICKNESS "thickness"
#define ARGNAME_COMPNAME "component_name"
#define ARGNAME_COMPVALUE "component_value"
#define ARGNAME_NUMBERX "number_x"
#define ARGNAME_NUMBERY "number_y"
#define ARGNAME_LEFT_UP "left_up"
#define ARGNAME_SIDE_SIZE "side_size"


#define SHORT_OPTIONS "i:o:h"
#define LONG_OPT_FLAG 0
#define NO_ARG_VAL ':'
#define UNKNOWN_ARG '?'

/* Task codes */

#define TASKCODE_HELP 1
#define TASKCODE_INFO 2
#define TASKCODE_CIRC 4
#define TASKCODE_RGBF 8
#define TASKCODE_SPLT 16
#define TASKCODE_SQRL 32
#define TASKCODE_FILL 64
#define TASKCODE_RMBS 128

/* TaskConfig error flags */

#define FLAG_UNKNOWN_ARGUMENT 1
#define FLAG_NO_ARGUMENT_VALUE 2
#define FLAG_INVALID_ARGUMENT 4
#define FLAG_NO_INPUT_FILE 8
#define FLAG_EQ_INPUT_OUTPUT 16
#define FLAG_NO_COMMAND 32
#define FLAG_MANY_COMMAND 64
#define FLAG_NO_REQUIRED_ARG 128

/* Image error flags */

#define FLAG_WRONG_SINGATURE 1
#define FLAG_FAIL_CREATE_PNG_STRUCT 2
#define FLAG_FAIL_CREATE_INFO_STRUCT 4
#define FLAG_FAIL_READ_HEADER 8
#define FLAG_FAIL_WRITE_HEADER 8
#define FLAG_ERROR_READ_FILE 16
#define FLAG_ERROR_WRITE_FILE 16
#define FLAG_ERROR_READ_DATA 32
#define FLAG_ERROR_WRITE_DATA 32
#define FLAG_WRONG_BIT_DEPTH 64
#define FLAG_WRONG_CHANNELS 128

/* panic() errors */

#define ERROR_TEMPLATE "Error: %s!\n"

#define UNKNOWN_ARGUMENT_ERROR "unknown argument was passed"
#define NO_ARGUMENT_VALUE_ERROR "value must be set for all arguments"
#define ARGUMENT_VALUE_ERROR "argument(s) value is not correct"
#define NO_COMMAND_ERROR "no control arguments was passed"
#define MANY_COMMANDS_ERROR "more than 2 control arguments was passed"
#define NO_REQUIRED_ARG_ERROR "all required options must be set"
#define NO_INPUT_FILE_ERROR "input file must be set"
#define SAME_FILES_ERROR "input file is the same as output file"
#define FILE_OPEN_ERROR "file could not be opened"
#define FILE_READ_ERROR "fail ro read data from file"
#define FILE_WRITE_ERROR "fail to write data to file"
#define WRONG_FILETYPE_ERROR "given file is not a PNG"
#define INAPPRORIATE_IMAGE_ERROR "inappropriate image was given"
#define INTERNAL_LIBRARY_ERROR "internal libpng error (see above)"

/* Math macros */

#define MAX(l, r) (((l) >= (r)) ? (l) : (r))
#define MIN(l, r) (((l) <= (r)) ? (l) : (r))
#define HASH_PRIME 0xC52304CCB73
#define TWO(c) (0x01 << (c))
#define MASK(c) (((uint8_t)(-1)) / (TWO(TWO(c)) + 0x01))
#define COUNT(x, c) ((x) & MASK(c)) + (((x) >> (TWO(c))) & MASK(c))
#define IN_RANGE(x, min, max) ((min <= x) && (x <= max))

/* Help message */

#define HELP_MESSAGE "Course work for option 5.17, created by Anna Kadnikova.\n\n" \
                     "List of supported commands:\n" \
                     "\n\t\x1b[1m-h --help\x1b[0m\tPrint this message and exit\n" \
                     "\n\t\x1b[1m--info\x1b[0m filename\tPrint header of image and exit\n" \
                     "\n\t\x1b[1m--circle\x1b[0m\tDraw a circle\n" \
                     "\n\t\t--center x.y\t\tSet center of a circle\n" \
                     "\t\t--radius x\t\tSet radius of a circle\n" \
                     "\t\t--thickness x\t\tSet thickness of a circle\n" \
                     "\t\t--color r.g.b\t\tColor of contour\n" \
                     "\t\t--fill\t\t\tIf was set, fill circle with fill_color\n" \
                     "\t\t--fill_color r.g.b\tFiller color\n" \
                     "\n\t\x1b[1m--rgbfilter\x1b[0m\tChange component of all pixels\n" \
                     "\n\t\t--component_name [red, green, blue]\tWhich component need to be changed\n" \
                     "\t\t--component_value x\t\t\tNew component value\n" \
                     "\n\t\x1b[1m--split\x1b[0m\t\tMake splitting lines\n" \
                     "\n\t\t--number_x x\tNumber of axis-Y splits\n" \
                     "\t\t--number_y x\tNumber of axis-X splits\n" \
                     "\t\t--thickness x\tThickness of line\n" \
                     "\t\t--color r.g.b\tColor of line\n" \
                     "\n\t\x1b[1m--squared_lines\x1b[0m Drawing a square with diagonals\n" \
                     "\n\t\t--left_up x.y\t\tLeft up corner coordinates\n" \
                     "\t\t--side_size x\t\tBorder size\n" \
                     "\t\t--thickness x\t\tThickness of border\n" \
                     "\t\t--color r.g.b\t\tBorder color\n" \
                     "\t\t--fill\t\t\tIf was set, fill square with fill_color\n" \
                     "\t\t--fill_color r.g.b\tFiller color\n"

#endif /* CONST_H */
