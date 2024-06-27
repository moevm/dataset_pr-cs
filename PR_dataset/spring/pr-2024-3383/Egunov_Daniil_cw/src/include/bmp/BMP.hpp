#ifndef BMP_BMP_HPP
#define BMP_BMP_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include "Axis.hpp"
#include "Point2D.hpp"
#include "RGB.hpp"

class BMP {
protected:
    struct BitmapFileHeader {
        std::uint16_t bfType{'M' << 8 | 'B'};
        std::uint32_t bfSize{0};
        std::uint16_t bfReserved1{0};
        std::uint16_t bfReserved2{0};
        std::uint32_t bfOffBits{54};
    };
    struct BitmapInfoHeader {
        std::uint32_t biSize{40};
        std::int32_t biWidth{0};
        std::int32_t biHeight{0};
        std::uint16_t biPlanes{1};
        std::uint16_t biBitCount{24};
        std::uint32_t biCompression{0};
        std::uint32_t biSizeImage{0};
        std::int32_t biXPelsPerMeter{2835};
        std::int32_t biYPelsPerMeter{2835};
        std::uint32_t biClrUsed{0};
        std::uint32_t biClrImportant{0};
    };

    uint32_t m_width{0};
    uint32_t m_height{0};

    std::vector<std::vector<RGB>> m_pixels{};

    std::unique_ptr<BitmapFileHeader> m_fileHeader{};
    std::unique_ptr<BitmapInfoHeader> m_infoHeader{};

    static void readFileHeader(std::ifstream &stream, BitmapFileHeader &header);

    static void readInfoHeader(std::ifstream &stream, BitmapInfoHeader &header);

    static void writeFileHeader(std::ofstream &stream, const BitmapFileHeader &header);

    static void writeInfoHeader(std::ofstream &stream, const BitmapInfoHeader &header);

    void updateHeaders();

    [[nodiscard]] bool isPointInside(const Point2D &point) const;

    void fitPointInBounds(Point2D &point) const;

public:
    BMP(size_t width, size_t height);

    BMP(size_t width, size_t height, const RGB &color);

    BMP(const BMP &image);

    BMP(const BMP &image, const Point2D &start, const Point2D &end);

    explicit BMP(const char *filepath);

    explicit BMP(const std::string &filepath);

    ~BMP();

    [[nodiscard]] const RGB &getPixelColor(const Point2D &point) const;

    void setPixelColor(const Point2D &point, const RGB &color);

    [[nodiscard]] uint32_t getHeight() const;

    [[nodiscard]] uint32_t getWidth() const;

    void writeToFile(const std::string &filepath);

    void writeToFile(const char *filepath);

    void readFromFile(const std::string &filepath);

    void readFromFile(const char *filepath);

    void printInfo();

    void crop(const Point2D &point1, const Point2D &point2);

    void resize(size_t width, size_t height, const RGB &color);

    void insert(const BMP &image, const Point2D &dest);

    void mirror(Axis axis, const Point2D &start, const Point2D &end);

    void copy(const Point2D &start, const Point2D &end, const Point2D &dest);

    void replaceColor(const RGB &old_color, const RGB &new_color);

    void split(size_t number_x, size_t number_y, const RGB &color, size_t thickness);

    void outsideOrnament(size_t thickness, const RGB &color);
};

#endif //BMP_BMP_HPP
