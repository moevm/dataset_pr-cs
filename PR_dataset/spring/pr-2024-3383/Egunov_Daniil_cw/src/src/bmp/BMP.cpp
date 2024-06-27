#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstdint>
#include <cmath>
#include "../../include/bmp/BMP.hpp"
#include "../../include/bmp/utility.hpp"
#include "../../include/bmp/exceptions.hpp"

BMP::BMP(size_t width, size_t height) :
        m_width(width),
        m_height(height),
        m_pixels(height, std::vector<RGB>(width)),
        m_fileHeader(std::make_unique<BitmapFileHeader>()),
        m_infoHeader(std::make_unique<BitmapInfoHeader>()) {
    updateHeaders();
}

BMP::BMP(size_t width, size_t height, const RGB &color) :
        m_width(width),
        m_height(height),
        m_pixels(height, std::vector<RGB>(width, color)),
        m_fileHeader(std::make_unique<BitmapFileHeader>()),
        m_infoHeader(std::make_unique<BitmapInfoHeader>()) {
    updateHeaders();
}

BMP::BMP(const BMP &image) :
        m_width(image.m_width),
        m_height(image.m_height),
        m_pixels(image.m_pixels),
        m_fileHeader(std::make_unique<BitmapFileHeader>(*image.m_fileHeader)),
        m_infoHeader(std::make_unique<BitmapInfoHeader>(*image.m_infoHeader)) {
    updateHeaders();
}

BMP::BMP(const BMP &image, const Point2D &point1, const Point2D &point2) {
    auto [start, end] = arrangePointsCoordinates(point1, point2);
    image.fitPointInBounds(start);
    image.fitPointInBounds(end);

    m_width = end.x - start.x;
    m_height = end.y - start.y;

    m_pixels.reserve(m_height);
    for (int64_t y = start.y; y < end.y; y++) {
        std::vector<RGB> row = std::vector<RGB>(image.m_pixels[y].begin() + static_cast<long>(start.x),
                                                image.m_pixels[y].begin() + static_cast<long>(end.x));
        m_pixels.push_back(row);
    }

    m_fileHeader = std::make_unique<BitmapFileHeader>(*image.m_fileHeader);
    m_infoHeader = std::make_unique<BitmapInfoHeader>(*image.m_infoHeader);
    updateHeaders();
}

BMP::BMP(const std::string &filepath) {
    readFromFile(filepath);
}

BMP::BMP(const char *filepath) {
    readFromFile(filepath);
}

BMP::~BMP() = default;

uint32_t BMP::getHeight() const {
    return m_height;
}

uint32_t BMP::getWidth() const {
    return m_width;
}

bool BMP::isPointInside(const Point2D &point) const {
    return Point2D{0, 0} <= point && point < Point2D{m_width, m_height};
}

void BMP::fitPointInBounds(Point2D &point) const {
    point.x = std::max(0l, std::min(point.x, static_cast<int64_t>(m_width) - 1));
    point.y = std::max(0l, std::min(point.y, static_cast<int64_t>(m_height) - 1));
}

const RGB &BMP::getPixelColor(const Point2D &point) const {
    if (!isPointInside(point)) {
        throw std::out_of_range(
                "BMP::getPixelColor: " + std::string(point) + " beyond the boundaries of the image"
        );
    }
    return m_pixels[point.y][point.x];
}

void BMP::setPixelColor(const Point2D &point, const RGB &color) {
    if (!isPointInside(point)) {
        throw std::out_of_range(
                "BMP::setPixelColor: " + std::string(point) + " beyond the boundaries of the image"
        );
    }
    m_pixels[point.y][point.x] = color;
}

void BMP::readFileHeader(std::ifstream &stream, BitmapFileHeader &header) {
    readFromStream(stream, header.bfType);
    readFromStream(stream, header.bfSize);
    readFromStream(stream, header.bfReserved1);
    readFromStream(stream, header.bfReserved2);
    readFromStream(stream, header.bfOffBits);
}

