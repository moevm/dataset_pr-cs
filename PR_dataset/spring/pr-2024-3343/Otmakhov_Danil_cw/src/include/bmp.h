#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "command_line.h"


void checkBMPFileFormat(BitmapFileHeader bmfhdr);

void printFileHeader(BitmapFileHeader header);

void printInfoHeader(BitmapInfoHeader header);

void printBMPFileInfo(BMP* bmp_file);

BMP* readBMPFile(char file_name[]);

bool compareColor(RGB first_color, RGB second_color);

void setColor(BMP* bmp_file, int x, int y, RGB new_color);

void colorReplace(BMP* bmp_file, CommandLineOptions* options);

void rgbFilter(BMP* bmp_file, CommandLineOptions* options);

void split(BMP* bmp_file, CommandLineOptions* options);

void writeBMPFile(char file_name[], BMP* bmp_file);

void freeBMPFile(BMP* bmp_file);

//void swapInt(int* a, int* b);

//RGB** copy(BMP* bmp_file, int x0, int y0, int x1, int y1);

//void paste(BMP* bmp_file, int x0, int y0, RGB** buf, int buf_h, int buf_w);

//void shift(BMP* bmp_file, CommandLineOptions* options);

void binarization(BMP* bmp_file, CommandLineOptions* options);


#endif
