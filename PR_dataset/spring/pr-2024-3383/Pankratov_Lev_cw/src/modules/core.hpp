#ifndef MODULES_CORE_HPP_
#define MODULES_CORE_HPP_

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

class Coord
{
public:
    int16_t x;
    int16_t y;
};

class Coordinates
{
public:
    int16_t leftX, rightX;
    int16_t leftY, rightY;
};

class Side
{
public:
    int16_t left;
    int16_t right;
    int16_t above;
    int16_t below;
};

namespace BmpSystem
{
#pragma pack(push, 1)

    class BitmapFileHeader
    {
    public:
        int16_t signature;
        int32_t fileSize;
        int16_t reserved1;
        int16_t reserved2;
        int32_t pixelArrOffset;
    };

    class BitmapInfoHeader
    {
    public:
        int32_t size;
        int32_t width;
        int32_t height;
        int16_t planes;
        int16_t bitPerPixel;
        int32_t compression;
        int32_t imageSize;
        int32_t xPixelsPerMeter;
        int32_t yPixelsPerMeter;
        int32_t colorsInColorTable;
        int32_t importantColorCount;
    };

    class Rgb
    {
    public:
        uint8_t rgbBlue;
        uint8_t rgbGreen;
        uint8_t rgbRed;
    };
    
#pragma pack(pop)

    class Bmp
    {
    public:
        Bmp(const char *inputPathFile);

        void writeBmp(const char *outputPathFile);
        void printFileInfo();
        void inverseColorInArea(const char *outputPathFile, Coordinates coord);
        void blackAndWhite(const char *outputPathFile, Coordinates coord);
        void setPixel(int x, int y, Rgb color);
        bool isCorrectSize(Side side);
        void resize(const char *outputPathFile, Side side, Rgb color);
        void replaceCoord(Coordinates* coord);
        void drawRomb(const char* outputPathFile, Coord coord, Rgb color, int size);
        int edge(Coord p0, Coord p1, Coord p);

    private:
        BitmapFileHeader *fileHeader;
        BitmapInfoHeader *infoHeader;
        Rgb **dataPixels;
    };
}

void printInstruction();
std::vector<std::string> split(std::string s, std::string delimiter);

#endif