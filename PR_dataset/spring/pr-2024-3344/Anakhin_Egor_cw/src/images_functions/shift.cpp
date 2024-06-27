#include "shift.h"

void shift(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int width = infoHeader.width;
    int height = infoHeader.height;
    std::string axis = argsMap["axis"];
    int step = std::stoi(argsMap["step"]);


    std::vector<std::vector<Pixel>> new_arr;

    for (int i = 0; i < height; i++) {
        std::vector<Pixel> row;
        for (int j = 0; j < width; j++) {
            row.push_back(bytesARR[i][j]);
        }
        new_arr.push_back(row);
    }

    if (axis == "y") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                bytesARR[(i + step) % height][j] = new_arr[i][j];
        }
        
    }return;
    } else if (axis == "x") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                bytesARR[i][(j + step) % width] = new_arr[i][j];
            }
            
    }return;} else if (axis == "xy") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                bytesARR[(i + step) % height][(j + step) % width] = new_arr[i][j];
            }} return;
    } else {
        std::cout << "Axis can only be x or y or xy";
        exit(41);
    }
}