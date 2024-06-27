#ifndef IMAGE_BMP
#define IMAGE_BMP

#include "structures.h"

#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <limits.h>

#define VERTICAL                     0
#define HORIZONTAL                   1
#define FILE_ERROR                   40
#define BMP_PROCESSING_ERROR         41

namespace ie
{

void throwError(const char *message, int exit_code);

bool checkFileFormat(unsigned char *signature, unsigned int compression,
    unsigned short bits_per_pixel);

class ImageBMP
{
public:
    ImageBMP();

    ~ImageBMP();

    int getWidth();
    
    int getHeight();

    void readImageFromFile(const char *input_file_name);

    void showImageInfo();

    void writeImageToFile(const char *output_file_name);

    void clear();

    void setSize(int width, int height);
    
    ImageBMP copy(int x0, int y0, int x1, int y1);

    Color getColor(int x, int y);

    void setColor(int x, int y, Color color);

    void drawLine(int x0, int y0, int x1, int y1, 
        int thickness, Color color);

    void drawBresenhamCircle(int x0, int y0, int radius, Color color);

    void drawCircle(int x0, int y0, int radius, int thickness, 
        Color color, bool fill, Color fill_color);

    void rgbFilter(int component_idx, int component_value);

    void concatBMP(ImageBMP& second_image_bmp, int axis, Color fill_color);

    void borderRectangles(Color rectangles_color, Color border_color, int thickness);

    bool checkCoordsValidity(int x, int y);

private:
    BMPHeader            bmph;
    DIBHeader            dibh;
    int                  Width;
    int                  Height;
    RGB                  **bitmap;

    void allocateMemmoryForPixels();

    void freeMemmoryForPixels();

    void clearPixels();

    void drawLineHigh(int x0, int y0, int x1, int y1, 
        int thickness, Color color);

    void drawLineLow(int x0, int y0, int x1, int y1, 
        int thickness, Color color);
};

}
#endif