#include <stdio.h>
#include <stdlib.h>
#include "read_bmp.h"
#include "failure.h"

void read_image_bmp(const char* path, image_bmp * img) {
    FILE * file = fopen(path, "rb");
    if (!file) failure("Невозможно открыть файл");
    bitmap_file_header bheader;
    bitmap_info_header dheader;
    fread(&bheader, 1, sizeof(bitmap_file_header),file);
    fread(&dheader, 1, sizeof(bitmap_info_header),file);
    if(dheader.header_size != 40 || dheader.bit_per_pixel != 24 || (bheader.signature != 0x424d && bheader.signature != 0x4d42) || dheader.compression != 0){
        fclose(file);
        failure("Извините, данный формат BMP не поддерживается нашей программой, ждите обновлений)");
    }
    img->bheader = bheader;
    img->dheader = dheader;
    size_t height = dheader.height;
    size_t width = dheader.width;
    img->data = (rgb**)malloc(sizeof(rgb*) * height);
    int padding = ((PADDING_BMP_SIZE - (width * sizeof(rgb)) % PADDING_BMP_SIZE) % PADDING_BMP_SIZE);
    for (size_t i = 0; i < height; i++) {
    	img->data[i] = (rgb*)malloc(width * sizeof(rgb) + padding);
        fread(img->data[i], 1, sizeof(rgb) * width + padding, file);
    }
    fclose(file);
}
