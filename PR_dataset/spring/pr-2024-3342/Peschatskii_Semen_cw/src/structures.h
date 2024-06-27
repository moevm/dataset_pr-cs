typedef struct{
        unsigned short signa;
        unsigned int filesize;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int pixelArrOffset;
}__attribute__ ((packed))BitmapFileHeader;
typedef struct{
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
}__attribute__ ((packed))BitmapInfoHeader;
typedef struct Rgb{
        unsigned char b;
        unsigned char g;
        unsigned char r;
}__attribute__ ((packed))Rgb;

Rgb **read_bmp(FILE* fptr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);
void write_bmp(Rgb **arr, int h, int w, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char* out);
