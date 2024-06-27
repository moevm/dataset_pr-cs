#include "files_action.h"

unsigned int padding(unsigned int w){
    unsigned int padding = (w * sizeof(Rgb)) % 4;
    if(padding) padding = 4 - padding;
    return padding;
}

unsigned int row_len(unsigned int w){
    return w * sizeof(Rgb) + padding(w);
}

int check_bmp_color_depth(FILE *file) {
    fseek(file, 28, SEEK_SET); // Переходим к байту, содержащему информацию о битовой глубине цвета
    
    unsigned short color_depth;
    fread(&color_depth, sizeof(unsigned short), 1, file);
    
    // Проверяем битовую глубину цвета
    if (color_depth == 24) {
        return 1; // Битовая глубина 24 бита
    } else {
        fprintf(stderr, "Wrong color format\n");
        exit(41);
    }
}

int check_bmp_signature(FILE *file) {
    char signature[2];
    fread(signature, sizeof(char), 2, file);
    if (signature[0] == 'B' && signature[1] == 'M') {
        return 1;
    } else {
        fprintf(stderr, "Wrong format\n");
        exit(41);
    }
}

Rgb **read_bmp(char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif)
{
    FILE *test = fopen(file_name, "rb"); 
    if (check_bmp_signature(test)){
        if (check_bmp_color_depth(test))
        {
            fclose(test);
        }
    }
    FILE *f = fopen(file_name, "rb"); 
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;

    Rgb **arr = malloc(H*sizeof(Rgb*));
    for(int i=0; i<H;i++){
        arr[i] = malloc(row_len(W));
        fread(arr[i], 1, row_len(W), f);
    }
    fclose(f);
    return arr;
}

void write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif)
{
    FILE *ff = fopen(file_name, "wb");
    bmif.height = H;
    bmif.width = W;
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int w = row_len(W);
    for(int i=0; i<H; i++){
        fwrite(arr[i], 1, w, ff);
    }
    fclose(ff);
}

void print_file_header(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}
