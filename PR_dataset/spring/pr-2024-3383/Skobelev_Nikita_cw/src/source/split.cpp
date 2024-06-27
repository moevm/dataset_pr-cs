//
// Created by nikit on 28.04.2024.
//
#include <bits/stdc++.h>
#include "../header/class_bmp.h"


void BMP::split(int nx, int ny, int thin, std::vector<unsigned char> color){
    int step = info_header.width / nx;
    int start_x = step + info_header.width % nx;
    for(int i = start_x; i < info_header.width; i += step){
        for(int th = 0; th <= thin/2; th++) {
            for (int j = 0; j < info_header.height; j++) {
                paint(j, i + th, color);
                paint(j, i - th, color);
            }
        }
    }
    step = info_header.height / ny;
    int start_y = step + info_header.height % ny;
    for(int i = start_y; i < info_header.height; i += step){
        for(int th = 0; th <= thin/2; th++) {
            for (int j = 0; j < info_header.width; j++) {
                paint(i + th, j, color);
                paint(i - th, j, color);
            }
        }
    }

}