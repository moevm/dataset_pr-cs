#ifndef STRUCTS_H
#define STRUCTS_H

#define HELP_INFO "Course work for option 4.10, created by Pavel Ivanov.\n\
–-input, -i: Имя входного изображения.\n\
-–output, -o: Имя выходного изображения.\n\
–-info: Вывод информации об изображении и завершение работы.\n\
–-help, -h: Вывод справки.\n\
--color_replace, -r: Замена всех пикселей одного цвета на другой.\n\
--old_color: Цвет для замены.\n\
--new_color: Цвет, на который заменить.\n\
--ornament, -n: Создание рамки в виде узора.\n\
--pattern: Тип узора (rectangle, circle, semicircles).\n\
--color: Цвет узора.\n\
--thickness: Ширина рамки.\n\
--count: Количество повторений узора.\n\
--filled_rects, -f: Поиск и обводка всех залитых прямоугольников заданного цвета.\n\
--color: Цвет прямоугольников.\n\
--border_color: Цвет линии обводки.\n\
--thickness: Толщина линии обводки."

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

extern unsigned int size_image;

#pragma pack(push, 1)
struct BMPHeader {
    //BitMap file
    char Type[2];
    unsigned int Size;
    short int Reserved_1;
    short int Reserved_2;
    unsigned int OffsetBits;
    //BitMap info
    unsigned int HeaderSize;
    int Width;
    int Height;
    unsigned short int Planes;
    unsigned short int BitCount;
    unsigned int Compression;
    unsigned int SizeImage;
    int XPixelsPerMeter;
    int YPixelsPerMeter;
    unsigned int ColorsUsed;
    unsigned int ColorsImportant;
};
#pragma pack(pop)

struct PICInfo{
    BMPHeader header;
    vector<uint8_t> pixels;
};

struct Pixel{
    uint8_t* red;
    uint8_t* green;
    uint8_t* blue;
};

struct OptionTools{
    //for replace_color flag
    int* old_color = nullptr;
    int* new_color = nullptr;

    //for ornament flag
    string pattern;
    int* pattern_color = nullptr;
    int pattern_thickness = 0;
    int count = 0;

    //for find flag
    int* rect_color = nullptr;
    int* border_color = nullptr;
    int border_thickness = 0;
};

const struct option long_flags[] = {
        {"input", required_argument, nullptr, 'i'},
        {"output", required_argument, nullptr, 'o'},
        {"info", no_argument, nullptr, 256},
        {"help", no_argument, nullptr, 'h'},

        {"color_replace", no_argument, nullptr, 'r'},
        {"old_color", required_argument, nullptr, 257},
        {"new_color", required_argument, nullptr, 258},

        {"ornament", no_argument, nullptr, 'n'},
        {"pattern", required_argument, nullptr, 259},
        {"color", required_argument, nullptr, 260}, //multi-flag
        {"thickness", required_argument, nullptr, 261}, //multi-flag
        {"count", required_argument, nullptr, 262},

        {"filled_rects", no_argument, nullptr, 'f'},
        {"border_color", required_argument, nullptr, 263},

        {"hsv", no_argument, nullptr, 'w'},
        {nullptr, 0, nullptr, 0}
};

#endif
