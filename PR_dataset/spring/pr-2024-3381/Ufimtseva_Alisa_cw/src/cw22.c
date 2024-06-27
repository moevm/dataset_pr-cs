#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Png
{
    int width, height;  //высота, ширина
    png_byte colorType; //тип цвета
    png_byte bitDepth;  //глубина цвета
    png_structp pngPtr;
    png_infop infoPtr;
    int numberOfPasses; //количество проходов для полной обработки
    png_bytep *rowPointers;
};

void printInfo(struct Png *image)
{
    printf("Ширина изображения: %d\n", image->width);
    printf("Высота изображения: %d\n", image->height);
    printf("Тип цвета: %u\n", image->colorType);
    printf("Глубина цвета: %u\n", image->bitDepth);
}

void printHelp()
{
    printf("Course work for option 5.12, created by Alisa Ufimtseva.\n\n");
    printf("[имя файла] --info/-i - получить информацию об изображении\n");
    printf("[имя файла] --help/-h - вызвать справку\n\n");

    printf("Это программа с CLI для редактирования png-изображений! \n"
           "Поддерживаются файлы с глубиной цвета 8 бит, RGB\n");
    printf("Формат ввода: [./pngedit] [command] [in.png] -[o]/--[option] "
           "[argument] [out.png]\n\n");
    printf("Доступные команды:\n\n");

    printf("[имя файла] --square/-q - нарисовать квадрат\n");
    printf("--left_up/-s [x-координата].[y-координата] - левый верхний угол\n");
    printf("--side_size/-l [число] - длина стороны\n");
    printf("--thickness/-t [число] - толщина линий (в пикселях)\n");
    printf("--color/-c [R].[G].[B] - числа от 0 до 255, цвет линий\n");
    printf("--fill/-f [число] - опция заливки, по умолчанию без неё (1 - "
           "заливка, 0 - нет)\n");
    printf("--fill_color/-b [R].[G].[B] - числа от 0 до 255, цвет заливки\n\n");

    printf("[имя файла] --exchange/-d - поменять местами 4 куска области\n");
    printf(
        "--left_up/-s [x1-координата].[y1-координата] - левый верхний угол\n");
    printf("--right_down/-e [x2-координата].[y2-координата] - правый нижний "
           "угол\n");
    printf("--exchange_type/-p [clockwise / counterclockwise / diagonals] - "
           "способ (по часовой стрелке / против часовой стрелки / по "
           "диагонали)\n\n");

    printf("[имя файла] --freq_color/-m - заменить самый часто встречающийся "
           "цвет на новый\n");
    printf("--color/-c [R].[G].[B] - числа от 0 до 255, новый цвет (RGB)\n\n");

    printf(
        "[имя файла] --inverse/-n - инвертировать цвет в заданной области\n");
    printf(
        "--left_up/-s [x1-координата].[y1-координата] - левый верхний угол\n");
    printf("--right_down/-e [x2-координата].[y2-координата] - правый нижний "
           "угол\n\n");

    printf("--input/-v [имя файла] - имя входного файла\n");
    printf("--output/-o [имя файла] - имя выходного файла\n\n");
}

