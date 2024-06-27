//
// Created by rect on 09.05.2024.
//


#pragma once

#include "opts_reader.hpp"
#include <cstring>
#include <fstream>
#include <vector>

#pragma pack(push, 1)
struct BMPHeader
{
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

class Picture{
public:
    Picture(std::string path);
    BMPHeader bmpHeader;
    std::vector<uint8_t> data;
    void setPixel(int x, int y, Color color);
    Color getPixel(int x, int y);
    void save(std::string fileName);
    void setPixelToData(std::vector<uint8_t> &newData, int x, int y, Color color, int32_t width, int32_t height);
    void copyPixelToData(std::vector<uint8_t> &newData, int oldX, int oldY, int x, int y, int32_t width, int32_t height);
    void printInfo();
private:
    void validate();
};

