#ifndef STRUCTS_H
#define STRUCTS_H
#define thickness_error 40
#define coords_error 41
#define broken_file_error 42
#define openning_error 43
#define format_error 44
#define color_error 45
#define wrong_value 46
#define draw_rect 1
#define draw_hex 2
#define copy_area 3
#define draw_smooth_rect 4
#define bin 5
#include <png.h>

typedef struct png {
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep* row_pointers;
} png_t;

typedef struct ipoint {
    int x;
    int y;
} ipoint_t;

typedef struct color {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} color_t;

const char* all_funcs_short_opts = "T:BRSHCIhi:u:d:t:c:fl:o:O:r:p:";

const struct option all_funcs[] = {
    {"rect", no_argument, 0, 'R'},
    {"binarization", no_argument, 0, 'B'},
    {"smooth_rect", no_argument, 0, 'S'},
    {"hexagon", no_argument, 0, 'H'},
    {"copy", no_argument, 0, 'C'},
    {"info", no_argument, 0, 'I'},
    {"help", no_argument, 0, 'h'},
    {"input", required_argument, 0, 'i'},
    {"threshold", required_argument, 0, 'T'},
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'd'},
    {"thickness", required_argument, 0, 't'},
    {"color", required_argument, 0, 'c'},
    {"fill", no_argument, 0, 'f'},
    {"fill_color", required_argument, 0, 'l'},
    {"output", required_argument, 0, 'o'},
    {"center", required_argument, 0, 'O'},
    {"radius", required_argument, 0, 'r'},
    {"dest_left_up", required_argument, 0, 'p'},
    { NULL, 0, NULL, 0 }
};

#endif