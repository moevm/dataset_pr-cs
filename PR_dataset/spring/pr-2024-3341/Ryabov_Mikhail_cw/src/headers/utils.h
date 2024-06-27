#pragma once
#include "defines.h"

void callHelp();
void callInfo(char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo);
void callError(int status);
void print_file_header(const BitmapFileHeader header);
void print_info_header(const BitmapInfoHeader header);
void strToDouble(char* num, double* val);
void parseCoords(char* coords, int* x, int* y);
void strToNum(char* num, int* val);
void strToRGB(char* str, Rgb* color);
char* getStrClone(const char* src);
Rgb** readFile(const char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo);
void writeFile(const char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo, Rgb** arr);
unsigned int padding(const unsigned int width);
unsigned int lenRow(const unsigned int width);
int matchRegExp(const char* buffer, const char* pattern);
int isCorrectType(char* type);
void checkCorrectPlacement(int* left, int* up, int* right, int* down, int width, int height);
void validCoord(int* value, const int edge);

