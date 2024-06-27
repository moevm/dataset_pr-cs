#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include "BMP.hpp"
#include "functions.hpp"
#include "secondary_functions.hpp"
#include "check_functions.hpp"


using namespace std;


int 
checkMirrorValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int left, up, right, down, isCorrect;
    char axis;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "m") return 0;
        
        if (dict[i].first == "A") {
            if (dict[i].second.length() != 1 || (dict[i].second != "x" && dict[i].second != "y")) {
                cerr << "Введено некорректное значение для флага --axis\n";
                return 0;
            }
            axis = dict[i].second[0];

        } else if (dict[i].first == "L") {
            isCorrect = stringDecomposeFunc(&left, &up, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --left_up\n";
                return 0;
            }

        } else if (dict[i].first == "R") {
            isCorrect = stringDecomposeFunc(&right, &down, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --right_down\n";
                return 0;
            }
        
        } else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "m") {
            continue;
        
        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 3) {
        checkCoords(&left, &up, &right, &down, H, W);
        mirrorFunc(arr, axis, left, up, right, down, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции\n";
        return 0;
    }
    return 1;
}


int 
checkCopyValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int left, up, right, down, newLeft, newUp, isCorrect;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "c") return 0;
        
        if (dict[i].first == "L") {
            isCorrect = stringDecomposeFunc(&left, &up, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --left_up\n";
                return 0;
            }
        } else if (dict[i].first == "R") {
            isCorrect = stringDecomposeFunc(&right, &down, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --right_down\n";
                return 0;
            }
        } else if (dict[i].first == "D") {
            isCorrect = stringDecomposeFunc(&newLeft, &newUp, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --dest_left_up\n";
                return 0;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "c") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 3) {
        down = H - down - 1;
        up = H - up - 1;
        checkCoords(&left, &down, &right, &up, H, W);
        copyFunc(arr, left, up, right, down, newLeft, H - newUp - 1, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
        return 0;
    }
    return 1;
}


int
checkReplaceValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int r, g, b, newR, newG, newB, isCorrect;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "r") return 0;
        
        if (dict[i].first == "O") {
            isCorrect = colorDecomposeFunc(&r, &g, &b, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --old_color\n";
                return 0;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное знаение компоненты цвета\n";
                return 0;
            }
        } else if (dict[i].first == "N") {
            isCorrect = colorDecomposeFunc(&newR, &newG, &newB, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --new_color\n";
                return 0;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное знаение компоненты цвета\n";
                return 0;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "r") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 2) {
        replaceFunc(arr, r, g, b, newR, newG, newB, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
        return 0;
    }
    return 1;
}


int
checkFilterValues(vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    string component;
    size_t compVal;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "f") return 0;

        if (dict[i].first == "C") {
            component = dict[i].second;
            if (component != "red" && component != "blue" && component != "green") {
                cerr << "Введено некорректное значение для флага --component_name\n";
                return 0;
            }
        } else if (dict[i].first == "V") {
            stringstream s;
            s << dict[i].second;
            s >> compVal;
            if (s.str() != to_string(compVal) || compVal < 0 || compVal > 255) {
                cerr << "Введено некорректное значение для флага --component_value\n";
                return 0;
            }
        }else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "f") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 2) {
        filterFunc(arr, component, compVal, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции\n";
        return 0;
    }
    return 1;
}


int
checkCircleValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int x, y, radius, r, g, b, isCorrect;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "z") return 0;

        if (dict[i].first == "Z") {
            isCorrect = stringDecomposeFunc(&x, &y, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --center\n";
                return 0;
            }
        } else if (dict[i].first == "y") {
            stringstream s;
            s << dict[i].second;
            s >> radius;
            if (s.str() != to_string(radius) || radius <= 0) {
                cerr << "Введено некорректное значение для флага --radius\n";
                return 0;
            }
        } else if (dict[i].first == "Y") {
            isCorrect = colorDecomposeFunc(&r, &g, &b, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --old_color\n";
                return 0;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное значение компоненты цвета\n";
                return 0;
            }
        }else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "z") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 3) {
        circleFunc(arr, x, y, radius, r, g, b, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции\n";
        return 0;
    }
    return 1;
}


int 
checkLineValues(vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int x1, y1, x2, y2, thickness, r, g, b, isCorrect;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "x") return 0;

        if (dict[i].first == "X") {
            isCorrect = stringDecomposeFunc(&x1, &y1, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --start\n";
                return 0;
            }
        } else if (dict[i].first == "w") {
            isCorrect = stringDecomposeFunc(&x2, &y2, dict[i].second);
            if (isCorrect != 1) {
                cerr << "Введено некорректное значение для флага --end\n";
                return 0;
            }
        } else if (dict[i].first == "Y") {
            isCorrect = colorDecomposeFunc(&r, &g, &b, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --color\n";
                return 0;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное значение компоненты цвета\n";
                return 0;
            }
        } else if (dict[i].first == "W") {
            stringstream s;
            s << dict[i].second;
            s >> thickness;
            if (s.str() != to_string(thickness) || thickness < 0) {
                cerr << "Введено некорректное значение для флага --thickness\n";
                return 0;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "x") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 4) {
        lineFunc(arr, x1, y1, x2, y2, r, g, b, thickness, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции\n";
        return 0;
    }
    return 1;
}


int 
checkAValues(std::vector <std::pair<std::string, std::string>> dict, Rgb** arr, BitmapInfoHeader bmif, BitmapFileHeader bmfh, std::string file) {
    unsigned short int countValues = 0;
    int thickness, r, g, b, isCorrect;

    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].second == "NULL" && dict[i].first != "p") return 0;

        if (dict[i].first == "Y") {
            isCorrect = colorDecomposeFunc(&r, &g, &b, dict[i].second);
            if (isCorrect == 1) {
                return 2;
            }
            if (isCorrect == 2) {
                return 2;
            }
        } else if (dict[i].first == "W") {
            stringstream s;
            s << dict[i].second;
            s >> thickness;
            if (s.str() != to_string(thickness) || thickness <= 0) {
                return 2;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o" || dict[i].first == "p") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции\n";
            return 0;
        }
        countValues++;
    }

    if (countValues == 2) {
        AFunc(arr, r, g, b, thickness, bmif, bmfh, file);
    } else {
        cerr << "Введены не все флаги, необходимые для опции\n";
        return 0;
    }
    return 1;
}