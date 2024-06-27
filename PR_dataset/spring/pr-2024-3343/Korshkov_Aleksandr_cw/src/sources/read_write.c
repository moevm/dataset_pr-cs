#include "../include/read_write.h"

/* функция чтения из файла */
void read_png_file(char *file_name, Png *image)
{
    int x, y; /* размеры изображения */
    FILE *fp = fopen(file_name, "rb"); /* открытие файла в бинарном режиме */
    if (!fp)
    {
        printf("File \"%s\" not found!\n", file_name); /* файл не найден/не существует */
        exit(43);
    }

    char header[8]; /* заголовок файла */
    fread(header, 1, 8, fp); /* чтение заголовка */
    /* проверка заголовка */
    if (png_sig_cmp(header, 0, 8))
    {
        printf("Probably, file \"%s\" is not a png!\n", file_name);
        fclose(fp); /* закрытие файла */
        exit(42);
    }
    /* создание структуры для чтения изображения*/
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        printf("Error in png structure!\n"); /* структура не создана */
        fclose(fp); /* закрытие файла */
        exit(44);
    }
    /* создание структуры с информацией об изображении */
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("Error in png info-structure (information is broken)!\n"); /* структура не создана */
        png_destroy_read_struct(&image->png_ptr, NULL, NULL); /* удаление структур */
        fclose(fp); /* закрытие файла */
        exit(44);
    }
    /* неизвестная ошибка */
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        printf("Unknown Error!\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL); /* удаление структур */
        fclose(fp);
        exit(49);
    }

    png_init_io(image->png_ptr, fp); /* открытие потока ввода/вывода */
    png_set_sig_bytes(image->png_ptr, 8); /* установка заголовка */
    png_read_info(image->png_ptr, image->info_ptr); /* чтение информации об изображении */

    image->width = png_get_image_width(image->png_ptr, image->info_ptr); /* получение ширины изображения */
    image->height = png_get_image_height(image->png_ptr, image->info_ptr); /* получение высоты изображения */
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr); /* получение типа изображения */
    if (image->color_type != PNG_COLOR_TYPE_RGB && image->color_type != PNG_COLOR_TYPE_RGBA) {
        puts("The color type of image isn't RGB or RGBA.");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        exit(46);
    }
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr); /* получение глубины изображения (бит на пиксель) */
    image->number_of_passes = png_set_interlace_handling(image->png_ptr); /* получение количества проходов для инициализации */

    png_read_update_info(image->png_ptr, image->info_ptr); /* чтение информации об изображении */
    image->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height); /* выделение памяти под указатели на строки */
    for (y = 0; y < image->height; y++)
    {
        image->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr)); /* выделение памяти под строку */
    }
    png_read_image(image->png_ptr, image->row_pointers); /* чтение изображения */
    fclose(fp); /* закрытие файла */
}

/* функция записи в файл */
void write_png_file(char *file_name, Png *image)
{
    int x, y; /* размеры изображения */
    FILE *fp = fopen(file_name, "wb"); /* открытие файла для записи */

    if (!fp)
    {
        printf("The file \"%s\" cannot be created!\n", file_name); /* файл не может быть создан */
        exit(43);
    }
    /* создание структуры для записи */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        printf("It\'s impossible to write the structure of file \"%s\"!\n", file_name); /* структура не создана */
        fclose(fp); /* закрытие файла */
        exit(44);
    }
    /* создание структуры с информацией об изображении */
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        printf("It\'s impossible to write the information of file \"%s\"!\n", file_name);
        png_destroy_write_struct(&image->png_ptr, NULL);
        fclose(fp);
        exit(44);
    }
    /* неизвестная ошибка */
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        exit(49);
    }

    png_init_io(image->png_ptr, fp); /* открытие потока для записи */

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE); /* установка заголовка */

    /*запись информации об изображении */
    png_write_info(image->png_ptr, image->info_ptr);
    /* ошибка при записи информации об изображении */
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr); /* удаление структур */
        fclose(fp); /* закрытие файла */
        exit(45);
    }

    /* запись изображения */
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        exit(45);
    }
    png_write_end(image->png_ptr, NULL); /* завершение записи*/
    free_png(image);
    fclose(fp);
}