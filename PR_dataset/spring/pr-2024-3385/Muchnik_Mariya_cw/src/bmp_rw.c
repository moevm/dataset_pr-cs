#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "bmp_rw.h"
#include "error_handler.h"
#include "print_info.h"

#define VALID_SIGNATURE 19778
#define VALID_HEADER_SIZE 40
#define VALID_BITS_PER_PIXEL 24
#define VALID_COMPRESSION 0
#define VALID_COLORS_IN_TABLE 0

Rgb** read_bmp (char* file_name, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif){
    FILE* f = fopen(file_name, "rb");
    if (f == NULL) {
        char* mes = (char*)malloc((strlen("File doesn't exist!")+strlen(file_name))*sizeof(char));
        sprintf(mes, "File %s doesn't exist!\n", file_name);
        print_error(mes, bmfh, bmif, NULL);
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f); 
    if (bmfh->signature != VALID_SIGNATURE)
        print_error("Incorrect signature of BMP file!\n", bmfh, bmif, NULL);

    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    if (bmif->headerSize != VALID_HEADER_SIZE) {
        print_info(bmif, bmfh);
        print_error("Incorrect version of BMP file! File should have 3rd version (headerSize = 40).\n", bmfh, bmif, NULL);
    }
    if (bmif->bitsPerPixel != VALID_BITS_PER_PIXEL) {
        print_info(bmif, bmfh);
        print_error("Pixel format must be equal to 24 (rgb-format)!\n", bmfh, bmif, NULL);
    }
    if (bmif->compression != VALID_COMPRESSION) {
        print_info(bmif, bmfh);
        print_error("The image should not have compression!\n", bmfh, bmif, NULL);
    }
    if (bmif->colorsInColorTable != VALID_COLORS_IN_TABLE) {
        print_info(bmif, bmfh);
        print_error("I can't handle such comlex pixel interpetation as color palette. Please, enter another file.\n", bmfh, bmif, NULL);
    }

    unsigned int H = abs((int)bmif->height);
    unsigned int W = bmif->width;
    unsigned int padding = (W*3)%4;
    if (padding)
        padding = 4 - padding;
    Rgb** arr = (Rgb**)malloc(H*sizeof(Rgb*));
    for (int i = 0; i < H; i++) {
        arr[i] = (Rgb*)malloc(W*sizeof(Rgb) + padding); 
        if (arr[i] == NULL)
            print_error("Not enought memory!\n", bmfh, bmif, arr);
        fread(arr[i], 1, W*sizeof(Rgb) + padding, f);
    }
    fclose(f);
    return arr;
} 

void write_bmp(char* file_name, Rgb** arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif) {
    FILE* ff = fopen(file_name, "wb");
    if (ff == NULL) {
        char* mes = (char*)malloc((strlen("Cannot write to file \n.")+strlen(file_name))*sizeof(char));
        sprintf(mes, "Cannot write to file %s!\n.", file_name);
        print_error(mes, &bmfh, &bmif, arr);
    }
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int padding = (W*sizeof(Rgb))%4;
    if (padding)
        padding = 4 - padding;
    char* pad_arr = calloc(8, padding);
    for (int i = 0; i < H; i++) {
        fwrite(arr[i], 1, W*sizeof(Rgb), ff);
        fwrite(pad_arr, 1, padding, ff);
    }
    free(pad_arr);
    fclose(ff);
} 
