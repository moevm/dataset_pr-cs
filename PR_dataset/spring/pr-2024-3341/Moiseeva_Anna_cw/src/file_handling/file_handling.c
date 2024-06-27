#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

int check_bmp(char *file_name, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif) {
    FILE *f = fopen(file_name, "rb");
    if (!f) {
        fprintf(stderr, "Не удалось открыть файл\n");
        return 0;
    }

    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);

    if (bmfh->signature != 0x4D42) {
        fprintf(stderr, "Файл должен иметь формат bmp\n");
        fclose(f);
        return 0;
    }
    if (bmif->compression != 0) {
        fprintf(stderr, "Изображение должно быть без сжатия\n");
        fclose(f);
        return 0;
    }
    if (bmif->headerSize != 40) {
        fprintf(stderr, "Изображение старой версии, не поддерживается\n");
        fclose(f);
        return 0;
    }
    if (bmif->bitsPerPixel != 24) {
        fprintf(stderr, "Изображение должно иметь 24 бита на пиксель\n");
        fclose(f);
        return 0;
    }
    if (bmif->width > 50000 || bmif->height > 50000) {
        fprintf(stderr, "Изображение слишком большое\n");
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

Rgb** read_bmp(char *file_name, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif) {
    FILE *f = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);

    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    size_t padding = (4 - (W * sizeof(Rgb)) % 4) % 4;
    Rgb **arr = malloc(H * sizeof(Rgb*));

    for (int i = H - 1; i >= 0; i--) {
        arr[i] = malloc(W * sizeof(Rgb) + padding);
        fread(arr[i], 1, W * sizeof(Rgb) + padding, f);
    }

    fclose(f);
    return arr;
}

void write_bmp(char *new_file, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr) {
    FILE *f = fopen(new_file, "wb");
    fwrite(bmfh, 1, sizeof(BitmapFileHeader), f);
    fwrite(bmif, 1, sizeof(BitmapInfoHeader), f);

    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    size_t padding = (4 - (W * sizeof(Rgb)) % 4) % 4;

    for (int i = H - 1; i >= 0; i--) {
        fwrite(arr[i], 1, W * sizeof(Rgb) + padding, f);
    }

    fclose(f);
}

void show_info(BitmapFileHeader *bmfh, BitmapInfoHeader *bmif) {
    printf("signature:\t%x (%hx)\n", bmfh->signature, bmfh->signature);
    printf("filesize:\t%x (%u)\n", bmfh->filesize, bmfh->filesize);
    printf("reserved1:\t%x (%hx)\n", bmfh->reserved1, bmfh->reserved1);
    printf("reserved2:\t%x (%hx)\n", bmfh->reserved2, bmfh->reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", bmfh->pixelArrOffset, bmfh->pixelArrOffset);
    printf("headerSize:\t%x (%u)\n", bmif->headerSize, bmif->headerSize);
    printf("width:\t%x (%u)\n", bmif->width, bmif->width);
    printf("height:\t%x (%u)\n", bmif->height, bmif->height);
    printf("planes:\t%x (%hx)\n", bmif->planes, bmif->planes);
    printf("bitsPerPixel:\t%x (%hx)\n", bmif->bitsPerPixel, bmif->bitsPerPixel);
    printf("compression:\t%x (%u)\n", bmif->compression, bmif->compression);
    printf("imageSize:\t%x (%u)\n", bmif->imageSize, bmif->imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", bmif->xPixelsPerMeter, bmif->xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", bmif->yPixelsPerMeter, bmif->yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", bmif->colorsInColorTable, bmif->colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", bmif->importantColorCount, bmif->importantColorCount);
}