void readPngFile(char *fileName, struct Png *image)
{
    int y;
    char header[8]; //длина заголовка 8

    /* Открыть и проверить, что файл png */
    FILE *fp = fopen(fileName, "rb");
    if (!fp)
    {
        printf("Error: Невозможно прочитать файл: %s :с\n", fileName);
        exit(40);
    }

    /*Проверить по возможной сигнатуре, является ли это изображение PNG*/
    fread(header, 1, 8, fp);
    if (png_sig_cmp((const unsigned char *)header, 0, 8))
    {
        printf("Error: %s не является PNG файлом :c\n", fileName);
        exit(41);
    }

    /* Инициализация структуры PNG */
    image->pngPtr =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->pngPtr)
    {
        // Блок исполнится при ошибке в структуре PNG
        printf("Error: проблема в структуре PNG :c\n");
        exit(42);
    }

    /*создается базовая структура info_ptr, которая содержит информацию об
     * изображении*/
    image->infoPtr = png_create_info_struct(image->pngPtr);
    if (!image->infoPtr)
    {
        printf("Error: проблема в информационной структуре PNG :c\n");
        exit(42);
    }

    if (setjmp(png_jmpbuf(image->pngPtr)))
    {
        printf("Error: Ошибка записи данных исходного файла :c\n");
        exit(43);
    }

    /*Заполение структуры PNG*/
    png_init_io(image->pngPtr, fp);
    png_set_sig_bytes(image->pngPtr, 8);
    png_read_info(image->pngPtr, image->infoPtr);

    image->width = png_get_image_width(image->pngPtr, image->infoPtr);
    image->height = png_get_image_height(image->pngPtr, image->infoPtr);
    image->colorType = png_get_color_type(image->pngPtr, image->infoPtr);
    image->bitDepth = png_get_bit_depth(image->pngPtr, image->infoPtr);
    image->numberOfPasses = png_set_interlace_handling(image->pngPtr);

    png_read_update_info(image->pngPtr, image->infoPtr);

    if (image->bitDepth != 8)
    {
        printf("Error: поддерживается только 8-битная глубина цвета :c\n");
        exit(42);
    }

    /* чтение файла */
    image->rowPointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
    {
        image->rowPointers[y] =
            (png_byte *)malloc(png_get_rowbytes(image->pngPtr, image->infoPtr));
    }

    png_read_image(image->pngPtr, image->rowPointers);
    fclose(fp);
}

void processFile(struct Png *image)
{
    int x, y;
    if (png_get_color_type(image->pngPtr, image->infoPtr) != PNG_COLOR_TYPE_RGB)
    {
        printf("Error: Поддерживается только тип цвета RGB :с.\n");
        exit(42);
    }

    for (y = 0; y < image->height; y++)
    {
        png_byte *row = image->rowPointers[y];
        for (x = 0; x < image->width; x++)
        {
            png_byte *ptr = &(row[x * 3]);
            printf("Пиксель на позиции [ %d - %d ] имеет RGB значения: %d - %d "
                   "- %d\n",
                   x, y, ptr[0], ptr[1], ptr[2]);
        }
    }
}

void writePngFile(char *fileName, struct Png *image)
{
    int y;
    /* создание файла */
    FILE *fp = fopen(fileName, "wb");
    if (!fp)
    {
        // Если не открылся файл
        printf("Error: Не удалось создать файл итогового изображения :с\n");
        exit(45);
    }

    /* Инициализация структуры */
    image->pngPtr =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->pngPtr)
    {
        // Если не удалось создать структуру
        printf(
            "Error: Не удалось создать структуру итогового изображения :с\n");
        exit(42);
    }

    image->infoPtr = png_create_info_struct(image->pngPtr);

    if (!image->infoPtr)
    {
        printf("Error: Не удалось создать информационную структуру об итоговом "
               "изображении :с\n");
        exit(42);
    }

    if (setjmp(png_jmpbuf(image->pngPtr)))
    {
        printf("Error: Ошибка записи данных итогового файла :c\n");
        exit(43);
    }

    png_init_io(image->pngPtr, fp);

    /* запись заголовка */
    if (setjmp(png_jmpbuf(image->pngPtr)))
    {
        // Ошибка в записи заголовка
        printf(" Error: Ошибка записи заголовка итогового файла :c\n");
        exit(41);
    }

    png_set_IHDR(image->pngPtr, image->infoPtr, image->width, image->height,
                 image->bitDepth, image->colorType, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->pngPtr, image->infoPtr);

    if (setjmp(png_jmpbuf(image->pngPtr)))
    {
        printf("Error: Ошибка записи данных итогового файла :c\n");
        exit(44);
    }

    png_write_image(image->pngPtr, image->rowPointers);

    /* Конец записи */
    if (setjmp(png_jmpbuf(image->pngPtr)))
    {
        printf("Error: Ошибка при окончании записи итогового файла :c\n");
        exit(44);
    }

    png_write_end(image->pngPtr, NULL);

    /* Очистка памяти */
    for (y = 0; y < image->height; y++)
    {
        free(image->rowPointers[y]);
    }
    free(image->rowPointers);
    fclose(fp);
}

