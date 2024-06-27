#ifndef BMP_READER_H
#define BMP_READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <getopt.h>
#include <regex.h>

#pragma pack(push, 1)
typedef struct BmpFileHeader { // (информация) не зависит от конкретного изображения
  unsigned char ID[2]; //идентификатор файла(file's signature)
  unsigned int file_size; //размер файла в байтах(заголовки, данные)
  unsigned char unused[4]; // little endian
  unsigned int offset_pixels; //смещение(начальный адрес байта, в котором находится изображение)
} BmpFileHeader;

typedef struct BmpInfoHeader { // информация о изображении конкретном
  unsigned int header_size; // чисто изображение, без заголовков ((w * h * bpp) // 8 (байты))
  unsigned int width; // ширина
  unsigned int height; // высота
  unsigned short color_planes; // для каждого пикселя количество цветовых плоскостей
  unsigned short bits_per_pixel; // битов на пиксель(качество, количество цветов)
  unsigned int comp; // признак наличия сжатия(метод сжатия(есть нет))
  unsigned int data_size; // необработанные данные (выравнивание сторк пикселей)
  unsigned int pwidth; // разрешение для печати ширина
  unsigned int pheight; // разрешение для печати высота
  unsigned int colors_count; // количество цветов в палитре
  unsigned int imp_colors_count; // количество важных цветов (0 все важны)
} BmpInfoHeader;

typedef struct RGB {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}  rgb;

typedef struct BMPfile {
  BmpFileHeader bmpfh;
  BmpInfoHeader bmpih;
  rgb** data;
} BMPfile;

typedef struct coord{
    int x, y;
} coord;



#pragma pack(pop)

BMPfile* loadBMP(char* fname);
void readRowByRow(FILE* f, BMPfile* bmp_file);
void writeBMP(char* fname, BMPfile* bmp_file);
void freeBMP(BMPfile* bmp_file);
#endif
