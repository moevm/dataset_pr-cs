#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME 256
#define PRINT_HELP 1000

#define SUCCESS 0
#define ERROR_OPEN_FILE 40
#define ERROR_NOT_BMP_FILE 41
#define ERROR_NOT_SUPPORTED_FILE 42
#define ERROR_INVALID_ARGUMENT 43
#define ERROR_MEMORY_ALLOCATION 44
#define ERROR_WRITE_FILE 45

#pragma pack(push, 1) // отключаем выравнивание

typedef struct
{
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
    uint32_t headerSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPixelsPerMeter;
    uint32_t yPixelsPerMeter;
    uint32_t colorsInColorTable;
    uint32_t importantColorCount;
} BitmapInfoHeader;

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Rgb;

#pragma pack(pop) // включаем выравнивание

struct option longOptions[] = {{"squared_lines", no_argument, 0, 'S'},
                               {"left_up", required_argument, 0, 'l'},
                               {"right_down", required_argument, 0, 'r'},
                               {"side_size", required_argument, 0, 's'},
                               {"thickness", required_argument, 0, 't'},
                               {"color", required_argument, 0, 'c'},
                               {"fill", no_argument, 0, 'f'},
                               {"fill_color", required_argument, 0, 'g'},
                               {"rgbfilter", no_argument, 0, 'F'},
                               {"component_name", required_argument, 0, 'n'},
                               {"component_value", required_argument, 0, 'v'},
                               {"rotate", no_argument, 0, 'R'},
                               {"angle", required_argument, 0, 'a'},
                               {"output", required_argument, 0, 'o'},
                               {"info", no_argument, 0, 'I'},
                               {"input", required_argument, 0, 'i'},
                               {"help", no_argument, 0, 'h'},
                               {"paving", no_argument, 0, 'p'},
                               {0, 0, 0, 0}};

typedef struct
{
    char fileName[MAX_FILE_NAME];       // input file
    char outputFileName[MAX_FILE_NAME]; // output file
    short squaredLines; // bool requires left_up side_size thickness color
    short fill;         // bool requires fill_color
    short rgbfilter;    // bool requires component_name component_value
    short rotate;       // bool requires left_up right_down angle
    short info;         // bool
    int leftUp[2];      // x, y
    int rightDown[2];   // x, y
    int sideSize;       // size
    int thickness;      // thickness
    int color[3];       // r, g, b
    int fillColor[3];   // r, g, b
    char componentName; // r/g/b
    int componentValue; // value
    int angle;          // angle
    short paving;       // bool
} Args;

void printHelp()
{
    puts("Usage: ./cw [OPTIONS] FILE");
    puts("Options:");
    puts("  -S  --squared_lines: Draw a square with diagonals.");
    puts("  -F  --rgbfilter: Apply an RGB filter to the entire image.");
    puts("  -R  --rotate: Rotate the image or part of it by 90, 180, or 270 "
         "degrees.");
    puts("  -l  --left_up x.y: Set the coordinates of the top left corner of "
         "the square or rotation area.");
    puts("  -s  --side_size SIZE: Set the side size of the square. Must be "
         "greater than 0.");
    puts("  -t  --thickness THICKNESS: Set the line thickness. Must be "
         "greater than 0.");
    puts("  -c  --color r.g.b: Set the line color in the format rrr.ggg.bbb.");
    puts("  -f  --fill: Fill the square. If this flag is present, the square "
         "is filled.");
    puts("  -g  --fill_color r.g.b: Set the fill color in the format "
         "rrr.ggg.bbb.");
    puts("  -n  --component_name red/green/blue: Choose the component to "
         "change with the RGB filter.");
    puts("  -v  --component_value VALUE: Set the value of the chosen "
         "component for the RGB filter. Must be between 0 and 255.");
    puts("  -r  --right_down x.y: Set the coordinates of the bottom right "
         "corner of the rotation area.");
    puts("  -a  --angle ANGLE: Set the rotation angle. Can be 90, 180, or "
         "270.");
    puts("  -o  --output FILE: Specify the output file.");
    puts("  -i  --input FILE: Explicitly specify the input file.");
    puts("  -I  --info: Display information about the image.");
    puts("  -h  --help: Display this help message.");
}

