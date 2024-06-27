#pragma once


typedef struct {
    unsigned int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep* row_pointers;
} Png;

typedef struct {
    int xy1[2];
    int xy2[2];
    int xy3[2];
    int base_color[3];
    int fill_color[3];
    int thickness;
    int number_y, number_x;
} args;

typedef struct {
    int input_file;
    int points;
    int color; 
    int tickness;
    int fill;
    int fill_or_new_color;
    int start_or_number_x;
    int end_or_number_y;
    int main_flag;
    int num;
} flags;

void comr(Png* img, Png* new_img, int);
void check_extra_arg(char* str, char* flag, int number_arguments, int next_ind, int max_ind, int flag_input_file);
int* string_tok(char* string_arg, int size);
int is_digit(char* string_digit);
void read_png_file(char* file_name, Png* image);
void write_png_file(char* file_name, Png* image);
void free_image_data(Png* img); 
void print_help();
void print_png_info(Png* img);
int is_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
void draw_triangle(Png* img, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int* line_color, int fill, int* fill_color);
void recolor_max_rectangle(Png* img, int* old_color, int* new_color);
void make_collage(Png* img, Png* new_img, int n, int m);
void draw_thick_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* line_color);