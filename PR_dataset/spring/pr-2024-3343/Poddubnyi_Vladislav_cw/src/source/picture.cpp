#include "../include/picture.hpp"

Picture::Picture(std::string path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("File does not exist!");
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    validate();

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t rowSize = ((bmpHeader.width * bytesPerPixel + 3) / 4) * 4;
    uint32_t imageSize = rowSize * bmpHeader.height;

    data.resize(imageSize);
    file.seekg(bmpHeader.dataOffset, std::ios_base::beg);
    file.read(reinterpret_cast<char*>(data.data()), imageSize);
    file.close();
    if (data.empty()) throw std::runtime_error("BMP data is empty!");
}

void Picture::validate() {
    if (std::strncmp(bmpHeader.signature, "BM", 2) != 0) throw std::runtime_error("Wrong BMP signature!");
    if (bmpHeader.width <= 0 || bmpHeader.height <= 0) throw std::runtime_error("Wrong image width or height!");
    if (bmpHeader.bitsPerPixel != 24) throw std::runtime_error("Wrong bits per pixel!");
    if (bmpHeader.compression != 0) throw std::runtime_error("Does not support files with compression!");
}

void Picture::setPixel(int x, int y, Color color) {
    if (x < 0 || x >= bmpHeader.width || y < 0 || y >= bmpHeader.height) return;

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t bytesPerRow = (bytesPerPixel * bmpHeader.width + 3) & ~3;
    uint32_t index = (bmpHeader.height - 1 - y) * bytesPerRow + (x * bytesPerPixel);
    
    data[index] = color.blue;
    data[index + 1] = color.green;
    data[index + 2] = color.red;
}



void Picture::copyPixelToData(std::vector<uint8_t> &newData, int oldX, int oldY, int x, int y, int32_t width,
                              int32_t height) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t bytesPerRow = (bytesPerPixel * width + 3) & ~3;
    uint32_t index = ((height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);

    Color color = getPixel(oldX, oldY);
    newData[index] = color.blue;
    newData[index + 1] = color.green;
    newData[index + 2] = color.red;
}

void Picture::setPixelToData(std::vector<uint8_t> &newData, int x, int y, Color color, int32_t width, int32_t height) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t bytesPerRow = (bytesPerPixel * width + 3) & ~3;
    uint32_t index = ((height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);
    uint32_t index2 = 123;
    
    newData[index] = color.blue;
    newData[index + 1] = color.green;
    newData[index + 2] = color.red;
}

Color Picture::getPixel(int x, int y) {
    if (x < 0 || x >= bmpHeader.width || y < 0 || y >= bmpHeader.height) return Color();

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t bytesPerRow = (bytesPerPixel * bmpHeader.width + 3) & ~3;
    uint32_t index = ((bmpHeader.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);

    return {data[index + 2], data[index + 1], data[index]};
}

void Picture::save(std::string fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Error while saving file!");

    uint32_t bytesPerPixel = bmpHeader.bitsPerPixel / 8;
    uint32_t rowSize = ((bmpHeader.width * bytesPerPixel + 3) / 4) * 4;

    file.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    file.seekp(bmpHeader.dataOffset, std::ios::beg);
    for (int y = 0; y < bmpHeader.height; ++y) {
        file.write(reinterpret_cast<char*>(data.data() + y * rowSize), rowSize);
    }
    file.close();
}

void Picture::printInfo() {
    std::cout << "signature:\t" << std::hex << bmpHeader.signature << " (" << std::dec << bmpHeader.signature << ")"
              << std::endl;
    std::cout << "filesize:\t" << std::hex << bmpHeader.fileSize << " (" << std::dec << bmpHeader.fileSize << ")"
              << std::endl;
    std::cout << "reserved1:\t" << std::hex << bmpHeader.reserved1 << " (" << std::dec << bmpHeader.reserved1 << ")"
              << std::endl;
    std::cout << "reserved2:\t" << std::hex << bmpHeader.reserved2 << " (" << std::dec << bmpHeader.reserved2 << ")"
              << std::endl;
    std::cout << "pixelArrOffset:\t" << std::hex << bmpHeader.dataOffset << " (" << std::dec << bmpHeader.dataOffset
              << ")" << std::endl;
    std::cout << "headerSize:\t" << std::hex << bmpHeader.headerSize << " (" << std::dec << bmpHeader.headerSize << ")"
              << std::endl;
    std::cout << "width: \t" << std::hex << bmpHeader.width << " (" << std::dec << bmpHeader.width << ")" << std::endl;
    std::cout << "height: \t" << std::hex << bmpHeader.height << " (" << std::dec << bmpHeader.height << ")"
              << std::endl;
    std::cout << "planes: \t" << std::hex << bmpHeader.planes << " (" << std::dec << bmpHeader.planes << ")"
              << std::endl;
    std::cout << "bitsPerPixel:\t" << std::hex << bmpHeader.bitsPerPixel << " (" << std::dec << bmpHeader.bitsPerPixel
              << ")" << std::endl;
    std::cout << "compression:\t" << std::hex << bmpHeader.compression << " (" << std::dec << bmpHeader.compression
              << ")" << std::endl;
    std::cout << "imageSize:\t" << std::hex << bmpHeader.imageSize << " (" << std::dec << bmpHeader.imageSize << ")"
              << std::endl;
    std::cout << "xPixelsPerMeter:\t" << std::hex << bmpHeader.xPixelsPerMeter << " (" << std::dec
              << bmpHeader.xPixelsPerMeter << ")" << std::endl;
    std::cout << "yPixelsPerMeter:\t" << std::hex << bmpHeader.yPixelsPerMeter << " (" << std::dec
              << bmpHeader.yPixelsPerMeter << ")" << std::endl;
    std::cout << "colorsInColorTable:\t" << std::hex << bmpHeader.colorsUsed << " (" << std::dec << bmpHeader.colorsUsed
              << ")" << std::endl;
    std::cout << "importantColorCount:\t" << std::hex << bmpHeader.colorsImportant << " (" << std::dec
              << bmpHeader.colorsImportant << ")" << std::endl;
}