int parseArgs(Args *args, int argc, char *const argv[])
{
    typedef struct
    {
        short leftUp;
        short rightDown;
        short sideSize;
        short thickness;
        short color;
        short fillColor;
        short componentName;
        short componentValue;
        short angle;
    } PassedArgs;

    PassedArgs passedArgs = {0};
    strcpy(args->outputFileName, "out.bmp"); // default output file name
    int c;

    /* getopt_long stores the option index here. */
    int optionIndex = 0;
    while (1)
    {
        c = getopt_long(argc, argv, "SfFRIhl:r:s:t:c:g:n:v:a:o:i:", longOptions,
                        &optionIndex);

        /* Detect the end of the options. */
        if (c == -1) break;

        switch (c)
        {
            case 'l':
                if (sscanf(optarg, "%d.%d", args->leftUp, args->leftUp + 1) !=
                    2)
                {
                    fprintf(stderr, "Error: left_up format must be x.y\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.leftUp = 1;
                break;
            case 'r':
                if (sscanf(optarg, "%d.%d", args->rightDown,
                           args->rightDown + 1) != 2)
                {
                    fprintf(stderr, "Error: right_down format must be x.y\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.rightDown = 1;
                break;
            case 's':
                if (sscanf(optarg, "%d", &args->sideSize) != 1)
                {
                    fprintf(stderr, "Error: side_size must be an integer\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->sideSize <= 0)
                {
                    fprintf(stderr, "Error: side_size must be > 0\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.sideSize = 1;
                break;
            case 't':
                if (sscanf(optarg, "%d", &args->thickness) != 1)
                {
                    fprintf(stderr, "Error: thickness must be an integer\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->thickness <= 0)
                {
                    fprintf(stderr, "Error: thickness must be > 0\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.thickness = 1;
                break;
            case 'c':
                if (sscanf(optarg, "%d.%d.%d", args->color, args->color + 1,
                           args->color + 2) != 3)
                {
                    fprintf(stderr,
                            "Error: color format must be rrr.ggg.bbb\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->color[0] < 0 || args->color[1] < 0 ||
                    args->color[2] < 0 || args->color[0] > 255 ||
                    args->color[1] > 255 || args->color[2] > 255)
                {
                    fprintf(stderr,
                            "Error: color component must be >= 0 and <=255\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.color = 1;
                break;
            case 'g':
                if (sscanf(optarg, "%d.%d.%d", args->fillColor,
                           args->fillColor + 1, args->fillColor + 2) != 3)
                {
                    fprintf(stderr,
                            "Error: fill_color format must be rrr.ggg.bbb\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->fillColor[0] < 0 || args->fillColor[1] < 0 ||
                    args->fillColor[2] < 0 || args->fillColor[0] > 255 ||
                    args->fillColor[1] > 255 || args->fillColor[2] > 255)
                {
                    fprintf(
                        stderr,
                        "Error: fill_color component must be >= 0 and <=255\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.fillColor = 1;
                break;
            case 'n':
                if (strcmp(optarg, "red") == 0)
                {
                    args->componentName = 'r';
                }
                else if (strcmp(optarg, "green") == 0)
                {
                    args->componentName = 'g';
                }
                else if (strcmp(optarg, "blue") == 0)
                {
                    args->componentName = 'b';
                }
                else
                {
                    fprintf(
                        stderr,
                        "Error: component_name must be red, green or blue\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.componentName = 1;
                break;
            case 'v':
                if (sscanf(optarg, "%d", &args->componentValue) != 1)
                {
                    fprintf(stderr,
                            "Error: component_value must be an integer\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->componentValue < 0 || args->componentValue > 255)
                {
                    fprintf(stderr,
                            "Error: component_value must be >= 0 and <=255\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.componentValue = 1;
                break;
            case 'a':
                if (sscanf(optarg, "%d", &args->angle) != 1)
                {
                    fprintf(stderr, "Error: angle must be an integer\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                if (args->angle != 90 && args->angle != 180 &&
                    args->angle != 270)
                {
                    fprintf(stderr, "Error: angle must be 90, 180 or 270\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                passedArgs.angle = 1;
                break;
            case 'o':
                if (strlen(optarg) > MAX_FILE_NAME)
                {
                    fprintf(stderr, "Error: output file name is too long\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                strncpy(args->outputFileName, optarg, MAX_FILE_NAME);
                break;
            case 'i':
                if (strlen(optarg) > MAX_FILE_NAME)
                {
                    fprintf(stderr, "Error: input file name is too long\n");
                    return ERROR_INVALID_ARGUMENT;
                }
                strncpy(args->fileName, optarg, MAX_FILE_NAME);
                break;
            case 'S':
                args->squaredLines = 1;
                break;
            case 'f':
                args->fill = 1;
                break;
            case 'F':
                args->rgbfilter = 1;
                break;
            case 'R':
                args->rotate = 1;
                break;
            case 'I':
                args->info = 1;
                break;
            case 'p':
                args->paving = 1;
                break;
            case 'h':
                printHelp();
                return PRINT_HELP;
                break;
            case '?':
                fprintf(stderr, "Error: Error while parsing options\n");
                return ERROR_INVALID_ARGUMENT;
                break;
        }
    }
    if (argc == 1)
    {
        printHelp();
        return PRINT_HELP;
    }
    if (optind < argc && strlen(args->fileName) == 0)
    {
        strcpy(args->fileName, argv[optind]);
        optind += 1;
    }
    if (strlen(args->fileName) == 0)
    {
        fprintf(stderr, "Error: No input file\n");
        return ERROR_INVALID_ARGUMENT;
    }

    if (args->squaredLines + args->rgbfilter + args->rotate + args->paving > 1)
    {
        fprintf(stderr,
                "Error: Only one of squared_lines, rgbfilter, paving or "
                "rotate can be used\n");
        return ERROR_INVALID_ARGUMENT;
    }

    if (args->squaredLines && !(passedArgs.leftUp && passedArgs.sideSize &&
                                passedArgs.thickness && passedArgs.color))
    {
        fprintf(
            stderr,
            "Error: left_up, side_size, thickness and color are required for "
            "squared_lines\n");
        return ERROR_INVALID_ARGUMENT;
    }
    if (args->fill && !passedArgs.fillColor)
    {
        fprintf(stderr, "Error: fill_color is required for fill\n");
        return ERROR_INVALID_ARGUMENT;
    }
    if (args->rgbfilter &&
        !(passedArgs.componentName && passedArgs.componentValue))
    {
        fprintf(stderr,
                "Error: component_name and component_value are required for "
                "rgbfilter\n");
        return ERROR_INVALID_ARGUMENT;
    }
    if (args->rotate &&
        !(passedArgs.leftUp && passedArgs.rightDown && passedArgs.angle))
    {
        fprintf(
            stderr,
            "Error: left_up, right_down and angle are required for rotate\n");
        return ERROR_INVALID_ARGUMENT;
    }
    if (args->paving && !(passedArgs.leftUp && passedArgs.rightDown))
    {
        fprintf(stderr, "Error: left_up, right_down are required for paving\n");
        return ERROR_INVALID_ARGUMENT;
    }
    if (strcmp(args->fileName, args->outputFileName) == 0)
    {
        fprintf(stderr, "Error: Input and output files must be different\n");
        return ERROR_INVALID_ARGUMENT;
    }
    return SUCCESS;
}

void printFileHeader(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset,
           header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header)
{
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel,
           header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter,
           header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter,
           header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable,
           header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount,
           header.importantColorCount);
}

void swapInt(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void imageFree(Rgb **arr, int H)
{
    for (int i = 0; i < H; i++)
        free(arr[i]);
    free(arr);
}

void setPixel(Rgb **arr, int x, int y, int *color)
{
    arr[y][x].r = *(color);
    arr[y][x].g = *(color + 1);
    arr[y][x].b = *(color + 2);
}

int readBmp(Rgb ***arr, char *fileName, BitmapFileHeader *bmfh,
            BitmapInfoHeader *bmif)
{
    FILE *f = fopen(fileName, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Error: file %s not found\n", fileName);
        return ERROR_OPEN_FILE;
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    if (bmfh->signature != 0x4D42)
    {
        fprintf(stderr, "Error: file %s is not a BMP file\n", fileName);
        fclose(f);
        return ERROR_NOT_BMP_FILE;
    }
    if (bmif->bitsPerPixel != 24 || bmif->compression != 0)
    {
        fprintf(stderr, "Error: BMP file %s is not supported\n", fileName);
        fclose(f);
        return ERROR_NOT_SUPPORTED_FILE;
    }
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb **newArr = malloc(H * sizeof(Rgb *));
    if (newArr == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return ERROR_MEMORY_ALLOCATION;
    }
    fseek(f, bmfh->pixelArrOffset,
          SEEK_SET); // Move the file pointer to the pixel array offset
    for (int i = 0; i < H; i++)
    {
        // padding
        // https://stackoverflow.com/questions/61360044/reading-data-from-bmp-file-in-c
        newArr[i] = malloc(W * sizeof(Rgb) + (4 - ((3 * W) % 4)) % 4);
        if (newArr[i] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            imageFree(newArr, i);
            return ERROR_MEMORY_ALLOCATION;
        }
        fread(newArr[i], 1, W * sizeof(Rgb) + (4 - ((3 * W) % 4)) % 4, f);
    }
    fclose(f);
    *arr = newArr;
    return SUCCESS;
}

int writeBmp(char *fileName, Rgb **arr, int H, int W, BitmapFileHeader *bmfh,
             BitmapInfoHeader *bmif)
{
    FILE *ff = fopen(fileName, "wb");
    if (ff == NULL)
    {
        fprintf(stderr, "Error: file %s cannot be created\n", fileName);
        return ERROR_WRITE_FILE;
    }
    fwrite(bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(bmif, 1, sizeof(BitmapInfoHeader), ff);
    fseek(ff, bmfh->pixelArrOffset,
          SEEK_SET); // Move the file pointer to the pixel array offset
    for (int i = 0; i < H; i++)
    {
        fwrite(arr[i], 1, W * sizeof(Rgb) + (4 - ((3 * W) % 4)) % 4, ff);
    }
    fclose(ff);
    return SUCCESS;
}

void rgbfilter(Rgb **arr, int H, int W, char component, int value)
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            switch (component)
            {
                case 'r':
                    arr[i][j].r = value;
                    break;
                case 'g':
                    arr[i][j].g = value;
                    break;
                case 'b':
                    arr[i][j].b = value;
                    break;
            }
        }
    }
}

void drawCircle(Rgb **arr, int H, int W, int x, int y, int r, int *color)
{
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r) // x^2 + y^2 <= r^2
            {
                if (y - i >= 0 && y - i < H && x + j >= 0 && x + j < W)
                {
                    setPixel(arr, x + j, y - i, color);
                }
            }
        }
    }
}

void drawLine(Rgb **arr, int H, int W, int x0, int y0, int x1, int y1,
              int thickness, int *color)
{
    int thicknessIsEven = thickness % 2 == 0;
    if (thickness % 2 == 1)
    {
        thickness = thickness / 2;
    }
    else
    {
        thickness = thickness / 2 - 1;
    }
    // vertical line (x0 == x1)
    if (x0 == x1)
    {
        if (y0 > y1)
        {
            swapInt(&y0, &y1);
        }
        for (int y = y0; y < y1; y++)
        {
            for (int j = -thickness; j <= thickness + thicknessIsEven; j++)
            {
                if (y >= 0 && x0 + j >= 0 && x0 + j < W && y < H)
                {
                    setPixel(arr, x0 + j, y, color);
                }
            }
        }
    }
    // horizontal line (y0 == y1)
    else if (y0 == y1)
    {
        if (x0 > x1)
        {
            swapInt(&x0, &x1);
        }
        for (int x = x0; x < x1; x++)
        {
            for (int j = -thickness - thicknessIsEven; j <= thickness; j++)
            {
                if (y0 + j >= 0 && x >= 0 && x < W && y0 + j < H)
                {
                    setPixel(arr, x, y0 + j, color);
                }
            }
        }
    }
    // line with slope (x0 != x1 and y0 != y1) using Bresenham's algorithm
    // https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0
    else
    {
        if (x0 > x1)
        {
            swapInt(&x0, &x1);
            swapInt(&y0, &y1);
        }
        int k = (y1 - y0) / (x1 - x0);
        for (int x = x0; x <= x1; x++)
        {
            int y = y0 + k * (x - x0); // y = kx + b
            drawCircle(arr, H, W, x, y, thickness, color);
        }
    }
}

void drawSquareSquaredLines(Rgb **arr, int H, int W, int x, int y, int sideSize,
                            int thickness, int *color, int fill, int *fillColor)
{
    // fill the square
    if (fill)
    {
        for (int i = 0; i < sideSize; i++)
        {
            for (int j = 0; j < sideSize; j++)
            {
                if (y - i >= 0 && y - i < H && x + j >= 0 && x + j < W)
                {
                    setPixel(arr, x + j, y - i, fillColor);
                }
            }
        }
    }
    // draw the square
    drawLine(arr, H, W, x, y, x + sideSize, y, thickness, color);
    drawLine(arr, H, W, x, y, x, y - sideSize, thickness, color);
    drawLine(arr, H, W, x + sideSize, y, x + sideSize, y - sideSize, thickness,
             color);
    drawLine(arr, H, W, x, y - sideSize, x + sideSize, y - sideSize, thickness,
             color);
    // draw diagonals
    drawLine(arr, H, W, x, y, x + sideSize, y - sideSize, thickness, color);
    drawLine(arr, H, W, x, y - sideSize, x + sideSize, y, thickness, color);
}

Rgb **cutImage(Rgb **arr, int H, int W, int x, int y, int sizeX, int sizeY)
{
    Rgb **newArr = calloc(sizeY, sizeof(Rgb *));
    if (newArr == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < sizeY; i++)
    {
        newArr[i] = calloc(sizeX, sizeof(Rgb));
        if (newArr[i] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            imageFree(newArr, i);
            return NULL;
        }
        for (int j = 0; j < sizeX; j++)
        {
            if (y - i >= 0 && y - i < H && x + j >= 0 && x + j < W)
            {
                newArr[i][j] = arr[y - i][x + j];
            }
        }
    }
    return newArr;
}

Rgb **rotateImageCounterclock(Rgb **arr, int H, int W)
{
    // Transposing the matrix
    Rgb **newArr = malloc(W * sizeof(Rgb *));
    if (newArr == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < W; i++)
    {
        newArr[i] = malloc(H * sizeof(Rgb));
        if (newArr[i] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            imageFree(newArr, i);
            return NULL;
        }
        for (int j = 0; j < H; j++)
        {
            newArr[i][j] = arr[j][i];
        }
    }
    // Reversing each column
    for (int j = 0; j < H; j++)
    {
        for (int i = 0; i < W / 2; i++)
        {
            Rgb temp = newArr[i][j];
            newArr[i][j] = newArr[W - i - 1][j];
            newArr[W - i - 1][j] = temp;
        }
    }

    imageFree(arr, H);
    return newArr;
}

int rotatePartOfPicture(Rgb **arr, int H, int W, int x0, int y0, int x1, int y1,
                        int degrees)
{
    if (x0 > x1)
    {
        swapInt(&x0, &x1);
    }
    if (y1 > y0) // H - y1 - 1 - (H - y0 - 1) = y0 - y1
    {
        swapInt(&y0, &y1);
    }

    int sizeX = x1 - x0;
    int sizeY = -(y1 - y0); // H - y1 - 1 - (H - y0 - 1) = -(y1 - y0)
    Rgb **newArr = cutImage(arr, H, W, x0, y0, sizeX, sizeY);
    if (newArr == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < degrees / 90; i++)
    {
        newArr = rotateImageCounterclock(newArr, sizeY, sizeX);
        if (newArr == NULL)
        {
            return ERROR_MEMORY_ALLOCATION;
        }
        swapInt(&sizeX, &sizeY);
    }

    int newX0 = x0;
    int newY0 = y0;
    if (degrees == 90 || degrees == 270)
    {
        newX0 = x0 + sizeY / 2 - sizeX / 2;
        newY0 = y0 - (sizeX / 2 - sizeY / 2);
    }

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (newY0 - i >= 0 && newY0 - i < H && newX0 + j >= 0 &&
                newX0 + j < W)
            {
                arr[newY0 - i][newX0 + j] = newArr[i][j];
            }
        }
    }

    imageFree(newArr, sizeY);

    return SUCCESS;
}

int paving(Rgb **arr, int H, int W, int x0, int y0, int x1, int y1)
{
    if (x0 > x1)
    {
        swapInt(&x0, &x1);
    }
    if (y1 > y0) // H - y1 - 1 - (H - y0 - 1) = y0 - y1
    {
        swapInt(&y0, &y1);
    }

    int sizeX = x1 - x0;
    int sizeY = -(y1 - y0); // H - y1 - 1 - (H - y0 - 1) = -(y1 - y0)
    Rgb **newArr = cutImage(arr, H, W, x0, y0, sizeX, sizeY);
    if (newArr == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (int newX0 = 0; newX0 < W; newX0 += sizeX)
    {
        for (int newY0 = H - 1; newY0 > 0; newY0 -= sizeY)
        {
            for (int i = 0; i < sizeY; i++)
            {
                for (int j = 0; j < sizeX; j++)
                {
                    if (newY0 - i >= 0 && newY0 - i < H && newX0 + j >= 0 &&
                        newX0 + j < W)
                    {
                        arr[newY0 - i][newX0 + j] = newArr[i][j];
                    }
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *const argv[])
{
    puts("Course work for option 4.12, created by Dmitrii Zhuravlev.");
    Args args = {0};
    int parseArgsRetcode = parseArgs(&args, argc, argv);
    if (parseArgsRetcode != SUCCESS)
    {
        if (parseArgsRetcode == PRINT_HELP)
        {
            return 0;
        }
        return parseArgsRetcode;
    }
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;
    Rgb **arr;
    int readBmpRetcode = readBmp(&arr, args.fileName, &bmfh, &bmif);
    if (readBmpRetcode != SUCCESS)
    {
        return readBmpRetcode;
    }
    // inverting input y
    args.leftUp[1] = bmif.height - args.leftUp[1] - 1;
    args.rightDown[1] = bmif.height - args.rightDown[1] - 1;

    if (args.info)
    {
        printFileHeader(bmfh);
        printInfoHeader(bmif);
        imageFree(arr, bmif.height);
        return 0;
    }

    if (args.paving)
    {
        int pavingRetcode =
            paving(arr, bmif.height, bmif.width, args.leftUp[0], args.leftUp[1],
                   args.rightDown[0], args.rightDown[1]);
        if (pavingRetcode != SUCCESS)
        {
            imageFree(arr, bmif.height);
            return pavingRetcode;
        }
    }

    if (args.squaredLines)
    {
        drawSquareSquaredLines(arr, bmif.height, bmif.width, args.leftUp[0],
                               args.leftUp[1], args.sideSize, args.thickness,
                               args.color, args.fill, args.fillColor);
    }

    if (args.rgbfilter)
    {
        rgbfilter(arr, bmif.height, bmif.width, args.componentName,
                  args.componentValue);
    }

    if (args.rotate)
    {
        int rotatePartOfPictureRetcode = rotatePartOfPicture(
            arr, bmif.height, bmif.width, args.leftUp[0], args.leftUp[1],
            args.rightDown[0], args.rightDown[1], args.angle);
        if (rotatePartOfPictureRetcode != SUCCESS)
        {
            imageFree(arr, bmif.height);
            return rotatePartOfPictureRetcode;
        }
    }

    int writeBmpRetcode = writeBmp(args.outputFileName, arr, bmif.height,
                                   bmif.width, &bmfh, &bmif);
    if (writeBmpRetcode != SUCCESS)
    {
        imageFree(arr, bmif.height);
        return writeBmpRetcode;
    }

    imageFree(arr, bmif.height);

    return 0;
}