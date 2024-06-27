#include "ImageProcessor.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <cstring>

bool ImageProcessor::isBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    char header[2];
    file.read(header, 2);
    bool isBmp = (header[0] == 'B' && header[1] == 'M');
    file.close();
    return isBmp;
}

bool ImageProcessor::readBmp(const std::string& fileName, BitmapFileHeader &fileHeader,
                             BitmapInfoHeader &infoHeader, Rgb** &pixelArray){
    std::fstream file(fileName, std::ios::binary | std::ios::in);
    try {
        if (!file.is_open()) return false;
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
        int rowSize = ((infoHeader.width * sizeof(Rgb)) + 3) & (~3);
        pixelArray = new Rgb*[infoHeader.height];
        for (int rowIndex = infoHeader.height - 1; rowIndex >= 0; rowIndex--) {
            pixelArray[rowIndex] = new Rgb[infoHeader.width];
            file.read(reinterpret_cast<char*>(pixelArray[rowIndex]), rowSize);
        }
        file.close();
    } catch (const std::bad_alloc& exception) {
        return false;
    }
    if (!isBMP(fileName)) return false;
    return true;
}

void ImageProcessor::writeBmp(const std::string& fileName, BitmapFileHeader &fileHeader,
                              BitmapInfoHeader &infoHeader, Rgb** &pixelArray){
    std::fstream file(fileName, std::ios::binary | std::ios::out);
    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(BitmapFileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(BitmapInfoHeader));
    int rowSize = ((infoHeader.width * sizeof(Rgb)) + 3) & (~3);
    for (int rowIndex = infoHeader.height - 1; rowIndex >= 0; rowIndex--) {
        file.write(reinterpret_cast<char*>(pixelArray[rowIndex]), rowSize);
    }
    file.close();
}

bool ImageProcessor::checkValidCoord(int& xCoord, int& yCoord, BitmapInfoHeader &infoHeader){
    if (static_cast<unsigned int>(xCoord) >= infoHeader.width || xCoord < 0) return false;
    if (static_cast<unsigned int>(yCoord) >= infoHeader.height || yCoord < 0) return false;
    return true;
}

void ImageProcessor::getRgb(const std::string &color, int* rgbArray){
    char colorRgb[color.size()+1];
    char* token;
    strcpy(colorRgb, color.c_str());
    token = strtok(colorRgb, ".");
    rgbArray[0] = atoi(token);
    token = strtok(NULL, ".");
    rgbArray[1] = atoi(token);
    token = strtok(NULL, ".");
    rgbArray[2] = atoi(token);
}

void ImageProcessor::drawCircle(int& centerX, int& centerY, int thickness, const std::string& color,
                                Rgb** &pixelArray, BitmapInfoHeader &infoHeader){
    int radius = thickness / 2;
    int rgbArray[3];
    getRgb(color, rgbArray);
    if (radius < 1) {
        if (checkValidCoord(centerX, centerY, infoHeader)) {
            pixelArray[centerY][centerX].r = rgbArray[0];
            pixelArray[centerY][centerX].g = rgbArray[1];
            pixelArray[centerY][centerX].b = rgbArray[2];
        }
        return;
    }
    int xCoord = radius;
    int yCoord = 0;
    int decisionParam = 1 - radius;
    while (xCoord >= yCoord) {
        int xLeft  = centerX - xCoord;
        int xRight = centerX + xCoord;
        int yTop = centerY + yCoord;
        int yBottom = centerY - yCoord;
        int yRight = centerY + xCoord;
        int xBottom = centerX + yCoord;
        int xTop  = centerX - yCoord;
        int yLeft = centerY - xCoord;
        for (int i = xLeft; (i <= xRight) && (i < static_cast<int>(infoHeader.width)); i++) {
            if ((yTop >= 0) && (i >= 0) && (yTop < static_cast<int>(infoHeader.height))) {
                pixelArray[yTop][i].r = rgbArray[0];
                pixelArray[yTop][i].g = rgbArray[1];
                pixelArray[yTop][i].b = rgbArray[2];
            }
            if ((yBottom >= 0) && (i >= 0) && (yBottom < static_cast<int>(infoHeader.height))) {
                pixelArray[yBottom][i].r = rgbArray[0];
                pixelArray[yBottom][i].g = rgbArray[1];
                pixelArray[yBottom][i].b = rgbArray[2];
            }
        }
        for (int i = xTop; (i <= xBottom) && (i < static_cast<int>(infoHeader.width)); i++) {
            if ((yRight >= 0) && (i >= 0) && (yRight < static_cast<int>(infoHeader.height))) {
                pixelArray[yRight][i].r = rgbArray[0];
                pixelArray[yRight][i].g = rgbArray[1];
                pixelArray[yRight][i].b = rgbArray[2];
            }
            if ((yLeft >= 0) && (i >= 0) && (yLeft < static_cast<int>(infoHeader.height))) {
                pixelArray[yLeft][i].r = rgbArray[0];
                pixelArray[yLeft][i].g = rgbArray[1];
                pixelArray[yLeft][i].b = rgbArray[2];
            }
        }
        yCoord++;
        if (decisionParam <= 0) {
            decisionParam = decisionParam + 2 * yCoord + 1;
        } else {
            xCoord--;
            decisionParam = decisionParam + 2 * (yCoord - xCoord) + 1;
        }
    }
}

