#include "read_picture.h"

pixels_t* read_bmp_file(char file_name[], bmp_file_header_t* file_header, bmp_info_header_t* info_header){
    FILE *file = fopen(file_name, "rb");
    if(!file){
        char error_string[strlen(NO_FILE_ERROR_TEMPLATE) + strlen(file_name)+ 2];
        sprintf(error_string, "%s %s\n", NO_FILE_ERROR_TEMPLATE, file_name);
        leave(error_string, ARGUMENT_ERROR_CODE);
    }
    fread(file_header, 1, sizeof(bmp_file_header_t), file);
    fread(info_header, 1, sizeof(bmp_info_header_t), file);

    if(info_header->bitsPerPixel != BITS_PER_PIXEL)
        leave(BITS_PER_PIXEL_ERROR, IMAGE_ERROR_CODE);
    if(file_header->signature != BMP_SIGNATURE)
        leave(SIGNATURE_ERROR, IMAGE_ERROR_CODE);
    if(info_header->headerSize != sizeof(bmp_info_header_t)){
        leave(NOT_INFO_HEADER_ERROR, IMAGE_ERROR_CODE);
    }

    rgb_t** arr = malloc(info_header->height * sizeof(rgb_t*));
    size_t padd = (4 - (info_header->width * sizeof(rgb_t)) % 4) % 4;
    for(int i = info_header->height-1; i >= 0; i--){
        arr[i] = malloc(info_header->width * sizeof(rgb_t) + padd);
        fread(arr[i], 1, info_header->width * sizeof(rgb_t) + padd, file);
    }
    fclose(file);
    pixels_t *pixels = (pixels_t*)malloc(sizeof(pixels_t));
    pixels->arr = arr;
    pixels->height = info_header->height;
    pixels->width = info_header->width;
    return pixels;
} 

void write_bmp_file(char file_name[], rgb_t** pixels, bmp_file_header_t* file_header, bmp_info_header_t* info_header){
    FILE *output_file = fopen(file_name, "wb");
    fwrite(file_header, 1, sizeof(bmp_file_header_t), output_file);
    fwrite(info_header, 1, sizeof(bmp_info_header_t), output_file);
    size_t padd = (4 - (info_header->width * sizeof(rgb_t)) % 4) % 4;
    for(int i = info_header->height-1; i >= 0; i--){
        fwrite(pixels[i], 1, info_header->width * sizeof(rgb_t) + padd, output_file);
    }
    fclose(output_file);
}