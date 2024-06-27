#include "processing.h"
#include "bmp.h"
#include <errors.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void crop_image(bmp_file_t* image, point_t left_up, point_t right_down)
{
    rgb_t** new_rbg;
    unsigned int new_width, new_heigt, i, y, x;

    check_crop_params(image->dibh.width, image->dibh.height, &left_up, &right_down);
    new_width = right_down.x - left_up.x;
    new_heigt = right_down.y - left_up.y;
    new_rbg = (rgb_t**)malloc(new_heigt * sizeof(rgb_t*));

    for (i = 0; i < new_heigt; ++i)
        new_rbg[i] = (rgb_t*)malloc(new_width * sizeof(rgb_t));

    for (y = 0; y < new_heigt; ++y)
        for (x = 0; x < new_width; ++x)
            new_rbg[y][x] = image->rgb[left_up.y + y][left_up.x + x];

    for (i = 0; i < image->dibh.height; ++i)
        free(image->rgb[i]);
    free(image->rgb);

    image->dibh.width = new_width;
    image->dibh.height = new_heigt;
    image->dibh.image_size = new_width * new_heigt * sizeof(rgb_t);
    image->bmph.filesize = sizeof(bmp_header_t) + sizeof(dib_header_t) + image->dibh.image_size;
    image->rgb = new_rbg;
}

void process_circle(bmp_file_t* image, point_t center, int radius, rgb_t color, void (*process_pixel)(bmp_file_t*, point_t, rgb_t))
{
    point_t current, point;
    int w, h, i, j;

    w = image->dibh.width;
    h = image->dibh.height;
    for (i = center.x - radius; i <= center.x + radius; ++i) {
        for (j = center.y - radius; j <= center.y + radius; ++j) {
            current.x = i - center.x;
            current.y = j - center.y;
            if (current.x * current.x + current.y * current.y <= radius * radius) {
                point = (point_t) { i, j };
                if (check(point, w, h)) {
                    process_pixel(image, point, color);
                }
            }
        }
    }
}

void inverse_inside_circle(bmp_file_t* image, point_t point, int radius)
{
    process_circle(image, point, radius, (rgb_t) { 0, 0, 0 }, inverse_pixel);
}

void draw_line(bmp_file_t* bmp, point_t start, point_t end, int thickness, rgb_t color)
{
    int dx, dy, sx, sy, err0, err1;

    check_thickness(thickness);
    dx = abs(end.x - start.x);
    dy = abs(end.y - start.y);
    sx = start.x < end.x ? 1 : -1;
    sy = start.y < end.y ? 1 : -1;
    err0 = dx - dy;

    while (1) {
        if (check(start, bmp->dibh.width, bmp->dibh.height)) {
            process_circle(bmp, start, thickness, color, set_pixel);
        }
        if (start.x == end.x && start.y == end.y)
            break;
        err1 = err0 * 2;
        if (err1 > -dy) {
            err0 -= dy;
            start.x += sx;
        }
        if (err1 < dx) {
            err0 += dx;
            start.y += sy;
        }
    }
}

void draw_triangle(bmp_file_t* image, point_t p0, point_t p1, point_t p2, rgb_t color, int thickness, unsigned char fill, rgb_t color_fill)
{
    point_t point;
    int min_x, max_x, min_y, max_y, x, y;

    if (fill) {
        min_x = min(p0.x, min(p1.x, p2.x));
        max_x = max(p0.x, max(p1.x, p2.x));
        min_y = min(p0.y, min(p1.y, p2.y));
        max_y = max(p0.y, max(p1.y, p2.y));

        for (y = min_y; y < max_y; ++y) {
            for (x = min_x; x < max_x; ++x) {
                point = (point_t) { x, y };
                if (point_inside_triangle(point, p0, p1, p2)) {
                    set_pixel(image, point, color_fill);
                }
            }
        }
    }
    draw_line(image, p0, p1, thickness / 2, color);
    draw_line(image, p1, p2, thickness / 2, color);
    draw_line(image, p2, p0, thickness / 2, color);
}

void circle_pixel(bmp_file_t* image, int w, int h, rgb_t color, rgb_t circle_color, int size)
{
    point_t point;
    int i, j, a, b;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if (image->rgb[i][j].b == color.b && image->rgb[i][j].g == color.g && image->rgb[i][j].r == color.r) {
                for (a = i - size; a < i + size; a++) {
                    for (b = j - size; b < j + size; b++) {
                        point = (point_t) { b, a };
                        if (check(point, w, h)) {
                            if (a != i || b != j) {
                                if (image->rgb[a][b].b != color.b && image->rgb[a][b].g != color.g && image->rgb[a][b].r != color.r)
                                    image->rgb[a][b] = circle_color;
                            }
                        }
                    }
                }
            }
        }
    }
}
#if 0
    void circle_pixel(RGB** rgb, int height, int width, RGB color, RGB circle, int s)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(rgb[i][j].b == color.b && rgb[i][j].g == color.g && rgb[i][j].r == color.r) {
                for (int a = i - s; a < i + s; a++) {
                    for (int b = j - s; b < j + s; b++) {
                        if (check_coordinates(b, a, height, width)) {
                            if (a != i || b != j) {
                                if (rgb[a][b].b != color.b || rgb[a][b].g != color.g || rgb[a][b].r != color.r) {
                                    rgb[a][b] = circle;
#endif