void ImageProcessor::drawLine(int startX, int startY, int endX, int endY, int thickness,
                              const std::string& color, Rgb** &pixelArray, BitmapInfoHeader &infoHeader){
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    int sx = startX < endX ? 1 : -1;
    int sy = startY < endY ? 1 : -1;
    int error = dx - dy;
    int xCoord = startX;
    int yCoord = startY;
    while (xCoord != endX || yCoord != endY) {
        drawCircle(xCoord, yCoord, thickness, color, pixelArray, infoHeader);
        int error2 = 2 * error;
        if (error2 > -dy) {
            error -= dy;
            xCoord += sx;
        }
        if (error2 < dx) {
            error += dx;
            yCoord += sy;
        }
    }
    drawCircle(endX, endY, thickness, color, pixelArray, infoHeader);
}

void ImageProcessor::fillRect(int leftX, int leftY, int rightX, int rightY, int thickness,
                              Rgb** &pixelArray, const std::string &fillColor, BitmapInfoHeader &infoHeader){
    int rgbFillArray[3];
    getRgb(fillColor, rgbFillArray);
    for (int i = leftX; i <= rightX; i++) {
        for (int j = leftY; j <= rightY; j++) {
            if (checkValidCoord(i, j, infoHeader)) {
                pixelArray[j][i].r = rgbFillArray[0];
                pixelArray[j][i].g = rgbFillArray[1];
                pixelArray[j][i].b = rgbFillArray[2];
            }
        }
    }
}

void ImageProcessor::drawRect(int leftX, int leftY, int rightX, int rightY, int thickness,
                              const std::string& color, bool fill, const std::string& fillColor,
                              Rgb** &pixelArray, BitmapInfoHeader &infoHeader){
    if (fill) fillRect(leftX, leftY, rightX, rightY, thickness, pixelArray, fillColor, infoHeader);
    drawLine(leftX, leftY, rightX, leftY, thickness, color, pixelArray, infoHeader);
    drawLine(rightX, leftY, rightX, rightY, thickness, color, pixelArray, infoHeader);
    drawLine(leftX, rightY, rightX, rightY, thickness, color, pixelArray, infoHeader);
    drawLine(leftX, leftY, leftX, rightY, thickness, color, pixelArray, infoHeader);
}

void ImageProcessor::drawSquareWithDiagonals(int leftX, int leftY, int sideSize, int thickness,
                                             const std::string& color, bool fill, const std::string& fillColor,
                                             Rgb** &pixelArray, BitmapInfoHeader &infoHeader) {
    drawRect(leftX, leftY, leftX + sideSize, leftY + sideSize, thickness, color, fill, fillColor, pixelArray, infoHeader);

    drawLine(leftX, leftY, leftX + sideSize, leftY + sideSize, thickness, color, pixelArray, infoHeader);
    drawLine(leftX + sideSize, leftY, leftX, leftY + sideSize, thickness, color, pixelArray, infoHeader);
}

void ImageProcessor::applyRGBFilter(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, const std::string& componentName, int componentValue) {
    int componentIndex = (componentName == "red") ? 2 : (componentName == "green" ? 1 : 0);
    for (unsigned int rowIndex = 0; rowIndex < infoHeader.height; ++rowIndex) {
        for (unsigned int colIndex = 0; colIndex < infoHeader.width; ++colIndex) {
            unsigned char* component = reinterpret_cast<unsigned char*>(&pixelArray[rowIndex][colIndex]) + componentIndex;
            *component = static_cast<unsigned char>(componentValue);
        }
    }
}

