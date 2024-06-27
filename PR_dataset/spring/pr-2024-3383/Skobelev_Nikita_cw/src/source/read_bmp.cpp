//
// Created by niks on 27.04.2024.
//
#include <bits/stdc++.h>
#include "../header/class_bmp.h"

void BMP::read(const char *filename){
    std::ifstream fin(filename, std::ios::binary);
    if (fin){
        fin.read((char*)&file_header, sizeof(BMP_file_header));
        if(file_header.file_type!=0x4D42){
            error_type(0);
        }
        else{
            fin.read((char*)&info_header, sizeof(BMP_info_header));
            if(info_header.size!= 40) error_type(2);
            if(info_header.bit_count!= 24) error_type(3);
            data = std::vector<std::vector<std::vector<unsigned char>>>(info_header.height,std::vector<std::vector<unsigned char>>(info_header.width,std::vector<unsigned char>(3)));
            padding.resize((4 - ((info_header.width)*3)%4)%4);
            for ( int i = 0; i < info_header.height; i++){
                for ( int j = 0; j < info_header.width; j++) {
                    fin.read((char *) (data[i][j].data()), 3);
                }
                fin.read((char *) (padding.data()),padding.size());
            }
        }
    }
    else error_type(1);
}

std::vector<int> BMP::parse(char* st, const char del){
    std::vector<int> res(0);
    char *prev = st;
    for(;*st != '\0';st++){
        if(*st == del){
            *st = '\0';
            res.push_back(atoi(prev));
            prev = st+1;
        }else{
            if(*st <'0' || *st > '9')error_type(5);
        }
    }
    res.push_back(atoi(prev));
    return res;
}