void BMP::readInfoHeader(std::ifstream &stream, BitmapInfoHeader &header) {
    readFromStream(stream, header.biSize);
    readFromStream(stream, header.biWidth);
    readFromStream(stream, header.biHeight);
    readFromStream(stream, header.biPlanes);
    readFromStream(stream, header.biBitCount);
    readFromStream(stream, header.biCompression);
    readFromStream(stream, header.biSizeImage);
    readFromStream(stream, header.biXPelsPerMeter);
    readFromStream(stream, header.biYPelsPerMeter);
    readFromStream(stream, header.biClrUsed);
    readFromStream(stream, header.biClrImportant);
}

void BMP::writeFileHeader(std::ofstream &stream, const BitmapFileHeader &header) {
    writeToStream(stream, header.bfType);
    writeToStream(stream, header.bfSize);
    writeToStream(stream, header.bfReserved1);
    writeToStream(stream, header.bfReserved2);
    writeToStream(stream, header.bfOffBits);
}

void BMP::writeInfoHeader(std::ofstream &stream, const BitmapInfoHeader &header) {
    writeToStream(stream, header.biSize);
    writeToStream(stream, header.biWidth);
    writeToStream(stream, header.biHeight);
    writeToStream(stream, header.biPlanes);
    writeToStream(stream, header.biBitCount);
    writeToStream(stream, header.biCompression);
    writeToStream(stream, header.biSizeImage);
    writeToStream(stream, header.biXPelsPerMeter);
    writeToStream(stream, header.biYPelsPerMeter);
    writeToStream(stream, header.biClrUsed);
    writeToStream(stream, header.biClrImportant);
}

void BMP::updateHeaders() {
    static const uint32_t fileHeaderSize = 14;
    static const uint32_t infoHeaderSize = 40;

    const uint32_t paddingSize = (4 - (m_width * 3) % 4) % 4;
    const uint32_t sizeImage = m_height * (m_width * 3 + paddingSize);
    const uint32_t fileSize = fileHeaderSize + infoHeaderSize + sizeImage;

    m_fileHeader->bfType = 'M' << 8 | 'B';
    m_fileHeader->bfSize = fileSize;
    m_fileHeader->bfReserved1 = 0;
    m_fileHeader->bfReserved2 = 0;
    m_fileHeader->bfOffBits = fileHeaderSize + infoHeaderSize;

    m_infoHeader->biSize = infoHeaderSize;
    m_infoHeader->biWidth = static_cast<int32_t>(m_width);
    m_infoHeader->biHeight = static_cast<int32_t>(m_height);
    m_infoHeader->biPlanes = 3;
    m_infoHeader->biBitCount = 24;
    m_infoHeader->biCompression = 0;
    m_infoHeader->biSizeImage = sizeImage;
    if (m_infoHeader->biXPelsPerMeter == 0)
        m_infoHeader->biXPelsPerMeter = 2835;
    if (m_infoHeader->biYPelsPerMeter == 0)
        m_infoHeader->biYPelsPerMeter = 2835;
    m_infoHeader->biClrUsed = 0;
    m_infoHeader->biClrImportant = 0;
}

void BMP::writeToFile(const std::string &filepath) {
    updateHeaders();

    std::ofstream file(filepath, std::ios::binary);

    if (!file.good()) {
        throw std::ofstream::failure("BMP::writeToFile: Error opening file " + filepath);
    }

    writeFileHeader(file, *m_fileHeader);
    writeInfoHeader(file, *m_infoHeader);

    char padding[3] = {0, 0, 0};
    const size_t paddingSize = (4 - (m_width * 3) % 4) % 4;

    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            RGB color = m_pixels[m_height - y - 1][x];
            uint8_t color_arr[] = {color.b, color.g, color.r};
            writeToStream(file, color_arr);
        }
        file.write(padding, static_cast<long>(paddingSize));
    }

    if (file.fail()) {
        throw std::ifstream::failure("BMP::writeToFile: Error writing to file " + filepath);
    }
}