void ImageProcessor::rotate(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, int coords[2][2], int angle) {
    using std::min, std::max;

    int left = coords[0][0];
    int top = coords[0][1];
    int right = coords[1][0];
    int bottom = coords[1][1];

    int rectWidth = right - left;
    int rectHeight = bottom - top;
    int centerX = left + rectWidth / 2;
    int centerY = top + rectHeight / 2;

    Rgb** buffer = new Rgb*[infoHeader.height];
    for (unsigned int rowIndex = 0; rowIndex < infoHeader.height; ++rowIndex) {
        buffer[rowIndex] = new Rgb[infoHeader.width];
        std::copy(pixelArray[rowIndex], pixelArray[rowIndex] + infoHeader.width, buffer[rowIndex]);
    }

    for (unsigned int rowIndex = 0; rowIndex < infoHeader.height; ++rowIndex) {
        for (unsigned int colIndex = 0; colIndex < infoHeader.width; ++colIndex) {
            int oldX = 0, oldY = 0;
            int deltaX = 0, deltaY = 0;
            switch (angle) {
                case 270:
                    oldX = centerX + (rowIndex - centerY);
                    oldY = centerY - (colIndex - centerX);
                    if ((rectHeight % 2) != (rectWidth % 2)) {
                        if ((rectHeight % 2)) {
                            deltaY = -1 + (rectHeight % 2);
                            deltaX = -(rectWidth % 2);
                        } else {
                            deltaY = -(rectHeight % 2);
                            deltaX = -(rectWidth % 2);
                        }
                    } else {
                        deltaY = -((1 + rectHeight) % 2);
                        deltaX = -((1 + rectWidth) % 2);
                    }
                    break;
                case 180:
                    oldX = centerX - (colIndex - centerX);
                    oldY = centerY - (rowIndex - centerY);
                    if (!(rectHeight % 2) && !(rectWidth % 2)) {
                        deltaX = -1 + (rectHeight % 2);
                        deltaY = -1 + (rectWidth % 2);
                    } else {
                        deltaX = -(rectHeight % 2);
                        deltaY = -(rectWidth % 2);
                    }
                    break;
                case 90:
                    oldX = centerX - (rowIndex - centerY);
                    oldY = centerY + (colIndex - centerX);
                    deltaY = -1 + (rectWidth % 2);
                    deltaX = -(rectHeight % 2);
                    break;
                default:
                    return;
            }

            if ((oldX < 0 || oldY < 0 || oldX >= static_cast<int>(infoHeader.width) || oldY >= static_cast<int>(infoHeader.height)) ||
                (oldY < top || oldY >= bottom || oldX < left || oldX >= right))
                continue;
            
            Rgb oldPixel = pixelArray[oldY][oldX];
            if (rowIndex + deltaY >= 0 && static_cast<unsigned int>(rowIndex + deltaY) < infoHeader.height && colIndex + deltaX >= 0 && static_cast<unsigned int>(colIndex + deltaX) < infoHeader.width) {
                buffer[rowIndex + deltaY][colIndex + deltaX] = oldPixel;
            }
        }
    }

    for (unsigned int rowIndex = 0; rowIndex < infoHeader.height; ++rowIndex) {
        delete[] pixelArray[rowIndex];
    }
    delete[] pixelArray;
    pixelArray = buffer;
}

void ImageProcessor::applyContrast(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, float alpha, int beta){
    for(unsigned int rowIndex = 0; rowIndex < infoHeader.height; rowIndex++){
        for(unsigned int colIndex = 0; colIndex < infoHeader.width; colIndex++){
            int r = static_cast<int>(alpha * pixelArray[rowIndex][colIndex].r + beta);
            int g = static_cast<int>(alpha * pixelArray[rowIndex][colIndex].g + beta);
            int b = static_cast<int>(alpha * pixelArray[rowIndex][colIndex].b + beta);

            pixelArray[rowIndex][colIndex].r = std::clamp(r, 0, 255);
            pixelArray[rowIndex][colIndex].g = std::clamp(g, 0, 255);
            pixelArray[rowIndex][colIndex].b = std::clamp(b, 0, 255);
        }
    }
}

bool ImageProcessor::convertCoords(const std::string& stringCoords, int &xCoord, int &yCoord){
    if (!std::regex_match(stringCoords.c_str(), std::regex("(-?[0-9]+).(-?[0-9]+)"))) return false;
    xCoord = atoi(stringCoords.c_str());
    int i = 0;
    while (true) {
        if (stringCoords[i] == '.') break;
        i++;
    }
    yCoord = atoi(i + 1 + stringCoords.c_str());
    return true;
}

bool ImageProcessor::checkValidName(const std::string& name){
    return (std::regex_match(name, std::regex("((./)||((\\w+/)+))?(\\w+).(\\w+)")));
}

