#ifndef ARG_DICT_H
#define ARG_DICT_H

#include <stdlib.h>
#include <string.h>
#include "errors.h"

#define HELP_MSG \
    "Usage: cw [OPTIONS] [input_file_path]\n\n" \
    "Global options\n" \
    "-h,    --help\n" \
    "         Show this help\n" \
    "-i,    --input <path> (REQUIRED if no input_file_path specified)\n" \
    "         Input file path can be passed this way too\n" \
    "-o,    --output <path> (OPTIONAL)\n" \
    "         Output file path\n" \
    "         Default: out.png\n" \
    "-I,    --info\n" \
    "         Print info about input file and exit\n" \
    "-z,    --compression <level> (OPTIONAL)\n" \
    "         Set output compression level, 0-9,\n" \
    "         0 - no compression, 9 - best compression\n" \
    "         Default: 0\n\n" \
    "This program has 5 work modes:\n" \
    "-t,    --triangle\n" \
    "         Draw triangle\n" \
    "-b,    --biggest_rect\n" \
    "         Fill biggest rectangle with selected color\n" \
    "-c,    --collage\n" \
    "         Create collage from one image\n" \
    "-l,    --line\n" \
    "         Draw line\n" \
    "-r,    --outside_ornament\n" \
    "         Draw ouside ornament - defence task\n\n" \
    "Draw triangle mode:\n" \
    "-P,    --points <X1.Y1.X2.Y2.X3.Y3> (REQUIRED)\n" \
    "         Coordinates of the triangle vertices\n" \
    "-T,    --thickness <positive int> (REQUIRED)\n" \
    "         Thickness of the triangle outline\n" \
    "-C,    --color <R.G.B> (REQUIRED)\n" \
    "         Color of the triangle outline in RGB format\n" \
    "         Decimal (0...255) for each channel\n" \
    "-f,    --fill (OPTIONAL)\n" \
    "         If set, program draws triangle infill\n" \
    "-F,    --fill_color <R.G.B> (REQUIRED if -f set)\n" \
    "         Color of the triangle infill in RGB format\n" \
    "         Decimal (0...255) for each channel\n\n" \
    "Fill biggest rectangle mode:\n" \
    "-O,    --old_color <R.G.B> (REQUIRED)\n" \
    "         Rectangle color to search for\n" \
    "         Decimal (0...255) for each channel\n" \
    "-N,    --new_color <R.G.B> (REQUIRED)\n" \
    "         Color to replace with\n" \
    "         Decimal (0...255) for each channel\n\n" \
    "Collage mode:\n" \
    "-X,    --number_x <positive int>\n" \
    "         Number of the image repetitions along X axis\n" \
    "-Y,    --number_y <positive int>\n" \
    "         Number of the image repetitions along Y axis\n\n" \
    "Draw line mode:\n" \
    "-S,    --start <X.Y> (REQUIRED)\n" \
    "         Coordinates of the start of the line\n" \
    "-E,    --end <X.Y> (REQUIRED)\n" \
    "         Coordinates of the end of the line\n" \
    "-T,    --thickness <positive int> (REQUIRED)\n" \
    "         Thickness of the line\n\n" \
    "Draw outside ornament:\n" \
    "-T,    --thickness <positive int> (REQUIRED)\n" \
    "         Thickness of the outside ornament\n" \
    "-C,    --color <R.G.B> (REQUIRED)\n" \
    "         Color of the outside ornament in RGB format\n" \
    "         Decimal (0...255) for each channel\n\n" \
    "Note: the X axis is horizontal and increasing to the right,\n" \
    "      the Y axis is vertical and incresing to the bottom.\n\n" \
    "Note: PNG format does not change during processing except for palette\n" \
    "      PNG files, that will be converted to 8-bit RGB PNG files."

enum ArgType {
    ARG_OUTPUT_NAME,
    ARG_INPUT_NAME,
    ARG_PRINT_INFO,
    ARG_POINTS,
    ARG_THICKNESS,
    ARG_COLOR,
    ARG_FILL,
    ARG_FILL_COLOR,
    ARG_OLD_COLOR,
    ARG_NEW_COLOR,
    ARG_NUM_X,
    ARG_NUM_Y,
    ARG_START,
    ARG_END,
    ARG_COMPRESSION
};

enum Mode {
    MODE_NONE,
    MODE_HELP,
    MODE_TRIANGLE,
    MODE_RECT_SEARCH,
    MODE_COLLAGE,
    MODE_LINE,
    MODE_ORNAMENT
};

struct DictNode {
    enum ArgType key;
    char *value;
};

typedef struct ArgDict_struct {
    struct DictNode *arr;
    size_t len;
} ArgDict;

ArgDict *argdict_new();

int argdict_set(ArgDict *dict, enum ArgType key, char *value);

int argdict_find(ArgDict *dict, enum ArgType key, char **result);

void argdict_del(ArgDict *dict);

#endif
