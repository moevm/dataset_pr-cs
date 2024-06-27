//
// Created by niks on 27.04.2024.
//
#include "bits/stdc++.h"
#include "../header/class_bmp.h"

void BMP::error_type(short type){
    error = true;
    std::cout <<"ERROR: ";
    switch (type){
        case 0:
            std::cout << "FILE_TYPE\n";
            break;
        case 1:
            std::cout << "OPEN_ERROR\n";
            break;
        case 2:
            std::cout << "FILE_SIZE\n";
            break;
        case 3:
            std::cout << "BIT_COUNT\n";
            break;
        case 4:
            std::cout << "OHHHH... NO SIR!!!\nincorrect data\n";
            break;
        case 5:
            std::cout << "INVALID_DIGIT\n";
            break;
    }
    exit(40);
}