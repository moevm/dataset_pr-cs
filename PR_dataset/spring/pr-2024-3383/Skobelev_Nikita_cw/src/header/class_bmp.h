#ifndef CLASS_BMP_H
#define CLASS_BMP_H

#include "../header/struct_bmp.h"

class BMP {
private:
    BMP_file_header file_header;
    BMP_info_header info_header;
    std::vector <std::vector<std::vector < unsigned char>>>data;
    bool error;
    std::vector<unsigned char> padding;
public:
    BMP(int argc, char **argv);

    void read(const char *filename);

    void write(const char *filename);

    void split(int nx, int ny, int thin, std::vector<unsigned char> color);

    void filled_rects(std::vector<unsigned char> fin_color, std::vector<unsigned char> color, int th);

    void rgb_filter(const char *color, unsigned char new_color);

    void circle(int c_x, int c_y, int r, int th, std::vector<unsigned char> color, bool fill,std::vector<unsigned char> fill_color);

    void circle_for_line(int xc, int yc, int r, std::vector<unsigned char> color);

    void line(int x0, int y0, int x1, int y1, std::vector<unsigned char> color, int th);

    void error_type(short type);

    void compress(int n);

    void help();

    void info();

private:
    bool check_rec(std::vector<unsigned char> fin_color,
                   std::pair<int, int> start_low,
                   std::pair<int, int> end_low,
                   std::pair<int, int> start_high,
                   std::pair<int, int> end_high,
                   std::vector <std::vector<short>> &help_data);

    void paint(int y, int x, std::vector<unsigned char> &new_color);

public:
    std::vector<int> parse(char *st, const char del);
};
#endif