#include "bmp.h"

void check_bmp(const char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif)
{
    FILE *file = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), file);
    fread(bmif, 1, sizeof(BitmapInfoHeader), file);
    if (!file){
        fprintf(stderr, "File Error: file could not be opened\n");
        fclose(file);
        exit(43);
    }
    if (bmfh->signature != 0x4d42){
        fprintf(stderr, "File Error: file must be bmp\n");
        fclose(file);
        exit(43);
    }
    if (bmif->compression != 0){
        fprintf(stderr, "File Error: file must be uncompressed\n");
        fclose(file);
        exit(43);
    }
    if (bmif->bitsPerPixel != 24){
        fprintf(stderr, "File Error: file must have 24 bits per pixel\n");
        fclose(file);
        exit(43);
    }
    fclose(file);
}

Rgb** read_bmp(const char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    FILE* file = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), file);
    fread(bmif, 1, sizeof(BitmapInfoHeader), file);
    unsigned int Height = bmif->height;
    unsigned int Width = bmif->width;
    unsigned int padding = (Width*sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;
    Rgb** arr = (Rgb**)calloc(Height, sizeof(Rgb*));
    for (int i = Height - 1; i>=0 ; i--) {
        arr[i] = (Rgb *) calloc(Width*sizeof(Rgb)+padding, sizeof(Rgb));
        fread(arr[i], 1, Width*sizeof(Rgb) + padding, file);
    }
    fclose(file);
    return arr;
}

void write_bmp(const char new_file[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr) {
    FILE *file = fopen(new_file, "wb");
    fwrite(bmfh, 1, sizeof(BitmapFileHeader), file);
    fwrite(bmif, 1, sizeof(BitmapInfoHeader), file);
    unsigned int Height = bmif->height;
    unsigned int Width = bmif->width;
    size_t padding = (4 - (Width * sizeof(Rgb)) % 4) % 4;
    for (int i = Height - 1; i>=0 ; i--) {
        fwrite(arr[i], 1, Width * sizeof(Rgb) + padding, file);
    }
    fclose(file);
}
