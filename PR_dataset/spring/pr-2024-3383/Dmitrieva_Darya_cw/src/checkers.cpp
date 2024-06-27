#include "checkers.h"

Point* PointChecker(string input) {
    istringstream iss(input);
    int x, y;
    char dot;
    iss >> x >> dot >> y;
    if (iss.fail() || !iss.eof() || dot != '.'){
        return nullptr;
    }
    Point* p = new Point{x, y};
    return p;
}

Tuple* RgbChecker(string input) {
    istringstream iss(input);
    unsigned int r, g, b;
    char dot;
    iss >> r >> dot >> g >> dot >> b;
    if (iss.fail() || !iss.eof() || dot != '.'|| r > 255 || g > 255 || b > 255){
        return nullptr;
    }
    Tuple* t = new Tuple{(unsigned char)r,(unsigned char)g,(unsigned char)b};
    return t;
}

Size* ResizeChecker(string input){
    istringstream iss(input);
    int value;
    iss >> value;
    if (iss.fail() || !iss.eof()){
        return nullptr;
    }
    Size* s = new Size{value};
    return s;
    
}
