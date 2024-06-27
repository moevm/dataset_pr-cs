#include "bmp.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

bmp_file_t* read_bmp(char file_name[])
{
    int i, j;
    unsigned int h, w;
    FILE* file;
    bmp_file_t* bmp_file;

    file = fopen(file_name, "rb");
    if (!file) {
        raise_error("incorrect file name", FILE_OPEN_ERR);
    }
    bmp_file = (bmp_file_t*)malloc(sizeof(bmp_file_t));
    fread(&bmp_file->bmph, sizeof(bmp_header_t), 1, file);
    if (bmp_file->bmph.signature != 0x4d42) {
        raise_error("incorrect file type", FILE_TYPE_ERR);
    }
    fread(&bmp_file->dibh, sizeof(dib_header_t), 1, file);

    h = bmp_file->dibh.height;
    w = bmp_file->dibh.width;
    bmp_file->rgb = (rgb_t**)malloc(h * sizeof(rgb_t*));

    for (i = 0; i < h; ++i) {
        bmp_file->rgb[h - 1 - i] = (rgb_t*)malloc(w * sizeof(rgb_t) + (4 - (w * sizeof(rgb_t)) % 4) % 4);
        fread(bmp_file->rgb[h - 1 - i], 1, w * sizeof(rgb_t) + (4 - (w * sizeof(rgb_t)) % 4) % 4, file);
    }
    fclose(file);
    return bmp_file;
}

void write_bmp(char file_name[], bmp_file_t* bmp_file)
{
    int i;
    unsigned int h, w;
    FILE* file;

    file = fopen(file_name, "wb");
    fwrite(&bmp_file->bmph, 1, sizeof(bmp_header_t), file);
    fwrite(&bmp_file->dibh, 1, sizeof(dib_header_t), file);
    h = bmp_file->dibh.height;
    w = bmp_file->dibh.width;

    for (i = 0; i < h; i++) {
        fwrite(bmp_file->rgb[h - 1 - i], 1, w * sizeof(rgb_t) + (4 - (w * sizeof(rgb_t)) % 4) % 4, file);
    }
    fclose(file);
}

void free_bmp_file(bmp_file_t* bmp_file)
{
    int i;

    if (bmp_file) {
        if (bmp_file->rgb) {
            for (i = 0; i < bmp_file->dibh.height; i++)
                free(bmp_file->rgb[i]);
            free(bmp_file->rgb);
        }
        free(bmp_file);
    }
}

void print_file_header(bmp_header_t header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixel_arr_offset, header.pixel_arr_offset);
    exit(EXIT_SUCCESS);
}

void print_info_header(dib_header_t header)
{
    printf("headerSize:\t%x (%u)\n", header.header_size, header.header_size);
    printf("Width: \t%x (%u)\n", header.width, header.width);
    printf("Height: \t%x (%u)\n", header.height, header.height);
    printf("Planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("Bint per pixel:\t%x (%hu)\n", header.bits_per_pixel, header.bits_per_pixel);
    printf("Compression:\t%x (%u)\n", header.compression, header.compression);
    printf("Image size:\t%x (%u)\n", header.image_size, header.image_size);
    printf("X pizels per meter:\t%x (%u)\n", header.x_pixels_per_meter, header.x_pixels_per_meter);
    printf("Y pizels per meter:\t%x (%u)\n", header.y_pixels_per_meter, header.y_pixels_per_meter);
    printf("Colors in color table:\t%x (%u)\n", header.colors_in_color_table, header.colors_in_color_table);
    printf("Important color count:\t%x (%u)\n", header.important_color_count, header.important_color_count);
    exit(EXIT_SUCCESS);
}

void print_help()
{
    printf("Course work for option 5.5, created by Naumkin Artyom.\n"
           "Options:\n"
           "-i, --input <file.bmp>: Исходное изображение\n"
           "-o, --output  <file.bmp>: Вывод полученного изображения\n"
           "-h, --help: Вывод справки\n\n"

           "--inverse_circle: Инверировать цвета внутри окружности\n"
           "--center: Координаны центра\n"
           "--radius: Радиус\n\n"

           "--trim: Обрезка изображения\n"
           "--left_up: Координата левого нижнего угла\n"
           "--righ_down: Координата правого верхнего угла\n\n"

           "--triangle: Рисование треугольника\n"
           "--points <x0.y0.x1.y1.x2.y2>: Координаты вершин\n"
           "--color <rrr.ggg.bbb>: Цвет рамки\n"
           "--fill <0|1>: Флаг заливки\n"
           "--fill_color <rrr.ggg.bbb>: Цвет заливки\n"
           "--thickness <num>: Толщина рамки\n\n"

           "--line: Рисовании линии\n"
           "--start <x0.y0>: Координаты начала линии\n"
           "--end <x0.y0>: Координаты конца линии\n"
           "--color <rrr.ggg.bbb>: Цвет линии\n"
           "--thickness <num>: Толщина линии\n");
}