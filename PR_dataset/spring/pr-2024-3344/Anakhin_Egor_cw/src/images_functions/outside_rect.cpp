#include "outside_rect.h"

void outsideRect(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int width = infoHeader.width;
    int height = infoHeader.height;

    int x_start = 0;
    int x_end = 0;
    int y_start = 0;
    int y_end = 0;

    Pixel new_color_rgb = parsePixel(argsMap["color"]);

    try {
        getCoords(argsMap["left_up"], &x_start, &y_start);
        getCoords(argsMap["right_down"], &x_end, &y_end);
    } catch (const std::exception& e) {
        std::cout << "Error while running programm:\n" << e.what() << std::endl;
        exit(41);
    }

    if (x_start >= x_end || y_start >= y_end) {
        std::cout << "Invalid coordinates: left_up should be less than right_down." << std::endl;
        exit(41);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < y_start || i > y_end || j < x_start || j > x_end) {
                bytesARR[i][j] = new_color_rgb;
            }
        }
    }
}