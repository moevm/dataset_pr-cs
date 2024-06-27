#ifndef BMP_H
#define BMP_H

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} rgb_t;

#pragma pack(push, 1)
typedef struct {
    unsigned short signature; // Сигнатура файла BMP (2 байт)
    unsigned int filesize; // Размер файла (4 байт)
    unsigned short reserved1; // Не используется (2 байт)
    unsigned short reserved2; // Не используется (2 байт)
    unsigned int pixel_arr_offset; // Местонахождение данных растрового массива (4 байт)
} bmp_header_t;

typedef struct {
    unsigned int header_size; // Длина этого заголовка (4 байт)
    unsigned int width; // Ширина изображения (4 байт)
    unsigned int height; // Высота изображения (4 байт)
    unsigned short planes; // Число цветовых плоскостей (2 байт)
    unsigned short bits_per_pixel; // Бит/пиксел (2 байт)
    unsigned int compression; // Метод сжатия (4 байт)
    unsigned int image_size; // Длина растрового массива (4 байт)
    unsigned int x_pixels_per_meter; // Горизонтальное разрешение (4 байт)
    unsigned int y_pixels_per_meter; // Вертикальное разрешение (4 байт)
    unsigned int colors_in_color_table; // Число цветов изображения (4 байт)
    unsigned int important_color_count; // Число основных цветов (4 байт)
} dib_header_t;

typedef struct {
    bmp_header_t bmph;
    dib_header_t dibh;
    rgb_t** rgb;
} bmp_file_t;
#pragma pack(pop)

bmp_file_t* read_bmp(char file_name[]);

void write_bmp(char file_name[], bmp_file_t* bmp_file);

void free_bmp_file(bmp_file_t* bmp_file);

void print_file_header(bmp_header_t header);

void print_info_header(dib_header_t header);

void print_help();

#endif
