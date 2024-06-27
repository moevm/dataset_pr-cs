#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct
{
    unsigned short signature;
    unsigned int filesize;
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
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

void help()
{
    printf("Course work for option 4.9, created by Asiya Kireeva.\n\n");
    printf("Flags:\n");
    printf("--help, -h: displays information about the program\n");
    printf("--input, -i: defines the name of the input image\n");
    printf("--output, -o: defines the name of the output image\n");
    printf("--info, -f: displays image information\n\n");

    printf("--rect, -e: calls a function that draws a rectangle based on the "
           "specified parameters\n");
    printf("--left_up, -l: specifies the coordinates of the upper left corner "
           "of the rectangle\n");
    printf("--right_down, -r: specifies the coordinates of the lower right "
           "corner of the rectangle\n");
    printf("--thickness, -t: sets the line thickness\n");
    printf("--color, -c: sets the line color\n");
    printf("--fill, -z: sets the fill of the rectangle\n");
    printf("--fill_color, -n: sets the fill color\n\n");

    printf("--hexagon, -g: calls a function that draws a regular hexagon "
           "taking into account the specified parameters\n");
    printf("--center, -x: sets the coordinates of the center of the shape\n");
    printf("--radius, -y: sets the radius of the circumscribed circle\n");
    printf("--thickness, -t: sets the line thickness\n");
    printf("--color, -c: sets the color of the line\n");
    printf("--fill, -z: sets the hexagon fill\n");
    printf("--fill_color, -n: sets the fill color\n\n");

    printf("--copy, -p: calls a function that copies the specified area of the "
           "image\n");
    printf("--left_up, -l: sets the coordinates of the upper-left corner of "
           "the area\n");
    printf("--right_down, -r: sets the coordinates of the lower-right corner "
           "of the area\n");
    printf("--dest_left_up, -d: sets the upper-left corner of the destination "
           "area\n");
}

void printFileHeader(BitmapFileHeader header)
{
    printf("signature:\t%hu\n", header.signature);
    printf("filesize:\t%u\n", header.filesize);
    printf("reserved1:\t%hu\n", header.reserved1);
    printf("reserved2:\t%hu\n", header.reserved2);
    printf("pixelArrOffset:\t%u\n", header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header)
{
    printf("headerSize:\t%u\n", header.headerSize);
    printf("width: \t%u\n", header.width);
    printf("height: \t%u\n", header.height);
    printf("planes: \t%hu\n", header.planes);
    printf("bitsPerPixel:\t%hu\n", header.bitsPerPixel);
    printf("compression:\t%u\n", header.compression);
    printf("imageSize:\t%u\n", header.imageSize);
    printf("xPixelsPerMeter:\t%u\n", header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%u\n", header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%u\n", header.colorsInColorTable);
    printf("importantColorCount:\t%u\n", header.importantColorCount);
}

Rgb **readBmp(char fileName[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmih)
{
    FILE *f = fopen(fileName, "rb");
    if (!f)
    {
        printf("Error opening file for reading.\n");
        exit(42);
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmih, 1, sizeof(BitmapInfoHeader), f);
    if (bmih->headerSize != 40)
    {
        printf("Invalid version of the BMP file.\n");
        exit(44);
    }
    if (bmih->bitsPerPixel != 24)
    {
        printf("Only 24 bits per pixel are supported.\n");
        exit(44);
    }
    if (bmfh->signature != 0x4D42)
    {
        printf("Invalid version of the BMP file.\n");
        exit(44);
    }
    if (bmih->compression != 0)
    {
        printf("The image must be uncompressed.\n");
        exit(44);
    }
    unsigned int H = bmih->height;
    unsigned int W = bmih->width;
    Rgb **arr = malloc(H * sizeof(Rgb *));
    int linePadding = (4 - ((W * sizeof(Rgb)) % 4)) % 4;
    for (int i = 0; i < H; i++)
    {
        arr[i] = malloc(W * sizeof(Rgb) + linePadding);
        fread(arr[i], 1, W * sizeof(Rgb) + linePadding, f);
    }
    if (fclose(f) != 0)
    {
        printf("Error closing file for reading.\n");
        exit(42);
    }
    return arr;
}

void writeBmp(char fileName[], Rgb **arr, unsigned int H, unsigned int W,
              BitmapFileHeader bmfh, BitmapInfoHeader bmih)
{
    FILE *ff = fopen(fileName, "wb");
    if (!ff)
    {
        printf("Error opening file for writing.\n");
        exit(42);
    }
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmih, 1, sizeof(BitmapInfoHeader), ff);
    int linePadding = (4 - ((W * sizeof(Rgb)) % 4)) % 4;
    for (int i = 0; i < H; i++)
    {
        fwrite(arr[i], 1, W * sizeof(Rgb) + linePadding, ff);
    }
    if (fclose(ff) != 0)
    {
        printf("Error closing file for writing.\n");
        exit(42);
    }
}

void freeMemory(Rgb **arr, unsigned int H)
{
    for (int i = 0; i < H; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

Rgb **fill_circle(Rgb **arr, BitmapInfoHeader *bmih, int x, int y, int radius,
                  Rgb color)
{
    int xmin = x - radius;
    int xmax = x + radius;
    int ymin = y - radius;
    int ymax = y + radius;

    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= bmih->width) xmax = bmih->width - 1;
    if (ymax >= bmih->height) ymax = bmih->height - 1;

    for (int i = ymin; i <= ymax; i++)
    {
        for (int j = xmin; j <= xmax; j++)
        {
            if ((j - x) * (j - x) + (i - y) * (i - y) <= radius * radius)
            {
                if (i >= 0 && j >= 0 && i < bmih->height && j < bmih->width)
                {
                    arr[i][j] = color;
                }
            }
        }
    }
    return arr;
}

Rgb **drawLine(Rgb **arr, BitmapInfoHeader *bmih, int x1, int y1, int x2,
               int y2, int thickness, Rgb color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;
    if (x1 < x2)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }
    if (y1 < y2)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }
    int err = dx - dy;
    while (1)
    {
        if (x1 >= 0 && x1 < bmih->width && y1 >= 0 && y1 < bmih->height)
        {
            if (thickness == 1) arr[y1][x1] = color;
        }
        arr = fill_circle(arr, bmih, x1, y1, thickness / 2, color);

        if (x1 == x2 && y1 == y2)
        {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    return arr;
}

Rgb **drawRect(Rgb **arr, BitmapInfoHeader *bmih, int x1, int y1, int x2,
               int y2, int thickness, Rgb color, int fill, Rgb fillColor)
{
    if (y1 > y2)
    {
        int t = y1;
        y1 = y2;
        y2 = t;
    }
    if (x1 > x2)
    {
        int t = x1;
        x1 = x2;
        x2 = t;
    }
    y1 = bmih->height - y1;
    y2 = bmih->height - y2;
    int coord[5][2] = {{x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}, {x1, y1}};
    for (int i = 1; i < 5; i++)
    {
        arr = drawLine(arr, bmih, coord[i - 1][0], coord[i - 1][1], coord[i][0],
                       coord[i][1], thickness, color);
    }
    if (fill)
    {
        for (int i = y2 + thickness / 2 + 1; i < y1 - thickness / 2; i++)
        {
            for (int j = x1 + thickness / 2 + 1; j < x2 - thickness / 2; j++)
            {
                if (j >= 0 && j < bmih->width && bmih->height - i >= 0 &&
                    bmih->height - i < bmih->height)
                {
                    arr[i][j] = fillColor;
                }
            }
        }
    }
    return arr;
}

Rgb **drawHex(Rgb **arr, BitmapInfoHeader *bmih, int x0, int y0, int radius,
              int thickness, Rgb color, int fill, Rgb fillColor)
{
    int h = (int)((sqrt(3) * radius) / 2);
    y0 = bmih->height - y0;
    int coord[7][2] = {{x0 - radius, y0},         {x0 - radius / 2, y0 - h},
                       {x0 + radius / 2, y0 - h}, {x0 + radius, y0},
                       {x0 + radius / 2, y0 + h}, {x0 - radius / 2, y0 + h},
                       {x0 - radius, y0}};
    if (fill)
    {
        for (int i = coord[1][1] + thickness / 2 + 1;
             i < coord[4][1] - thickness / 2; i++)
        {
            for (int j = coord[1][0]; j <= coord[4][0]; j++)
            {
                if (i >= 0 && i < bmih->height && j >= 0 && j < bmih->width)
                {
                    arr[i][j] = fillColor;
                }
            }
        }
        int x1 = coord[1][0], y1 = coord[1][1];
        int x2 = coord[5][0], y2 = coord[5][1];
        int x3 = coord[0][0], y3 = coord[0][1];
        for (int i = y1; i < y2; i++)
        {
            for (int j = x3; j < x0 - radius / 2; j++)
            {
                if (i >= 0 && i < bmih->height && j >= 0 && j < bmih->width)
                {
                    int a = (x1 - j) * (y2 - y1) - (x2 - x1) * (y1 - i);
                    int b = (x2 - j) * (y3 - y2) - (x3 - x2) * (y2 - i);
                    int c = (x3 - j) * (y1 - y3) - (x1 - x3) * (y3 - i);
                    if ((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0))
                    {
                        arr[i][j] = fillColor;
                    }
                }
            }
        }
        x1 = coord[2][0], y1 = coord[2][1];
        x2 = coord[4][0], y2 = coord[4][1];
        x3 = coord[3][0], y3 = coord[3][1];
        for (int i = y1; i < y2; i++)
        {
            for (int j = x0 + radius / 2; j < x3; j++)
            {
                if (i >= 0 && i < bmih->height && j >= 0 && j < bmih->width)
                {
                    int a = (x1 - j) * (y2 - y1) - (x2 - x1) * (y1 - i);
                    int b = (x2 - j) * (y3 - y2) - (x3 - x2) * (y2 - i);
                    int c = (x3 - j) * (y1 - y3) - (x1 - x3) * (y3 - i);
                    if ((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0))
                    {
                        arr[i][j] = fillColor;
                    }
                }
            }
        }
    }
    for (int i = 1; i < 7; i++)
    {
        arr = drawLine(arr, bmih, coord[i - 1][0], coord[i - 1][1], coord[i][0],
                       coord[i][1], thickness, color);
    }
    return arr;
}

Rgb **copyImage(Rgb **arr, BitmapInfoHeader *bmih, int x1, int y1, int x2,
                int y2, int dx, int dy)
{
    if (x1 > x2)
    {
        int t = x1;
        x1 = x2;
        x2 = t;
    }
    if (y1 > y2)
    {
        int t = y1;
        y1 = y2;
        y2 = t;
    }
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 > bmih->width) x2 = bmih->width;
    if (y2 > bmih->height) y2 = bmih->height;

    int sizeX = x2 - x1;
    int sizeY = y2 - y1;

    if (sizeX < 0 || sizeY < 0)
    {
        printf("Invalid coordinates for copying image.\n");
        exit(40);
    }
    Rgb **tempArr = malloc(sizeY * sizeof(Rgb *));
    if (!tempArr)
    {
        printf("Memory allocation failed for temporary image array.\n");
        exit(41);
    }
    for (int i = 0; i < sizeY; i++)
    {
        tempArr[i] = malloc(sizeX * sizeof(Rgb));
        if (!tempArr[i])
        {
            printf("Memory allocation failed for temporary image row.\n");
            for (int j = 0; j < i; j++)
            {
                free(tempArr[j]);
            }
            free(tempArr);
            exit(41);
        }
    }
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = x1; j < x2; j++)
        {
            tempArr[i][j - x1] = arr[bmih->height - y2 + i][j];
        }
    }
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (bmih->height - dy - sizeY + i >= 0 &&
                bmih->height - dy - sizeY + i < bmih->height && dx + j >= 0 &&
                dx + j < bmih->width)
            {
                arr[bmih->height - dy - sizeY + i][dx + j] = tempArr[i][j];
            }
        }
    }
    freeMemory(tempArr, sizeY);
    return arr;
}

