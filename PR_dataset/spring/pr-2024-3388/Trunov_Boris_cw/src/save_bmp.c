#include <stdio.h>
#include <stdlib.h>
#include "save_bmp.h"

void save_bmp(const char* path, image_bmp img) {
    FILE * f = fopen(path, "wb");
    if (!f){
        printf("Невозможно открыть файл\n");
        exit(-1);
    }
    fwrite(&img.bheader, 1, sizeof(bitmap_file_header), f);
    fwrite(&img.dheader, 1, sizeof(bitmap_info_header), f);
    size_t height = img.dheader.height;
    size_t width = img.dheader.width;
    int padding = ((PADDING_BMP_SIZE - (width * sizeof(rgb)) % PADDING_BMP_SIZE) % PADDING_BMP_SIZE);
    for (size_t i = 0; i < height; i++) {
        fwrite(img.data[i], 1, sizeof(rgb) * width + padding, f);
    }
    fclose(f);
}
