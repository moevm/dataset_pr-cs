#include "input.h"

void read_png_file(char *file_name, struct Png *image) {

    int x, y;
    char header[8]; //8 - максимальная длина, которую можно проверить 

    //открыть файл (fopen возвращает NULL, если файл не может быть открыт)
    FILE *fp = fopen(file_name, "rb"); //rb - открыть двоичный файл для чтения
    if (!fp){
        printf("Cannot read file: %s\n", file_name);
        exit(1);
    }

    
    fread(header, 1, 8, fp);  //size_t fread(void *buf, size_t size, size_t count, FILE *stream)
    //проверить, что файл PNG
    if (png_sig_cmp(header, 0, 8)){  //start - второй аргумент, num_to_check - третий
        printf("%s is not recognized as a PNG\n", file_name);
        exit(1);
    }

    //инициализация структуры PNG
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        printf("Error in PNG structure\n");
        exit(1);
    } 

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Error in PNG info-structure\n");
        exit(1);
    } 

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io\n");
        exit(1);
    }

    //заполнение структуры PNG

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);

    if (image->color_type == PNG_COLOR_TYPE_GRAY) {
        printf("The program does not support working with the PNG_COLOR_TYPE_GRAY color type.\n");
        exit(1);
    } else if (image->color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        printf("The program does not support working with the PNG_COLOR_TYPE_GRAY_ALPHA color type.\n");
        exit(1);
    } else if (image->color_type == PNG_COLOR_TYPE_PALETTE) {
        printf("The program does not support working with the PNG_COLOR_TYPE_PALETTE color type.\n");
        exit(1);
    }

    png_read_update_info(image->png_ptr, image->info_ptr);

    //чтение файла

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during read_image\n");
        return;
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++) {
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}

void write_png_file(char *file_name, struct Png *image) {
    int x,y;

    /* создание файла */
    FILE *fp = fopen(file_name, "wb");  //wb - создать двочиный файл для записи
    if (!fp){
        printf("%s could not be opened\n", file_name);
        exit(1);
    }

    /* инициализация структуры */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_write_struct failed\n");
        exit(1);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        exit(1);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io\n");
        exit(1);
    }

    png_init_io(image->png_ptr, fp);


    /* запись заголовка */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing header\n");
        exit(1);
    }

    //set image header information in info_ptr
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    /* запись байтов */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing bytes\n");
        exit(1);
    }

    png_write_image(image->png_ptr, image->row_pointers);


    /* конец записи */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during the end of writing\n");
        exit(1);
    }

    png_write_end(image->png_ptr, NULL);

    /* очистка */

    free_image_data(image);

    fclose(fp);
}

void free_image_data(struct Png *image) {
    for (int y = 0; y < image->height; y++) {
        free(image->row_pointers[y]);
    }
    free(image->row_pointers);
}