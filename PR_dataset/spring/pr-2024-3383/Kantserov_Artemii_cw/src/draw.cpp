#include "draw.h"
#include <png.h>
//#include "/opt/homebrew/include/png.h"
#include "struct_png.h"
#include <cmath>
#include <iostream>

using namespace std;

void set_pixel(struct Png* image, int x, int y, int* color){
    png_byte *row = image->row_pointers[y];
    row[x * 3] = color[0];
    row[x * 3 + 1] = color[1];
    row[x * 3 + 2] = color[2];
}

void draw_circle(struct Png* png, int xc, int yc, int radius, int* color) {
    for (int x = max(0, xc-radius); x < min(xc+radius+1,png->width); x++) {
        for (int y = max(0,yc-radius); y < min(yc+radius+1, png->height); y++) {
            if ((x-xc)*(x-xc) + (y-yc)*(y-yc) <= radius*radius) {
                set_pixel(png, x, y, color);
            }
        }
    }
}

void diagonal(struct Png* image, int* cor1, int* cor2, int thickness, int* color) {
    int x1 = cor2[0], y1 = cor2[1];
    int x0 = cor1[0], y0 = cor1[1];
    int dx = abs(x1 - x0), sx = x0 < x1? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        if(x0 - thickness/2 < image -> width && x0 + thickness/2 >=0 && y0 - thickness/2< image -> height && y0 + thickness/2>=0)
            draw_circle(image, x0, y0, thickness/2, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void fill_rect(struct Png* image, int* cor1, int *cor2, int* color_fill){
    int x, y;
    for (y = min(cor1[1], cor2[1]); y < max(cor1[1], cor2[1]); y++) {
        for (x = min(cor1[0], cor2[0]); x < max(cor1[0], cor2[0]); x++) {
            if ((x < 0 || x >= image->width) || (y < 0 || y >= image->height)) {
                continue;
            }
            set_pixel(image, x, y, color_fill);
        }
    }
}

void rect(struct Png* image, int* cor1, int *cor2, int thickness, int* color, int fill, int* color_fill) {
    int k1[2] = {cor1[0], cor1[1]};
    int k2[2] = {cor2[0], cor1[1]};
    int k3[2] = {cor2[0], cor2[1]};
    int k4[2] = {cor1[0], cor2[1]};
    if (fill) fill_rect(image, cor1, cor2, color_fill);
    diagonal(image, k4, k1, thickness, color);
    diagonal(image, k1, k2, thickness, color);
    diagonal(image, k2, k3, thickness, color);
    diagonal(image, k3, k4, thickness, color);
}

void draw_circle_points(struct Png* png, int xc, int yc, int x, int y, int* color, int thickness){
    draw_circle(png, xc + x, yc + y, thickness / 2, color);
    draw_circle(png, xc - x, yc + y, thickness / 2, color);
    draw_circle(png, xc + x, yc - y, thickness / 2, color);
    draw_circle(png, xc - x, yc - y, thickness / 2, color);
    draw_circle(png, xc + y, yc + x, thickness / 2, color);
    draw_circle(png, xc - y, yc + x, thickness / 2, color);
    draw_circle(png, xc + y, yc - x, thickness / 2, color);
    draw_circle(png, xc - y, yc - x, thickness / 2, color);
}

void star(struct Png* image, int* center, int radius, int* color, int thickness) {
    double pi = M_PI;
    int cor1[2] = {(int)(radius * cos(-pi/10) + center[0]), (int)(radius * sin(-pi/10) + center[1])};
    int cor2[2] = {(int)(radius * cos(-pi/10 + 2*pi/5) + center[0]), (int)(radius * sin(-pi/10 + 2*pi/5) + center[1])};
    int cor3[2] = {(int)(radius * cos(-pi/10 + 4*pi/5) + center[0]), (int)(radius * sin(-pi/10 + 4*pi/5) + center[1])};
    int cor4[2] = {(int)(radius * cos(-pi/10 + 6*pi/5) + center[0]), (int)(radius * sin(-pi/10 + 6*pi/5) + center[1])};
    int cor5[2] = {(int)(radius * cos(-pi/10 + 8*pi/5) + center[0]),  (int)(radius * sin(-pi/10 + 8*pi/5) + center[1])};
    diagonal(image, cor1, cor3, thickness, color);
    diagonal(image, cor4, cor1, thickness, color);
    diagonal(image, cor2, cor4, thickness, color);
    diagonal(image, cor2, cor5, thickness, color);
    diagonal(image, cor3, cor5, thickness, color);
}

void circle(struct Png* image, int* center, int radius, int* color, int thickness) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    int xc = center[0], yc = center[1];
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        draw_circle_points(image, xc, yc, x, y, color, thickness);
    }
}

