#ifndef WRITE_AND_READ
#define WRITE_AND_READ
#include "bmp.h"
void writeBMP(std::string &filename, BMPImage& image);
BMPImage readBMP(const char* filename);
void printInfo(BMPImage& image, std::string filename);
#endif