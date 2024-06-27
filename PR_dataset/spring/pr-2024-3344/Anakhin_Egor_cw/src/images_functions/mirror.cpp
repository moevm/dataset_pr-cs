#include "mirror.h"

void mirror(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int width = infoHeader.width;
    int height = infoHeader.height;
    std::string axis = argsMap["axis"];

    int x_start;
    int x_end;
    int y_start;
    int y_end;

    try {
        getCoords(argsMap["left_up"], &x_start, &y_start);
        getCoords(argsMap["right_down"], &x_end, &y_end);
    } catch (const std::exception& e) {
        std::cout << "Error while running programm:\n" << e.what() << std::endl;
        exit(41);
    }

     if (x_start >= x_end or y_start >= y_end) {
        std::cout << "Invalid coordinates: left_up should be less than right_down." << std::endl;
        exit(41);
    }

    if (axis == "x") {
        reverseX(width, height, bytesARR, x_start, y_start, x_end, y_end);
    } else if (axis == "y") {
        reverseY(width, height, bytesARR, x_start, y_start, x_end, y_end);
    } else {
        std::cout << "Axis can only be x or y";
        exit(41);
    }
}

void reverseX(int width, int height, std::vector<std::vector<Pixel>> &bytesARR, int x_start, int y_start, int x_end, int y_end) {
    for (int y = y_start; y <= y_end; ++y) {
        for (int x = x_start; x <= (x_start + x_end) / 2; ++x) {
            int mirror_x = x_start + x_end - x;
            Pixel temp = bytesARR[y][x];
            bytesARR[y][x] = bytesARR[y][mirror_x];
            bytesARR[y][mirror_x] = temp;
        }
    }
}

void reverseY(int width, int height, std::vector<std::vector<Pixel>> &bytesARR, int x_start, int y_start, int x_end, int y_end) {
    for (int y = y_start; y <= (y_start + y_end) / 2; ++y) {
        int mirror_y = y_start + y_end - y;
        for (int x = x_start; x <= x_end; ++x) {
            Pixel temp = bytesARR[y][x];
            bytesARR[y][x] = bytesARR[mirror_y][x];
            bytesARR[mirror_y][x] = temp;
        }
    }
}