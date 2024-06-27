#include "image.h"

image *open_image(char *path) {
    
    if (!is_png_file(path)) {
        fprintf(stderr, is_PNG);
        exit(40);
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, input_file_error);
        exit(40);
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!png_ptr || !info_ptr) {
        fprintf(stderr, input_file_error);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(file);
        exit(40);
    }

    if(setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, input_file_error);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(file);
        exit(40);
    }

    png_init_io(png_ptr, file);
    png_read_info(png_ptr, info_ptr);
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    if (color_type != PNG_COLOR_TYPE_RGB || bit_depth != 8) {
        fprintf(stderr, deepth);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        exit(40);
    }

    png_bytep *data = (png_bytep *)calloc(height, sizeof(png_bytep));
    for (int y = 0; y < height; y++) {
        data[y] = (png_bytep)calloc(png_get_rowbytes(png_ptr, info_ptr), sizeof(png_byte));
    }
    png_read_image(png_ptr, data);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(file);

    image *img = calloc(1, sizeof(image));
    img->path = path;
    img->width = width;
    img->height = height;
    img->color_type = color_type;
    img->bit_depth = bit_depth;
    img->data = data;
    return img;
}

int save_image(image *img, char *path) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, drop_file);
    }
    
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr || !png_ptr) {
        fprintf(stderr, drop_struct);
        fclose(file);
        exit(40);
    }

    if(setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, input_file_error);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        exit(40);
    }

    png_init_io(png_ptr, file);
    png_set_IHDR(png_ptr, info_ptr, img->width, img->height, img->bit_depth, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, img->data);
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(file);
    return 0;
}

void free_image(image *img) {
    if (img) {
        for (int y = 0; y < img->height; y++) {
            free(img->data[y]);
        }
        free(img->data);
    }
}