void drawSquare(struct Png *image, int x, int y, int l, int t, int *color,
                int fill, int *colorF)
{
    if (l < 0 || t < 0)
    {
        printf("Error: Длина стороны и толщина линии не могут быть "
               "отрицательными\n");
        exit(42);
    }
    int thickout = t / 2 + 1;
    int thickin = t - thickout;
    int x1 = x;
    int y1 = y;
    int x2 = x + l - 1;
    int y2 = y + l - 1;

    //заливка
    if (fill)
    {
        for (int i = y1; i <= y2; i++)
        {
            if (i >= 0 && i < image->height)
            {
                png_byte *row = image->rowPointers[i];

                for (int j = x1; j <= x2; j++)
                {
                    if (j >= 0 && j < image->width)
                    {
                        png_byte *ptr = &(row[j * 3]);
                        ptr[0] = colorF[0];
                        // printf("%d",colorF[0]);
                        ptr[1] = colorF[1];
                        ptr[2] = colorF[2];
                    }
                }
            }
        }
    }
    //границы без уголков
    for (int i = y1 - thickout; i <= y1 + thickin; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x1; j <= x2; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    ptr[0] = color[0];
                    ptr[1] = color[1];
                    ptr[2] = color[2];
                }
            }
        }
    }
    for (int i = y2 - thickin - 1; i <= y2 + thickout - 1; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x1; j <= x2; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    ptr[0] = color[0];
                    ptr[1] = color[1];
                    ptr[2] = color[2];
                }
            }
        }
    }
    for (int i = y1; i <= y2; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x1 - thickout; j <= x1 + thickin; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    ptr[0] = color[0];
                    ptr[1] = color[1];
                    ptr[2] = color[2];
                }
            }
        }
    }
    for (int i = y1; i <= y2; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];
            for (int j = x2 - thickin - 1; j <= x2 + thickout - 1; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    ptr[0] = color[0];
                    ptr[1] = color[1];
                    ptr[2] = color[2];
                }
            }
        }
    }

    //уголки
    for (int i = y1 - thickout; i <= y1; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x1 - thickout; j <= x1; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    if ((x1 - j) * (x1 - j) + (y1 - i) * (y1 - i) <=
                        thickout * thickout)
                    {
                        ptr[0] = color[0];
                        ptr[1] = color[1];
                        ptr[2] = color[2];
                    }
                }
            }
        }
    }
    for (int i = y1 - thickout; i <= y1; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x2; j <= x2 + thickout; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    if ((x2 - j) * (x2 - j) + (y1 - i) * (y1 - i) <=
                        thickout * thickout)
                    {
                        ptr[0] = color[0];
                        ptr[1] = color[1];
                        ptr[2] = color[2];
                    }
                }
            }
        }
    }
    for (int i = y2; i <= y2 + thickout - 1; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x2; j <= x2 + thickout; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    if ((x2 - j) * (x2 - j) + (y2 - i) * (y2 - i) <=
                        thickout * thickout)
                    {
                        ptr[0] = color[0];
                        ptr[1] = color[1];
                        ptr[2] = color[2];
                    }
                }
            }
        }
    }
    for (int i = y2; i <= y2 + thickout - 1; i++)
    {
        if (i >= 0 && i < image->height)
        {
            png_byte *row = image->rowPointers[i];

            for (int j = x1 - thickout; j <= x1; j++)
            {
                if (j >= 0 && j < image->width)
                {
                    png_byte *ptr = &(row[j * 3]);
                    if ((x1 - j) * (x1 - j) + (y2 - i) * (y2 - i) <=
                        thickout * thickout)
                    {
                        ptr[0] = color[0];
                        ptr[1] = color[1];
                        ptr[2] = color[2];
                    }
                }
            }
        }
    }
}

