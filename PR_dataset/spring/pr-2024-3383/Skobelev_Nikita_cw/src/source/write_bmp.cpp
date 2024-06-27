//
// Created by niks on 27.04.2024.
//
#include "bits/stdc++.h"
#include "../header/class_bmp.h"

void BMP::write(const char *filename){
    if(error) error_type(4);
    std::ofstream fout(filename, std::ios::binary);
    if (fout){
        fout.write((char*)&file_header, sizeof(BMP_file_header));
        fout.write((char*)&info_header, sizeof(BMP_info_header));
        for ( int i = 0; i < info_header.height; i++){
            for ( int j = 0; j < info_header.width; j++) {
                fout.write((char *) data[i][j].data(), 3);
            }
            fout.write((char *) padding.data(), padding.size());
        }
    }
}

void BMP::paint (int y, int x, std::vector<unsigned char>&new_color){
    if (y >=0 && y < info_header.height && x >=0 && x < info_header.width){
        data[y][x] = new_color;
    }
}
