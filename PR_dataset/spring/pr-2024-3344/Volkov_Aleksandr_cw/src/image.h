#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define PIXSIZE 3 * sizeof(png_byte)

#define STR_ERR_OPEN "Invalid file\n"
#define STR_ERR_PNG_STRUCT "Failed to create png struct\n"
#define STR_ERR_READ_PNG "Failed to read png file\n"
#define STR_ERR_WRITE_PNG "Failed to write png file\n"
#define STR_ERR_COLOR "RGB color model and 8-bit depth are expected\n"

// Ошибки чтения-записи PNG файлов
#define ERR_OPEN 101
#define ERR_PNG_STRUCT 102
#define ERR_WRITE_PNG 103
#define ERR_PNGLIB_ERROR 104

// Ошибки изменения изображения
#define ERR_INVALID_SIZE 201

typedef png_uint_32 uint;

// Структура цвета RGB
typedef struct color_struct
{
    double R;
    double G;
    double B;
} color;

// Структура точки
typedef struct point_struct
{
    double x;
    double y;
} point;

// Структура пикселя (точка + указатель на место в массиве байт)
typedef struct pixel_struct
{
    point *pos;
    png_bytep byte;
} pixel;

// Структура изображения
typedef struct image_struct
{
    char *path;
    uint width;
    uint height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytepp bytes;
} image;

// Структура рабочей области
typedef struct selection_struct
{
    point *start;
    point *end;
    image *img;
} selection;

color *init_color(double R, double G, double B);
point *init_point(double x, double y);
pixel *init_pixel(point *pos, png_bytep byte);
selection *init_selection(image *img, point *start, point *end);
image* init_image(uint width, uint height, color* clr);
selection *select_all(image *img);
image *load_image(char *path);
image *copy_image(image *img);
int save_image(image *img, char *path);
pixel *read_selection(selection *slct);
void free_pixel(pixel** pix);
void free_image(image **img);
void free_selection(selection** slct);