void BMP::writeToFile(const char *filepath) {
    writeToFile(std::string(filepath));
}

void BMP::readFromFile(const std::string &filepath) {
    // BitmapFileHeader desired variables
    static const uint16_t type = 'M' << 8 | 'B';
    static const uint32_t pixelsOffset = 54;

    // BitmapInfoHeader desired variables
    static const uint32_t infoHeaderSize = 40;
    static const uint16_t planes = 1;
    static const uint16_t bitCount = 24;
    static const uint32_t compression = 0;
    static const uint32_t clrUsed = 0;

    std::ifstream file(filepath, std::ios::binary);

    if (!file.good()) {
        throw std::ifstream::failure("BMP::readFromFile: Error opening file " + filepath);
    }

    m_fileHeader = std::make_unique<BitmapFileHeader>();
    readFileHeader(file, *m_fileHeader);
    if (file.fail()) {
        throw std::ifstream::failure("BMP::readFromFile: Error reading file header from file " + filepath);
    }

    if (m_fileHeader->bfType != type) {
        throw std::ifstream::failure("BMP::readFromFile: File " + filepath + " is not a bitmap image");
    }

    if (m_fileHeader->bfOffBits != pixelsOffset) {
        throw UnsupportedBMPHeaderFieldValueError(filepath,
                                                  "bfOffBits",
                                                  std::to_string(m_fileHeader->bfOffBits),
                                                  std::to_string(pixelsOffset)
        );
    }

    m_infoHeader = std::make_unique<BitmapInfoHeader>();
    readInfoHeader(file, *m_infoHeader);
    if (file.fail()) {
        throw std::ifstream::failure("BMP::readFromFile: Error reading info header from file " + filepath);
    }

    if (m_infoHeader->biSize != infoHeaderSize) {
        throw UnsupportedBMPHeaderFieldValueError(
                filepath,
                "biSize",
                std::to_string(m_infoHeader->biSize),
                std::to_string(infoHeaderSize)
        );
    }

    if (m_infoHeader->biPlanes != planes) {
        throw UnsupportedBMPHeaderFieldValueError(
                filepath,
                "biPlanes",
                std::to_string(m_infoHeader->biPlanes),
                std::to_string(planes)
        );
    }

    if (m_infoHeader->biBitCount != bitCount) {
        throw UnsupportedBMPHeaderFieldValueError(
                filepath,
                "biBitCount",
                std::to_string(m_infoHeader->biBitCount),
                std::to_string(bitCount)
        );
    }

    if (m_infoHeader->biCompression != compression) {
        throw UnsupportedBMPHeaderFieldValueError(
                filepath,
                "biCompression",
                std::to_string(m_infoHeader->biCompression),
                std::to_string(compression)
        );
    }

    if (m_infoHeader->biClrUsed != clrUsed) {
        throw UnsupportedBMPHeaderFieldValueError(
                filepath,
                "biClrUsed",
                std::to_string(m_infoHeader->biClrUsed),
                std::to_string(clrUsed)
        );
    }

    m_width = m_infoHeader->biWidth;
    m_height = m_infoHeader->biHeight;
    m_pixels = std::vector(m_height, std::vector<RGB>(m_width));

    const size_t paddingSize = (4 - (m_width * 3) % 4) % 4;

    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            uint8_t color[3];
            readFromStream(file, color);

            m_pixels[m_height - y - 1][x].r = color[2];
            m_pixels[m_height - y - 1][x].g = color[1];
            m_pixels[m_height - y - 1][x].b = color[0];
        }
        file.ignore(static_cast<long>(paddingSize)
        );
    }

    if (file.fail()) {
        throw std::ifstream::failure("BMP::readFromFile: Error reading pixel data from file " + filepath);
    }
}

