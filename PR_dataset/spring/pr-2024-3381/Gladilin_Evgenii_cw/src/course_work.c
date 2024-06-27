#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <getopt.h>

#define NO_ARGUMENT 0
#define REQIURED_ARGUMENT 1
#define OPTIONAL_ARGUMENT 2
#define MAX_FILE_NAME 256
#define FILE_ERROR 40
#define INPUT_ERROR 41

#pragma pack(push, 1)

typedef struct
{
    unsigned short signature;
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int yPixelsPerMeter;
    unsigned int xPixelsPerMeter;
    unsigned int totalColors;
    unsigned int importantColors;
} BitmapInfoHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

typedef struct
{
    char fileName[MAX_FILE_NAME];
    char outputName[MAX_FILE_NAME];
    short info;
    short inverse;
    short gray;
    short resize;
    int leftUp[2];
    int rightDown[2];
    Rgb color;
    int sideSize[4];
    short binarization;
    short threshold;
} Args;

#pragma pack(pop)

unsigned int padding(unsigned int w)
{
    unsigned int res = (sizeof(Rgb) * w) % 4;
    if (res)
    {
        res = 4 - res;
    }
    return res;
}

unsigned int rowLen(unsigned int w)
{
    return w * sizeof(Rgb) + padding(w);
}

Rgb **readBmp(char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih)
{
    FILE *f = fopen(fileName, "rb");
    if (!f)
    {
        printf("File %s not found\n", fileName);
        exit(FILE_ERROR);
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmih, 1, sizeof(BitmapInfoHeader), f);
    fseek(f, bmfh->pixelArrOffset, SEEK_SET);
    unsigned int h = bmih->height;
    unsigned int w = bmih->width;
    Rgb **arr = malloc(sizeof(Rgb *) * h);
    for (int i = 0; i < h; i++)
    {
        arr[h - i - 1] = malloc(rowLen(w));
        fread(arr[h - i - 1], 1, rowLen(w), f);
    }
    fclose(f);
    return arr;
}

void writeBmp(char fileName[], Rgb **arr, int w, int h, BitmapFileHeader bmfh, BitmapInfoHeader bmih)
{
    FILE *ff = fopen(fileName, "wb");
    if (!ff)
    {
        printf("File %s can't be writed\n", fileName);
        exit(FILE_ERROR);
    }
    bmih.height = h;
    bmih.width = w;
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmih, 1, sizeof(BitmapInfoHeader), ff);
    fseek(ff, bmfh.pixelArrOffset, SEEK_SET);
    for (int i = 0; i < h; i++)
    {
        fwrite(arr[h - i - 1], 1, rowLen(w), ff);
    }
    fclose(ff);
}

