#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include "pngdata.h"
#include "pngio.h"

int
read_png_file(char* path, image_t* image) {
    png_byte header[8];
    FILE* fp = fopen(path, "rb");
    if (!fp) {
        printf("Error: Could not open input file.\n");
        return 43;
    }
    fread(header, sizeof(png_byte), 8, fp);
    if (png_sig_cmp((png_const_bytep)header, 0, 8)) {
        printf("Error: Input file is not a PNG file.\n");
        fclose(fp);
        return 43;
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        printf("Error: Error with creating PNG read struct.\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        fclose(fp);
        return 43;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        printf("Error: Error with creating PNG info struct.\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        fclose(fp);
        return 43;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Error: Unexpected error with reading a PNG file.\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        fclose(fp);
        return 43;
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    int width = png_get_image_width(image->png_ptr, image->info_ptr);
    int height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGB) {
        printf("Error: Input file is not a PNG RGB image.\n");
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
        fclose(fp);
        return 43;
    }
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    image->canvas = create_canvas(width, height);
    png_read_update_info(image->png_ptr, image->info_ptr);
    png_read_image(image->png_ptr, image->canvas->grid);
    png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
    fclose(fp);
    return 0;
}

int
write_png_file(char* path, image_t* image) {
    FILE* fp = fopen(path, "wb");
    if (!fp) {
        printf("Error: Could not open output file.\n");
        return 43;
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        printf("Error: Error with creating PNG write struct.\n");
        fclose(fp);
        return 43;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        printf("Error: Error with creating PNG info struct.\n");
        fclose(fp);
        return 43;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Error: Unexpected error with writing a PNG file.\n");
        return 43;
    }
    png_init_io(image->png_ptr, fp);
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Error: Unexpected error after IO session initialization.\n");
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        return 43;
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->canvas->width, image->canvas->height, image->bit_depth,
                 image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Error: Unexpected error after writing a PNG file metadata.\n");
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        return 43;
    }
    png_write_image(image->png_ptr, image->canvas->grid);
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Error: Unexpected error after writing a PNG file image content.\n");
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(fp);
        return 43;
    }
    png_write_end(image->png_ptr, NULL);
    png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
    fclose(fp);
    return 0;
}