double triangle_area(int* cor1, int* cor2, int* cor3) {
    double area = abs(0.5 * ((cor1[0] - cor3[0]) * (cor2[1] - cor3[1]) - (cor2[0] - cor3[0]) * (cor1[1] - cor3[1])));
    return area;
}

void triangle_fill(struct Png* image, int* cor1, int* cor2, int* cor3, int* color_fill) {
    int x, y;
    int x_min = min(cor1[0], min(cor2[0], cor3[0]));
    int x_max = max(cor1[0], max(cor2[0], cor3[0]));
    int y_min = min(cor1[1], min(cor2[1], cor3[1]));
    int y_max = max(cor1[1], max(cor2[1], cor3[1]));
    for (x = x_min; x < x_max; x++) {
        for (y = y_min; y < y_max; y++) {
            int cor4[2] = {x, y};
            if (abs(triangle_area(cor4, cor1, cor2) + triangle_area(cor4, cor2, cor3) + triangle_area(cor4, cor3, cor1) - triangle_area(cor1, cor2, cor3)) == 0) {
                if ((x < 0 || x >= image->width) || (y < 0 || y >= image->height)) {
                    continue;
                }
                set_pixel(image, x, y, color_fill);
            }
        }
    }
}

void hexagon(struct Png* image, int* center, int radius, int thickness, int* color, bool fill, int* color_fill) {
    double pi = M_PI;
    int cor1[2] = {(int)(radius * cos(0) + center[0]), (int)(radius * sin(0) + center[1])};
    int cor2[2] = {(int)(radius * cos(pi/3) + center[0]), (int)(radius * sin(pi/3) + center[1])};
    int cor3[2] = {(int)(radius * cos(2*pi/3) + center[0]), (int)(radius * sin(2*pi/3) + center[1])};
    int cor4[2] = {(int)(radius * cos(pi) + center[0]), (int)(radius * sin(pi) + center[1])};
    int cor5[2] = {(int)(radius * cos(4*pi/3) + center[0]),  (int)(radius * sin(4*pi/3) + center[1])};
    int cor6[2] = {(int)(radius * cos(5*pi/3) + center[0]), (int)(radius * sin(5*pi/3) + center[1])};
    if (fill) {
        fill_rect(image, cor3, cor6, color_fill);
        triangle_fill(image, cor1, cor2, cor6, color_fill);
        triangle_fill(image, cor3, cor4, cor5, color_fill);
    }
    diagonal(image, cor1, cor2, thickness, color);
    diagonal(image, cor2, cor3, thickness, color);
    diagonal(image, cor3, cor4, thickness, color);
    diagonal(image, cor4, cor5, thickness, color);
    diagonal(image, cor5, cor6, thickness, color);
    diagonal(image, cor6, cor1, thickness, color);
}

void pentagram(struct Png* image, int* center, int radius, int thickness, int* color) {
    if(!(center[0] - thickness/2 < image -> width && center[0] + thickness/2 >=0 && center[1]-thickness/2 < image -> height && center[1] + thickness/2 >=0)) return;
    circle(image, center, radius, color, thickness);
    star(image, center, radius, color, thickness);
}