Rgb **drawRhombus(Rgb **arr, BitmapInfoHeader *bmih, int ux, int uy, int size, Rgb fillColor)
{
    uy = bmih->height - uy;
    int d = (size * sqrt(2)) / 2;
    int coord[5][2] = {{ux, uy}, {ux + d, uy - d}, {ux, uy - 2 * d}, {ux - d, uy - d}, {ux, uy}};
    int thickness = 1;
    Rgb color;
    color.r = 0;
    color.b = 0;
    color.g = 0;
    for (int i = 1; i < 5; i++)
    {
        arr = drawLine(arr, bmih, coord[i - 1][0], coord[i - 1][1], coord[i][0],
                       coord[i][1], thickness, color);
    }
    int x1 = coord[0][0], y1 = coord[0][1];
    int x2 = coord[2][0], y2 = coord[2][1];
    int x3 = coord[3][0], y3 = coord[3][1];
    for (int i = y2; i < y1; i++)
    {
        for (int j = x3; j < ux; j++)
        {
            if (i >= 0 && i < bmih->height && j >= 0 && j < bmih->width)
            {
                int a = (x1 - j) * (y2 - y1) - (x2 - x1) * (y1 - i);
                int b = (x2 - j) * (y3 - y2) - (x3 - x2) * (y2 - i);
                int c = (x3 - j) * (y1 - y3) - (x1 - x3) * (y3 - i);
                if ((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0))
                {
                    arr[i][j] = fillColor;
                }
            }
        }
    }
    for (int i = y2 + 1; i < y1; i++) {
        if (i >= 0 && i < bmih->height)
        {
            arr[i][ux] = fillColor;
        }
    }
    x1 = coord[0][0], y1 = coord[0][1];
    x2 = coord[2][0], y2 = coord[2][1];
    x3 = coord[1][0], y3 = coord[1][1];
    for (int i = y2; i < y1; i++)
    {
        for (int j = ux; j < x3; j++)
        {
            if (i >= 0 && i < bmih->height && j >= 0 && j < bmih->width)
            {
                int a = (x1 - j) * (y2 - y1) - (x2 - x1) * (y1 - i);
                int b = (x2 - j) * (y3 - y2) - (x3 - x2) * (y2 - i);
                int c = (x3 - j) * (y1 - y3) - (x1 - x3) * (y3 - i);
                if ((a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0))
                {
                    arr[i][j] = fillColor;
                }
            }
        }
    }
    return arr;
}

