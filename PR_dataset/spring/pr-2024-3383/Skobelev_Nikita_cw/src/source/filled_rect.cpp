//
// Created by niks on 28.04.2024.
//
#include <bits/stdc++.h>
#include "../header/class_bmp.h"

bool BMP::check_rec(std::vector<unsigned char>fin_color,
                    std::pair<int, int> start_low,
                    std::pair<int, int> end_low,
                    std::pair<int, int> start_high,
                    std::pair<int, int> end_high,
                    std::vector<std::vector<short>>&help_data){
    bool check = true;
    if(start_high.first != end_high.first) return false;
    for(int i = start_low.second; i <= end_low.second; i++){
        if(start_low.first-1 > 0)
        if(help_data[start_low.first-1][i] != 0 ){
            check = false;
            break;
        }
        if(start_high.first+1 < info_header.height)
        if(help_data[start_high.first+1][i] != 0){
            check = false;
            break;
        }
    }
    for(int i = start_low.first; i <= end_high.first; i++){
        if(start_low.second-1 > 0)
        if(help_data[i][start_low.second-1] != 0){
            check = false;
            break;
        }
        if(end_high.second+1 < info_header.width){
            if(help_data[i][end_high.second+1] != 0) {
                check = false;
                break;
            }
        }
    }
    for(int i = start_low.first; i <= start_high.first; i++){
        for(int j = start_low.second; j <= end_low.second; j++) {
            if (help_data[i][j] != 1) {
                check = false;
                break;
            }
        }
    }
    return check;
}


void BMP::filled_rects(std::vector<unsigned char>fin_color, std::vector<unsigned char>color,int th){
    std::vector<std::vector<short>>help_data(info_header.height, std::vector<short>(info_header.width));
    for(int i = 0; i < info_header.height; i++){
        for(int j = 0; j < info_header.width; j++) {
            if (data[i][j] == fin_color) {
                help_data[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < info_header.height; i++){
        for(int j = 0; j < info_header.width; j++){
            if(help_data[i][j] == 1){
                std::pair<int,int> start_low , end_low, start_high, end_high;
                start_low = {i,j}, end_low = {i,j};
                while(end_low.second < info_header.width && help_data[end_low.first][end_low.second] == 1){
                    end_low.second++;
                    if(end_low.second == info_header.width) break;
                }
                end_low.second--;
                start_high = start_low;
                end_high = end_low;
                while(start_high.first < info_header.height && help_data[start_high.first][start_high.second] == 1){
                    start_high.first++;
                }
                start_high.first--;
                while(end_high.first < info_header.height && help_data[end_high.first][end_high.second] == 1){
                    end_high.first++;
                }
                end_high.first--;
                j = end_low.second;

                if(check_rec(fin_color, start_low, end_low, start_high, end_high, help_data)) {
                    for (int i1 = start_low.first; i1 <= end_high.first; i1++) {
                        for (int j1 = start_low.second; j1 <= end_low.second; j1++) {
                            help_data[i1][j1] = 0;
                        }
                    }
                    for (int i1 = start_low.first; i1 <= end_high.first; i1++) {
                        for (int l = 0; l < th; l++) {
                            paint(i1, start_low.second + l, color);
                            paint(i1, end_low.second - l, color);
                        }
                    }
                    for (int i1 = start_low.second; i1 <= end_low.second; ++i1) {
                        for (int l = 0; l < th; l++) {
                            paint(start_low.first + l, i1, color);
                            paint(end_high.first - l, i1, color);
                        }
                    }
                }
            }
        }
    }
}
