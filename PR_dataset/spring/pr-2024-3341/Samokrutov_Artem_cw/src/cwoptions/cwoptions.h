#ifndef CWOPTIONS_H
#define CWOPTIONS_H

#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include "../cwstructures/cwstructures.h"
#include "../cwdrawing/cwdrawing.h"
#include "../cwerror/cwerror.h"

#define INFO_OPT 1000
#define LINE_OPT 1001
#define INVERSE_CIRCLE_OPT 1002
#define TRIM_OPT 1003
#define START_OPT 1004
#define END_OPT 1005
#define COLOR_OPT 1006
#define THICKNESS_OPT 1007
#define CENTER_OPT 1008
#define RADIUS_OPT 1009
#define LEFT_UP_OPT 1010
#define RIGHT_DOWN_OPT 1011
#define CONTRAST_OPT 1012
#define ALPHA_OPT 1013
#define BETA_OPT 1014

#define MAX_FILENAME_LEN 127


struct Line_config {
    bool flag_start;
    bool flag_end;
    bool flag_color;
    bool flag_thickness;

    Coord_t start;
    Coord_t end;
    RGB_t color;
    int thickness;
};

struct Inverse_circle_config {
    bool flag_center;
    bool flag_radius;

    Coord_t center;
    int radius;
};

struct Trim_config {
    bool flag_left_up;
    bool flag_right_down;

    Coord_t left_up;
    Coord_t right_down;
};

struct Contrast_config {
    bool flag_alpha;
    bool flag_beta;

    float alpha;
    int beta;
};

struct Config {
    char *input_file;
    char *output_file;

    bool flag_help;
    bool flag_info;
    
    bool flag_line;
    bool flag_inverse_circle;
    bool flag_trim;
    bool flag_contrast;

    struct Line_config *line;
    struct Inverse_circle_config *inverse_circle;
    struct Trim_config *trim;
    struct Contrast_config *contrast;
};

struct Config *init_config();

void destroy_config(struct Config *config);

bool big_flag_is_set(const struct Config *config);

struct Config *get_options(int argc, char **argv);


#endif