void swapFrags(struct Png *image, int x1, int y1, int x2, int y2, int w, int h)
{
    png_bytep **tmpPix = calloc(h, sizeof(png_bytep *));
    for (int i = 0; i < h; i++)
    {
        tmpPix[i] = (png_bytep *)calloc(w, sizeof(png_bytep));
        for (int j = 0; j < w; j++)
        {
            tmpPix[i][j] = (png_bytep)calloc(3, sizeof(png_byte));
        }
    }
    for (int i = 0; i < h; i++)
    {
        png_byte *row1 = image->rowPointers[i + y1];
        png_byte *row2 = image->rowPointers[i + y2];
        for (int j = 0; j < w; j++)
        {
            png_byte *ptr1 = &(row1[(j + x1) * 3]);
            png_byte *ptr2 = &(row2[(j + x2) * 3]);
            tmpPix[i][j][0] = ptr1[0];
            tmpPix[i][j][1] = ptr1[1];
            tmpPix[i][j][2] = ptr1[2];

            ptr1[0] = ptr2[0];
            ptr1[1] = ptr2[1];
            ptr1[2] = ptr2[2];

            ptr2[0] = tmpPix[i][j][0];
            ptr2[1] = tmpPix[i][j][1];
            ptr2[2] = tmpPix[i][j][2];
        }
    }
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            free(tmpPix[y][x]);
        }
        free(tmpPix[y]);
    }
    free(tmpPix);
}

void swapAreas(struct Png *image, int x1, int y1, int x2, int y2,
               char *exchangeType)
{
    if (x1 < 0 || y1 < 0 || x1 >= image->width || y1 >= image->height ||
        x2 < 0 || x2 >= image->width || y2 < 0 || y2 >= image->height)
    {
        printf("Error: Неверно введены координаты углов :c\n");
        exit(42);
    }
    int w = (x2 - x1) / 2;
    int h = (y2 - y1) / 2;
    if (!strcmp(exchangeType, "diagonals"))
    {
        swapFrags(image, x1, y1, x1 + w, y1 + h, w, h);
        swapFrags(image, x1, y1 + h, x1 + w, y1, w, h);
    }
    else if (!strcmp(exchangeType, "counterclockwise"))
    {
        swapFrags(image, x1, y1, x1 + w, y1, w, h);
        swapFrags(image, x1 + w, y1, x1 + w, y1 + h, w, h);
        swapFrags(image, x1 + w, y1 + h, x1, y1 + h, w, h);
    }
    else if (!strcmp(exchangeType, "clockwise"))
    {
        swapFrags(image, x1, y1, x1, y1 + h, w, h);
        swapFrags(image, x1, y1 + h, x1 + w, y1 + h, w, h);
        swapFrags(image, x1 + w, y1 + h, x1 + w, y1, w, h);
    }
    else
    {
        printf("Error: Неверно введен способ обмена частей :c\n");
        exit(42);
    }
}

