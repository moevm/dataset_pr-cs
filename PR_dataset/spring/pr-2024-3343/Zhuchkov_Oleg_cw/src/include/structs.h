#ifndef structs
#define structs

#include <png.h>
#include <stdbool.h>

typedef struct {
    png_byte r, g, b;
} rgb_t;

typedef struct {
    png_structp png_ptr;
    png_infop info_ptr;
    png_byte bit_depth, color_type;
    int number_passes;
    int width, height;
    png_bytepp rows;
} png_t;

typedef struct{
    char* input;
    char* output;
    bool info;
    bool help;

    bool rect;
    int left_up_x;
    int left_up_y;
    int right_down_x;
    int right_down_y;
    int thickness;
    rgb_t color;
    bool fill;
    rgb_t fill_color;
    bool color_input;
    bool fcolor_input;

    bool hexagon;
    int center_x;
    int center_y;
    int radius;

    bool copy;
    int dest_left_up_x;
    int dest_left_up_y;

    bool blur;
    int size;
} params_t;
#endif