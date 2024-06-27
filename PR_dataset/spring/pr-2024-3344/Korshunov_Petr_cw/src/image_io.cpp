#include "structs.h"
#include "image_bmp.h"

void Image::printFileHeader()
{
    cout << "signature:    \t0x" << hex << bmfh.signature << " (" << dec << bmfh.signature << ")" << endl;
    cout << "filesize:    \t0x" << hex << bmfh.filesize << " (" << dec << bmfh.filesize << ")" << endl;
    cout << "reserved1:    \t0x" << hex << bmfh.reserved1 << " (" << dec << bmfh.reserved1 << ")" << endl;
    cout << "reserved2:    \t0x" << hex << bmfh.reserved2 << " (" << dec << bmfh.reserved2 << ")" << endl;
    cout << "pixelArrOffset:\t0x" << hex << bmfh.pixelArrOffset << " (" << dec << bmfh.pixelArrOffset << ")" << endl;
}

void Image::printInfoHeader()
{
    cout << "headerSize:   \t0x" << hex << bmif.headerSize << " (" << dec << bmif.headerSize << ")" << endl;
    cout << "width:        \t0x" << hex << bmif.width << " (" << dec << bmif.width << ")" << endl;
    cout << "height:       \t0x" << hex << bmif.height << " (" << dec << bmif.height << ")" << endl;
    cout << "planes:       \t0x" << hex << bmif.planes << " (" << dec << bmif.planes << ")" << endl;
    cout << "bitsPerPixel: \t0x" << hex << bmif.bitsPerPixel << " (" << dec << bmif.bitsPerPixel << ")" << endl;
    cout << "compression:  \t0x" << hex << bmif.compression << " (" << dec << bmif.compression << ")" << endl;
    cout << "imageSize:    \t0x" << hex << bmif.imageSize << " (" << dec << bmif.imageSize << ")" << endl;
    cout << "xPixelsPerMeter:\t0x" << hex << bmif.xPixelsPerMeter << " (" << dec << bmif.xPixelsPerMeter << ")" << endl;
    cout << "yPixelsPerMeter:\t0x" << hex << bmif.yPixelsPerMeter << " (" << dec << bmif.yPixelsPerMeter << ")" << endl;
    cout << "colorsInColorTable:\t0x" << hex << bmif.colorsInColorTable << " (" << dec << bmif.colorsInColorTable << ")" << endl;
    cout << "importantColorCount:\t0x" << hex << bmif.importantColorCount << " (" << dec << bmif.importantColorCount << ")" << endl;
}

Rgb **Image::read_bmp(string bmp_name)
{
    FILE *f = fopen(bmp_name.c_str(), "rb");

    if (!f)
    {
        cout << "Error in read_bmp: failed to open " << bmp_name.c_str() << endl;
        exit(46);
    }

    fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&bmif, 1, sizeof(BitmapInfoHeader), f);

    if (bmfh.signature != 0x4d42 || bmif.compression != 0 || bmif.bitsPerPixel != 24)
    {
        cout << "Error in read_bmp: Invalid BMP file format: incorrect signature or unsupported compression or incorrect color depth" << endl;
        exit(46);
    }

    unsigned int H = bmif.height;
    unsigned int W = bmif.width;
    unsigned int padding = (W * sizeof(Rgb)) % 4;
    if (padding)
        padding = 4 - padding;

    Rgb **arr = new Rgb *[H];
    for (int i = 0; i < H; i++)
    {
        arr[H - i - 1] = new Rgb[W + padding];
        fread(arr[H - i - 1], 1, W * sizeof(Rgb) + padding, f);
    }

    fclose(f);

    return arr;
}

void Image::write_bmp(string bmp_name)
{
    FILE *ff = fopen(bmp_name.c_str(), "wb");

    if (!ff)
    {
        cout << "Error in write_bmp: failed to open " << bmp_name.c_str() << endl;
        exit(47);
    }

    unsigned int H = bmif.height;
    unsigned int W = bmif.width;
    unsigned int padding = (W * sizeof(Rgb)) % 4;
    if (padding)
        padding = 4 - padding;

    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int w = W * sizeof(Rgb) + padding;
    for (int i = 0; i < H; i++)
    {
        fwrite(arr[H - i - 1], 1, w, ff);
    }
    fclose(ff);
}