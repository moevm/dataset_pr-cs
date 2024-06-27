#include "picture.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int padding(unsigned int w) { return (4 - (w * sizeof(Rgb)) % 4) % 4; }

unsigned int row_len(unsigned int w) { return w * sizeof(Rgb) + padding(w); }

Rgb **read_bmp(char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif) {
    FILE *f = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb **arr = malloc(H * sizeof(Rgb *));
    for (int i = 0; i < H; i++) {
        arr[i] = malloc(row_len(W));
        fread(arr[i], 1, row_len(W), f);
    }
    fclose(f);
    if ((*bmfh).signature != 0x4d42) {
        printf("xnjn-yt nfr ");
        exit(48);
    }
    if ((*bmif).headerSize != 40) {
        printf("unsuported bmp version");
        exit(49);
    }
    if ((*bmif).bitsPerPixel != 24) {
        exit(49);
    }
    return arr;
}

void write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif) {
    FILE *ff = fopen(file_name, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    for (int i = 0; i < H; i++) {
        fwrite(arr[i], 1, row_len(W), ff);
    }
    fclose(ff);
}