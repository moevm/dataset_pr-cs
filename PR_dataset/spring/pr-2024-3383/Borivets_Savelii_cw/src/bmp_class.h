#ifndef COURSE_BMP_CLASS_H
#define COURSE_BMP_CLASS_H

#include "my_lib.h"
#include "collectoprover.h"

class Bitmap {
public:
    void read_bmp(string filename);
    void write_bmp(string filename);
    void print_file_header();
    void print_info_header();
    unsigned int get_height();
    unsigned int get_width();
    void rgbfilter(string component_name, unsigned char component_value);
    void pix_puter(int x, int y, Rgb color);
    void square(int left, int up, int side_size, int thickness, Rgb color, bool fill, Rgb fill_color);
    vector<vector<Rgb>> part_taker(int left, int up, int right, int down);
    void part_placer(int left, int up, vector<vector<Rgb>> part);
    void exchange(int left, int up, int right, int down, char exchange_type);
    void freq_color(Rgb color);
    void fill_circle(int Xmid, int Ymid, int r, Rgb color);
    void line(int x0, int y0, int x1, int y1, int thickness, Rgb color);
    void outside_ornament(int thickness, Rgb color);
private:
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;
    unsigned int H;
    unsigned int W;
    vector<vector<Rgb>> pixels;
};


#endif //COURSE_BMP_CLASS_H
