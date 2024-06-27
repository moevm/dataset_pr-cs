#ifndef COURSE_WORK_STRUCTURESDEFINITION_HPP
#define COURSE_WORK_STRUCTURESDEFINITION_HPP

#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <fstream>

#pragma pack (push, 1)

typedef struct BitmapFileHeader {
    /** Bitmap file header structure that contains: */
    unsigned short signature; /**< signature that must be 'BM' */
    unsigned int fileSize; /**< size of file in bytes */
    unsigned short reserved1; /**< reserved1 count of bytes */
    unsigned short reserved2; /**< reserved2 count of bytes */
    unsigned int pixelArrOffset; /**< offset to pixel array in bytes */
} BitmapFileHeader;

typedef struct BitmapInfoHeader {
    /** Bitmap info header structure that contains: */
    unsigned int headerSize; /**< size of header in bytes */
    unsigned int width; /**< width of image in pixels */
    unsigned int height; /**< height of image in pixels */
    unsigned short planes; /**< planes count (should be 1) */
    unsigned short bitsPerPixel; /**< bits per pixel */
    unsigned int compression; /**< compression method */
    unsigned int imageSize; /**< image size in bytes */
    unsigned int xPixelsPerMeter; /**< x pixels per meter */
    unsigned int yPixelsPerMeter; /**< y pixels per meter */
    unsigned int colorsInColorTable; /**< colors in color table */
    unsigned int importantColorCount; /**< important color count */
} BitmapInfoHeader;

typedef struct Rgb {
    /** structure that contains: */
    unsigned char blue; /**< blue value */
    unsigned char green; /**< green value */
    unsigned char red; /**< red value */
} Rgb;
#pragma pack(pop)

class Bmp {
public:
    explicit
    Bmp(const char *filename); //defined in additional_funcs.cpp

    ~Bmp(); //defined in additional_funcs.cpp

    void
    get_info(); //defined in additional_funcs.cpp

    void
    save(const char *output_filename); //defined in additional_funcs.cpp

    void
    draw_rectangle(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness, const char *color,
                   bool fill, const char *fillColor); //defined in drawing_funcs.cpp

    void
    draw_circle(std::pair<int, int> center, unsigned int radius, unsigned int thickness, const char *color,
                bool fill, const char *fillColor); //defined in drawing_funcs.cpp

    void
    drawOrnament(const char *pattern, const char *color, size_t thickness, size_t count); //defined in drawing_funcs.cpp

    void
    rotate_image(std::pair<int, int> leftUp, std::pair<int, int> rightDown, int angle); //defined in rotate_func.cpp

    void straight_angle(std::pair<int, int> leftUp, std::pair<int, int> rightDown); //defined in rotate_func.cpp

    void full_right_angle();

    void field_right_angle(std::pair<int, int> leftUp, std::pair<int, int> rightDown);

    void field_right_and_straight_angle(std::pair<int, int> leftUp, std::pair<int, int> rightDown);

    void check_coordinates(std::pair<int, int> &leftUp, std::pair<int, int> &rightDown);

    void
    draw_line(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness, const char *color);

    void koch(int x1, int y1, int x2, int y2, unsigned int thickness, const char *color, int count, int i);

    void
    draw_snowflake(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness, const char *color, int count);

    void fill_circle(std::pair<int,int> center, int radius, const char *color);

    void compress(int n);

private:
    BitmapFileHeader *header;
    BitmapInfoHeader *info;
    Rgb **data;
    int padding;
};

#endif //COURSE_WORK_STRUCTURESDEFINITION_HPP
