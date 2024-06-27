#ifndef BMP_IMAGES_H
#define BMP_IMAGES_H

#include<string>
#include"bmpStructures.h"

class BmpImage
{
private: 
    BmpFileHeader mBmfh;
    BmpInfoHeader mBmih;
    Rgb** mPixelArr;
    int mHeight;
    int mWidth;
    std::string filePath;

    int checkFileFormat() noexcept;
    void fileHeaderInit() noexcept;
    void infoHeaderInit() noexcept;
    int checkColor(Rgb color) noexcept;
    void checkZone(Point &leftUp, Point &rightDown) noexcept;
public:
    BmpImage() noexcept;
    BmpImage(const std::string filePath);
    BmpImage(const int width, const int height, Rgb defaultColor={0, 0, 0});
    void open(const std::string filePath);
    BmpFileHeader getFileHeader() noexcept;
    BmpInfoHeader getInfoHeader() noexcept;
    void printPath() noexcept;
    void save();
    void save(const std::string newFilePath);
    void resize(const int newWidth, const int newHeight, const Rgb defaultColor={0, 0, 0});
    void drawCircle(int radius, Point center, int thickness, Rgb lineColor, bool isFill=false, Rgb fillColor = {255, 0, 0});
    void drawLine(Point leftUp, Point rightDown, int thickness, Rgb color);
    void drawRectangle(Point leftUp, Point rightDown, int thickness, Rgb lineColor, bool isFill = false, Rgb fillColor = {255, 0, 0}, bool smooth=false);
    Rgb** copy(Point leftUp, Point rightDown, int &height, int &width) noexcept;
    void paste(Point leftUp, Rgb** arr, int width, int height) noexcept;//width and height - sizes of arr 
    void invertImage();
    void blackAndWhite();
    void mirror();
    void circleOrnament(Rgb color={0, 255, 0});
    void rectangleOrnament(Rgb color, int thickness, int count);
    void semiCircleOrnament(Rgb color, int thickness, int count);
    void rotate(Point leftUp, Point rightDown, int angle);
    void drawRhombus(Point vertex, int size, Rgb fill_color);
    ~BmpImage();
};

#endif