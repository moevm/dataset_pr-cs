#include "ornament.h"

std::vector<std::vector<Pixel>> ornament(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int width = infoHeader.width;
    int height = infoHeader.height;

    int thickness = std::stoi(argsMap["thickness"]);
    Pixel color = parsePixel(argsMap["color"]);

    std::vector<std::vector<Pixel>> new_img;
    for (int i = 0; i < height + thickness * 2; i++) {
        std::vector<Pixel> row;
        for (int j = 0; j < width + thickness * 2; j++) {
            row.push_back(color);            
        }
        new_img.push_back(row);
    }

    for (int i = thickness; i < height + thickness; i++) {
        for (int j = thickness; j < thickness + width; j++) {
            new_img[i][j] = bytesARR[i - thickness][j - thickness];
        }
    }
    std::copy(new_img.begin(), new_img.end(), bytesARR.begin());
}