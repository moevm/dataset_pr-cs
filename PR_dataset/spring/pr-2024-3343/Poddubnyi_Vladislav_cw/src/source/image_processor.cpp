#include "../include/image_processor.hpp"

void ImageProcessor::inverse(Picture &picture, Coordinate leftUp, Coordinate rightDown) {
    std::vector<uint8_t> data =  picture.data;

    for (int y = leftUp.y; y <= rightDown.y; ++y) {
        for (int x = leftUp.x; x <= rightDown.x; ++x) {
            Color pixel = picture.getPixel(x, y);
            pixel.blue = 255 - pixel.blue;
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            picture.setPixel(x, y, pixel);
        }
    }
}

void ImageProcessor::gray(Picture &picture, Coordinate leftUp, Coordinate rightDown){
    std::vector<uint8_t> data =  picture.data;

    for (int y = leftUp.y; y <= rightDown.y; ++y) {
        for (int x = leftUp.x; x <= rightDown.x; ++x) {
            Color pixel = picture.getPixel(x, y);
            uint8_t grayValue = std::round(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
            picture.setPixel(x, y, Color(grayValue, grayValue, grayValue));
        }
    }
}

void ImageProcessor::resize(Picture &picture, int32_t left, int32_t above, int32_t right, int32_t below, Color color){
    std::vector<uint8_t> data =  picture.data;
    int32_t oldHeight = picture.bmpHeader.height;
    int32_t oldWidth = picture.bmpHeader.width;
    int32_t newHeight = oldHeight + above + below;
    int32_t newWidth = oldWidth + right + left;

    uint32_t bytesPerPixel = picture.bmpHeader.bitsPerPixel / 8;
    uint32_t rowSize = ((newWidth * bytesPerPixel + 3) / 4) * 4;
    uint32_t imageSize = rowSize * newHeight;

    int32_t leftUpY = oldHeight + below;
    int32_t leftUpX = 0 + -left;
    std::vector<uint8_t> newData(imageSize);

    int oldY = leftUpY - 1;
    for (int y = newHeight-1; y >= 0; --y) {
        int oldX = leftUpX;
        for (int x = 0; x <= newWidth; ++x) {
                if (!(oldX <= oldWidth && oldY <= oldHeight && oldY >= 0 && oldX >=0)) {
                    picture.setPixelToData(newData, x, y, color, newWidth, newHeight);
                } else {
                    picture.copyPixelToData(newData, oldX, oldY, x, y, newWidth, newHeight);
                }
            oldX++;
        }
        oldY--;
    }

    picture.bmpHeader.height = newHeight;
    picture.bmpHeader.width = newWidth;
    picture.bmpHeader.imageSize = imageSize;
    picture.data = newData;
    picture.bmpHeader.fileSize = picture.bmpHeader.dataOffset + picture.bmpHeader.imageSize;
}

void ImageProcessor::ornament(Picture &picture, int32_t thickness, Color color){
    resize(picture, thickness, thickness, thickness, thickness, color);
}

void ImageProcessor::line(Picture &picture, Coordinate startPoint, Coordinate endPoint, Color color, int32_t lineThickness) {
    int deltaX = abs(endPoint.x - startPoint.x);
    int deltaY = abs(endPoint.y - startPoint.y);
    int stepX = (startPoint.x < endPoint.x) ? 1 : -1;
    int stepY = (startPoint.y < endPoint.y) ? 1 : -1;
    int error = deltaX - deltaY;

    while (true) {
        int rectX = startPoint.x - lineThickness / 2;
        int rectY = startPoint.y - lineThickness / 2;
        int rectWidth = lineThickness;
        int rectHeight = lineThickness;
        if (rectX >= 0 && rectX + rectWidth < picture.bmpHeader.width &&
            rectY >= 0 && rectY + rectHeight < picture.bmpHeader.height) {
            for (int y = rectY; y < rectY + rectHeight; ++y) {
                for (int x = rectX; x < rectX + rectWidth; ++x) {
                    picture.setPixel(x, y, color);
                }
            }
        }

        if (startPoint.x == endPoint.x && startPoint.y == endPoint.y) break;

        int doubleError = 2 * error;
        if (doubleError > -deltaY) {
            error -= deltaY;
            startPoint.x += stepX;
        }
        if (doubleError < deltaX) {
            error += deltaX;
            startPoint.y += stepY;
        }
    }

}