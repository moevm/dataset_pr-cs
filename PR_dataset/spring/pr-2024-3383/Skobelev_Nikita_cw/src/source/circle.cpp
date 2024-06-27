//
// Created by niks on 29.04.2024.
//
#include "bits/stdc++.h"
#include "../header/class_bmp.h"

void BMP::circle(int c_x, int c_y, int r, int th,std::vector<unsigned char>color, bool fill, std::vector<unsigned char>fill_color){
    c_y = info_header.height-c_y;
    int thvn = th / 2;
    int thna = th - thvn;
    for(int i = c_y - r - th; i <= c_y + r + th; i++){
        for(int j = c_x - r - th; j <= c_x + r + th; j++) {
            long long point = (i - c_y) * (i - c_y) + (j - c_x) * (j - c_x);
            if (fill) {
                if (point < r * r) {
                    paint (i, j, fill_color);
                }
            }
            if (point >= (r-thvn) * (r-thvn) && point < (r + thna) * (r + thna)) {
                paint(i, j, color);
            }
        }
    }
}

void BMP::line(int x0, int y0, int x1, int y1, std::vector<unsigned char>color, int th){
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1)? 1 : -1;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        std:: cout<< "OK";
        if (steep) {
            circle(y, x, th/2, 0, color, true, color);
        } else {
            circle(x, y, th/2, 0, color, true, color);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void BMP::circle_for_line(int xc, int yc, int r, std::vector<unsigned char> color){
    for(int x = std::max(0, xc - r); x < std::min(xc+r+1, info_header.width);++x){
        for(int y = std::max(0, yc - r); y < std::min(yc+r+1, info_header.height);++y){
            if((x-xc)*(x-xc) + (y-yc)*(y-yc) <= r*r){std::cout<<x<<' '<<y<<'\n';
                paint(y,x,color);
            }
        }
    }
}

//void BMP::line(int x0, int y0, int x1, int y1, std::vector<unsigned char>color, int th ){
//    y0 = info_header.height - y0-1;
//    y1 = info_header.height - y1-1;
//    int dx = abs(x1 - x0), sx = x0 < x1 ? 1:-1;
//    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1:-1;
//    int error = dx + dy;
//    while(true) {
//        std::cout<< x0<<' '<<x1<<'\n';
//        if (x0 - th / 2 < info_header.width && x0 + th / 2 >= 0 && y0 - th / 2 < info_header.height && y0 + th / 2 >= 0)
//            circle_for_line(x0, y0, th / 2, color);
//        if (x0 == x1 && y1 == y0)
//            break;
//        if (2*error >= dy){
//            error += dy; x0 += sx;
//        }
//        if(2*error <= dx) {
//            error += dx; y0 += sy;
//        }
//    }
//}