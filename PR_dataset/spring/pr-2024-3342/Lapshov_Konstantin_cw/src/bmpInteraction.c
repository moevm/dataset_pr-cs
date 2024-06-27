#include "bmpInteraction.h"


int
getOffset(size_t width){
    unsigned int offset = (width * sizeof(RGB)) % 4;
    offset = (offset ? 4-offset : 0);

    return offset;
}


BMP
readBMP(const char *filename) {
    FILE *bmpFile = fopen(filename, "rb");
    if (bmpFile == NULL) {
        showError("The file cannot be opened!\nCheck the name of the input file", FILE_OPEN_FAILURE);
    }

    BMP bmp;
    fread(&bmp.bmfh, 1, sizeof(bmp.bmfh), bmpFile);
    fread(&bmp.bmih, 1, sizeof(bmp.bmih), bmpFile);
    if (bmp.bmfh.bfSign != 0x4D42 || bmp.bmih.biBitSize != 24 || bmp.bmih.biCompression != 0) {
        showError("Wrong file type!", FILE_READ_FAILURE);
    }

    const size_t height = bmp.bmih.biHeight;
    const size_t width = bmp.bmih.biWidth;

    // Перемещаем указатель файла на начало пиксельных данных
    fseek(bmpFile, bmp.bmfh.bfArrOffset, SEEK_SET);

    bmp.img = createArrayOfPixels(height, width);
    for (size_t i = 0; i < height; i++) {
        fread(bmp.img[i], 1, width * sizeof(RGB) + getOffset(width), bmpFile);
    }

    fclose(bmpFile);
    return bmp;
}


void
saveBMP(const char *filename, BMP bmp) {
    FILE *bmpFile = fopen(filename, "wb");
    if (bmpFile == NULL) {
        showError("The file cannot be saved!", FILE_WRITE_FAILURE);
    }
    fwrite(&bmp.bmfh, 1, sizeof(bmp.bmfh), bmpFile);
    fwrite(&bmp.bmih, 1, sizeof(bmp.bmih), bmpFile);

    const size_t height = bmp.bmih.biHeight;
    const size_t width = bmp.bmih.biWidth;

    // Перемещаем указатель файла на начало пиксельных данных
    fseek(bmpFile, bmp.bmfh.bfArrOffset, SEEK_SET);

    for (size_t i = 0; i < height; i++) {
        fwrite(bmp.img[i], 1, width * sizeof(RGB) + getOffset(width), bmpFile);
    }
    fclose(bmpFile);
}

RGB**
createArrayOfPixels(int height, int width) {
    RGB **new_arr = (RGB **)malloc(height * sizeof(RGB *));
    if(new_arr == NULL) showError("Memory allocation error!", MEMORY_ALLOCATION_FAILURE);
    for(int i = 0; i < height; i++) {
        new_arr[i] = (RGB *)malloc(width * sizeof(RGB));
        if(new_arr[i] == NULL) showError("Memory allocation error!", MEMORY_ALLOCATION_FAILURE);
    }
    return new_arr;
}

void
freeArrayOfPixels(BMP* bmp) {
    for (int i = 0; i < bmp->bmih.biHeight; i++) {
        free(bmp->img[i]);
    }
    free(bmp->img);
}

void
printInfo(BMP bmp){
    printf("Signature:              \t%x (%hu)\n", bmp.bmfh.bfSign, bmp.bmfh.bfSign);
    printf("Size of file:           \t%x (%u)\n", bmp.bmfh.bfSize, bmp.bmfh.bfSize);
    printf("First reserved field:   \t%x (%hu)\n", bmp.bmfh.bfReserved1, bmp.bmfh.bfReserved1);
    printf("Second reserved field:  \t%x (%hu)\n", bmp.bmfh.bfReserved2, bmp.bmfh.bfReserved2);
    printf("Pixel array offset:     \t%x (%u)\n", bmp.bmfh.bfArrOffset, bmp.bmfh.bfArrOffset);
    printf("Size of header:         \t%x (%u)\n", bmp.bmih.biSize, bmp.bmih.biSize);
    printf("Image width:            \t%x (%u)\n", bmp.bmih.biWidth, bmp.bmih.biWidth);
    printf("Image height:           \t%x (%u)\n", bmp.bmih.biHeight, bmp.bmih.biHeight);
    printf("Planes:                 \t%x (%hu)\n", bmp.bmih.biPlanes, bmp.bmih.biPlanes);
    printf("Bits for pixel:         \t%x (%hu)\n", bmp.bmih.biBitSize, bmp.bmih.biBitSize);
    printf("Compression:            \t%x (%u)\n", bmp.bmih.biCompression, bmp.bmih.biCompression);
    printf("Size of image:          \t%x (%u)\n", bmp.bmih.biImageSize, bmp.bmih.biImageSize);
    printf("Pixels per meter (x):   \t%x (%u)\n", bmp.bmih.biXPixelsPerMeter, bmp.bmih.biXPixelsPerMeter);
    printf("Pixels per meter (y):   \t%x (%u)\n", bmp.bmih.biYPixelsPerMeter, bmp.bmih.biYPixelsPerMeter);
    printf("Colors in color table:  \t%x (%u)\n", bmp.bmih.biClrTotal, bmp.bmih.biClrTotal);
    printf("Important color count:  \t%x (%u)\n", bmp.bmih.biClrImportant, bmp.bmih.biClrImportant);
}