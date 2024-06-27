#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include "BGR.h"
using namespace std;

class BMP {
private:

    typedef struct {
        unsigned short signature;
        unsigned int filesize;
        unsigned int reserved1;
        unsigned int reserved2;
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

    unsigned short read_u16(FILE *fp);

    unsigned int read_u32(FILE *fp);

    void write_u16(unsigned short value, FILE *fp);

    void write_u32(unsigned int value, FILE *fp);

    void writeBitmapFile(const char* outfilename);

    void set_color(vector<vector<Bgr> > *vector_name, int y, int x, Bgr color);

    void fill_circle(int center_x, int center_y, int radius, Bgr color);


public:

    BitmapFileHeader header;
    BitmapInfoHeader bmiHeader;
    vector<vector<Bgr>> pixels;

    int readBitmapFile(const char *filename);

    void INFO();

    void black_and_white(const char *outfilename, int left, int up, int right, int below);

    void inversion(const char *outfilename, int left, int up, int right, int below);

    void draw_lines_with_thickness(const char* outfilename, int x00, int y00, int x11, int y11, int thickness, Bgr color);

    void resize(const char *outfilename, string direction, int size, Bgr color = {255, 255, 255});

    void ornament(const char *outfilename, int thickness, Bgr color);
};