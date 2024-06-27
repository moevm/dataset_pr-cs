#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

#include "BMP.hpp"
#include "secondary_functions.hpp"
#include "secondary_functions.hpp"


using namespace std;


void print_file_header (BitmapFileHeader header) {
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
} 


void print_info_header (BitmapInfoHeader header) {
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


Rgb**
readBMP (string& file_name, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    // Открытие файла
    ifstream f(file_name, ios::binary);
    if (!f.is_open()) {
        cerr << "Не удалось считать файл\n";
        return NULL;
    }
    // -----------------


    // Считывание заголовков
    f.read(reinterpret_cast <char*> (bmfh), sizeof(BitmapFileHeader));
    f.read(reinterpret_cast <char*> (bmif), sizeof(BitmapInfoHeader));
    // -----------------

    // Проверка на корректность
    if (bmfh->signature != 0x4D42) {
        cerr << "Файл не является bmp\n";
        return NULL;
    }
    if (bmif->compression != 0 || bmif->bitsPerPixel != 24 || bmif->headerSize != 40) {
        cerr << "Данная версия bmp не поддерживается\n";
        return NULL;
    }
    // ----------------------
    
    // Считывание массива пикселей
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;

    int padding = (4 - (W * sizeof(Rgb)) % 4) % 4;

    Rgb** arr;
    arr = new Rgb* [H];
    //arr = (Rgb**)malloc(H * sizeof(Rgb*));

    for (size_t i = 0; i < H; i++) {
        arr[i] = new Rgb [W * sizeof(Rgb) + padding];
        f.read(reinterpret_cast <char*> (arr[i]), W * sizeof(Rgb) + padding);
    }
    // ----------------------

    f.close();

    return arr;
}


void
writeBMP (string& fileName, Rgb** arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif) {
    ofstream f(fileName, ios::binary);

    f.write(reinterpret_cast <char*> (&bmfh), sizeof(BitmapFileHeader));
    f.write(reinterpret_cast <char*> (&bmif), sizeof(BitmapInfoHeader));

    int padding = (4 - (W * sizeof(Rgb)) % 4) % 4;

    for (size_t i = 0; i < H; i++) {
        f.write(reinterpret_cast <char*> (arr[i]), W * sizeof(Rgb) + padding);
    }

    f.close();
}

// 1 - True; 0 - False
int
stringDecomposeFunc(int* first, int* second, string value) {
    char dot;
    istringstream sd(value);
    sd >> *first >> dot >> *second;
    sd.clear();

    if (sd.fail() || dot != '.') return 0;
    return 1;
}

// 0 - True; 1 - Wrong type; 2 - Wrong color
int
colorDecomposeFunc(int* r, int* g, int* b, string value) {
    char dot1, dot2;
    istringstream sd(value);

    sd >> *r >> dot1 >> *g >> dot2 >> *b;
    sd.clear();

    if (sd.fail() || dot1 != '.' || dot2 != '.') return 1;

    if (*r > 255 || *r < 0 || *b > 255 || *b < 0 || *g > 255 || *g < 0) return 2;

    return 0;
}


void
checkCoords (int* left, int* up, int* right, int* down, int H, int W) {
    if (*right >= W) *right = W - 1;
    if (*left < 0) *left = 0;
    if (*down >= H) *down = H - 1;
    if (*up < 0) *up = 0;
}


int
findInputFile (vector <pair<string, string>> dict, string* InputFileName) {
    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].first == "i" && dict[i].second != "NULL") {
            (*InputFileName) = dict[i].second;
            return 1;
        }
    }
    return 0;
}


void
findOutputFile (vector <pair<string, string>> dict, string* OutputFileName) {
    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].first == "o" && dict[i].second != "NULL") {
            (*OutputFileName) = dict[i].second;
            return;
        }
    }
}

// 0 - wrong file; 1 - normal file
int
checkFileName (string filename) {
    if (filename.size() < 5) return 0;

    return 1;
}