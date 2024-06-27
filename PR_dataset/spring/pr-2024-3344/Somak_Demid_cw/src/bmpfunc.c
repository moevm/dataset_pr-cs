#include "bmpfunc.h"
#include "secondary_func.h"

void print_imageinfo(BitmapInfoHeader bmih, BitmapFileHeader bmfh){
    printf("FileHeader:\n");
    printf("signature:\t%x (%hu)\n", bmfh.signature,bmfh.signature);
    printf("filesize:\t%x (%u)\n", bmfh.filesize,bmfh.filesize);
    printf("reserved1:\t%x (%hu)\n", bmfh.reserved1,bmfh.reserved1);
    printf("reserved2:\t%x (%hu)\n", bmfh.reserved2,bmfh.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", bmfh.pixelArrOffset, bmfh.pixelArrOffset);
    printf("\nInfoHeader:\n");
    printf("headerSize:\t%x (%u)\n", bmih.headerSize,bmih.headerSize);
    printf("width: \t%x (%u)\n", bmih.width, bmih.width);
    printf("height: \t%x (%u)\n", bmih.height,bmih.height);
    printf("planes: \t%x (%hu)\n", bmih.planes,bmih.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", bmih.bitsPerPixel, bmih.bitsPerPixel);
    printf("compression:\t%x (%u)\n", bmih.compression, bmih.compression);
    printf("imageSize:\t%x (%u)\n", bmih.imageSize,bmih.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", bmih.xPixelsPerMeter, bmih.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", bmih.yPixelsPerMeter, bmih.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", bmih.colorsInColorTable, bmih.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", bmih.importantColorCount, bmih.importantColorCount);
} 


void read_bmp(char file_name[], Image *img){

    FILE *f = fopen(file_name, "rb");
    if(f == NULL){
        fprintf(stderr,"can't open the read_file or it wasn't given\n");
        exit(1);
    }

    fread(&img->bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&img->bmih, 1, sizeof(BitmapInfoHeader), f);

    if (img->bmfh.signature != 0x4d42){
        fprintf(stderr,"image is not BMP");
        exit(41);
    }

    if (img->bmih.compression != 0 || img->bmih.bitsPerPixel != 24 || img->bmih.headerSize != 40) {
        fprintf(stderr,"this version of the BMP is not supported");
        exit(41);
    }

    unsigned int H = img->bmih.height;
    unsigned int W = img->bmih.width;
    img->pixels = malloc(H * sizeof(Rgb*));
    for(int i = 0; i < H; i++){
        img->pixels[H - i - 1] = malloc(row_len(W));
        fread(img->pixels[H - i - 1], 1, row_len(W),f);
    }
    fclose(f);
} 

void write_bmp(char file_name[],Image img){
    FILE *ff = fopen(file_name, "wb");
    if(ff == NULL){
        fprintf(stderr,"can't open the write_file\n");
        exit(1);
    }
    unsigned int H = img.bmih.height;
    unsigned int W = img.bmih.width;
    fwrite(&img.bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&img.bmih, 1, sizeof(BitmapInfoHeader), ff);
    for(int i = 0; i < H; i++){
        fwrite(img.pixels[H - i - 1], 1, row_len(W),ff);
    }
    fclose(ff);
}  
