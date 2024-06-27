#include "pixels.h"
#include "bmp.h"

int check(point_t point, int w, int h)
{
    return point.x >= 0 && point.x < w && point.y >= 0 && point.y < h;
}

void set_pixel(bmp_file_t* bmpf, point_t point, rgb_t color)
{
    if (check(point, bmpf->dibh.width, bmpf->dibh.height)) {
        bmpf->rgb[point.y][point.x] = color;
    }
}

void inverse_pixel(bmp_file_t* image, point_t point, rgb_t color)
{
    rgb_t* pixel = &image->rgb[point.y][point.x];
    pixel->r = 255 - pixel->r;
    pixel->g = 255 - pixel->g;
    pixel->b = 255 - pixel->b;
}

int point_inside_triangle(point_t p, point_t v0, point_t v1, point_t v2)
{
    int as_x, as_y, s_ab;

    as_x = p.x - v0.x;
    as_y = p.y - v0.y;
    s_ab = (v1.x - v0.x) * as_y - (v1.y - v0.y) * as_x > 0;

    if (((v2.x - v0.x) * as_y - (v2.y - v0.y) * as_x > 0) == s_ab) {
        return 0;
    }
    if (((v2.x - v1.x) * (p.y - v1.y) - (v2.y - v1.y) * (p.x - v1.x) > 0) != s_ab) {
        return 0;
    }
    return 1;
}