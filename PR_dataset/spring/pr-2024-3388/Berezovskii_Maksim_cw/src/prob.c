#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

#define NO_ERROR 0
#define MALLOC_ERROR 1
#define DATA_ERROR 2
#define IMAGE_ERROR 3
#define KEY_ERROR 4
#define COLOR_ERROR 5
#define ARG_ERROR 6
#define OPEN_IMAGE_ERROR 7
#define UNDEFINED_KEY 8
#define UNDEFINED_IMAGE 9
#define UNDEFINED_OUT_IMAGE 10

#define MAX_COLOR_VALUE 255
#define PAD 4

static const char* error_msg[] = {
    "ОК",
    "Не удалось выделить память",
    "Неверно введены данные",
    "Изображение не найдено",
    "Неверно введены аргументы ключей",
    "Неизвестный цвет",
    "Неверное количество аргументов",
    "Не удалось открыть изображение",
    "Неизвестный ключ",
    "Не указан путь к изображению",
    "Не указан путь к выходному файлу"
};

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

typedef struct {
    BitmapInfoHeader InfoH;
    BitmapFileHeader FileH;
    Rgb **pixels;
} Image;

#pragma pack(pop)

void print_file_header(BitmapFileHeader *header) {
    printf("signature:\t%d\n", header->signature);
    printf("filesize:\t%d\n", header->filesize);
    printf("reserved1:\t%d\n", header->reserved1);
    printf("reserved2:\t%d\n", header->reserved2);
    printf("pixelArrOffset:\t%d\n", header->pixelArrOffset);
}

void print_info_header(BitmapInfoHeader *header) {
    printf("headerSize:\t%d\n", header->headerSize);
    printf("width:\t%d\n", header->width);
    printf("height:\t%d\n", header->height);
    printf("planes:\t%d\n", header->planes);
    printf("bitsPerPixel:\t%d\n", header->bitsPerPixel);
    printf("compression:\t%d\n", header->compression);
    printf("imageSize:\t%d\n", header->imageSize);
    printf("xPixelsPerMeter:\t%d\n", header->xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%d\n", header->yPixelsPerMeter);
    printf("colorsInColorTable:\t%d\n", header->colorsInColorTable);
    printf("importantColorCount:\t%d\n", header->importantColorCount);
}

Image read_image(const char *filename, int *err) {
    Image image = {0};
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        *err = OPEN_IMAGE_ERROR;
        return image;
    }

    fread(&image.FileH, sizeof(BitmapFileHeader), 1, f);
    fread(&image.InfoH, sizeof(BitmapInfoHeader), 1, f);

    unsigned int H = image.InfoH.height;
    unsigned int W = image.InfoH.width;

    unsigned int padding = ((PAD - (W * sizeof(Rgb)) % PAD) % PAD);

    image.pixels = (Rgb**)malloc(H * sizeof(Rgb*));
    if (image.pixels == NULL) {
        *err = MALLOC_ERROR;
        fclose(f);
        return image;
    }

    for (unsigned int i = 0; i < H; i++) {
        image.pixels[i] = (Rgb*)malloc(sizeof(Rgb) * W + padding);
        if (image.pixels[i] == NULL) {
            *err = MALLOC_ERROR;
            fclose(f);
            return image;
        }
        fread(image.pixels[i], 1, sizeof(Rgb) * W + padding, f);
    }

    fclose(f);
    *err = NO_ERROR;
    return image;
}

void write_image(const char *filename, Image *image) {
    FILE *ff = fopen(filename, "wb");
    if (ff == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть файл для записи.\n");
        return;
    }

    unsigned int H = image->InfoH.height;
    unsigned int W = image->InfoH.width;

    unsigned int padding = ((PAD - (W * sizeof(Rgb)) % PAD) % PAD);

    fwrite(&image->FileH, sizeof(BitmapFileHeader), 1, ff);
    fwrite(&image->InfoH, sizeof(BitmapInfoHeader), 1, ff);

    for (unsigned int i = 0; i < H; i++) {
        fwrite(image->pixels[i], 1, sizeof(Rgb) * W + padding, ff);
    }
    fclose(ff);
}

void inverse(Image *image) {
    unsigned int H = image->InfoH.height;
    unsigned int W = image->InfoH.width;

    for (unsigned int i = 0; i < H; i++) {
        for (unsigned int j = 0; j < W; j++) {
            image->pixels[i][j].r = MAX_COLOR_VALUE - image->pixels[i][j].r;
            image->pixels[i][j].g = MAX_COLOR_VALUE - image->pixels[i][j].g;
            image->pixels[i][j].b = MAX_COLOR_VALUE - image->pixels[i][j].b;
        }
    }
}