bool isNumber(const char *str)
{
    int i = 0;
    while (isdigit(str[i]))
        i++;
    return str[i] == '\0';
}

int main(int argc, char **argv)
{
    static struct option longOptions[] = {
        {"help", no_argument, NULL, 'h'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"info", no_argument, NULL, 'f'},

        {"rect", no_argument, NULL, 'e'},
        {"left_up", required_argument, NULL, 'l'},
        {"right_down", required_argument, NULL, 'r'},
        {"thickness", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
        {"fill", no_argument, NULL, 'z'},
        {"fill_color", required_argument, NULL, 'n'},

        {"hexagon", no_argument, NULL, 'g'},
        {"center", required_argument, NULL, 'x'},
        {"radius", required_argument, NULL, 'y'},
        {"thickness", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
        {"fill", no_argument, NULL, 'z'},
        {"fill_color", required_argument, NULL, 'n'},

        {"copy", no_argument, NULL, 'p'},
        {"left_up", required_argument, NULL, 'l'},
        {"right_down", required_argument, NULL, 'r'},
        {"dest_left_up", required_argument, NULL, 'd'},

        {"square_rhombus", no_argument, NULL, 's'},
        {"upper_vertex", required_argument, NULL, 'u'},
        {"size", required_argument, NULL, 'k'},
        {"fill_color", required_argument, NULL, 'n'},
        {NULL, 0, NULL, 0}};
    char *shortOptions = "hfegpszi:o:l:r:t:c:n:x:y:d:u:k:";
    int optionIndex = 0;
    char opt = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex);
    char inputFile[100] = "./";
    char outputFile[100] = "./";
    int k, r, g, b;
    int x1, y1, x2, y2, thickness, x0, y0, radius, dx, dy, ux, uy, size;
    Rgb color, fillColor;
    int operation = -1, inputFlag = 0, outputFlag = 0, leftFlag = 0,
        rightFlag = 0, thicknessFlag = 0, colorFlag = 0, fillFlag = 0,
        fillColorFlag = 0, centerFlag = 0, radiusFlag = 0, destFlag = 0, sizeFlag = 0, upperVertexFlag = 0;
    while (opt != -1)
    {
        switch (opt)
        {
            case 'h':
                help();
                exit(0);
            case 'i':
                inputFlag = 1;
                sprintf(inputFile, "%s%s", inputFile, argv[optind - 1]);
                break;
            case 'o':
                outputFlag = 1;
                sprintf(outputFile, "%s%s", outputFile, argv[optind - 1]);
                break;
            case 'f':
                operation = 0;
                break;
            case 'e':
                operation = 1;
                break;
            case 'g':
                operation = 2;
                break;
            case 'p':
                operation = 3;
                break;
            case 's':
                operation = 4;
                break;
            case 'u':
                upperVertexFlag = 1;
                k = sscanf(optarg, "%d.%d", &ux, &uy);
                if (k != 2)
                {
                    printf("Incorrect coordinate input format.\n");
                    exit(40);
                }
                break;
            case 'k':
                sizeFlag = 1;
                if (!isNumber(optarg))
                {
                    printf("Incorrect size input format.\n");
                    exit(40);
                }
                size = atoi(optarg);
                if (size <= 0)
                {
                    printf("Incorrect size input format.\n");
                    exit(40);
                }
                break;
            case 'l':
                leftFlag = 1;
                k = sscanf(optarg, "%d.%d", &x1, &y1);
                if (k != 2)
                {
                    printf("Incorrect coordinate input format.\n");
                    exit(40);
                }
                break;
            case 'r':
                rightFlag = 1;
                k = sscanf(optarg, "%d.%d", &x2, &y2);
                if (k != 2)
                {
                    printf("Incorrect coordinate input format.\n");
                    exit(40);
                }
                break;
            case 't':
                thicknessFlag = 1;
                if (!isNumber(optarg))
                {
                    printf("Incorrect thickness input format.\n");
                    exit(40);
                }
                thickness = atoi(optarg);
                if (thickness <= 0)
                {
                    printf("Incorrect thickness input format.\n");
                    exit(40);
                }
                break;
            case 'c':
                colorFlag = 1;
                k = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (k != 3)
                {
                    printf("Incorrect line color input format'.\n");
                    exit(40);
                }
                if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
                {
                    printf("Incorrect line color input format.\n");
                    exit(40);
                }
                color.r = r;
                color.g = g;
                color.b = b;
                break;
            case 'z':
                fillFlag = 1;
                break;
            case 'n':
                fillColorFlag = 1;
                k = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
                if (k != 3)
                {
                    printf("Incorrect fill color input format'.\n");
                    exit(40);
                }
                if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
                {
                    printf("Incorrect fill color input format.\n");
                    exit(40);
                }
                fillColor.r = r;
                fillColor.g = g;
                fillColor.b = b;
                break;
            case 'x':
                centerFlag = 1;
                k = sscanf(optarg, "%d.%d", &x0, &y0);
                if (k != 2)
                {
                    printf("Incorrect coordinate input format.\n");
                    exit(40);
                }
                break;
            case 'y':
                radiusFlag = 1;
                if (!isNumber(optarg))
                {
                    printf("Incorrect radius input format.\n");
                    exit(40);
                }
                radius = atoi(optarg);
                if (radius <= 0)
                {
                    printf("Incorrect radius input format.\n");
                    exit(40);
                }
                break;
            case 'd':
                destFlag = 1;
                k = sscanf(optarg, "%d.%d", &dx, &dy);
                if (k != 2)
                {
                    printf("Incorrect coordinate input format.\n");
                    exit(40);
                }
                break;
            default:
                printf("Incorrect command input format.\n");
                exit(40);
        }
        opt = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex);
    }
    if ((optind < argc) && (inputFlag == 0))
    {
        sprintf(inputFile, "%s%s", inputFile, argv[optind++]);
    }
    if (strcmp(inputFile, "./") == 0)
    {
        printf("Incorrect input file name format.\n");
        exit(40);
    }
    if (strcmp(outputFile, "./") == 0 || outputFlag == 0)
    {
        strcat(outputFile, "out.bmp");
    }
    if (strcmp(inputFile, outputFile) == 0)
    {
        printf("Incorrect format for entering the name of the input or output "
               "file.\n");
        exit(40);
    }
    BitmapFileHeader *bmfh = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *bmih = malloc(sizeof(BitmapInfoHeader));
    if (!bmfh || !bmih)
    {
        printf("Error allocating memory for headers.\n");
        exit(41);
    }
    Rgb **arr = readBmp(inputFile, bmfh, bmih);
    if (!arr)
    {
        printf("Error reading image file.\n");
        free(bmfh);
        free(bmih);
        exit(43);
    }
    switch (operation)
    {
        case 0:
            printFileHeader(*bmfh);
            printInfoHeader(*bmih);
            exit(0);
        case 1:
            if ((leftFlag && rightFlag && thicknessFlag && colorFlag &&
                 fillFlag && fillColorFlag) ||
                (leftFlag && rightFlag && thicknessFlag && colorFlag &&
                 !fillFlag && fillColorFlag) ||
                (leftFlag && rightFlag && thicknessFlag && colorFlag &&
                 !fillFlag && !fillColorFlag))
            {
                arr = drawRect(arr, bmih, x1, y1, x2, y2, thickness, color,
                               fillFlag, fillColor);
                if (!arr)
                {
                    printf("Error drawing a rectangle.\n");
                    free(bmfh);
                    free(bmih);
                    exit(43);
                }
            }
            else
            {
                printf("Error entering arguments for drawing a rectangle.\n");
                exit(40);
            }
            break;
        case 2:
            if ((centerFlag && radiusFlag && thicknessFlag && colorFlag &&
                 fillFlag && fillColorFlag) ||
                (centerFlag && radiusFlag && thicknessFlag && colorFlag &&
                 !fillFlag && fillColorFlag) ||
                (centerFlag && radiusFlag && thicknessFlag && colorFlag &&
                 !fillFlag && !fillColorFlag))
            {
                arr = drawHex(arr, bmih, x0, y0, radius, thickness, color,
                              fillFlag, fillColor);
                if (!arr)
                {
                    printf("Error drawing a hexagon.\n");
                    free(bmfh);
                    free(bmih);
                    exit(43);
                }
            }
            else
            {
                printf("Error entering arguments for drawing a hexagon.\n");
                exit(40);
            }
            break;
        case 3:
            if (leftFlag && rightFlag && destFlag)
            {
                arr = copyImage(arr, bmih, x1, y1, x2, y2, dx, dy);
                if (!arr)
                {
                    printf("Error copying the image area.\n");
                    free(bmfh);
                    free(bmih);
                    exit(43);
                }
            }
            else
            {
                printf("Error entering arguments to copy the image area.\n");
                exit(40);
            }
            break;
        case 4:
            if (upperVertexFlag && sizeFlag && fillColorFlag)
            {
                arr = drawRhombus(arr, bmih, ux, uy, size, fillColor);
                if (!arr)
                {
                    printf("Error drawing a rhombus.\n");
                    free(bmfh);
                    free(bmih);
                    exit(43);
                }
            }
            else
            {
                printf("Error entering arguments for drawing a rhombus.\n");
                exit(40);
            }
            break;
        default:
            printf("Error entering the operation number.\n");
            exit(40);
    }
    writeBmp(outputFile, arr, bmih->height, bmih->width, *bmfh, *bmih);
    freeMemory(arr, bmih->height);
    free(bmfh);
    free(bmih);
    return 0;
}
