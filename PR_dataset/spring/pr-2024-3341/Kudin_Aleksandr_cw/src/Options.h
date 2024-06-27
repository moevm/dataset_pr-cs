#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>

static struct option selectAction[] = {
    {"help", no_argument, 0, 'h'},
    {"output", required_argument, 0, 'o'},
    {"input", required_argument, 0, 'i'},
    {"info", no_argument, 0, 'd'},
    {"squared_lines", no_argument, 0, 's'},
    {"rgbfilter", no_argument, 0, 'e'},
    {"rotate", no_argument, 0, 'r'},
    {"contrast", no_argument, 0, 'k'},
    {0, 0, 0, 0}
};

static struct option squared_linesKeys[] = {
    {"left_up", required_argument, 0, 'u'},
    {"side_size", required_argument, 0, 's'},
    {"thickness", required_argument, 0, 't'},
    {"color", required_argument, 0, 'c'},
    {"fill", no_argument, 0, 'f'},
    {"fill_color", required_argument, 0, 'g'},
    {0, 0, 0, 0}
};

static struct option rgbFilterKeys[] = {
    {"component_name", required_argument, 0, 'n'},
    {"component_value", required_argument, 0, 'v'},
    {0, 0, 0, 0}
};

static struct option rotateKeys[] = {
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'd'},
    {"angle", required_argument, 0, 'a'},
    {0, 0, 0, 0}
};

static struct option contrastKeys[] = {
    {"alpha", required_argument, 0, 'l'},
    {"beta", required_argument, 0, 'b'},
    {0, 0, 0, 0}
};

#endif // OPTIONS_H