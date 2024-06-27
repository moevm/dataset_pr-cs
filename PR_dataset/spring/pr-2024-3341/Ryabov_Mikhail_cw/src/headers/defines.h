#pragma once
#pragma pack (push, 1)  //Set padding in 1 byte для того чтобы они лежали подряд для fread

#define IS_SQUARE       1
#define IS_EXCHANGE     2
#define IS_FREQ_COLOR   3
#define IS_GAMMA        4

typedef struct {
    unsigned short  signature;
    unsigned int    filesize;
    unsigned short  reserved1;
    unsigned short  reserved2;
    unsigned int    pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int    headerSize;
    unsigned int    width;
    unsigned int    height;
    unsigned short  planes;
    unsigned short  bitsPerPixel;
    unsigned int    compression;
    unsigned int    imageSize;
    unsigned int    xPixelsPerMeter;
    unsigned int    yPixelsPerMeter;
    unsigned int    colorsInColorTable;
    unsigned int    importantColorCount;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop) //удаление со стека единичного выравнивания

typedef struct SquareProperty
{
    unsigned int    sumStatusKeys;
    int             left;
    int             up;
    int             side_size;
    int             thickness;
    Rgb             color;
    Rgb             fill_color;
} SquareProperty;

typedef struct varOptions{
    int                 isFillSquare;
    int                 left;
    int                 up;
    int                 right;
    int                 down;
    int                 sideSize;
    int                 thickness;
    Rgb                 color;
    Rgb                 fillColor;
    double              value;
    char*               inputImage;
    char*               outputImage;
    char*               typeExchange;
    Rgb**               pixels;
    BitmapInfoHeader*   BMPInfo;
    BitmapFileHeader*   BMPFile;
}varOptions;
