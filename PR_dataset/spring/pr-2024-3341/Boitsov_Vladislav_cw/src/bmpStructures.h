#ifndef BMP_STRUCTURES_H
#define BMP_STRUCTURES_H

#define SIGNATURE_VALUE 0x4d42
#define BITS_PER_PIXEL_VALUE 24
#define COMPRESSION_VALUE 0

#pragma pack(push, 1)

typedef struct
{
    unsigned short signature;
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BmpFileHeader;

typedef struct
{
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
} BmpInfoHeader; 

typedef struct 
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

typedef struct
{
    int x;
    int y;
} Point;

#endif