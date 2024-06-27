#include "copy_part.h"
#include <sstream>
#include <stdexcept>

void copyPartOfImage(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int x_start, y_start, x_end, y_end, copy_x, copy_y;

    try {
        getCoords(argsMap["left_up"], &x_start, &y_start);
        getCoords(argsMap["right_down"], &x_end, &y_end);
        getCoords(argsMap["dest_left_up"], &copy_x, &copy_y);
    } catch (const std::exception& e) {
        // std::cout << "Error while running programm:\n" << e.what() << std::endl;
        exit(41);
    }

    if (x_start >= x_end || y_start >= y_end) {
        // std::cout << "Invalid coordinates: left_up should be less than right_down." << std::endl;
        exit(41);
    }

    x_start = std::max(0, x_start);
    y_start = std::max(0, y_start);
    x_end = std::min(x_end, infoHeader.width);
    y_end = std::min(y_end, infoHeader.height);

    int copy_width = x_end - x_start;
    int copy_height = y_end - y_start;

    std::vector<std::vector<Pixel>> newBytesARR(copy_height, std::vector<Pixel>(copy_width));

    for (int y = 0; y < copy_height; ++y) {
        int source_y = y_start + y;
        int dest_y = copy_y + y;
        if (source_y < 0 || source_y >= infoHeader.height || dest_y < 0 || dest_y >= infoHeader.height) {
            continue; // Пропускаем строку, если выходит за пределы
        }
        for (int x = 0; x < copy_width; ++x) {
            int source_x = x_start + x;
            int dest_x = copy_x + x;
            if (source_x < 0 || source_x >= infoHeader.width || dest_x < 0 || dest_x >= infoHeader.width) {
                continue; // Пропускаем элемент, если выходит за пределы
            }
            newBytesARR[y][x] = bytesARR[source_y][source_x];
        }
    }

    for (int y = 0; y < copy_height; ++y) {
        int dest_y = copy_y + y;
        if (dest_y < 0 || dest_y >= infoHeader.height) {
            continue; // Пропускаем строку, если выходит за пределы
        }
        for (int x = 0; x < copy_width; ++x) {
            int dest_x = copy_x + x;
            if (dest_x < 0 || dest_x >= infoHeader.width) {
                continue; // Пропускаем элемент, если выходит за пределы
            }
            bytesARR[dest_y][dest_x] = newBytesARR[y][x];
        }
    }

}