int component_sum(Image *image, const char *color) {
    unsigned int H = image->InfoH.height;
    unsigned int W = image->InfoH.width;
    int r = NO_ERROR;

    for (unsigned int i = 0; i < H; i++) {
        for (unsigned int j = 0; j < W; j++) {
            unsigned int delta = 0;
            if (strcmp(color, "red") == 0) {
                delta = image->pixels[i][j].g + image->pixels[i][j].b;
                image->pixels[i][j].r = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : delta;
            } else if (strcmp(color, "green") == 0) {
                delta = image->pixels[i][j].r + image->pixels[i][j].b;
                image->pixels[i][j].g = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : delta;
            } else if (strcmp(color, "blue") == 0) {
                delta = image->pixels[i][j].r + image->pixels[i][j].g;
                image->pixels[i][j].b = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : delta;
            } else {
                r = COLOR_ERROR;
                break;
            }
        }
    }
    return r;
}

void apply_gamma(Image* image, float value) {
    unsigned int H = image->InfoH.height;
    unsigned int W = image->InfoH.width;
    float delta = 0;
    for (unsigned int i = 0; i < H; i++) {
        for (unsigned int j = 0; j < W; j++) {
            delta = (powf(((float)image->pixels[i][j].r / MAX_COLOR_VALUE), value) * MAX_COLOR_VALUE);
            image->pixels[i][j].r = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : (int)(delta);
            delta = (powf(((float)image->pixels[i][j].g / MAX_COLOR_VALUE), value) * MAX_COLOR_VALUE);
            image->pixels[i][j].g = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : (int)(delta);
            delta = (powf(((float)image->pixels[i][j].b / MAX_COLOR_VALUE), value) * MAX_COLOR_VALUE);
            image->pixels[i][j].b = (delta > MAX_COLOR_VALUE) ? MAX_COLOR_VALUE : (int)(delta);
        }
    }
}

void print_help() {
    printf("Course work for option 3.2, created by Maksim Berezovskii\n");
    printf("Используйте: ./a.out -i [INPUT FILE] [OPTION] -o [OUTPUT FILE]\n");
    printf("Опции:\n");
    printf("  -h, --help            Показать подсказку\n");
    printf("  -i, --input FILE      Укажите входной BMP-файл\n");
    printf("  -o, --output FILE     Укажите выходной BMP-файл\n");
    printf("  -I, --inverse         Инвертирование изображения\n");
    printf("  -s, --component_sum   Устанавливает один цветовой компонент как сумму двух других\n");
    printf("  -n, --component_name  Укажите цветовой компонент для изменения (red, green, blue)\n");
    printf("  -d, --info            Посмотреть информацию об изображении\n");
    printf("  -g, --gamma           Применить формулу для изменения гаммы каждого пикселя\n");
    printf("  -v, --value           Укажите числовое значение с плавающей точкой для изменения гаммы\n");
}

void process_image(const char *input_name, const char *output_name, int component_correction, const char *color, int apply_inversion, int display_info, int apply_gamma_correction, double gamma_value) {
    int status = 0;
    Image image = read_image(input_name, &status);

    if (status == NO_ERROR && component_correction && color != NULL) {
        status = component_sum(&image, color);
    }

    if (status == NO_ERROR && apply_inversion) {
        inverse(&image);
    }

    if (status == NO_ERROR && apply_gamma_correction) {
        apply_gamma(&image, gamma_value);
    }

    if (output_name) {
        write_image(output_name, &image);
    }

    if (display_info) {
        print_file_header(&image.FileH);
        print_info_header(&image.InfoH);
    } else if (status != NO_ERROR) {
        fprintf(stderr, "Ошибка: %s.\nИспользуйте --help для справки.\n", error_msg[status]);
    }
}

int main(int argc, char *argv[]) {
    const struct option long_options[] = {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"component_sum", no_argument, NULL, 's'},
        {"component_name", required_argument, NULL, 'n'},
        {"inverse", no_argument, NULL, 'I'},
        {"info", no_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
        {"gamma", no_argument, NULL, 'g'},
        {"value", required_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    int option = 0;
    int long_index = -1;

    char *input_name = NULL;
    char *output_name = NULL;
    char *color = NULL;
    int component_correction = 0;
    int apply_inversion = 0;
    int display_info = 0;
    int apply_gamma_correction = 0;
    double gamma_value = 0.0;

    while ((option = getopt_long(argc, argv, "i:o:Isn:dhgv:", long_options, &long_index)) != -1) {
        switch (option) {
            case 'i':
                input_name = optarg;
                break;
            case 'o':
                output_name = optarg;
                break;
            case 's':
                component_correction = 1;
                break;
            case 'n':
                color = optarg;
                break;
            case 'I':
                apply_inversion = 1;
                break;
            case 'd':
                display_info = 1;
                break;
            case 'h':
                print_help();
                return 0;
            case 'g':
                apply_gamma_correction = 1;
                break;
            case 'v':
                gamma_value = atof(optarg);
                break;
            default:
                fprintf(stderr, "Неизвестная опция. Используйте --help для справки.\n");
                return 1;
        }
    }

    if (input_name) {
        process_image(input_name, output_name, component_correction, color, apply_inversion, display_info, apply_gamma_correction, gamma_value);
    } else {
        fprintf(stderr, "Не указан входной файл. Используйте --help для справки.\n");
    }

    return 0;
}