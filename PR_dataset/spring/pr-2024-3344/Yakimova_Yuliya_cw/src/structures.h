#pragma once

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;  //число проходов для полной обработки изображения
    png_bytep *row_pointers;
}; 

struct Color{ 
    char* old_color;
    char* new_color;

    int old_color_f;
    int new_color_f;
};

struct Copy{
    char* left_up;
    char* right_down;
    char* dest_left_up;

    int left_up_f;
    int right_down_f;
    int dest_left_up_f;
};

struct Ornament{
    char* pattern;
    char* color;
    char* thickness;
    char* count;

    int pattern_f;
    int color_f;
    int thickness_f;
    int count_f;
};

struct Filled_Rect {
    char* color;
    char* border_color;
    char* thickness;

    int color_f;
    int border_color_f;
    int thickness_f;
};

struct Coordinates {
    int x0, y0, x1, y1;
};

struct Circle_Pix {
    char* size;
    char* color;
    char* circle_color;

    int size_f;
    int color_f;
    int circle_color_f;
};