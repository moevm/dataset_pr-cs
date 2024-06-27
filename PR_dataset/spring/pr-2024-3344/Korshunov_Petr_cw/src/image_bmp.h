#ifndef IMG_BMP_H
#define IMG_BMP_H

#include "structs.h"

class Image
{

public:
    BitmapInfoHeader bmif;
    BitmapFileHeader bmfh;
    unsigned int H;
    unsigned int W;
    Rgb **arr;

    Image(string bmp_name)
    {
        arr = read_bmp(bmp_name);
        H = bmif.height;
        W = bmif.width;
    }

    ~Image()
    {
        for (int i = 0; i < H; ++i)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    void printFileHeader();

    void printInfoHeader();

    void outside_ornament(int thickness, Rgb color);

    void set_pixel(Rgb &pix, Rgb new_pix);

    void swap_pixel(Rgb &pix, Rgb &new_pix);

    void fill_zone(int i, int j, Rgb border);

    void plort_circle(int x, int y, int x0, int y0, Rgb new_pix, int thickness);

    // Модифицированный пример из книги Г.Шилдта «Си для профессиональных программистов» (алгоритм мичнера)
    void draw_circle(int y0, int x0, int radius, Rgb new_pix, bool isfill = false, int thickness = 0, bool fillcolor = false, Rgb new_in_pix = {0, 0, 0});

    void draw_line(int x1, int y1, int x2, int y2, Rgb &new_pix, int thickness = 0);

    void rgbfilter(string comp_n, int comp_v);

    void draw_square(int h, int w, int side_size, Rgb new_pix, int thickness = 1, bool isfill = false, Rgb new_in_pix = {0, 0, 0});

    void exchange(int left_up[], int right_down[], string exchange_type);

    Rgb get_frequent();

    void swap_frequent(Rgb new_pix);

    Rgb **read_bmp(string bmp_name);

    void write_bmp(string bmp_name);

private:
    bool check_coords(int y, int x) { return !(y < 0 || y >= H || x < 0 || x >= W); }
};

#endif