void BMP::readFromFile(const char *filepath) {
    readFromFile(std::string(filepath));
}

void BMP::crop(const Point2D &point1, const Point2D &point2) {
    auto [start, end] = arrangePointsCoordinates(point1, point2);
    fitPointInBounds(start);
    fitPointInBounds(end);

    m_width = end.x - start.x + 1;
    m_height = end.y - start.y + 1;

    std::vector<std::vector<RGB>> new_pixels;
    new_pixels.reserve(m_height);
    for (int64_t y = start.y; y < end.y; ++y) {
        std::vector<RGB> row{m_pixels[y].begin() + static_cast<long>(start.x),
                             m_pixels[y].begin() + static_cast<long>(end.x)};
        new_pixels.push_back(row);
    }
    m_pixels = new_pixels;
}

void BMP::resize(size_t width, size_t height, const RGB &color = RGB()) {
    if (width == 0 || height == 0) {
        width = height = 0;
    }

    m_pixels.resize(height, std::vector<RGB>(width, color));

    size_t rows_to_resize = std::min(static_cast<size_t>(m_height), height);
    for (size_t y = 0; y < rows_to_resize; ++y) {
        m_pixels[y].resize(width, color);
    }

    m_width = width;
    m_height = height;
}

void BMP::insert(const BMP &image, const Point2D &dest) {
    if (dest.x >= m_width || dest.y >= m_height) return;

    Point2D actual_dest(dest);
    fitPointInBounds(actual_dest);
    Point2D diff{actual_dest.x - dest.x, actual_dest.y - dest.y};

    size_t rows_to_insert = std::min(image.m_height - diff.y, m_height - actual_dest.y);
    size_t cols_to_insert = std::min(image.m_width - diff.x, m_width - actual_dest.x);
    for (size_t y = 0; y < rows_to_insert; ++y) {
        for (size_t x = 0; x < cols_to_insert; ++x) {
            m_pixels[actual_dest.y + y][actual_dest.x + x] = image.m_pixels[diff.y + y][diff.x + x];
        }
    }
}

void BMP::mirror(const Axis axis, const Point2D &point1, const Point2D &point2) {
    auto [start, end] = arrangePointsCoordinates(point1, point2);
    fitPointInBounds(start);
    fitPointInBounds(end);

    switch (axis) {
        case Axis::X:
            for (int64_t y = start.y; y < end.y; ++y) {
                for (int64_t x = 0; x < (end.x - start.x + 1) / 2; ++x) {
                    std::swap(m_pixels[y][start.x + x], m_pixels[y][end.x - x]);
                }
            }
            break;
        case Axis::Y:
            for (int64_t x = start.x; x < end.x; ++x) {
                for (int64_t y = 0; y < (end.y - start.y + 1) / 2; ++y) {
                    std::swap(m_pixels[start.y + y][x], m_pixels[end.y - y][x]);
                }
            }
            break;
    }
}

void BMP::copy(const Point2D &point1, const Point2D &point2, const Point2D &dest) {
    if (dest.x >= m_width || dest.y >= m_height) return;

    auto [start, end] = arrangePointsCoordinates(point1, point2);
    fitPointInBounds(start);
    fitPointInBounds(end);

    Point2D actual_dest(dest);
    fitPointInBounds(actual_dest);
    Point2D diff{actual_dest.x - dest.x, actual_dest.y - dest.y};

    auto new_pixels(m_pixels);
    size_t rows_to_copy = std::min(end.y - start.y - diff.y, m_height - actual_dest.y);
    size_t cols_to_copy = std::min(end.x - start.x - diff.x, m_width - actual_dest.x);
    for (size_t y = 0; y < rows_to_copy; ++y) {
        for (size_t x = 0; x < cols_to_copy; ++x) {
            new_pixels[actual_dest.y + y][actual_dest.x + x] = m_pixels[start.y + diff.y + y][start.x + diff.x + x];
        }
    }
    m_pixels = new_pixels;
}

