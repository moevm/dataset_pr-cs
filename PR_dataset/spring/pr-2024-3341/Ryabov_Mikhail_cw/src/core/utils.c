#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "../headers/utils.h"

const char* patternColor = "[0-9]+\\.[0-9]+\\.[0-9]+";
const char* patternCoords = "[0-9-]+\\.[0-9-]+";
const char* patternNum = "[0-9-]+";

void callHelp(){
    printf("Course work for option 4.4, created by Ryabov Mikhail.\n");
    exit(0);
}

void callInfo(char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo){
    printf("Name BMP image: %s\n", fileName);
    print_file_header(*BMPFile);
    print_info_header(*BMPInfo);
    exit(0);
}

void print_file_header(const BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(const BitmapInfoHeader header){
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

void callError(const int status){
    switch (status)
    {
        case 40:
            fprintf(stderr, "Incorrect color value.\n");
            break;
        case 41:
            fprintf(stderr, "Incorrect type flags.\n");
            break;
        case 42:
            fprintf(stderr, "Incorrect count of flags.\n");
            break;
        case 43:
            fprintf(stderr, "Incorrect fill/fill_color flags.\n");
            break;
        case 44:
            fprintf(stderr, "Input and Output files is the same.\n");
            break;
        case 45:
            fprintf(stderr, "Flag argument does not match pattern.\n");
            break;
        case 46:
            fprintf(stderr, "Inpossible open the file.\n");
            break;
        case 47:
            fprintf(stderr, "Your area is too small.\n");
            break;
        case 48:
            fprintf(stderr, "file header not match.\n");
        default:
            fprintf(stderr, "Unknown error...\n");
            break;
    }
    printf("call --help or -h to see more information.\n");
    exit(status);
}

int matchRegExp(const char* buffer, const char* pattern){
    regex_t regexCompiled;
    regcomp(&regexCompiled, pattern, REG_EXTENDED);
    if(regexec(&regexCompiled, buffer, 0, NULL, 0) == 0)
        return 1;
    return 0;
}

void strToDouble(char* num, double* val){
    char* argcpy = getStrClone(num);

    (*val) = strtod(argcpy, NULL);
    if((*val) < 0)
        callError(43);
}

void parseCoords(char* coords, int* x, int* y){
    if(!matchRegExp(coords, patternCoords))
        callError(45);
    char* argcpy = getStrClone(coords);
    (*x) = atoi(strtok(argcpy, "."));
    (*y) = atoi(strtok(NULL, "."));
}

void strToNum(char* num, int* val){
    if(!matchRegExp(num, patternNum))
        callError(43);
    char* argcpy = getStrClone(num);
    (*val) = atoi(strtok(argcpy, "."));
    if((*val) <= 0)
        callError(43);
}

void strToRGB(char* str, Rgb* color){
    if(!matchRegExp(str, patternColor))
        callError(40);
    char* argcpy = getStrClone(str);
    const int r = atoi(strtok(argcpy, "."));
    const int g = atoi(strtok(NULL, "."));
    const int b = atoi(strtok(NULL, "."));
    if((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
        callError(40);
    color->r = r;
    color->g = g;
    color->b = b;
}

char* getStrClone(const char* src){
    char* strClone = (char*)malloc(sizeof(char)*(strlen(src) + 1));
    strcpy(strClone, src);
    strClone[strlen(src)] = '\0';
    return strClone;
}

Rgb** readFile(const char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo)
{
    FILE *file = fopen(fileName, "rb");
    if(file == NULL)
        callError(46);

    fread(BMPFile, 1, sizeof(BitmapFileHeader), file);
    fread(BMPInfo, 1, sizeof(BitmapInfoHeader), file);

    if (BMPFile->signature != 0x4d42){
        fprintf(stderr, "File Error: file must be bmp\n");
        fclose(file);
        exit(48);
    }
    if (BMPInfo->compression != 0){
        fprintf(stderr, "File Error: file must be uncompressed\n");
        fclose(file);
        exit(48);
    }

    if (BMPInfo->bitsPerPixel != 24){
        fprintf(stderr, "File Error: file must have 24 bits per pixel\n");
        fclose(file);
        exit(48);
    }
    if (BMPInfo->width > 50000 || BMPInfo->height > 50000){
        fprintf(stderr, "file is too big\n");
        fclose(file);
        exit(48);
    }

    unsigned int width = BMPInfo->width;
    unsigned int height = BMPInfo->height;

    Rgb** bitmap = (Rgb**)malloc(sizeof(Rgb*) * height);
    for(int i = 0; i < height; i++)
        bitmap[i] = (Rgb*)malloc(lenRow(width));

    for(int i = 0; i < height; i++)
        fread(bitmap[height - i - 1], 1, lenRow(width), file);
    fclose(file);
    return bitmap;
}

void writeFile(const char* fileName, BitmapFileHeader* BMPFile, BitmapInfoHeader* BMPInfo, Rgb** arr)
{
    FILE* file = fopen(fileName, "wb");
    fwrite(BMPFile, 1, sizeof(BitmapFileHeader), file);
    fwrite(BMPInfo, 1, sizeof(BitmapInfoHeader), file);
    const unsigned int width = BMPInfo->width;
    const unsigned int height = BMPInfo->height;
    for(int i = 0; i < height; i ++)
        fwrite(arr[height - i - 1], 1, lenRow(width), file);
    fclose(file);
}

unsigned int padding(const unsigned int width)
{
    unsigned int padding = (width * sizeof(Rgb)) % 4;
    if(padding) padding = 4 - padding;
    return padding;
}

unsigned int lenRow(const unsigned int width)
{
    return width * sizeof(Rgb) + padding(width);
}

int isCorrectType(char* type)
{
    if(!strcmp("clockwise", type)) return 1;
    if(!strcmp("counterclockwise", type)) return 2;
    if(!strcmp("diagonals", type)) return 3;
    return 0;
}

void checkCorrectPlacement(int* left, int* up, int* right, int* down, int width, int height)
{
    validCoord(left, width);
    validCoord(right, width);
    validCoord(up, height);
    validCoord(down, height);
    //if(abs((*right) - (*left)) <= 1 || abs((*up) - (*down)) <= 1 ) callError(47);
    if(*left > *right)
    {
        int buf = *left;
        *left = *right;
        *right = buf;
    }
    if(*down < *up)
    {
        int buf = *up;
        *up = *down;
        *down = buf;
    }
}

void validCoord(int* value, const int edge)
{
    (*value) < 0 ? (*value) = 0 : (*value);
    (*value) >= edge ? (*value) = edge - 1 : (*value);
}
