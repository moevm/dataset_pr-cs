#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

#define PI 3.14
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
    unsigned int headerSize;      // размер заголовка
    unsigned int width;           // ширина изображения
    unsigned int height;          // высота изображения
    unsigned short planes;        // количество цветовых плоскостей
    unsigned short bitsPerPixel;  // количество битов на цвет, по условию курсовой: 24 бита
    unsigned int compression;     // наличие сжатия, по условию курсовой: 0
    unsigned int imageSize;       // размер массива пикселей в байтах
    unsigned int xPixelsPerMeter; // плотность пикселей
    unsigned int yPixelsPerMeter; // плотность пикселей
    unsigned int colorsInColorTable; // цветов в таблице цветов
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

// функции чтения BMP файла
void bmpRead(Rgb ***pixPtr, const char *fileName, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih);
void bmpWrite(Rgb ***pixPtr, const char *fileName, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih);

// функции вывода информации о BMP файле и вывода помощи
void printFileHeader(BitmapFileHeader bmfh);
void printInfoHeader(BitmapInfoHeader bmih);
void printHelp();

// функции-подзадачи
void fillCircle(Rgb ***pixPtr, int x0, int y0, int r, Rgb color, int h, int w);
void line(Rgb ***pixPtr, int x0, int y0, int x1, int y1, int t, Rgb color, int h, int w);
void mirror(Rgb ***pixPtr, char *axis, int x0, int y0, int x1, int y1, int h, int w);
void draw8Pixels(Rgb ***pixPtr, int x0, int y0, int x, int y, int t, Rgb color, int h, int w);
void circle(Rgb ***pixPtr, int x0, int y0, int r, int t, Rgb color, int fill, Rgb fillColor, int h, int w);
void pentagram(Rgb ***pixPtr, int x0, int y0, int r, int t, Rgb color, int h, int w);
void contrast(Rgb ***pixPtr, double alpha, int beta, int h, int w);

void swapInt(int *a, int *b);
void freePix(Rgb ***pixPtr, int h);

// структура наличия флагов
typedef struct
{
    int help;
    int info;
    int input;
    int output;
    int line;
    int start;
    int end;
    int color;
    int thickness;
    int mirror;
    int axis;
    int leftUp;
    int rightDown;
    int pentagram;
    int center;
    int radius;
    int contrast;
    int alpha;
    int beta;
} Flags;

// структура с аргументами флагов
typedef struct
{
    char *input;
    char *output;
    int start[2];
    int end[2];
    Rgb color;
    unsigned thickness;
    char *axis;
    int leftUp[2];
    int rightDown[2];
    int center[2];
    unsigned radius;
    double alpha;
    int beta;
} Args;

