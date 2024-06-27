#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#pragma pack(push, 1)
typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack(pop)

int check_bmp(char *file_name, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif);
Rgb** read_bmp(char *file_name, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif);
void write_bmp(char *new_file, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr);
void show_info(BitmapFileHeader *bmfh, BitmapInfoHeader *bmif);

#endif