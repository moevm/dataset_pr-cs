//
// Created by niks on 29.04.2024.
//
#include "bits/stdc++.h"
#include "../header/class_bmp.h"


void BMP::rgb_filter(const char* color, unsigned char new_color) {
    int k = 0;
    switch (color[0]){
        case 'b':
            k = 0;
            break;
        case 'g':
            k = 1;
            break;
        case 'r':
            k = 2;
            break;
    }
    for(int i =0;i<info_header.height;i++){
        for(int j=0;j<info_header.width;j++){
            data[i][j][k] = new_color;
        }
    }
}