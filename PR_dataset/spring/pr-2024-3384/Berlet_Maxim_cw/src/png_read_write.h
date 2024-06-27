#ifndef PNG_RW_H
#define PNG_RW_H
#define PNG_BYTES_TO_CHECK 8
#include <png.h>
#include <stdlib.h>
#include "structs.h"
#include "signatures.h"

bool check_if_png(const char* file_name) {
    FILE* fp = fopen(file_name, "rb");
    char header[PNG_BYTES_TO_CHECK];

    if (!fp) {
        printf("Could not open %s\n", file_name);
        exit(openning_error);
    }

    fread(header, 1, PNG_BYTES_TO_CHECK, fp);
    int is_png = png_sig_cmp(header, 0, PNG_BYTES_TO_CHECK);

    if (is_png) {
        fclose(fp);
        return false;
    }

    return true;
}

void read_png_file(const char* file_name, png_t* image) {
    FILE* fp = fopen(file_name, "rb");

    int x, y;

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        fprintf(stderr, "png_create_read_struct failed\n");
        exit(broken_file_error);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);

    if (!image->info_ptr) {
        fprintf(stderr, "png_create_info_struct failed\n");
        exit(broken_file_error);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "broken file\n");
        exit(broken_file_error);
    } 
    // заполняем структуру png_t
    png_init_io(image->png_ptr, fp);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*image->height);

    for (y = 0; y < image->height; ++y) {
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }

    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}

bool check_if_rgb(png_t* image) {
    if (image->color_type == PNG_COLOR_TYPE_RGB) {
        return true;
    }
    return false;
}

void write_png_file (const char* file_name, png_t* image) {
    int x, y;
    FILE* fp = fopen(file_name, "wb");

    if (!fp) {
        fprintf(stderr, "cannot open file %s\n", file_name);
        exit(openning_error);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        fprintf(stderr, "failed creating write struct");
        fclose(fp);
        exit(broken_file_error);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);

    if (!image->info_ptr) {
        fprintf(stderr, "failed creating info struct");
        fclose(fp);
        exit(broken_file_error);
    }

    png_init_io(image->png_ptr, fp);

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
    image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, 
    PNG_FILTER_TYPE_BASE);
    
    png_write_info(image->png_ptr, image->info_ptr);

    png_write_image(image->png_ptr, image->row_pointers);

    png_write_end(image->png_ptr, NULL);

    fclose(fp);
}

#endif