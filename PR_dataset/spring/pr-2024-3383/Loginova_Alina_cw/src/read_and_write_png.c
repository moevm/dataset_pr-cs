#include "read_and_write_png.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <png.h>
#include "image_data.h"
#include "call_func.h"
#include "print_usage.h"
#define nmemb 8
long width, height;
extern struct option long_opt[];

void read_and_write_png(int argc, char **argv) {
    int c, option_index;
    char *input_name = NULL, *output_name = NULL;

    do {
        c = getopt_long(argc, argv, "i:o:", long_opt, &option_index);
        switch(c) {
            case 'a':
                input_name = optarg;
                break;
            case 'o':
                output_name = optarg;
                break;
            case 'h':
                printf("Course work for option 5.11, created by Alina Loginova.\n");
                print_usage();
                exit(0);
            case '?':
                printf("Была введена неподдерживаемая опция.\n");
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    if(!input_name) {
        input_name = argv[argc-1];
    }

    FILE *fp_i = fopen(input_name, "rb");

    if(!fp_i) {
        printf("[read_and_write_png.c()] файла с именем %s не существует\n", input_name);
        exit(40);
    }

    unsigned char* header = calloc(nmemb, sizeof(char));
    size_t ret = fread(header, 1, nmemb, fp_i);

    if(ret != nmemb) {
        printf("[check_png()] fread() отработала некорректно. "
               "Ожидалось %d прочитанных элементов данных, по факту прочитано %zul.\n", nmemb, ret);
        exit(40);
    }

    if(png_sig_cmp(header, 1, nmemb)) {
        printf("Формат файла должен быть PNG.\n");
        print_usage();
        exit(40);
    }
    free(header);

    png_structp png_ptr_i = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!png_ptr_i) {
        printf("[read_and_write_png.c()] ошибка создания png_read_struct\n");
        exit(40);
    }

    png_infop info_ptr_i = png_create_info_struct(png_ptr_i);

    if(!info_ptr_i) {
        printf("[read_and_write_png.c()] ошибка создания png_info_struct\n");
        exit(40);
    }

    png_init_io(png_ptr_i, fp_i);
    png_set_sig_bytes(png_ptr_i, nmemb);
    png_read_png(png_ptr_i, info_ptr_i, PNG_TRANSFORM_IDENTITY, NULL);

    if(png_get_channels(png_ptr_i, info_ptr_i) == 4) {
        printf("Данная программа не поддерживает работу с PNG изображениями с 4-мя каналами.\n");
        exit(40);
    }

    height = png_get_image_height(png_ptr_i, info_ptr_i);
    width = png_get_image_width(png_ptr_i, info_ptr_i);

    png_byte b_d = png_get_bit_depth(png_ptr_i, info_ptr_i);
    png_byte c_t = png_get_color_type(png_ptr_i, info_ptr_i);

    image_data image = { (pixel**)png_get_rows(png_ptr_i, info_ptr_i), height, width };
    png_bytepp rows = call_func(argc, argv, image);

    if(!rows) {
        printf("INFO about file %s\n\n[Width: %12lu]\n\n"
               "[Height: %11lu]\n\n[Bit depth: %6d]\n\n[Color type: %5d]\n",
               input_name, width, height, b_d, c_t);
        exit(0);
    }

    if(!output_name) {
        output_name = "out.png";
    }
    else if(strcmp(input_name, output_name) == 0)
    {
        printf("Имя входного и выходного файла одинаковые.\n");
        exit(40);
    }

    FILE *fp = fopen(output_name, "wb");

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr) {
        printf("[read_and_write_png.c()] ошибка создания png_write_struct\n");
        exit(40);
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if(!info_ptr) {
        printf("[read_and_write_png.c()] ошибка создания png_info_struct\n");
        exit(40);
    }

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, b_d, c_t, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);
    png_write_rows(png_ptr, rows, height);

    png_write_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr_i, &info_ptr_i, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp_i);
    fclose(fp);
}