void changeColor(struct Png *image, int *newColor)
{
    if (newColor[0] > 255 || newColor[0] < 0 || newColor[1] > 255 ||
        newColor[1] < 0 || newColor[2] > 255 || newColor[2] < 0)
    {
        printf(
            "Error: Цветовая компонента должа иметь значение от 0 до 255 :c\n");
        exit(42);
    }

    int ***colors = calloc(256, sizeof(int **));
    for (int i = 0; i < 256; i++)
    {
        colors[i] = calloc(256, sizeof(int *));
        for (int j = 0; j < 256; j++)
        {
            colors[i][j] = calloc(256, sizeof(int));
        }
    }
    for (int y = 0; y < image->height; y++)
    {
        png_bytep row = image->rowPointers[y];
        for (int x = 0; x < image->width; x++)
        {
            png_bytep ptr = &(row[x * 3]);
            colors[ptr[0]][ptr[1]][ptr[2]]++;
        }
    }
    int maxValue = colors[0][0][0];
    int maxColors[] = {0, 0, 0};
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            for (int k = 0; k < 256; k++)
            {
                if (colors[i][j][k] > maxValue)
                {
                    maxColors[0] = i;
                    maxColors[1] = j;
                    maxColors[2] = k;
                    maxValue = colors[i][j][k];
                }
            }
        }
    }
    for (int j = 0; j < image->height; j++)
    {
        png_bytep row = image->rowPointers[j];
        for (int i = 0; i < image->width; i++)
        {
            png_bytep ptr = &(row[i * 3]);
            if (ptr[0] == maxColors[0] && ptr[1] == maxColors[1] &&
                ptr[2] == maxColors[2])
            {
                ptr[0] = newColor[0];
                ptr[1] = newColor[1];
                ptr[2] = newColor[2];
            }
        }
    }
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            free(colors[i][j]);
        }
        free(colors[i]);
    }
    free(colors);
}

void invertColors(struct Png *image, int x1, int y1, int x2, int y2)
{
    if (x1 < 0)
    {
        x1 = 0;
    }
    if (y1 < 0)
    {
        y1 = 0;
    }
    if (x2 > image->width - 1)
    {
        x2 = image->width - 1;
    }
    if (y2 > image->height - 1)
    {
        y2 = image->height - 1;
    }
    for (int i = y1; i <= y2; i++)
    {
        png_byte *row = image->rowPointers[i];
        for (int j = x1; j <= x2; j++)
        {
            png_byte *ptr = &(row[j * 3]);
            ptr[0] = 255 - ptr[0];
            ptr[1] = 255 - ptr[1];
            ptr[2] = 255 - ptr[2];
        }
    }
}

void compressFunc(struct Png *image, int numb){
    
    for (int i = 0; i < image->height/numb; i++)
    {
        png_byte *row = image->rowPointers[i];
        for (int j = 0; j <= image->width/numb; j++)
        {
            png_byte *ptr = &(row[j * 3]);
            int newRed=0;
            int newGreen=0;
            int newBlue=0;

            for (int i1 = i*numb; i1 < i*numb+numb; i1++)
            {
                png_byte *row1 = image->rowPointers[i1];
                for (int j1 = j*numb; j1 < j*numb+numb; j1++)
                {
                    png_byte *ptr1 = &(row1[j1 * 3]);
                    newRed+=ptr1[0];
                    newGreen+=ptr1[1];
                    newBlue+=ptr1[2];
                }
            }
            ptr[0]=newRed/(numb*numb);
            ptr[1]=newGreen/(numb*numb);
            ptr[2]=newBlue/(numb*numb);

            
        }
    }
    image->height/=numb;
    image->width/=numb;
    //return newImage;
}