void BMP::replaceColor(const RGB &old_color, const RGB &new_color) {
    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            if (m_pixels[y][x] == old_color) {
                m_pixels[y][x] = new_color;
            }
        }
    }
}

void BMP::split(size_t number_x, size_t number_y, const RGB &color, size_t thickness) {
    if (number_x == 0 || number_y == 0) return;

    int overall_parts_width = static_cast<int>(m_width) - static_cast<int>((number_x - 1) * thickness);
    int overall_parts_height = static_cast<int>(m_height) - static_cast<int>((number_y - 1) * thickness);
    int part_width = std::floor(static_cast<float> (overall_parts_width) / static_cast<float> (number_x));
    int part_height = std::floor(static_cast<float> (overall_parts_height) / static_cast<float> (number_y));

    if (part_width <= 0 && part_height <= 0) {
        for (size_t y = 0; y < m_height; ++y) {
            for (size_t x = 0; x < m_width; ++x) {
                m_pixels[y][x] = color;
            }
        }
        return;
    }

    int start_x = part_width;
    int start_y = part_height;
    int step_x = part_width + static_cast<int>(thickness);
    int step_y = part_height + static_cast<int>(thickness);

    for (size_t x = start_x; x < m_width; x += step_x) {
        size_t cols_to_draw = std::min(thickness, m_width - x);
        for (size_t y = 0; y < m_height; ++y) {
            for (size_t i = 0; i < cols_to_draw; ++i) {
                m_pixels[y][x + i] = color;
            }
        }
    }
    for (size_t y = start_y; y < m_height; y += step_y) {
        size_t rows_to_draw = std::min(thickness, m_height - y);
        for (size_t x = 0; x < m_width; ++x) {
            for (size_t i = 0; i < rows_to_draw; ++i) {
                m_pixels[y + i][x] = color;
            }
        }
    }
}

void BMP::printInfo() {
    std::cout << "Type: " << m_fileHeader->bfType << std::endl;
    std::cout << "Size: " << m_fileHeader->bfSize << std::endl;
    std::cout << "Reserved 1: " << m_fileHeader->bfReserved1 << std::endl;
    std::cout << "Reserved 2: " << m_fileHeader->bfReserved2 << std::endl;
    std::cout << "Offset: " << m_fileHeader->bfOffBits << std::endl;

    std::cout << "Header size: " << m_infoHeader->biSize << std::endl;
    std::cout << "Width: " << m_infoHeader->biWidth << std::endl;
    std::cout << "Height: " << m_infoHeader->biHeight << std::endl;
    std::cout << "Planes: " << m_infoHeader->biPlanes << std::endl;
    std::cout << "Bits per pixel: " << m_infoHeader->biBitCount << std::endl;
    std::cout << "Compression: " << m_infoHeader->biCompression << std::endl;
    std::cout << "Image size: " << m_infoHeader->biSizeImage << std::endl;
    std::cout << "Horizontal resolution: " << m_infoHeader->biXPelsPerMeter << std::endl;
    std::cout << "Vertical resolution: " << m_infoHeader->biYPelsPerMeter << std::endl;
    std::cout << "Used colors: " << m_infoHeader->biClrUsed << std::endl;
    std::cout << "Important colors: " << m_infoHeader->biClrImportant << std::endl;
}

void BMP::outsideOrnament(size_t thickness, const RGB &color) {
    uint32_t new_width = m_width + 2 * thickness;
    uint32_t new_height = m_height + 2 * thickness;
    std::vector<std::vector<RGB>> new_pixels(new_height, std::vector<RGB>(new_width, color));

    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            new_pixels[thickness + y][thickness + x] = m_pixels[y][x];
        }
    }

    m_pixels = new_pixels;
    m_width = new_width;
    m_height = new_height;
}
