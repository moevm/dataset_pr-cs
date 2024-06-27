#include "readwrite.h"


Rgb**
read_bmp(char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif){
    FILE *f = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    if (!check_if_bmp(bmfh)){
        printf("Error 49: invalid file format\n");
        exit(49);
    }
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb** arr = malloc(H * sizeof(Rgb*));
    for(int i = 0; i < H; i++){
        arr[i] = malloc(row_len(W));
        fread(arr[i], 1, row_len(W), f);
    }
    fclose(f);
    return arr;
}


void
write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif){
    FILE *ff = fopen(file_name, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    for(int i = 0; i < H; i++){
        fwrite(arr[i], 1, row_len(W), ff);
    }
    fclose(ff);
}
