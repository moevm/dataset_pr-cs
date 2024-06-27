#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define ERROR 41

#pragma pack(push, 1)
typedef struct
{
    unsigned short signature;     // сигнатура BMP файла, должна быть 0x4d42
    unsigned int fileSize;        // размер BMP файла
    unsigned short reserved1;     // зарезервированная память
    unsigned short reserved2;     // зарезервированная память
    unsigned int pixelArrOffset;  // номер байта, на котором находится массив пикселей
} BitmapFileHeader;

typedef struct
{
    unsigned int headerSize;          // размер заголовка
    unsigned int width;               // ширина изображения
    unsigned int height;              // высота изображения
    unsigned short planes;            // количество цветовых плоскостей
    unsigned short bitsPerPixel;      // количество битов на цвет, по условию курсовой: 24 бита
    unsigned int compression;         // наличие сжатия, по условию курсовой: 0
    unsigned int imageSize;           // размер массива пикселей в байтах
    unsigned int xPixelsPerMeter;     // плотность пикселей
    unsigned int yPixelsPerMeter;     // плотность пикселей
    unsigned int colorsInColorTable;  // цветов в таблице цветов
    unsigned int importantColorCount; // количество важных цветов. Если 0, то все цвета важны
} BitmapInfoHeader;

// компоненты в обратном порядке, так как в файле обратный порядок следования байт
typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack(pop)

// структура для хранения информации о наличии флагов
typedef struct
{
    int help;
    int info;
    int input;
    int output;
    int circle;
    int center;
    int radius;
    int color;
    int thickness;
    int fill;
    int fillColor;
    int mirror;
    int axis;
    int leftUp;
    int rightDown;
    int copy;
    int destLeftUp;

    int circlePixel;
    int circleColor;
    int size;

    int imageReaded;
} Flags;

// структура для хранения аргументов флагов
typedef struct
{
    char *input;
    char *output;
    Rgb color;
    unsigned thickness;
    char *axis;
    int leftUp[2];
    int rightDown[2];
    int center[2];
    unsigned radius;
    Rgb fillColor;
    int destLeftUp[2];
    Rgb circleColor;
    int size;
} Args;

// функции чтения BMP файла
void bmpRead(Rgb ***pixPtr, const char *fileName,
             BitmapFileHeader *bmfh, BitmapInfoHeader *bmih);
void bmpWrite(Rgb ***pixPtr, const char *fileName,
              BitmapFileHeader *bmfh, BitmapInfoHeader *bmih);

// функции вывода информации о BMP файле и вывода помощи
void printFileHeader(BitmapFileHeader bmfh);
void printInfoHeader(BitmapInfoHeader bmih);
void printHelp();

// рисование линии
void fillCircle(Rgb ***pixPtr, int x0, int y0,
                int r, Rgb color, int h, int w);
void line(Rgb ***pixPtr, int x0, int y0, int x1, int y1,
          int t, Rgb color, int h, int w);

// отражение заданной области
void mirror(Rgb ***pixPtr, char *axis, int x0, int y0,
            int x1, int y1, int h, int w);


// рисование круга
void draw8Pixels(Rgb ***pixPtr, int x0, int y0, int x, int y,
                 int t, Rgb color, int h, int w);
void circle(Rgb ***pixPtr, int x0, int y0, int r,
            int t, Rgb color, int fill, Rgb fillColor, int h, int w);

// копирование заданной области на заданную координату
Rgb** copyArea(Rgb ***pixPtr,
               int x0, int y0,
               int x1, int y1,
               int h, int w);
void replaceToArea(Rgb ***pixPtr, Rgb ***area,
                   int xD, int yD, int areaH, int areaW,
                   int h, int w);
void copy(Rgb ***pixPtr,
          int x0, int y0,
          int x1, int y1,
          int xD, int yD,
          int h, int w);

// функция обмена значения двух чисел
void swapInt(int *a, int *b);

// функция для очищения выделенной памяти
void freeMemory(Rgb ***pixPtr, BitmapInfoHeader bmih,
                Flags flags, Args args);