int main(int argc, char **argv)
{
    printf("Course work for option 4.8, created by Markov Mark\n");

    if (argc == 1)
    {
        printf("Программе не были переданы аргументы!\n");
        exit(ERROR);
    }

    Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Args args;

    // символ, представляющий возвращаемой значение getopt_long
    int optchar;

    // короткие и длинные опции
    char *opts = "hni:o:ls:e:c:t:ma:u:d:pC:r:SA:B:";
    struct option longOpts[] =
            {
                    {"help", no_argument, 0, 'h'},
                    {"info", no_argument, 0, 'n'},
                    {"input", required_argument, 0, 'i'},
                    {"output", required_argument, 0, 'o'},
                    {"line", no_argument, 0, 'l'},
                    {"start", required_argument, 0, 's'},
                    {"end", required_argument, 0, 'e'},
                    {"color", required_argument, 0, 'c'},
                    {"thickness", required_argument, 0, 't'},
                    {"mirror", no_argument, 0, 'm'},
                    {"axis", required_argument, 0, 'a'},
                    {"left_up", required_argument, 0, 'u'},
                    {"right_down", required_argument, 0, 'd'},
                    {"pentagram", no_argument, 0, 'p'},
                    {"center", required_argument, 0, 'C'},
                    {"radius", required_argument, 0, 'r'},
                    {"contrast", no_argument, 0, 'S'},
                    {"alpha", required_argument, 0, 'A'},
                    {"beta", required_argument, 0, 'B'},
                    {0, 0, 0, 0}
            };

    int ret;

    // временные переменные
    int r;
    int g;
    int b;
    int thickness;
    int radius;
    double alpha;
    int beta;

    // считываем флаги
    while ((optchar = getopt_long(argc, argv, opts, longOpts, &optind)) != -1)
    {
        switch (optchar)
        {
            case 'h':
                printHelp();
                return 0;
            case 'n':
                flags.info = 1;
                break;
            case 'i':
                flags.input = 1;
                args.input = optarg;
                break;
            case 'o':
                flags.output = 1;
                args.output = optarg;
                break;
            case 'l':
                flags.line = 1;
                break;
            case 's':
                flags.start = 1;
                ret = sscanf(optarg, "%d.%d", &args.start[0], &args.start[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Введите координаты числами в виде x.y!\n");
                    exit(ERROR);
                }
                break;
            case 'e':
                flags.end = 1;
                ret = sscanf(optarg, "%d.%d", &args.end[0], &args.end[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Введите координаты числами в виде x.y!\n");
                    exit(ERROR);
                }
                break;
            case 'c':
                flags.color = 1;
                ret = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (ret < 3)
                {
                    fprintf(stderr, "Нужно ввести целочисленные компоненты в виде r.g.b\n");
                    exit(ERROR);
                }
                else if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                {
                    fprintf(stderr, "Компоненты должны быть в диапазоне от 0 до 255 включительно\n");
                    exit(ERROR);
                }

                args.color.r = r;
                args.color.g = g;
                args.color.b = b;
                break;
            case 't':
                flags.thickness = 1;
                ret = sscanf(optarg, "%d", &thickness);
                if (ret < 1)
                {
                    fprintf(stderr, "Толщина должна быть числом\n");
                    exit(ERROR);
                }
                else if (thickness <= 0)
                {
                    fprintf(stderr, "Толщина должна быть положительным числом\n");
                    exit(ERROR);
                }

                args.thickness = thickness;
                break;
            case 'm':
                flags.mirror = 1;
                break;
            case 'a':
                flags.axis = 1;
                args.axis = optarg;
                if (strcmp("x", args.axis) && strcmp("y", args.axis)) {
                    fprintf(stderr, "--axis может принимать одно из значений  x или y\n");
                    exit(44);
                }
                break;
            case 'u':
                flags.leftUp = 1;
                ret = sscanf(optarg, "%d.%d", &args.leftUp[0], &args.leftUp[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    exit(44);
                }
                break;
            case 'd':
                flags.rightDown = 1;
                ret = sscanf(optarg, "%d.%d", &args.rightDown[0], &args.rightDown[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    exit(44);
                }
                break;
            case 'p':
                flags.pentagram = 1;
                break;
            case 'S':
                flags.contrast = 1;
                break;
            case 'A':
                flags.alpha = 1;
                ret = sscanf(optarg, "%lf", &alpha);
                if (ret < 1)
                {
                    fprintf(stderr, "Alpha должен быть числом\n");
                    exit(ERROR);
                }
                else if (alpha <= 0)
                {
                    fprintf(stderr, "Alpha должен быть положительным\n");
                    exit(ERROR);
                }
                args.alpha = alpha;
                break;
            case 'B':
                flags.beta = 1;
                ret = sscanf(optarg, "%d", &beta);
                if (ret < 1)
                {
                    fprintf(stderr, "Beta должен быть числом\n");
                    exit(ERROR);
                }
                args.beta = beta;
                break;
            case 'C':
                flags.center = 1;
                ret = sscanf(optarg, "%d.%d", &args.center[0], &args.center[1]);
                if (ret < 2)
                {
                    fprintf(stderr, "Нужно ввести координаты числами в формате x.y\n");
                    exit(44);
                }
                break;
            case 'r':
                flags.radius = 1;
                ret = sscanf(optarg, "%d", &radius);
                if (ret < 1)
                {
                    fprintf(stderr, "Радиус должен быть числом\n");
                    exit(ERROR);
                }
                else if (radius <= 0)
                {
                    fprintf(stderr, "Радиус должен быть положительным\n");
                    exit(ERROR);
                }

                args.radius = radius;
                break;
            case '?':
                fprintf(stderr, "Неизвестная опция!\n");
                exit(43);
        }
    }

    if (flags.input == 0)
    {
        flags.input = 1;
        args.input = strdup(argv[argc - 1]);
    }

    if (flags.output == 0)
    {
        flags.output = 1;
        args.output = strdup("out.bmp");
    }

    if (strcmp(args.input, args.output) == 0)
    {
        fprintf(stderr, "Имена входного и выходного изображения совпадают!\n");
    }

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb **pix;

    bmpRead(&pix, args.input, &bmfh, &bmih);

    int w = bmih.width;
    int h = bmih.height;

    if (flags.info == 1)
    {
        printf("Информация о заголовках:\n");
        printFileHeader(bmfh);
        printInfoHeader(bmih);
        return 0;
    }

    else if (flags.line)
    {
        if (flags.start == 0 || flags.end == 0 || flags.color == 0 || flags.thickness == 0)
        {
            fprintf(stderr, "Отсутствуют необходимые флаги!\n");
            exit(44);
        }
        line(&pix, args.start[0], args.start[1], args.end[0], args.end[1], args.thickness, args.color, bmih.height, bmih.width);
    }

    else if (flags.mirror)
    {
        if (flags.axis == 0 || flags.leftUp == 0 || flags.rightDown == 0)
        {
            fprintf(stderr, "Отсутствуют необходимые флаги!\n");
            exit(44);
        }
        mirror(&pix, args.axis, args.leftUp[0], args.leftUp[1], args.rightDown[0], args.rightDown[1], bmih.height, bmih.width);
    }

    else if (flags.pentagram)
    {
        if (flags.center == 0 || flags.radius == 0 || flags.thickness == 0 || flags.color == 0)
        {
            printf("Отсуствуют необходмые флаги\n");
            exit(44);
        }
        pentagram(&pix, args.center[0], args.center[1], args.radius, args.thickness, args.color, bmih.height, bmih.width);
    }

    else if (flags.contrast)
    {
        if (flags.alpha == 0 || flags.beta == 0)
        {
            printf("Отсуствуют необходмые флаги\n");
            exit(44);
        }
        contrast(&pix, args.alpha, args.beta, bmih.height, bmih.width);
    }

    bmpWrite(&pix, args.output, &bmfh, &bmih);

    freePix(&pix, bmih.height);

    return 0;
}

void bmpRead(Rgb ***pixPtr, const char *fileName, BitmapFileHeader *bmfh, BitmapInfoHeader *bmih)
{
    FILE *f = fopen(fileName, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Не удалость открыть BMP файл\n");
        exit(40);
    }

    // считываем заголовки
    fread(bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(bmih, sizeof(BitmapInfoHeader), 1, f);

    if (bmfh->signature != 0x4D42 || bmih->compression != 0 || bmih->bitsPerPixel != 24)
    {
        fprintf(stderr, "Либо это не BMP файл, либо такой BMP файл не поддерживается\n");
        exit(41);
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
        exit(40);
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
    printf("-l --line - рисование линии, требует для работы флаги --start, --end, --thickness и --color\n");
    printf("-s --start [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    printf("-e --end [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    printf("-c --color [цвет] - флаг, принимающий компоненты цвета формате r.g.b\n");
    printf("-t --thickness [положительно число] - флаг, принимающий положительное число - толщину линии\n");
    printf("-m --mirror - флаг, для выполнения отражения заданной области, для работы требует флаги --left_up, --right_down и --axis\n");
    printf("-a --axis [x|y] - флаг, принимающий название оси отражения, буква x или y\n");
    printf("-u --left_up [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    printf("-d --right_down [координаты точки] - флаг, принимающий координаты точки в формате x.y\n");
    printf("-p --pentagram - флаг для рисования пентаграммы, требует для работы флаги --center, --radius, --thickness и --color\n");
    printf("-C --center [координаты точки]- флаг, принимающий координаты точки в формате x.y\n");
    printf("-r --radius [положительное число] - флаг, принимающий радиус окружности\n");
}

void swapInt(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void freePix(Rgb ***pixPtr, int h)
{
    for (int y = 0; y < h; y++)
    {
        free((*pixPtr)[y]);
    }
    free(*pixPtr);
}

void contrast(Rgb ***pixPtr, double alpha, int beta, int h, int w)
{
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int newR = floor(alpha * (*pixPtr)[y][x].r + beta);
            int newG = floor(alpha * (*pixPtr)[y][x].g + beta);
            int newB = floor(alpha * (*pixPtr)[y][x].b + beta);

            if (newR > 255)
            {
                (*pixPtr)[y][x].r = 255;
            }
            else
            {
                (*pixPtr)[y][x].r = newR;
            }

            if (newG > 255)
            {
                (*pixPtr)[y][x].g = 255;
            }
            else
            {
                (*pixPtr)[y][x].g = newG;
            }
            if (newB > 255)
            {
                (*pixPtr)[y][x].b = 255;
            }
            else
            {
                (*pixPtr)[y][x].b = newB;
            }
        }
    }
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

    // проверяем, что линия находится в границах изображения

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

void mirror(Rgb ***pixPtr, char *axis, int x0, int y0, int x1, int y1, int h, int w)
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
            if (y - y0 >= 0 && y - y0 < h && x - x0 >= 0 && x - x0 < w && y >= 0 && y < h && x >= 0 && x < w)
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

    for (int i = 0; i < areaH; i++)
    {
        free(area[areaH - i - 1]);
    }

    free(area);
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

void circle(Rgb ***pixPtr, int x0, int y0, int r, int t, Rgb color, int fill, Rgb fillColor, int h, int w)
{
    int64_t horDist;
    int64_t diagDist;
    int64_t dist;

    int64_t x = 0;
    int64_t y = r;

    if (fill) {
        fillCircle(pixPtr, x0, y0, r, fillColor, h, w);
    }

    dist = 3 - 2 * y;
    while (x <= y) {
        draw8Pixels(pixPtr, x0, y0, x, y, t, color, h, w);
        if (dist < 0)
            dist = dist + 4 * x + 6;
        else {
            dist = dist + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void pentagram(Rgb ***pixPtr, int x0, int y0, int r, int t, Rgb color, int h, int w)
{
    int64_t x1 = x0 + r * cos(PI / 10);
    int64_t y1 = y0 - r * sin(PI / 10);

    int64_t x2 = x0 + r * cos(5 * PI / 10);
    int64_t y2 = y0 - r * sin(5 * PI / 10);

    int64_t x3 = x0 + r * cos(9 * PI / 10);
    int64_t y3 = y0 - r * sin(9 * PI / 10);

    int64_t x4 = x0 + r * cos(13 * PI / 10);
    int64_t y4 = y0 - r * sin(13 * PI / 10);

    int64_t x5 = x0 + r * cos(17 * PI / 10);
    int64_t y5 = y0 - r * sin(17 * PI / 10);

    if (y0 + r + t / 2 < 0 || y0 - r - t / 2 > h || x0 + r + t / 2 < 0 || x0 - r - t / 2 > w)
        return;

    circle(pixPtr, x0, y0, r, t / 2, color, 0, color, h, w);

    Rgb new_color = {21, 123, 90};

    line(pixPtr, x1, y1, x3, y3, t, color, h, w);
    line(pixPtr, x3, y3, x5, y5, t, color, h, w);
    line(pixPtr, x5, y5, x2, y2, t, color, h, w);
    line(pixPtr, x2, y2, x4, y4, t, color, h, w);
    line(pixPtr, x4, y4, x1, y1, t, color, h, w);
}