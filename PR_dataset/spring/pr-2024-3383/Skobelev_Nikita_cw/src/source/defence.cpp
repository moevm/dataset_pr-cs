//
// Created by niks on 23.05.2024.
//
#include <bits/stdc++.h>
#include "../header/class_bmp.h"

void BMP::compress(int n){
    int cntx = info_header.width/n;
    int cnty = info_header.height/n;
    int help = info_header.height%n -1;
    if(cntx == 0 || cnty == 0 || n <=0) error_type(4);
    std::vector <std::vector<std::vector < unsigned char>>>new_data(cnty, std::vector<std::vector < unsigned char>>(cntx, std::vector < unsigned char>(3)));
    for(int i = cnty; i>0;--i){
        for(int j = 0;j <cntx;++j){
            std::vector <int>tmp(3);
            for(int y = i*n + help;y>(i-1)*n + help;--y){
                //std::cout<<y<<' ';
                for(int x = j*n;x<(j+1)*n;++x){
                    tmp[0]+=data[y][x][0];
                    tmp[1]+=data[y][x][1];
                    tmp[2]+=data[y][x][2];
                }
            }
            new_data[i-1][j][0] = (unsigned char) (tmp[0]/(n*n));
            //std::cout<< tmp[0]/(n*n)<<' ';
            new_data[i-1][j][1] = (unsigned char) (tmp[1]/(n*n));
            new_data[i-1][j][2] = (unsigned char) (tmp[2]/(n*n));
        }
    }
    data = new_data;
    info_header.width = cntx;
    info_header.height = cnty;
    file_header.file_size = cntx * cnty * 3 + 54;
    padding.resize((4 - ((info_header.width)*3)%4)%4);
}