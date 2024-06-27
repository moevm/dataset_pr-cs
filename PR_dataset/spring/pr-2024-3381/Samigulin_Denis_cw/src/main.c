#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

#define NO_ARGS 40
#define INPUT_ERROR 41
#define OUTPUT_ERROR 42
#define WRONG_OPT 42
#define ERROR 43

#pragma pack(push, 1)
typedef struct {
    unsigned short signature;     
    unsigned int fileSize;        
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

Rgb **arr;
BitmapFileHeader bfh;
BitmapInfoHeader bih;
char *inputFile;
char *outputFile;

int getPad(int w) {
    int pad = w * sizeof(Rgb);
    if (4 - w * sizeof(Rgb) % 4 == 4) {
        return pad;
    }
    else {
        return pad + (4 - w * sizeof(Rgb) % 4);
    }
}

void readBmp() {
    FILE *f = fopen(inputFile, "rb");
    if (f == NULL) {
        printf("Не удалость открыть файл.\n");
        exit(INPUT_ERROR);
    }

    fread(&bfh, sizeof(BitmapFileHeader), 1, f);
    fread(&bih, sizeof(BitmapInfoHeader), 1, f);

    if (bfh.signature != 0x4D42) {
        printf("Неправильная сигнатура файла.\n");
        exit(INPUT_ERROR);
    }
    else if (bih.compression != 0) {
        printf("Файлы с сжатием не поддерживаются\n");
        exit(INPUT_ERROR);
    }
    else if (bih.bitsPerPixel != 24) {
        printf("Поддерживаются только изображения с 24 битами на пиксель\n");
        exit(INPUT_ERROR);
    } 

    fseek(f, bfh.pixelArrOffset, SEEK_SET);

    int h = bih.height;
    int w = bih.width;

    int pad = getPad(w);

    arr = (Rgb**)malloc(h * sizeof(Rgb*));
    for (int i = 0; i < h; i++) {
        arr[h - i - 1] = (Rgb*)malloc(pad);
        fread(arr[h - i - 1], pad, 1, f);
    }
    fclose(f);
    printf("Изображение было считано\n");
}

void writeBmp() {
    int h = bih.height;
    int w = bih.width;
    int pad = getPad(w);

    FILE *f = fopen(outputFile, "wb");
    if (f == NULL) {
        printf("Не получилось открыть файл!\n");
        exit(41);
    }

    fwrite(&bfh, sizeof(BitmapFileHeader), 1, f);
    fwrite(&bih, sizeof(BitmapInfoHeader), 1, f);

    fseek(f, bfh.pixelArrOffset, SEEK_SET);

    for (int i = 0; i < h; i++) {
        fwrite(arr[h - i - 1], pad, 1, f);
    }
    
    fclose(f);
    printf("Изображение успешно записано!\n");
}

void printFileHeader() {
    printf("BitmapFileHeader:\n");
    printf("signature:\t%x (%hu)\n", bfh.signature, bfh.signature);
    printf("fileSize:\t%x (%u)\n", bfh.fileSize, bfh.fileSize);
    printf("reserved1:\t%x (%hu)\n", bfh.reserved1, bfh.reserved1);
    printf("reserved2:\t%x (%hu)\n", bfh.reserved2, bfh.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", bfh.pixelArrOffset, bfh.pixelArrOffset);
}

void printInfoHeader() 
{
    printf("BitmapInfoHeader:\n");
    printf("headerSize:\t%x (%u)\n", bih.headerSize, bih.headerSize);
    printf("width:\t%x (%u)\n", bih.width, bih.width);
    printf("height:\t%x (%u)\n", bih.height, bih.height);
    printf("planes:\t%x (%hu)\n", bih.planes, bih.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", bih.bitsPerPixel, bih.bitsPerPixel);
    printf("compression:\t%x (%u)\n", bih.compression, bih.compression);
    printf("imageSize:\t%x (%u)\n", bih.imageSize, bih.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", bih.xPixelsPerMeter, bih.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", bih.yPixelsPerMeter, bih.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", bih.colorsInColorTable, bih.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", bih.importantColorCount, bih.importantColorCount);
}

void help() {
    puts("Функции курсовой работы:");
    puts("-h и --help - вывод помощи");
    puts("-I и --info имя файла - информация о заголовках");
    puts("-i и --input имя файла - ввод имени файла ввода");
    puts("-o и --output [имя выходного файла] - ввод имени файла вывода");
    puts("-c и --color_replace - функция замены цвета");
    puts("-O и --old_color - флаг ввода цвета");
    puts("-n и --new_color - флаг ввода цвета");
    puts("-С и --component_max - функция взятия максимума из компонент цвета");
}

Rgb getColor(char *arg) {
    regex_t reg;
    int groupsCount = 4;
    regmatch_t groups[groupsCount];

    char* str = "^([01]{0,1}[0-9]{0,1}[0-9]|2[0-4][0-9]|25[0-5])\\.([01]{0,1}[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]{0,1}[0-9]{0,1}[0-9]|2[0-4][0-9]|25[0-5])$";

    int val = regcomp(&reg, str, REG_EXTENDED);
    if (val) {
        printf("Ошибка компиляции регулярного выражения\n");
        exit(ERROR);
    }
    
    Rgb color;
    
    val = regexec(&reg, arg, groupsCount, groups, 0);
    int ind = 0;
    char buf[300];

    if (!val) {
        for (size_t i = 1; i < groupsCount; i++) {
				if (groups[i].rm_so == -1)
					break;

				for (size_t j = groups[i].rm_so; j < groups[i].rm_eo; j++)
				    buf[ind++] = arg[j];
				    
				buf[ind] = '\0';

				if (i - 1 == 0)
				    color.r = atoi(buf);
				else if (i - 2 == 0)
				    color.g = atoi(buf);
				else if (i - 3 == 0)
				    color.b = atoi(buf);
				ind = 0;
		}
		        
        regfree(&reg);
    }
    else {
        regfree(&reg);
        printf("Неверно введён цвет\n");
        exit(ERROR);
    }

    return color;
}

int colorsIsEqual(Rgb color1, Rgb color2) {
    if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
        return 1;
    else
        return 0;
}

void colorReplaceFunc(Rgb oldColor, Rgb newColor) {
    for (int i = 0; i < bih.height; i++) {
        for (int j = 0; j < bih.width; j++) {
            if (colorsIsEqual(arr[i][j], oldColor))
                arr[i][j] = newColor;
        }
    }
}

int max(Rgb color) {
    int r = color.r;
    int g = color.g;
    int b = color.b;
    if (r > g && r > b) {
        return r;
    }
    if (g > r && g > b) {
        return g;
    }
    if (b > r && b > g) {
        return b;
    }
    return r;
}

void componentMaxFunc() {
    for (int i = 0; i < bih.height; i++) {
        for (int j = 0; j < bih.width; j++) {
            int maxColor = max(arr[i][j]);
            arr[i][j].r = maxColor;
            arr[i][j].g = maxColor;
            arr[i][j].b = maxColor;
        }
    }
}

void contrast(double alpha, int beta) {
    for (int i = 0; i < bih.height; i++) {
        for (int j = 0; j < bih.width; j++) {
            int new_r = (int)(alpha * arr[i][j].r) + beta;
            int new_g = (int)(alpha * arr[i][j].g) + beta;
            int new_b = (int)(alpha * arr[i][j].b) + beta;
            if (new_r < 0)
                new_r = 0;
            else if (new_r > 255)
                new_r = 255;
            if (new_g < 0)
                new_g = 0;
            else if (new_g > 255)
                new_g = 255;
            if (new_b < 0)
                new_b = 0;
            else if (new_b > 255)
                new_b = 255;
            arr[i][j].r = new_r;
            arr[i][j].g = new_g;
            arr[i][j].b = new_b;
        }
    }
}

int main(int argc, char **argv) {
    int info = 0;
    int input = 0;
    int output = 0;
    int colorReplace = 0;
    int oldColor = 0;
    int newColor = 0;
    int componentMax = 0;
    int contrastFlag = 0;
    int alphaFlag = 0;
    int betaFlag = 0;

    Rgb oldColorArg;
    Rgb newColorArg;

    double alpha = 0;
    int beta = 0;
    
    puts("Course work for option 3.1, created by Denis Samigulin\n");

    if (argc < 2) {
        printf("Отсутствуют аргументы для программы\n");
        exit(40);
    }

    // короткие и длинные опции
    char *sopts = "hIi:o:cO:n:C";
    struct option lopts[] = {
        {"help", 0, 0, 'h'},
        {"info", 0, 0, 'I'},
        {"input", 1, 0, 'i'},
        {"output", 1, 0, 'o'},
        {"color_replace", 0, 0, 'c'},
        {"old_color", 1, 0, 'O'},
        {"new_color", 1, 0, 'n'},
        {"component_max", 0, 0, 'C'},
        {"contrast", 0, 0, 't'},
        {"alpha", 1, 0, 'a'},
        {"beta", 1, 0, 'b'},
        {0, 0, 0, 0}  
    };

    int opt;
    while ((opt = getopt_long(argc, argv, sopts, lopts, &optind)) != -1) {
        switch (opt) {
            case 'h':
                help();
                return 0;
            case 'I':
                info = 1;
                break;
            case 'i':
                input = 1;
                inputFile = optarg;
                break;
            case 'o':
                output = 1;
                outputFile = optarg;
                break;
            case 'c':
                colorReplace = 1;
                break;
            case 'O':
                oldColor = 1;
                oldColorArg = getColor(optarg);
                break;
            case 'n':
                newColor = 1;
                newColorArg = getColor(optarg);
                break;
            case 'C':
                componentMax = 1;
                break;
            case 't':
                contrastFlag = 1;
                break;
            case 'a':
                alphaFlag = 1;
                alpha = atof(optarg);
                if (alpha <= 0.0) {
                    printf("Wrong flag!\n");
                    exit(ERROR);
                }
                break;
            case 'b':
                betaFlag = 1;
                beta = atoi(optarg);
                break;
            case '?':
                printf("Неверная опция\n");
                exit(WRONG_OPT);
        }
    }

    if (input == 0) {
        int inputLen = strlen(argv[argc - 1]) + 1;
        inputFile = (char*)malloc(inputLen);
        strcpy(inputFile, argv[argc - 1]);
    }
    
    if (output == 0) {
        int outputLen = strlen("out.bmp") + 1;
        outputFile = (char*)malloc(outputLen);
        strcpy(outputFile, "out.bmp");
    }

    if (strcmp(inputFile, outputFile) == 0) {
        printf("Имена входного и выходного изображения не должны совпадать\n");
    }

    readBmp();

    if (info) {
        printf("Информация о заголовках:\n");
        printFileHeader();
        printInfoHeader();
        return 0;
    }

    if (colorReplace) {
        if (oldColor == 0 || newColor == 0) {
            printf("Ошибка! Нет необходимых флагов\n");
            exit(ERROR);
        }
        else {
            colorReplaceFunc(oldColorArg, newColorArg);
        }
    }

    else if (componentMax) {
        componentMaxFunc();
    }

    else if (contrastFlag && alphaFlag && betaFlag) {
        contrast(alpha, beta);
    }

    writeBmp();

    for (int i = 0; i < bih.height; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
