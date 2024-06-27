#ifndef CONST_H
#define CONST_H

#include <stdint.h>


/* I/O consts */

#define MIN_CORRECT_CHANNELS 3
#define CORRECT_BIT_DEPTH 8
#define SIGNATURE_SIZE 8
#define MAX_CHANNEL_VALUE 255

/* CLI flags */

#define ARGNAME_INPUT "input"
#define ARGNAME_SHORT_INPUT 'i'
#define ARGNAME_OUTPUT "output"
#define ARGNAME_SHORT_OUTPUT 'o'
#define DEFAULT_OUTPUT "out.png"

#define ARGNAME_HELP "help"
#define ARGNAME_SHORT_HELP 'h'
#define ARGNAME_INFO "info"
#define ARGNAME_COPY "copy"
#define ARGNAME_REPL "color_replace"
#define ARGNAME_ORNM "ornament"
#define ARGNAME_RECT "filled_rects"
#define ARGNAME_OUTO "outside_ornament"
#define ARGNAME_SRC_UP "left_up"
#define ARGNAME_SRC_DOWN "right_down"
#define ARGNAME_DEST_UP "dest_left_up"
#define ARGNAME_OLD_COLOR "old_color"
#define ARGNAME_NEW_COLOR "new_color"
#define ARGNAME_PATTERN "pattern"
#define ARGNAME_COLOR "color"
#define ARGNAME_BORDER_COLOR "border_color"
#define ARGNAME_THICKNESS "thickness"
#define ARGNAME_COUNT  "count"

#define SHORT_OPTIONS "i:o:h"
#define LONG_OPT_FLAG 0
#define NO_ARG_VAL ':'
#define UNKNOWN_ARG '?'

/* Task codes */

#define TASKCODE_HELP 1
#define TASKCODE_INFO 2
#define TASKCODE_COPY 4
#define TASKCODE_REPL 8
#define TASKCODE_ORNM 16
#define TASKCODE_RECT 32
#define TASKCODE_OUTO 64

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
#define HASH_PRIME 0x01000193
#define TWO(c) (0x01 << (c))
#define MASK(c) (((uint8_t)(-1)) / (TWO(TWO(c)) + 0x01))
#define COUNT(x, c) ((x) & MASK(c)) + (((x) >> (TWO(c))) & MASK(c))
#define IN_RANGE(x, min, max) ((min <= x) && (x <= max))

/* Help message */

#define HELP_MESSAGE "Course work for option 5.16, created by Andrei Pavlov.\n\n" \
                     "List of supported commands:\n" \
                     "\n\t\x1b[1m-h --help\x1b[0m\tPrint this message and exit\n" \
                     "\n\t\x1b[1m--info\x1b[0m filename\tPrint header of image and exit\n" \
                     "\n\t\x1b[1m--copy\x1b[0m\t\tMake a copy of selected image part\n" \
                     "\n\t\t--left_up x.y\t\tLeft-up point of source part\n" \
                     "\t\t--right_down x.y\tRight-down point of source part\n" \
                     "\t\t--dest_left_up x.y\tLeft-up point of destination\n" \
                     "\n\t\x1b[1m--color_replace\x1b[0m\tChange all pixels from one color to another\n" \
                     "\n\t\t--old_color r.g.b\tOld color\n" \
                     "\t\t--new_color r.g.b\tNew color\n" \
                     "\n\t\x1b[1m--ornament\x1b[0m\tMake a beatiful border around image\n" \
                     "\n\t\t--pattern [rectangle, circle, semicircles]\tType of border pattern\n" \
                     "\t\t--color r.g.b\t\t\t\t\tBorder color\n" \
                     "\t\t--thickness x\t\t\t\t\tThickness of border\n" \
                     "\t\t--count x\t\t\t\t\tCount of borders\n" \
                     "\n\t\x1b[1m--filled_rects\x1b[0m\tFind all the filled rectangles in the image and frame them\n" \
                     "\n\t\t--color r.g.b\t\tColor of rectangles\n" \
                     "\t\t--border_color r.g.b\tBorder color\n" \
                     "\t\t--thickness x\t\tThickness of border\n" \
                     "\n\t\x1b[1m--outside_ornament\x1b[0m\tOutline image with rectangle of given color and thickness\n" \
                     "\n\t\t--color r.g.b\t\tBorder color\n" \
                     "\t\t--thickness x\t\tBorder thickness\n"

#endif /* CONST_H */
