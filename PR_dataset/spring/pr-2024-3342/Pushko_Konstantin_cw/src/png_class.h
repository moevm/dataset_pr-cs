#ifndef PNG_CLASS_H
#define PNG_CLASS_H

#include <png.h>
#include <iostream>
#include <cmath>

class Png {
public:
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_byte channels;
    png_structp png_ptr;
    png_infop info_ptr;
    png_byte **row_pointers;

    Png();
    ~Png();

    void print_png_info();
    Png* create_collage(int size_x, int size_y);
    void recolor_biggest_rect(int old_color[],int new_color[]);
    void draw_triangle(int x0, int y0, int x1,int y1,int x2,int y2,int color[], float thickness, bool is_fill = false, int fill_color[] = NULL);
    void draw_line(int x0, int y0, int x1,int y1,int color[], float thickness);
    void rhombus(int color[]);

private:
    void set_pixel(int x, int y, int color[]);
    bool is_point_in_image(int x, int y);
    bool check_pixel_color(int x0,int y0,int color[]);
    void fill_circle(int x0,int y0,float thickness, int color[]);
    bool is_point_in_triangle(int x, int y,int x0, int y0, int x1,int y1,int x2,int y2);
    void fill_triangle(int x0, int y0, int x1,int y1,int x2,int y2,int color[]);
    void insert_image(Png* image,int x0,int y0);
    void fill_rect(int x0,int y0,int x1,int y1,int color[]);
    bool is_rect_filled(int x0,int y0,int x1,int y1,int color[]);
};


#endif

