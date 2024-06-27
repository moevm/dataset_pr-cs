#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <string>

#pragma pack(push, 1)

typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

class ImageProcessor {
public:
    static bool isBMP(const std::string& filename);
    static bool readBmp(const std::string& fileName, BitmapFileHeader &header,
                        BitmapInfoHeader &infoHeader, Rgb** &pixelArray);
    static void writeBmp(const std::string& fileName, BitmapFileHeader &header,
                         BitmapInfoHeader &infoHeader, Rgb** &pixelArray);
    static bool checkValidCoord(int& x, int& y, BitmapInfoHeader &infoHeader);
    static void getRgb(const std::string &color, int* arrayRgb);
    static void drawCircle(int& x, int& y, int thickness, const std::string& color,
                           Rgb** &pixelArray, BitmapInfoHeader &infoHeader);
    static void drawLine(int firstX, int firstY, int secondX, int secondY, int thickness,
                         const std::string& color, Rgb** &pixelArray, BitmapInfoHeader &infoHeader);
    static void fillRect(int leftX, int leftY, int rightX, int rightY, int thickness,
                         Rgb** &pixelArray, const std::string &fillColor, BitmapInfoHeader &infoHeader);
    static void drawRect(int leftX, int leftY, int rightX, int rightY, int thickness,
                         const std::string& color, bool fill, const std::string& fillColor,
                         Rgb** &pixelArray, BitmapInfoHeader &infoHeader);
    static void drawSquareWithDiagonals(int leftX, int leftY, int sideSize, int thickness,
                                        const std::string& color, bool fill, const std::string& fillColor,
                                        Rgb** &pixelArray, BitmapInfoHeader &infoHeader);
    static void applyRGBFilter(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, const std::string& component_name, int component_value);
    static void rotate(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, int coords[2][2], int angle);
    static void applyContrast(Rgb** &pixelArray, BitmapInfoHeader &infoHeader, float alpha, int beta);
    static bool convertCoords(const std::string& stringCoords, int &x, int &y);
    static bool checkValidName(const std::string& name);
};

#endif // IMAGEPROCESSOR_H