int isNumber(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printHelp();
        return 0;
    }

    struct Png image;

    char *oldFileName = malloc(1024 * sizeof(char));
    oldFileName[0] = '\0';

    char *newFileName = malloc(1024 * sizeof(char));
    newFileName[0] = '\0';
    
    int numb=-1;
    int length = -1;
    int thickness = -1;
    int fill = 0;
    int x1 = -1;
    int y1 = -1;
    int x2 = -1;
    int y2 = -1;
    int *color = calloc(3, sizeof(int));
    color[0] = -1;
    color[1] = -1;
    color[2] = -1;
    int *colorFill = calloc(3, sizeof(int));
    colorFill[0] = -1;
    colorFill[1] = -1;
    colorFill[2] = -1;
    char *exchangeType = malloc(10 * sizeof(char));
    int changeOutput = 0;
    int changeInput = 0;

    struct option long_opts[] = {
        {"info", no_argument, NULL, 'i'},
        {"help", no_argument, NULL, 'h'},
        {"square", no_argument, NULL, 'q'},
        {"side_size", required_argument, NULL, 'l'},
        {"thickness", required_argument, NULL, 't'},
        {"fill", no_argument, NULL, 'f'},
        {"fill_color", required_argument, NULL, 'b'},

        {"exchange", no_argument, NULL, 'd'},
        {"exchange_type", required_argument, NULL, 'p'},

        {"freq_color", no_argument, NULL, 'm'},
        {"color", required_argument, NULL, 'c'},

        {"inverse", no_argument, NULL, 'n'},
        {"left_up", required_argument, NULL, 's'},
        {"right_down", required_argument, NULL, 'e'},
        {"output", required_argument, NULL, 'o'},
        {"input", required_argument, NULL, 'v'},

        {"compress", no_argument, NULL, 'u'},
        {"num", required_argument, NULL, 'w'},
    };
    char *short_opts = "ihqdmnul:t:fb:p:c:s:e:o:v:w:";
    int opt;
    int numberOfFunc = 0;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1)
    {
        switch (opt)
        {
            case 'i':
                printInfo(&image);
                break;
            case 'h':
                printHelp();
                break;
            case 's':
            {
                int argLen = strlen(optarg);
                if (!isdigit(optarg[0]) && optarg[0] != '-')
                {
                    printf("Error: Неверно введены координаты левого верхнего "
                           "угла :с\n");
                    exit(42);
                }
                x1 = atoi(optarg);
                int i = 0;
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                if (!isdigit(optarg[i + 1]) && optarg[i + 1] != '-')
                {
                    printf("Error: Неверно введены координаты правого нижнего "
                           "угла :с\n");
                    exit(42);
                }
                y1 = atoi(&optarg[i + 1]);
                break;
            }
            case 'e':
            {
                int argLen = strlen(optarg);
                if (!isdigit(optarg[0]) && optarg[0] != '-')
                {
                    printf("Error: Неверно введены координаты левого верхнего "
                           "угла :с\n");
                    exit(42);
                }
                x2 = atoi(optarg);
                int i = 0;
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                if (!isdigit(optarg[i + 1]) && optarg[i + 1] != '-')
                {
                    printf("Error: Неверно введены координаты правого нижнего "
                           "угла :с\n");
                    exit(42);
                }
                y2 = atoi(&optarg[i + 1]);
                break;
            }
            case 'l':
            {
                if (!isNumber(optarg))
                {
                    printf("Error: не введен параметр :c\n");
                    exit(42);
                }
                length = atoi(optarg);
                if (length < 0)
                {
                    printf("Error: Длина стороны не может быть отрицательной "
                           ":с\n");
                    exit(42);
                }
                break;
            }
            case 't':
            {
                if (!isNumber(optarg))
                {
                    printf("Error: не введен параметр :c\n");
                    exit(42);
                }
                thickness = atoi(optarg);
                if (thickness < 0)
                {
                    printf("Error: Длина толщина линии не может быть "
                           "отрицательной :с\n");
                    exit(42);
                }
                break;
            }
            case 'w':
            {
                if (!isNumber(optarg))
                {
                    printf("Error: не введен параметр :c\n");
                    exit(42);
                }
                numb = atoi(optarg);
                if (numb < 0)
                {
                    printf("Error: Данный параметр не может быть отрицательным :с\n");
                    exit(42);
                }
                break;
            }
            case 'c':
            {
                int argLen = strlen(optarg);
                if (!isdigit(optarg[0])) break;
                color[0] = atoi(optarg);
                int i = 0;
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                i++;
                if (!isdigit(optarg[i])) break;
                color[1] = atoi(&optarg[i]);
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                i++;
                if (!isdigit(optarg[i])) break;
                color[2] = atoi(&optarg[i]);
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (color[0] > 255 || color[0] < 0 || color[1] > 255 ||
                    color[1] < 0 || color[2] > 255 || color[2] < 0)
                {
                    printf("Error: Цветовая компонента должа иметь значение от "
                           "0 до 255 :c\n");
                    exit(42);
                }
                break;
            }
            case 'f':
                fill = 1;
                break;
            case 'b':
            {
                int argLen = strlen(optarg);
                if (!isdigit(optarg[0])) break;
                colorFill[0] = atoi(optarg);
                int i = 0;
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                i++;
                if (!isdigit(optarg[i])) break;
                colorFill[1] = atoi(&optarg[i]);
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (i == argLen) break;
                i++;
                if (!isdigit(optarg[i])) break;
                colorFill[2] = atoi(&optarg[i]);
                while (optarg[i] != '.')
                {
                    if (i >= argLen) break;
                    i++;
                }
                if (colorFill[0] > 255 || colorFill[0] < 0 ||
                    colorFill[1] > 255 || colorFill[1] < 0 ||
                    colorFill[2] > 255 || colorFill[2] < 0)
                {
                    printf("Error: Цветовая компонента должа иметь значение от "
                           "0 до 255 :c\n");
                    exit(42);
                }
                break;
            }
            case 'p':
                strcpy(exchangeType, optarg);
                if (strcmp(exchangeType, "counterclockwise") != 0 &&
                    strcmp(exchangeType, "clockwise") != 0 &&
                    strcmp(exchangeType, "diagonals") != 0)
                {
                    printf("Error: неправильно введен exchangeType :c");
                    exit(42);
                }
                break;
            case 'o':
                changeOutput = 1;
                if (optarg[0] == '.' && optarg[1] == '/')
                {
                    for (int i = 2; i < strlen(optarg); i++)
                    {
                        newFileName[i - 2] = optarg[i];
                    }
                }
                else
                {
                    strcat(newFileName, optarg);
                }
                break;
            case 'v':
                changeInput = 1;
                if (optarg[0] == '.' && optarg[1] == '/')
                {
                    for (int i = 2; i < strlen(optarg); i++)
                    {
                        oldFileName[i - 2] = optarg[i];
                    }
                }
                else
                {
                    strcat(oldFileName, optarg);
                }
                break;

            case 'q':
                numberOfFunc = 1;
                break;
            case 'd':
                numberOfFunc = 2;
                break;
            case 'm':
                numberOfFunc = 3;
                break;
            case 'n':
                numberOfFunc = 4;
                break;
            case 'u':
                numberOfFunc = 5;
                break;
            default:
                printf("Error: введен несуществующий флаг :c\n");
                exit(43);
                break;
        }
    }

    if (changeInput == 0)
    {
        strcat(oldFileName, "in.png");
    }
    if (changeOutput == 0)
    {
        strcat(newFileName, "out.png");
    }

    readPngFile(oldFileName, &image);

    switch (numberOfFunc)
    {
        case 1:
            if (fill)
                drawSquare(&image, x1, y1, length, thickness, color, fill,
                           colorFill);
            else
                drawSquare(&image, x1, y1, length, thickness, color, fill,
                           NULL);
            writePngFile(newFileName, &image);
            break;
        case 2:
            // printf("%d %d %d %d %s", x1,y1,x2,y2,exchangeType);
            swapAreas(&image, x1, y1, x2, y2, exchangeType);
            writePngFile(newFileName, &image);
            break;
        case 3:
            changeColor(&image, color);
            writePngFile(newFileName, &image);
            break;
        case 4:
            invertColors(&image, x1, y1, x2, y2);
            writePngFile(newFileName, &image);
            break;
        case 5:
            compressFunc(&image, numb);
            writePngFile(newFileName, &image);
            break;
    }
    free(exchangeType);
    free(color);
    free(colorFill);
    free(newFileName);
    return 0;
}
