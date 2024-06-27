#include "paving.h"


void paving(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap) {
    int x_start;
    int x_end;
    int y_start;
    int y_end;
    int paveHeight;
    int paveWidth;
    
    int row = 0;
    int column = 0;
    int width = infoHeader.width;
    int height = infoHeader.height;

    try {
        getCoords(argsMap["left_up"], &x_start, &y_start);
        getCoords(argsMap["right_down"], &x_end, &y_end);
    } catch (const std::exception& e) {
        std::cout << "Error while running programm:\n" << e.what() << std::endl;
        exit(41);
    }

    paveHeight = y_end - y_start;
    paveWidth = x_end - x_start;

    std::vector<std::vector<Pixel>> paveArr;

    for (int i = y_start; i < y_end; i++) {
        std::vector<Pixel> row;
        for (int j = x_start; j < x_end; j++) {
            row.push_back(bytesARR[i][j]); 
        }
        paveArr.push_back(row);
    }

    for (int l = 0; l < height - 1 + paveHeight; l += paveHeight) {
        for (int k = 0; k < width - 1 + paveWidth; k += paveWidth) {
            for (int i = l; i < l + paveHeight and i < height; i++) {
                for (int j = k; j < k + paveWidth and i < width; j++) {
                    if (i < height && j < width) {
                        bytesARR[i][j] = paveArr[i - l][j - k];
                    }
                }
            }
        }
    }
}