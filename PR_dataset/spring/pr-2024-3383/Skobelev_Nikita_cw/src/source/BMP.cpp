//
// Created by niks on 27.04.2024.
//
#include "../header/class_bmp.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include <getopt.h>

BMP::BMP(int argc, char** argv) {
    char *filename;
    int opchar = 0;
    int what = 0;
    std::vector<int>v;
    std::vector<unsigned char>color;
    std::vector<unsigned char>border_color;
    int thickness = 0;
    int center_x = 0;
    int center_y = 0;
    int radius = 0;
    bool fill = 0;
    std::vector<unsigned char>fill_color;
    char *component_name;
    int component_value;
    int number_x = 0;
    int number_y = 0;
    char outputh[] ="out.bmp";
    char *output = outputh;
    char *input = argv[argc-1];
    int a;
    int num;
    struct option opts[] = {
            {"filled_rects", no_argument, &what, 'f'},
            {"circle", no_argument, &what, 'c'},
            {"rgbfilter", no_argument, &what, 'r'},
            {"split", no_argument, &what, 's'},
            {"help", no_argument, NULL, 'h'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},
            {"compress", no_argument, NULL, 'p'},
            {"color", required_argument, NULL, 1},
            {"border_color", required_argument, NULL, 2},
            {"thickness", required_argument, NULL, 3},
            {"center", required_argument, NULL, 4},
            {"radius", required_argument, NULL, 5},
            {"fill", no_argument, NULL, 6},
            {"fill_color", required_argument, NULL, 7},
            {"component_name", required_argument, NULL, 8},
            {"component_value", required_argument, NULL, 9},
            {"number_x", required_argument, NULL, 10},
            {"number_y", required_argument, NULL, 11},
            {"info", no_argument, NULL, 12},
            {"num", required_argument, NULL,13},
            {0,0,0,0},
    };
    std::vector<short> cnt(12);
    while (-1 != (opchar = getopt_long(argc, argv, "fcrshp", opts, NULL))) {
        switch (opchar) {
            case 'f':
                if (what != 0) error_type(4);
                what = 'f';
                break;
            case 'c':
                if (what != 0) error_type(4);
                what = 'c';
                break;
            case 'r':
                if (what != 0) error_type(4);
                what = 'r';
                break;
            case 's':
                if (what != 0) error_type(4);
                what = 's';
                break;
            case 'h':
                if (what != 0) error_type(4);
                what = 'h';
                break;
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 'p':
                what = 'p';
                break;
            case 1:
                cnt[1] ++;
                v = parse(optarg, '.');
                color.resize(v.size());
                if(v[0] > 255 || v[1] > 255 || v[2] > 255)error_type(4);
                std::copy(v.rbegin(), v.rend(), color.begin());
                break;
            case 2:
                cnt[2] ++;
                v = parse(optarg, '.');
                border_color.resize(v.size());
                if(v[0] > 255 || v[1] > 255 || v[2] > 255)error_type(4);
                std::copy(v.rbegin(), v.rend(), border_color.begin());
                break;
            case 3:
                cnt[3] ++;
                thickness = atoi(optarg);
                if(thickness < 1)error_type(4);
                break;
            case 4:
                cnt[4] ++;
                v = parse(optarg,'.');
                center_x = v[0];
                center_y = v[1];
                break;
            case 5:
                cnt[5] ++;
                radius = atoi(optarg);
                if(radius < 1)error_type(4);
                break;
            case 6:
                fill = 1;
                break;
            case 7:
                cnt[7] ++;
                v = parse(optarg, '.');
                fill_color.resize(v.size());
                if(v[0] > 255 || v[1] > 255 || v[2] > 255)error_type(4);
                std::copy(v.rbegin(), v.rend(), fill_color.begin());
                break;
            case 8:
                cnt[8] ++;
                component_name = optarg;
                break;
            case 9:
                cnt[9] ++;
                component_value = atoi(optarg);
                if(component_value < 0 || component_value > 255)error_type(4);
                break;
            case 10:
                cnt[10] ++;
                number_x = atoi(optarg);
                if(number_x < 2)error_type(4);
                break;
            case 11:
                cnt[11] ++;
                number_y = atoi(optarg);
                if(number_y < 2)error_type(4);
                break;
            case 12:
                if (what != 0) error_type(4);
                what = 'i';
                break;
            case 13:
                num = atoi(optarg);
                std::cout<<num;
                break;
        }
    }
    int kol = 0;
    for(int i = 0; i < cnt.size(); i++){
        kol += cnt[i];
    }
    error = false;
    if(strcmp(input, output) == 0)error_type(4);
    if(what != 'h')
    read(input);
    switch (what) {
        case 'f':
            if(kol == 3 && cnt[1] == 1 && cnt[2] == 1 && cnt[3] == 1)filled_rects(color, border_color, thickness);
            else error_type(4);
            break;
        case 'c':
            if(kol == 5 && cnt[4] == 1 && cnt[5] == 1 && cnt[3] == 1 && cnt[1] == 1  && cnt[7] == 1)circle(center_x, center_y, radius, thickness, color, fill, fill_color);
            else error_type(4);
            break;
        case 'r':
            if(kol== 2 && cnt[8] == 1 && cnt[9] == 1)rgb_filter(component_name, component_value);
            else error_type(4);
            break;
        case 's':
            if(kol == 4 &&  cnt[11] == 1 && cnt[10] == 1 && cnt[3] == 1 && cnt[1] == 1)split(number_x, number_y, thickness, color);
            else error_type(4);
            break;
        case 'h':
            if(kol == 0)help();
            else error_type(4);
            break;
        case 'i':
            if(kol == 0)info();
            else error_type(4);
            break;
        case 'p':
            compress(num);
            break;
    }
    if(what!= 'h' && what !='i')
        write(output);
}