int pixelCmp(Rgb p1, Rgb p2)
{
    if (p1.r == p2.r && p1.g == p2.g && p1.b == p2.b)
        return 1;
    return 0;
}

void circlePixel(Rgb ***pixPtr, Rgb circle_color, Rgb color, int size, int h, int w)
{
    Rgb **pix = *pixPtr;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (pixelCmp(pix[y][x], color))
            {
                for (int y0 = y - size; y0 < y + size + 1; y0++)
                {
                    for (int x0 = x - size; x0 < x + size + 1; x0++)
                    {
                        if (!(x0 == x && y0 == y) && y0 >= 0 && x0 >= 0 && y0 < h && x0 < w && !pixelCmp(pix[y0][x0], color))
                        {
                            pix[y0][x0] = circle_color;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    printf("Course work for option 4.1, created by Darya Bondarenko\n");

    // проеряем, что программе были переданы хоть какие-то аргументы
    if (argc == 1)
    {
        printf("Программе не были переданы аргументы!\n");
        exit(ERROR);
    }

    // иницииализируем структуры
    Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Args args;

    // определяем переменные для хранения информации об изображении
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb **pix;

    // символ, представляющий возвращаемой значение getopt_long
    int optchar;

    // короткие и длинные опции
    char *opts = "hni:o:RC:r:c:t:lL:ma:u:d:OD:";
    struct option longOpts[] =
    {
        // общие флаги
        {"help", no_argument, 0, 'h'},
        {"info", no_argument, 0, 'n'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},

        // флаги рисования окружности
        {"circle", no_argument, 0, 'R'},
        {"center", required_argument, 0, 'C'},
        {"radius", required_argument, 0, 'r'},
        {"color", required_argument, 0, 'c'},
        {"thickness", required_argument, 0, 't'},
        {"fill", no_argument, 0, 'l'},
        {"fill_color", required_argument, 0, 'L'},

        // флаги отражения области
        {"mirror", no_argument, 0, 'm'},
        {"axis", required_argument, 0, 'a'},
        {"left_up", required_argument, 0, 'u'},
        {"right_down", required_argument, 0, 'd'},

        // флаги копирования области
        {"copy", no_argument, 0, 'O'},
        {"dest_left_up", required_argument, 0, 'D'},

        {"circle_pixel", no_argument, 0, 'x'},
        {"circle_color", required_argument, 0, 'e'},
        {"size", required_argument, 0, 'q'},

        {0, 0, 0, 0}
    };

    // переменная для хранения возвращаемых значений функции sscanf
    int ret;

    // временные переменные для корректного считывания аргументов флагов
    int r;
    int g;
    int b;
    int thickness;
    int radius;
    int size;

    // считываем флаги
    while ((optchar = getopt_long(argc, argv, opts, longOpts, &optind)) != -1)
    {
        switch (optchar)
        {
            // общие флаги
            case 'h': // --help
                printHelp();
                return 0;
            case 'n': // --info
                flags.info = 1;
                break;
            case 'i': // --input
                flags.input = 1;

                int inputLen = strlen(optarg);
                args.input = (char*)malloc(inputLen * sizeof(char));
                strncpy(args.input, optarg, inputLen);
                break;
            case 'o': // --output
                flags.output = 1;
                int outputLen = strlen(optarg);
                args.output = (char*)malloc(outputLen * sizeof(char));
                strncpy(args.output, optarg, outputLen);
                break;

            // рисование окружности
            case 'R': // --circle
                flags.circle = 1;
                break;
            case 'C': // --center
                flags.center = 1;
                ret = sscanf(optarg, "%d.%d", &args.center[0], &args.center[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                break;
            case 'r': // --radius
                flags.radius = 1;
                ret = sscanf(optarg, "%d", &radius);
                if (ret < 1)
                {
                    fprintf(stderr, "Радиус должен быть числом\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                else if (radius <= 0)
                {
                    fprintf(stderr, "Радиус должен быть положительным\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.radius = radius;
                break;
            case 't': // --thickness
                flags.thickness = 1;
                ret = sscanf(optarg, "%d", &thickness);
                if (ret < 1)
                {
                    fprintf(stderr, "Толщина должна быть числом\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                else if (thickness <= 0)
                {
                    fprintf(stderr, "Толщина должна быть положительным числом\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.thickness = thickness;
                break;
            case 'c': // --color
                flags.color = 1;
                ret = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (ret < 3)
                {
                    fprintf(stderr, "Нужно ввести целочисленные компоненты в виде r.g.b\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                else if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                {
                    fprintf(stderr, "Компоненты должны быть в диапазоне от 0 до 255 включительно\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.color.r = r;
                args.color.g = g;
                args.color.b = b;
                break;
            case 'l': // --fill
                flags.fill = 1;
                break;
            case 'L': // --fillColor
                flags.fillColor = 1;
                ret = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (ret < 3)
                {
                    fprintf(stderr, "Компоненты цвета должны быть в диапазоне от 0 до 255 включительно\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.fillColor.r = r;
                args.fillColor.g = g;
                args.fillColor.b = b;
                break;

            case 'm': // --mirror
                flags.mirror = 1;
                break;
            case 'a': // --axis
                flags.axis = 1;
                args.axis = optarg;
                if (strcmp("x", args.axis) && strcmp("y", args.axis)) {
                    fprintf(stderr, "--axis может принимать одно из значений  x или y\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                break;
            case 'u': // --left_up
                flags.leftUp = 1;
                ret = sscanf(optarg, "%d.%d", &args.leftUp[0], &args.leftUp[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                break;
            case 'd': // --right_down
                flags.rightDown = 1;
                ret = sscanf(optarg, "%d.%d", &args.rightDown[0], &args.rightDown[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                break;

            case 'O': // --copy
                flags.copy = 1;
                break;
            case 'D': // --dest_left_up
                flags.destLeftUp = 1;
                ret = sscanf(optarg, "%d.%d", &args.destLeftUp[0], &args.destLeftUp[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                break;

            case 'x':
                flags.circlePixel = 1;
                break;
            case 'e':
                flags.circleColor = 1;
                 ret = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (ret < 3)
                {
                    fprintf(stderr, "Компоненты цвета должны быть в диапазоне от 0 до 255 включительно\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.circleColor.r = r;
                args.circleColor.g = g;
                args.circleColor.b = b;
                break;
            case 'q':
                flags.size = 1;
                ret = sscanf(optarg, "%d", &size);
                if (ret < 1)
                {
                    fprintf(stderr, "--size должен быть числом\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }
                else if (size <= 0)
                {
                    fprintf(stderr, "--size должен быть положительным\n");
                    freeMemory(&pix, bmih, flags, args);
                    exit(ERROR);
                }

                args.size = size;
                break;

            // в случае если был получен неизвестный флаг
            case '?':
                fprintf(stderr, "Неизвестная опция!\n");
                freeMemory(&pix, bmih, flags, args);
                exit(ERROR);
        }
    }

    // если не был передан флаг --input, значит имя
    // входного файла - это последний аргумент командной строки
    if (!flags.input)
    {
        flags.input = 1;
        int inputLen = strlen(argv[argc - 1]);
        args.input = (char*)malloc(inputLen * sizeof(char));
        strncpy(args.input, argv[argc - 1], inputLen);
    }

    // если не был передан флаг --output, значит у выходного
    // файла будет стандартное название "out.bmp"
    if (!flags.output)
    {
        flags.output = 1;
        int outputLen = strlen("out.bmp");
        args.output = (char*)malloc(outputLen * sizeof(char));
        strncpy(args.output, "out.bmp", outputLen);
    }

    // имя входного и выходного файла не должны совпадать
    if (strcmp(args.input, args.output) == 0)
    {
        fprintf(stderr, "Имена входного и выходного изображения совпадают!\n");
        freeMemory(&pix, bmih, flags, args);
        exit(ERROR);
    }

    // считываем изображение
    bmpRead(&pix, args.input, &bmfh, &bmih);
    flags.imageReaded = 1;

    int w = bmih.width;
    int h = bmih.height;

    // обрабатываем флаг --info
    if (flags.info)
    {
        printf("Информация о заголовках:\n");
        printFileHeader(bmfh);
        printInfoHeader(bmih);

        freeMemory(&pix, bmih, flags, args);
        return 0;
    }

    // обрабатываем флаг --circle
    else if (flags.circle)
    {
        if (!flags.center || !flags.radius ||
            !flags.color || !flags.thickness)
        {
            fprintf(stderr, "Отсутствуют необходимые флаги для --circle\n");
            freeMemory(&pix, bmih, flags, args);
            exit(ERROR);
        }
        else if (flags.fill && !flags.fillColor)
        {
            fprintf(stderr, "Неверно введены флаги --fill и --fill_color!\n");
            freeMemory(&pix, bmih, flags, args);
            exit(ERROR);
        }
        circle(&pix, args.center[0], args.center[1], args.radius, args.thickness, args.color, flags.fill, args.fillColor, h, w);
    }

    // обрабатываем флаг --mirror
    else if (flags.mirror)
    {
        if (flags.axis == 0 || flags.leftUp == 0 || flags.rightDown == 0)
        {
            fprintf(stderr, "Отсутствуют необходимые для --mirror флаги!\n");
            freeMemory(&pix, bmih, flags, args);
            exit(ERROR);
        }
        mirror(&pix, args.axis, args.leftUp[0], args.leftUp[1], args.rightDown[0], args.rightDown[1], bmih.height, bmih.width);
    }

    // обрабатываем флаг --copy
    else if (flags.copy)
    {
        if (!flags.leftUp || !flags.rightDown || !flags.destLeftUp)
        {
            fprintf(stderr, "Отсутствуют необходимые для --copy флаги\n");
            freeMemory(&pix, bmih, flags, args);
            exit(ERROR);
        }

        int x0 = args.leftUp[0];
        int y0 = args.leftUp[1];
        int x1 = args.rightDown[0];
        int y1 = args.rightDown[1];
        int xD = args.destLeftUp[0];
        int yD = args.destLeftUp[1];

        copy(&pix, x0, y0, x1, y1, xD, yD, h, w);
    }

    if (flags.circlePixel)
    {
        if (!flags.circleColor && !flags.size && !flags.color)
        {
            fprintf(stderr, "--circle_pixel need args\n");
            exit(ERROR);
        }

        circlePixel(&pix, args.circleColor, args.color, args.size, bmih.height, bmih.width);
    }

    // записываем полученное после обработки изображение в новый файл
    bmpWrite(&pix, args.output, &bmfh, &bmih);

    freeMemory(&pix, bmih, flags, args);

    return 0;
}

void freeMemory(Rgb ***pixPtr, BitmapInfoHeader bmih,
                Flags flags, Args args)
{
    // очищаем выделенную под имена память
    if (flags.input)
        free(args.input);
    if (flags.output)
        free(args.output);

    if (flags.imageReaded) {
        for (int y = 0; y < bmih.height; y++)
            free((*pixPtr)[y]);
        free(*pixPtr);
    }
}

void bmpRead(Rgb ***pixPtr, const char *fileName, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih)
{
    FILE *f = fopen(fileName, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Не удалость открыть BMP файл\n");
        exit(ERROR);
    }

    // считываем заголовки
    fread(bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(bmih, sizeof(BitmapInfoHeader), 1, f);

    if (bmfh->signature != 0x4D42 || bmih->compression != 0 || bmih->bitsPerPixel != 24)
    {
        fprintf(stderr, "Либо это не BMP файл, либо такой BMP файл не поддерживается\n");
        exit(ERROR);
    }

    // перемещаемся на позицию в файле, где находится массив пикселей
    fseek(f, bmfh->pixelArrOffset, SEEK_SET);

    int h = bmih->height;
    int w = bmih->width;

    int paddedWidth = w * sizeof(Rgb) + (4 - w * sizeof(Rgb) % 4) % 4;

    *pixPtr = (Rgb**)calloc(h, sizeof(Rgb*));
    for (int i = 0; i < h; i++)
    {
        (*pixPtr)[h - i - 1] = (Rgb*)calloc(paddedWidth, 1);
        fread((*pixPtr)[h - i - 1], paddedWidth, 1, f);
    }
    fclose(f);

    printf("Изображение было успешно считано!\n");
}

void bmpWrite(Rgb ***pixPtr, const char *fileName, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih)
{
    int h = bmih->height;
    int w = bmih->width;
    int paddedWidth = w * sizeof(Rgb) + (4 - w * sizeof(Rgb) % 4) % 4;

    FILE *f = fopen(fileName, "wb");
    if (f == NULL)
    {
        fprintf(stderr, "Не удалось записать файл!\n");
        exit(ERROR);
    }

    fwrite(bmfh, sizeof(BitmapFileHeader), 1, f);
    fwrite(bmih, sizeof(BitmapInfoHeader), 1, f);

    fseek(f, bmfh->pixelArrOffset, SEEK_SET);

    for (int i = 0; i < h; i++)
    {
        fwrite((*pixPtr)[h - i - 1], paddedWidth, 1, f);
    }

    fclose(f);

    printf("Изображение было успешно записано!\n");
}

void printFileHeader(BitmapFileHeader bmfh)
{
    printf("signature:\t%x (%hu)\n", bmfh.signature, bmfh.signature);
    printf("fileSize:\t%x (%u)\n", bmfh.fileSize, bmfh.fileSize);
    printf("reserved1:\t%x (%hu)\n", bmfh.reserved1, bmfh.reserved1);
    printf("reserved2:\t%x (%hu)\n", bmfh.reserved2, bmfh.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", bmfh.pixelArrOffset, bmfh.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader bmih)
{
    printf("headerSize:\t%x (%u)\n", bmih.headerSize, bmih.headerSize);
    printf("width:\t%x (%u)\n", bmih.width, bmih.width);
    printf("height:\t%x (%u)\n", bmih.height, bmih.height);
    printf("planes:\t%x (%hu)\n", bmih.planes, bmih.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", bmih.bitsPerPixel, bmih.bitsPerPixel);
    printf("compression:\t%x (%u)\n", bmih.compression, bmih.compression);
    printf("imageSize:\t%x (%u)\n", bmih.imageSize, bmih.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", bmih.xPixelsPerMeter, bmih.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", bmih.yPixelsPerMeter, bmih.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", bmih.colorsInColorTable, bmih.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", bmih.importantColorCount, bmih.importantColorCount);
}

void printHelp()
{
    printf("Помощь:\n");
    printf("-h --help - помощь\n");
    printf("-n --info [имя входного файла] - информация об изображении\n");
    printf("-i --input [имя входного файла] - переопределение имени файла ввода\n");
    printf("-o --output [имя выходного файла] - переопределение имени файла вывода\n");
    puts("");
    printf("-R --circle - функция рисования окружности, требует флаги --center, --radius, --color, --thickness для работы и опциональные флаги --fill и --fill_color\n");
    printf("-C --center [координаты точки]- флаг, принимающий координаты точки в формате x.y\n");
    printf("-r --radius [положительное число] - флаг, принимающий радиус окружности\n");
    printf("-c --color [цвет] - флаг, принимающий компоненты цвета формате r.g.b\n");
    printf("-t --thickness [положительно число] - флаг, принимающий положительное число - толщину линии\n");
    printf("-l --fill - если есть, то окружность буде залита, требует флаг --fill_color\n");
    printf("-L --fill_color [цвет] - принимает цвет в формате r.g.b\n");
    puts("");
    printf("-m --mirror - флаг, для выполнения отражения заданной области, для работы требует флаги --left_up, --right_down и --axis\n");
    printf("-a --axis [ось] - флаг, принимающий название оси отражения, латинская буква x или y\n");
    printf("-u --left_up [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    printf("-d --right_down [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    puts("");
    printf("-O --copy - функция копирования области, требует для работы флаги --left_up, --right_down и --dest_left_up\n");
    printf("-D --dest_left_up [координаты точки]- принимает координаты в формате x.y\n");
}

void swapInt(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void fillCircle(Rgb ***pixPtr, int x0, int y0, int r, Rgb color, int h, int w)
{
    if (x0 + r < 0 || x0 - r > w || y0 + r < 0 || y0 - r > h)
        return;

    for (int x = -r; x <= r; x++)
    {
        for (int y = -r; y <= r; y++)
        {
            int x_n = x0 + x;
            int y_n = y0 - y;
            if (x * x + y * y <= r * r && x_n >= 0 && x_n < w && y_n >= 0 && y_n < h)
            {
                (*pixPtr)[y_n][x_n] = color;
            }
        }
    }
}

void line(Rgb ***pixPtr, int x0, int y0, int x1, int y1, int t, Rgb color, int h, int w)
{
    if (x0 == x1)
    {
        // проверяем, что линия находится в границах изображения
        if (x0 + t / 2 < 0 || x0 - t / 2 > w)
        {
            return;
        }
        if (y0 > y1)
            swapInt(&y0, &y1);
        for (int y = y0; y < y1; y++)
        {
            fillCircle(pixPtr, x0, y, t / 2, color, h, w);
        }
        return;
    }

    // Ax + By + C = 0
    const int delta_x = labs(x1 - x0);
    const int delta_y = labs(y1 - y0);
    const int sign_x = x0 < x1 ? 1 : -1;
    const int sign_y = y0 < y1 ? 1 : -1;

    int error = delta_x - delta_y;

    fillCircle(pixPtr, x1, y1, t / 2, color, h, w);
    while (x0 != x1 || y0 != y1 )
    {
        fillCircle(pixPtr, x0, y0, t / 2, color, h, w);
        const int error2 = error * 2;
        if (error2 > -delta_y)
        {
            error -= delta_y;
            x0 += sign_x;
        }
        if (error2 < delta_x)
        {
            error += delta_x;
            y0 += sign_y;
        }
    }
}

void draw8Pixels(Rgb ***pixPtr, int x0, int y0,
                  int x, int y, int t, Rgb color,
                  int h, int w)
{
    fillCircle(pixPtr, x + x0, y + y0, t, color, h, w);
    fillCircle(pixPtr, x + x0, -y + y0, t, color, h, w);
    fillCircle(pixPtr, -x + x0, -y + y0, t, color, h, w);
    fillCircle(pixPtr, -x + x0, y + y0, t, color, h, w);
    fillCircle(pixPtr, y + x0, x + y0, t, color, h, w);
    fillCircle(pixPtr, y + x0, -x + y0, t, color, h, w);
    fillCircle(pixPtr, -y + x0, -x + y0, t, color, h, w);
    fillCircle(pixPtr, -y + x0, x + y0, t, color, h, w);
}

void circle(Rgb ***pixPtr, int x0, int y0,
            int r, int t, Rgb color, int fill,
            Rgb fillColor, int h, int w)
{
    int dist;

    int x = 0;
    int y = r;

    if (fill) {
        fillCircle(pixPtr, x0, y0, r, fillColor, h, w);
    }

    dist = 3 - 2 * y;
    while (x <= y) {
        draw8Pixels(pixPtr, x0, y0, x, y, t / 2, color, h, w);
        if (dist < 0)
            dist = dist + 4 * x + 6;
        else {
            dist = dist + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void mirror(Rgb ***pixPtr, char *axis, int x0, int y0,
            int x1, int y1, int h, int w)
{
    Rgb **pix = *pixPtr;

    if (x0 < 0)
        x0 = 0;
    if (x0 > w)
        x0 = w - 1;
    if (x1 < 0)
        x1 = 0;
    if (x1 > w)
        x1 = w - 1;

    if (y0 < 0)
        y0 = 0;
    if (y0 > h)
        y0 = h - 1;
    if (y1 < 0)
        y1 = 0;
    if (y1 > h)
        y1 = h - 1;


    int areaH = labs(y1 - y0) + 1;
    int areaW = labs(x0 - x1) + 1;

    if (x0 > x1)
    {
        swapInt(&x0, &x1);
    }
    if (y0 > y1)
    {
        swapInt(&y0, &y1);
    }

    // выделение памяти
    Rgb **area = (Rgb**)malloc(areaH * sizeof(Rgb*));
    for (int i = 0; i < areaH; i++)
    {
        area[areaH - i - 1] = (Rgb*)malloc(areaW * sizeof(Rgb));
    }

    // заполнение массива
    for (int x = x0; x <= x1; x++)
    {
        for (int y = y0; y <= y1; y++)
        {
            if (y - y0 >= 0 && y - y0 < h &&
                x - x0 >= 0 && x - x0 < w &&
                y >= 0 && y < h &&
                x >= 0 && x < w)
            {
                area[y - y0][x - x0] = pix[y][x];
            }
        }
    }

    if (!strcmp("x", axis))
    {
        for (int x = x0; x <= x1; x++)
        {
            for (int y = y0; y <= y1; y++)
            {
                if (y >= 0 && y < h && x >= 0 && x < w && y - y0 >= 0 && y - y0 < h && areaW - (x - x0) - 1 >= 0 && areaW - (x - x0) - 1 < w)
                {
                    pix[y][x] = area[y - y0][areaW - (x - x0) - 1];
                }
            }
        }
    }


    if (!strcmp("y", axis))
    {
        for (int x = x0; x <= x1; x++)
        {
            for (int y = y0; y <= y1; y++)
            {
                if (y >= 0 && y < h && x >= 0 && x < w && x - x0 >= 0 && x - x0 < w && areaH - (y - y0) - 1 >= 0 && areaH - (y - y0) - 1 < h)
                {
                    pix[y][x] = area[areaH - (y - y0) - 1][x - x0];
                }
            }
        }
    }

    // очищаем память из под area
    for (int y = 0; y < areaH; y++)
        free(area[y]);
    free(area);
}

void copy(Rgb ***pixPtr,
          int x0, int y0,
          int x1, int y1,
          int xD, int yD,
          int h, int w)
{
    // если координаты точки вышли за изображение - корректируем их
    if (x0 < 0)
        x0 = 0;
    if (x0 >= w)
        x0 = w - 1;
    if (y0 < 0)
        y0 = 0;
    if (y0 >= h)
        y0 = h - 1;

    if (x1 < 0)
        x1 = 0;
    if (x1 >= w)
        x1 = w - 1;
    if (y1 < 0)
        y1 = 0;
    if (y1 >= h)
        y1 = h - 1;

    Rgb **area = copyArea(pixPtr, x0, y0, x1, y1, h, w);

    int areaH = abs(y0 - y1) + 1;
    int areaW = abs(x0 - x1) + 1;
    replaceToArea(pixPtr, &area, xD, yD, areaH, areaW, h, w);

    // очищаем память из под area
    for (int y = 0; y < areaH; y++)
        free(area[y]);
    free(area);
}

Rgb** copyArea(Rgb ***pixPtr,
               int x0, int y0,
               int x1, int y1,
               int h, int w)
{
    if (x0 > x1)
        swapInt(&x0, &x1);
    if (y0 > y1)
        swapInt(&y0, &y1);

    int areaH = abs(y0 - y1) + 1;
    int areaW = abs(x1 - x0) + 1;

    Rgb **area = (Rgb**)malloc(areaH * sizeof(Rgb*));
    for (int i = 0; i < areaH; i++) {
        area[areaH - i - 1] = (Rgb*)malloc(areaW * sizeof(Rgb));
    }

    // fill area array
    for (int y = y0; y < y0 + areaH; y++) {
        for (int x = x0; x < x0 + areaW; x++) {
            // x and y coords in area array
            int areaY = y - y0;
            int areaX = x - x0;
            if (areaX >= 0 && areaX < w &&
                areaY >= 0 && areaY < h &&
                x >= 0 && x < w &&
                y >= 0 && y < h)
                area[areaY][areaX] = (*pixPtr)[y][x];
        }
    }

    return area;
}

void replaceToArea(Rgb ***pixPtr, Rgb ***area,
                   int xD, int yD, int areaH, int areaW,
                   int h, int w)
{
    // replace dest pixels
    for (int y = yD; y < yD + areaH; y++) {
        for (int x = xD; x < xD + areaW; x++) {
            // x and y coords in area array
            int areaY = y - yD;
            int areaX = x - xD;
            if (areaX >= 0 && areaX < w &&
                areaY >= 0 && areaY < h &&
                x >= 0 && x < w &&
                y >= 0 && y < h)
                (*pixPtr)[y][x] = (*area)[areaY][areaX];
        }
    }
}
