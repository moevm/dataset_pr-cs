#ifndef INVERSE_H
#define INVERSE_H
#include <vector>
#include <iostream>
#include "bmp.h"

void inverse_all(BMPImage& image_data);
Pixel get_pixel(BMPImage& info, int y, int x);
void set_pixel(BMPImage& info, int y, int x, Pixel pixel);
void component_max(BMPImage& image_data, std::string color);
void printInfo(BMPImage& image, std::string filename);
void shift_func(BMPImage& info,int shiftvalue,std::string axisfield);
bool validateShift(OptionFlags& flags);
void shift_x(BMPImage& info, int shiftvalue);
void shift_y(BMPImage &info, int shiftvalue);
void hsvconvert(BMPImage& info);
// void process_image(BMPImage* image, const std::string& component_name);
#endif