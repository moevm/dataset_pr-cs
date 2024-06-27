#ifndef WRITE_H
#define WRITE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../include/write.h"

uint32_t image_size;

uint32_t calculateImageSize(const BMPFileHeader &bmpInfoHeader) {
    // Размер изображения можно вычислить на основе ширины, высоты и бит на пиксель
    // В BMP-файлах данные изображения выровнены по 4 байтам, поэтому необходимо учесть это при вычислении
    const uint32_t bytesPerPixel = bmpInfoHeader.bit_count / 8;

    const uint32_t padding = (4 - (bmpInfoHeader.width * bytesPerPixel) % 4) % 4;
    const uint32_t rowSize = (bmpInfoHeader.width * bytesPerPixel) + padding;

    // Размер изображения в байтах
    uint32_t imageSize = rowSize * abs(bmpInfoHeader.height);

    // Если в заголовке уже указан размер изображения, используем его
    if (bmpInfoHeader.image_size != 0) {
        imageSize = bmpInfoHeader.image_size;
    }

    return imageSize;
}

void writeBMP(std::string &filename, BMPImage &image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        exit(41);
    }

    // Запись заголовка файла
    file.write(reinterpret_cast<const char *>(&image.file_header), sizeof(image.file_header));

    file.seekp(image.file_header.offset, std::ios::beg);
    // Запись данных изображения
    const uint32_t bytes_per_pixel = image.file_header.bit_count / 8;
    const uint32_t bytes_per_row = (((image.file_header.width * bytes_per_pixel) + 3) / 4) * 4;
    for (int i = 0; i < image.file_header.height; ++i) {

        file.write(reinterpret_cast<const char *>(image.data.data() + i * bytes_per_row), bytes_per_row);
        /* code */
    }


    file.close();
}

BMPImage readBMP(const char *filename) {
    BMPFileHeader header;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(46);
    }
    // Чтение заголовка файла
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (header.signature != 0x4D42) { // 'BM'
        std::cerr << "Not a BMP file." << std::endl;
        exit(46);
    }


    // const uint32_t bytes_per_pixel = header.bit_count / 8;
    // const uint32_t bytes_per_row = (((header.width * bytes_per_pixel) + 3) / 4) * 4;

    // image_size = header.height * bytes_per_row;
    image_size = calculateImageSize(header);

    std::vector<uint8_t> dataNew;

    dataNew.resize(image_size);
    if (dataNew.empty()) {
        std::cerr << "Error allocating memory for image data" << std::endl;
        exit(45);
    }


    // Чтение данных изображения
    file.seekg(header.offset, std::ios::beg);
    file.read(reinterpret_cast<char *>(dataNew.data()), image_size);


    BMPImage image{header, dataNew};


    file.close();

    return image;

}


void printInfo(BMPImage &image, std::string filename) {
    std::cout << "File name: " << filename << std::endl;
    std::cout << "File type: " << image.file_header.signature << std::endl;
    std::cout << "Height: " << image.file_header.height << std::endl;
    std::cout << "Width: " << image.file_header.width << std::endl;
    std::cout << "Size: " << image.file_header.file_size << " bytes" << std::endl;
    std::cout << "Color depth: " << image.file_header.bit_count << std::endl;
    exit(0);

}

#endif