void ImageProcessor::processSquareWithDiagonalsCommand(BitmapInfoHeader &infoHeader, Rgb** &pixelArray, int argc, char* argv[]) {
    int opt, keyIndex;
    int leftX = -1, leftY = -1, sideSize = -1, thickness = -1;
    std::string color = "", fillColor = "";
    bool fill = false;

    while ((opt = getopt_long(argc, argv, "", squared_linesKeys, &keyIndex)) != -1) {
        switch (opt) {
            case 'u':
                convertCoords(optarg, leftX, leftY);
                break;
            case 's':
                sideSize = std::atoi(optarg);
                if (sideSize <= 0) {
                    std::cerr << "Error: Side size must be a positive number." << std::endl;
                    exit(41);
                }
                break;
            case 't':
                thickness = std::atoi(optarg);
                if (thickness <= 0) {
                    std::cerr << "Error: Thickness must be a positive number." << std::endl;
                    exit(41);
                }
                break;
            case 'c':
                if (std::regex_match(optarg, std::regex("(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9]).(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9]).(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])")))
                    color = optarg;
                break;
            case 'f':
                fill = true;
                break;
            case 'g':
                if (std::regex_match(optarg, std::regex("(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9]).(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9]).(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])")))
                    fillColor = optarg;
                break;
        }
    }

    if (leftX == -1 || leftY == -1 || sideSize == -1 || thickness == -1 || color.empty()) {
        std::cerr << "Error: Not all required parameters were provided." << std::endl;
        exit(41);
    }
    if (fill && fillColor.empty()) {
        std::cerr << "Error: Fill is specified, but fill color is not provided." << std::endl;
        exit(41);
    }

    int rightX = leftX + sideSize;
    int rightY = leftY + sideSize;

    if (leftX > rightX) {
        std::swap(leftX, rightX);
    }
    if (leftY > rightY) {
        std::swap(leftY, rightY);
    }

    drawSquareWithDiagonals(leftX, leftY, sideSize, thickness, color, fill, fillColor, pixelArray, infoHeader);
}

void ImageProcessor::processRGBFilter(BitmapInfoHeader &infoHeader, Rgb** &pixelArray, int argc, char* argv[]) {
    int opt;
    int keyIndex;
    std::string componentName = "";
    int componentValue = -1;

    while (true) {
        opt = getopt_long(argc, argv, "", rgbFilterKeys, &keyIndex);
        if (opt == -1) {
            break;
        }
        switch (opt) {
            case 'n':
                componentName = optarg;
                break;
            case 'v':
                componentValue = std::stoi(optarg);
                if (componentValue < 0 || componentValue > 255) {
                    std::cout << "Component value must be between 0 and 255" << std::endl;
                    exit(41);
                }
                break;
        }
    }

    if (componentName.empty() || componentValue == -1) {
        std::cout << "Invalid or incomplete data for RGB filter" << std::endl;
        exit(41);
    }

    applyRGBFilter(pixelArray, infoHeader, componentName, componentValue);
}

void ImageProcessor::processRotate(BitmapInfoHeader &infoHeader, Rgb** &pixelArray, int argc, char* argv[]) {
    int opt;
    int keyIndex;
    int coords[2][2] = {{-1, -1}, {-1, -1}};
    int angle = 0;

    while (true) {
        opt = getopt_long(argc, argv, "", rotateKeys, &keyIndex);
        if (opt == -1) {
            break;
        }
        switch (opt) {
            case 'u':
                if (!convertCoords(optarg, coords[0][0], coords[0][1])) {
                    std::cout << "Invalid format for left_up coordinates" << std::endl;
                    exit(41);
                }
                break;
            case 'd':
                if (!convertCoords(optarg, coords[1][0], coords[1][1])) {
                    std::cout << "Invalid format for right_down coordinates" << std::endl;
                    exit(41);
                }
                break;
            case 'a':
                try {
                    angle = std::stoi(optarg);
                } catch (std::invalid_argument&) {
                    std::cout << "Angle must be an integer value" << std::endl;
                    exit(41);
                }
                if (angle != 90 && angle != 180 && angle != 270) {
                    std::cout << "Angle must be 90, 180, or 270 degrees" << std::endl;
                    exit(41);
                }
                break;
        }
    }

    if (coords[0][0] == -1 || coords[0][1] == -1 || coords[1][0] == -1 || coords[1][1] == -1) {
        std::cout << "Coordinates for both corners must be specified" << std::endl;
        exit(41);
    }

    rotate(pixelArray, infoHeader, coords, angle);
}

void ImageProcessor::processContrast(BitmapInfoHeader &infoHeader, Rgb** &pixelArray, int argc, char* argv[]){
    int opt;
    int keyIndex;
    float alpha = -1;
    int beta = -500;
    while (true){
        opt = getopt_long(argc, argv, "", contrastKeys, &keyIndex);
        if(opt == -1){
            opt = 0;
            break;
        }
        switch(opt){
            case 'l':
                alpha = std::stof(optarg);
                break;
            case 'b':
                beta = std::stoi(optarg);
                break;
        }
    }
    if(alpha == -1 || beta == -500){
        exit(41);
    }
       
    applyContrast(pixelArray, infoHeader,alpha,beta);

}