void freeRgb(Rgb **arr, int h)
{
    for (int i = 0; i < h; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

Rgb **copyArr(Rgb **arr, int w, int h)
{
    Rgb **newArr = malloc(sizeof(Rgb *) * h);
    for (int i = 0; i < h; i++)
    {
        newArr[i] = malloc(rowLen(w));
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            newArr[i][j] = arr[i][j];
        }
    }
    return newArr;
}

void field(int *x1, int *y1, int *x2, int *y2, BitmapInfoHeader *bmih)
{
    int tmp;
    int h = bmih->height;
    int w = bmih->width;
    if (*x1 > *x2)
    {
        tmp = *x1;
        *x1 = *x2;
        *x2 = tmp;
    }

    if (*y1 > *y2)
    {
        tmp = *y1;
        *y1 = *y2;
        *y2 = tmp;
    }

    if (*x1 < 0)
        *x1 = 0;

    if (*y1 < 0)
        *y1 = 0;

    if (*y2 > h)
        *y2 = h;

    if (*x2 > w)
        *x2 = w;
}

int customRound(double num)
{
    int intPart = (int)num;
    double doublePart = num - intPart;

    if (doublePart >= 0.5)
    {
        return (int)(intPart + 1);
    }
    else
    {
        return (int)intPart;
    }
}

void inverse(Rgb **arr, char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih, int x1, int y1, int x2, int y2)
{
    unsigned int w = bmih->width;
    unsigned int h = bmih->height;

    field(&x1, &y1, &x2, &y2, bmih);
    Rgb **newArr = copyArr(arr, w, h);

    for (int i = y1; i < y2; i++)
    {
        for (int j = x1; j < x2; j++)
        {
            newArr[i][j].r = 255 - arr[i][j].r;
            newArr[i][j].g = 255 - arr[i][j].g;
            newArr[i][j].b = 255 - arr[i][j].b;
        }
    }
    writeBmp(fileName, newArr, w, h, *bmfh, *bmih);
    freeRgb(newArr, h);
}

void gray(Rgb **arr, char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih, int x1, int y1, int x2, int y2)
{
    unsigned int h = bmih->height;
    unsigned int w = bmih->width;
    field(&x1, &y1, &x2, &y2, bmih);

    Rgb **newArr = copyArr(arr, w, h);

    for (int i = y1; i < y2; i++)
    {
        for (int j = x1; j < x2; j++)
        {
            int grayColor = customRound(arr[i][j].r * 0.299 + arr[i][j].g * 0.587 + arr[i][j].b * 0.114);
            newArr[i][j].r = grayColor;
            newArr[i][j].g = grayColor;
            newArr[i][j].b = grayColor;
        }
    }
    writeBmp(fileName, newArr, w, h, *bmfh, *bmih);
    freeRgb(newArr, h);
}

void resize(Rgb **arr, char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih, int *sideSize, Rgb color)
{
    unsigned int w = bmih->width;
    unsigned int h = bmih->height;


    w = w + sideSize[0] + sideSize[2];
    h = h + sideSize[1] + sideSize[3];

    Rgb **newArr = malloc(sizeof(Rgb *) * h);
    for (int i = 0; i < h; i++)
    {
        newArr[i] = malloc(rowLen(w));
        for (int j = 0; j < w; j++)
        {
            if ((j > sideSize[2]) && (j < w - sideSize[0]) && (i > sideSize[3]) && (i < h - sideSize[1]))
            {
                newArr[i][j] = arr[i - sideSize[3]][j - sideSize[2]];
            }
            else
            {
                newArr[i][j] = color;
            }
        }
    }

    writeBmp(fileName, newArr, w, h, *bmfh, *bmih);
    freeRgb(newArr, h);
}

void binarization(Rgb **arr, char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih, int num){
    unsigned int w = bmih->width;
    unsigned int h = bmih->height;
    unsigned int s;

    Rgb **newArr = malloc(sizeof(Rgb *) * h);
    for (int i = 0; i < h; i++){
        newArr[i] = malloc(rowLen(w));
        for (int j = 0; j < w; j++){
            s = arr[i][j].b+arr[i][j].r+arr[i][j].g;
            if (s >= num){
                newArr[i][j].r = 255;
                newArr[i][j].b = 255;
                newArr[i][j].g = 255;
            }else{
                newArr[i][j].r = 0;
                newArr[i][j].b = 0;
                newArr[i][j].g = 0;
            }
        }
    }
    writeBmp(fileName, newArr, w, h, *bmfh, *bmih);
    freeRgb(newArr, h);
}

void printFileHeader(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.fileSize, header.fileSize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header)
{
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:\t%x (%u)\n", header.width, header.width);
    printf("height:\t%x (%u)\n", header.height, header.height);
    printf("planes:\t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("totalColors:\t%x (%u)\n", header.totalColors, header.totalColors);
    printf("importantColors:\t%x (%u)\n", header.importantColors, header.importantColors);
}

void printHelp()
{
    wprintf(L"Общие сведения\n");
    wprintf(L"Программа предназначена для обработки 24-битного изображения формата BMP.");
    wprintf(L"Передаваемые аргументы:\n");
    wprintf(L"\t./a.out - имя исполняемого файла\n");
    wprintf(L"\t-f или -func - ключи для вызова выбранной функции(см. Ключи функций и их аргументы)\n");
    wprintf(L"\t<image.bmp> - имя файла\n");
    wprintf(L"\nКлючи функций и их аргументы:\n");
    wprintf(L"--inverse - инверсия цвета в заданной области\n");
    wprintf(L"\t--left_up - координаты левого верхнего угла, области. Значения подаются в формате left.up, где left - координата по x, а up - по y\n");
    wprintf(L"\t--right_down - координаты правого нижнего угла, области. Значения подаются в формате right.down, где right - координата по x, а down - по y\n");
    wprintf(L"\n--gray - преобразование в Ч/Б изображение области\n");
    wprintf(L"\t--left_up - координаты левого верхнего угла, области. Значения подаются в формате left.up, где left - координата по x, а up - по y\n");
    wprintf(L"\t--right_down - координаты правого нижнего угла, области. Значения подаются в формате right.down, где right - координата по x, а down - по y\n");
    wprintf(L"\n--resize - изменение размера с его обрезкой или расширением фона\n");
    wprintf(L"\t--<side> <change> - количеством изменения пикселей с определенной стороны. Где <side> может принимать значение left(с левой стороны), right(с правой стороны), above(с верхней стороны) и below(с нижней стороны). Если <change> является положительным числом, то идёт расширение, если отрицательным, то обрезка\n");
    wprintf(L"\t--color - цвет фона при расширении изображения. Цвет задаётся строкой rrr.ggg.bbb, где rrr/ggg/bbb - числа, задающие цветовую компоненту\n");
    wprintf(L"\n-info - печать подробной информации о изображении");
}

int main(int argc, char *argv[])
{
    printf("Course work for option 4.5, created by Gladilin Evgenii\n");
    setlocale(LC_ALL, "");
    if (strcmp(argv[argc - 1], "-h") == 0 || strcmp(argv[argc - 1], "--help") == 0)
    {
        printHelp();
        return 0;
    }

    Args args = {0};
    strcpy(args.outputName, "output.bmp");

    const char *shortOptions = "hIvgribS:R:L:B:A:u:d:c:o:t:";
    const struct option longOptions[] = {
        {"help", NO_ARGUMENT, NULL, 'h'},
        {"info", NO_ARGUMENT, NULL, 'I'},
        {"inverse", NO_ARGUMENT, NULL, 'v'},
        {"gray", NO_ARGUMENT, NULL, 'g'},
        {"resize", NO_ARGUMENT, NULL, 'r'},
        {"right", REQIURED_ARGUMENT, NULL, 'R'},
        {"left", REQIURED_ARGUMENT, NULL, 'L'},
        {"below", REQIURED_ARGUMENT, NULL, 'B'},
        {"above", REQIURED_ARGUMENT, NULL, 'A'},
        {"input", REQIURED_ARGUMENT, NULL, 'i'},
        {"left_up", REQIURED_ARGUMENT, NULL, 'u'},
        {"right_down", REQIURED_ARGUMENT, NULL, 'd'},
        {"color", REQIURED_ARGUMENT, NULL, 'c'},
        {"output", REQIURED_ARGUMENT, NULL, 'o'},
        {"binarization", NO_ARGUMENT, NULL, 'b'},
        {"threshold", REQIURED_ARGUMENT, NULL,'t'},
        {NULL, 0, NULL, 0}};

    int opt;
    int optionIndex = -1;
    unsigned char r, g, b;
    char outName[MAX_FILE_NAME];
    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex)) != -1)
    {
        switch (opt)
        {
        case 'h':
            printHelp();
            break;
        case 'I':
            args.info = 1;
            break;
        case 'R':
            if (sscanf(optarg, "%d", &args.sideSize[0]) != 1)
            {
                printf("Invalid argument. Argument must be integer\n");
                return INPUT_ERROR;
            }
            break;
        case 'b':
            args.binarization = 1;
            break;
        case 't':
            if (sscanf(optarg, "%hd", &args.threshold) != 1){
                printf("Invalid argument. Argument must be integer\n");
                return INPUT_ERROR;
            }
            break;
        case 'B':
            if (sscanf(optarg, "%d", &args.sideSize[1]) != 1)
            {
                printf("Invalid argument. Argument must be integer\n");
                return INPUT_ERROR;
            }
            break;
        case 'L':
            if (sscanf(optarg, "%d", &args.sideSize[2]) != 1)
            {
                printf("Invalid argument. Argument must be integer\n");
                return INPUT_ERROR;
            }
            break;
        case 'A':
            if (sscanf(optarg, "%d", &args.sideSize[3]) != 1)
            {
                printf("Invalid argument. Argument must be integer\n");
                return INPUT_ERROR;
            }
            break;
        case 'u':
            if (sscanf(optarg, "%d.%d", args.leftUp, args.leftUp + 1) != 2)
            {
                printf("Invalid argument. left_up argument must be x.y\n");
                return INPUT_ERROR;
            }
            break;
        case 'd':
            if (sscanf(optarg, "%d.%d", args.rightDown, args.rightDown + 1) != 2)
            {
                printf("Invalid argument. right_down argument must be x.y\n");
                return INPUT_ERROR;
            }
            break;
        case 'c':
            if ((sscanf(optarg, "%hhu.%hhu.%hhu", &r, &g, &b) != 3) || (r > 255) || (b > 255) || (g > 255))
            {
                printf("Invalid argument. Color argument must be rrr.ggg.bbb");
                return INPUT_ERROR;
            }
            args.color.r = r;
            args.color.g = g;
            args.color.b = b;

            break;
        case 'o':
            if (sscanf(optarg, "./%s", outName) != 1)
            {
                printf("Invalid argument.");
                return 1;
            }
            strcpy(args.outputName, outName);
            break;
        case 'i':
            if (sscanf(optarg, "./%s", args.fileName) != 1)
            {
                printf("Invalid argument.");
                return 1;
            }
            break;
        case 'v':
            args.inverse = 1;
            break;
        case 'g':
            args.gray = 1;
            break;
        case 'r':
            args.resize = 1;
            break;
        }
        optionIndex = -1;
    }

    if (strlen(args.fileName) == 0)
    {
        printf("No input file name was entered");
        return INPUT_ERROR;
    }
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb **arr = readBmp(args.fileName, &bmfh, &bmih);
    unsigned int h = bmih.height;

    if (bmfh.signature != 0x4d42)
    {
        printf("File doesnt't bmp.\n");
        return 0;
    }
    if (bmih.bitsPerPixel != 24)
    {
        printf("Image doesn't contain 24 bits per color.\n");
        return 0;
    }

    if ((args.inverse + args.gray + args.resize + args.info + args.binarization) != 1)
    {
        printf("[v - %d] [g - %d] [r - %d] [info - %d]", args.inverse, args.gray, args.resize, args.info);
        printf("Too many arguments or too few\n");
        return INPUT_ERROR;
    }
    if (args.info)
    {
        printFileHeader(bmfh);
        printInfoHeader(bmih);
    }

    if (args.inverse)
    {
        inverse(arr, args.outputName, &bmfh, &bmih, args.leftUp[0], args.leftUp[1], args.rightDown[0], args.rightDown[1]);
    }

    if (args.gray)
    {
        gray(arr, args.outputName, &bmfh, &bmih, args.leftUp[0], args.leftUp[1], args.rightDown[0], args.rightDown[1]);
    }

    if (args.resize)
    {
        resize(arr, args.outputName, &bmfh, &bmih, args.sideSize, args.color);
    }

    if (args.binarization){
        binarization(arr, args.outputName, &bmfh, &bmih, args.threshold);
    }
    freeRgb(arr, h);

    return 0;
}