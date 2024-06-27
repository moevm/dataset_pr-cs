#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP 1
#define INFO 2
#define ERROR_OPEN_FILE 40
#define NOT_BMP_FILE 41
#define NOT_SUPPORTED_FILE 42
#define INVALID_ARGUMENTS 43
#define MEMORY_ALLOCATION 44

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

typedef struct StackElement
{
    int x;
    int y;
    struct StackElement *next;

} StackElement;

typedef struct Stack
{
    StackElement *head;
    unsigned int sizeOfStack;

} Stack;

typedef struct
{
    short help;
    short info;
    short input;
    short output;

    short rect;
    short leftUp;
    short rightDown;
    short thickness;
    short color;
    short fill;
    short fillColor;

    short ornament;
    short pattern;
    short count;

    short rotate;
    short angle;

    short binarization;
    short threshold;

    short shift;
    short step;
    short xFlag;
    short yFlag;
    short xyFlag;
} OptFlags;

typedef struct
{
    char inputFile[1024];
    char outputFile[1024];
    char pattern[128];
    char axis[128];

    int leftUp[2];
    int rightDown[2];
    int color[3];
    int fillColor[3];

    int thickness;
    int count;
    int angle;

    int threshold;

    int step;
    short xFlag;
    short yFlag;
    short xyFlag;

    short command;
    short fill;
} OptArgs;

void printHelp();
void printFileHeader(BitmapFileHeader header);
void printInfoHeader(BitmapInfoHeader header);
int parseTerminal(OptArgs *argsToParse, int argc, char **argv);

StackElement *createStackElement(int x, int y);
Stack *createStack();
void push(Stack *stack, int x, int y);
void pop(Stack *stack);
void clearStack(Stack *stack);

void freeImage(Rgb **image, int heightOfImage);
int readBmp(Rgb ***image, char *fileNameToRead, BitmapFileHeader *bmfh,
            BitmapInfoHeader *bmih);
int writeRgb(FILE **f, char *fileNameToWrite, Rgb **image,
             BitmapFileHeader bmfh, BitmapInfoHeader bmih);
int createEmptyRgb(Rgb ***image, unsigned int height, unsigned int width,
                   int *colorOfPicture);

int *getPixel(Rgb **image, int x, int y);
void setPixel(Rgb **image, int *newColor, int x, int y);
int *getInveretedColor(int *colorToInvert, int index);
int colorCompare(int *colorWithCompare, int *colorToCompare);
int deleteEmptyPartsOfLine(int **coords, BitmapInfoHeader bmih, int x0, int y0,
                           int x1, int y1);
int isCircleCoverImage(int x0, int y0, int radius, int width, int height);
int rotatePartOfImage(Rgb **image, BitmapInfoHeader bmih, int x0, int y0,
                      int x1, int y1, int angleOfRotation);
int isInImage(int widthOfImage, int heightOfImage, int xToCheck, int yToCheck);
int isInside(Rgb **image, int width, int height, int *colorToFill, int x,
             int y);
void fill(Rgb **image, int width, int height, int *colorToFill, int x, int y);
void pasteArea(Rgb **image, Rgb **areaToPaste, int heightOfAreaToPaste,
               int widthOfAreaToPaste, int width, int height,
               int *invertedColor, int x0, int y0);
Rgb **copyArea(Rgb **image, int widthOfImage, int heightOfImage, int x0, int y0,
               int x1, int y1);
int MIN(int a, int b);
int MAX(int a, int b);

void dyeImageIntoNewColor(Rgb **image, int width, int height, int *colorToFill);
void drawLine(Rgb **image, BitmapInfoHeader bmih, int x0, int y0, int x1,
              int y1, int *color);
void drawLineWithThicknessForVerticalHorizontal(Rgb **image,
                                                BitmapInfoHeader bmih, int x0,
                                                int y0, int x1, int y1,
                                                int thickness, int *color);
void drawLineWithThicknessForRectangle(Rgb **image, BitmapInfoHeader bmih,
                                       int x0, int y0, int x1, int y1,
                                       int thickness, int *color);
void drawRectangle(Rgb **image, BitmapInfoHeader bmih, int x0, int y0, int x1,
                   int y1, int thickness, int isFill, int *borderColor,
                   int *colorToFill);
void drawRectangleForPattern(Rgb **image, BitmapInfoHeader bmih, int x0, int y0,
                             int x1, int y1, int thickness, int *borderColor);
void drawCircle(Rgb **image, int widthOfImage, int heightOfImage, int x0,
                int y0, int radius, int *borderColor);
void drawCircleWithThickness(Rgb **image, int widthOfImage, int heightOfImage,
                             int x0, int y0, int radius, int thickness,
                             int *borderColor);
void drawRound(Rgb **image, int widthOfImage, int heightOfImage, int x0, int y0,
               int radius, int *colorToFill);
void drawRectangleAsPattern(Rgb **image, BitmapInfoHeader bmih, int thickness,
                            int count, int *colorOfPattern);
void drawCentralCircleAsPattern(Rgb **image, BitmapInfoHeader bmih,
                                int *colorOfPattern);
void drawSemiciclesAsPattern(Rgb **image, BitmapInfoHeader bmih, int thickness,
                             int count, int *colorOfPattern);

void shiftTheImage(Rgb **image, BitmapInfoHeader bmih, int step, int xFlag,
                   int yFlag, int xyFlag);
void binarizateImage(Rgb **image, BitmapInfoHeader bmih, int threshold);

int main(int argc, char **argv)
{
    OptArgs args;
    int key = parseTerminal(&args, argc, argv);
    if (key != 0 && key != INFO && key != HELP)
    {
        return key;
    }
    if (key == HELP)
    {
        puts("Course work for option 4.3, created by Fedor Bondarenko.");
        printHelp();
        return 0;
    }
    puts("Course work for option 4.3, created by Fedor Bondarenko.");

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    Rgb **image;
    int check = readBmp(&image, args.inputFile, &bmfh, &bmih);
    if (check) return check;
    if (key == INFO)
    {
        printFileHeader(bmfh);
        printInfoHeader(bmih);
        freeImage(image, bmih.height);
        return 0;
    }

    switch (args.command)
    {
        case 1:
            drawRectangle(image, bmih, args.leftUp[0], args.leftUp[1],
                          args.rightDown[0], args.rightDown[1], args.thickness,
                          args.fill, args.color, args.fillColor);
            break;
        case 2:
            if (!strcmp(args.pattern, "rectangle"))
            {
                drawRectangleAsPattern(image, bmih, args.thickness, args.count,
                                       args.color);
            }
            else if (!strcmp(args.pattern, "circle"))
            {
                drawCentralCircleAsPattern(image, bmih, args.color);
            }
            else if (!strcmp(args.pattern, "semicircles"))
            {
                drawSemiciclesAsPattern(image, bmih, args.thickness, args.count,
                                        args.color);
            }
            break;
        case 3:
            check = rotatePartOfImage(image, bmih, args.leftUp[0],
                                      args.leftUp[1], args.rightDown[0],
                                      args.rightDown[1], args.angle);
            if (check)
            {
                freeImage(image, bmih.height);
                return check;
            }
            break;
        case 4:
            binarizateImage(image, bmih, args.threshold);
            break;
        case 5:
            shiftTheImage(image, bmih, args.step, args.xFlag, args.yFlag,
                          args.xyFlag);
            break;
    }

    FILE *f;
    check = writeRgb(&f, args.outputFile, image, bmfh, bmih);
    if (check)
    {
        freeImage(image, bmih.height);
        return check;
    }
    freeImage(image, bmih.height);

    return 0;
}

void printHelp()
{
    puts("Options:");
    puts("  -h  --help: Display this help message.");
    puts("  -I  --info: Display information about the image.");
    puts("  -i  --input FILE: Explicitly specify the input file.");
    puts("  -o  --output FILE: Specify the output file.");

    puts("  -R  --rect: Draw a rectangle.");
    puts("  -O  --ornament: Draw an ornament on the borders of the image.");
    puts("  -E  --rotate: Rotate part of image on 90, 180, 270 degrees.");

    puts("  -l  --left_up x.y: Set the coordinates of the top left corner of "
         "the square or rotation area.");
    puts("  -r  --right_down x.y: Set the coordinates of the bottom right "
         "corner of the rotation area.");
    puts("  -t  --thickness: Set the line thickness. Must be "
         "greater than 0.");
    puts("  -c  --color r.g.b: Set the color in the format rrr.ggg.bbb.");
    puts("  -f  --fill: Fill the rectangle.");
    puts("  -C  --fill_color r.g.b: Set the fill color in the format "
         "rrr.ggg.bbb.");
    puts("  -p  --pattern rectangle/circle/semicicles: Choose the pattern to "
         "be made for ornament.");
    puts("  -T  --count: Set the count of patterns if it allows");
    puts("  -a  --angle: Set the rotation angle. Can be 90, 180, or 270.");
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

int parseTerminal(OptArgs *argsToParse, int argc, char **argv)
{
    OptFlags flags = {0};
    OptArgs args = {0};

    struct option longOptions[] = {{"help", no_argument, NULL, 'h'},
                                   {"info", no_argument, NULL, 'I'},
                                   {"input", required_argument, NULL, 'i'},
                                   {"output", required_argument, NULL, 'o'},

                                   {"rect", no_argument, NULL, 'R'},
                                   {"left_up", required_argument, NULL, 'l'},
                                   {"right_down", required_argument, NULL, 'r'},
                                   {"thickness", required_argument, NULL, 't'},
                                   {"color", required_argument, NULL, 'c'},
                                   {"fill", no_argument, NULL, 'f'},
                                   {"fill_color", required_argument, NULL, 'C'},

                                   {"ornament", no_argument, NULL, 'O'},
                                   {"pattern", required_argument, NULL, 'p'},
                                   {"count", required_argument, NULL, 'T'},

                                   {"rotate", no_argument, NULL, 'E'},
                                   {"angle", required_argument, NULL, 'a'},

                                   {"binarization", no_argument, NULL, 'J'},
                                   {"threshold", required_argument, NULL, 'P'},

                                   {"shift", no_argument, NULL, 'K'},
                                   {"step", required_argument, NULL, 'L'},
                                   {"axis", required_argument, NULL, 'M'},

                                   {NULL, no_argument, NULL, 0}};
    char *shortOptions = "hIi:o:Rl:r:t:c:fC:Op:T:Ea:JP:";

    int optValue;
    while (1)
    {
        optValue = getopt_long(argc, argv, shortOptions, longOptions, &optind);
        if (optValue == -1) break;

        switch (optValue)
        {
            case 'h':
                flags.help = 1;
                break;
            case 'I':
                flags.info = 1;
                break;
            case 'i':
                flags.input = 1;
                strncpy(args.inputFile, optarg, 1024);
                break;
            case 'o':
                flags.output = 1;
                strncpy(args.outputFile, optarg, 1024);
                break;
            case 'R':
                flags.rect = 1;
                args.command = 1;
                break;
            case 'l':
                if (sscanf(optarg, "%d.%d", &args.leftUp[0], &args.leftUp[1]) !=
                    2)
                {
                    fprintf(stderr,
                            "Error: invalid format of left_up coordinate\n");
                    return INVALID_ARGUMENTS;
                }
                flags.leftUp = 1;
                break;
            case 'r':
                if (sscanf(optarg, "%d.%d", &args.rightDown[0],
                           &args.rightDown[1]) != 2)
                {
                    fprintf(stderr,
                            "Error: invalid format of right_down coordinate\n");
                    return INVALID_ARGUMENTS;
                }
                flags.rightDown = 1;
                break;
            case 't':
                if (sscanf(optarg, "%d", &args.thickness) != 1)
                {
                    fprintf(stderr, "Error: thickness must be an integer\n");
                    return INVALID_ARGUMENTS;
                }
                flags.thickness = 1;
                break;
            case 'c':
                if (sscanf(optarg, "%d.%d.%d", &args.color[0], &args.color[1],
                           &args.color[2]) != 3)
                {
                    fprintf(stderr, "Error: invalid color format\n");
                    return INVALID_ARGUMENTS;
                }
                for (int i = 0; i < 3; i++)
                {
                    if (args.color[i] > 255 || args.color[i] < 0)
                    {
                        fprintf(stderr, "Error: invalid code of color\n");
                        return INVALID_ARGUMENTS;
                    }
                }
                flags.color = 1;
                break;
            case 'f':
                flags.fill = 1;
                args.fill = 1;
                break;
            case 'C':
                if (sscanf(optarg, "%d.%d.%d", &args.fillColor[0],
                           &args.fillColor[1], &args.fillColor[2]) != 3)
                {
                    fprintf(stderr, "Error: invalid color format\n");
                    return INVALID_ARGUMENTS;
                }
                for (int i = 0; i < 3; i++)
                {
                    if (args.fillColor[i] > 255 || args.fillColor[i] < 0)
                    {
                        fprintf(stderr, "Error: invalid code of color\n");
                        return INVALID_ARGUMENTS;
                    }
                }
                flags.fillColor = 1;
                break;
            case 'O':
                flags.ornament = 1;
                args.command = 2;
                break;
            case 'p':
                flags.pattern = 1;
                strncpy(args.pattern, optarg, 16);
                break;
            case 'T':
                if (sscanf(optarg, "%d", &args.count) != 1)
                {
                    fprintf(stderr, "Error: invalid count format\n");
                    return INVALID_ARGUMENTS;
                }
                flags.count = 1;
                break;
            case 'E':
                flags.rotate = 1;
                args.command = 3;
                break;
            case 'a':
                if (sscanf(optarg, "%d", &args.angle) != 1)
                {
                    fprintf(stderr, "Error: invalid angle format\n");
                    return INVALID_ARGUMENTS;
                }
                if (args.angle != 90 && args.angle != 180 && args.angle != 270)
                {
                    fprintf(stderr, "Error: invalid angle format\n");
                    return INVALID_ARGUMENTS;
                }
                flags.angle = 1;
                break;
            case 'J':
                flags.binarization = 1;
                args.command = 4;
                break;
            case 'P':
                if (sscanf(optarg, "%d", &args.threshold) != 1)
                {
                    fprintf(stderr, "Error: invalid threshold format\n");
                    return INVALID_ARGUMENTS;
                }
                flags.threshold = 1;
                break;
            case 'K':
                flags.shift = 1;
                args.command = 5;
                break;
            case 'L':
                if (sscanf(optarg, "%d", &args.step) != 1)
                {
                    fprintf(stderr, "Error: invalid step format\n");
                    return INVALID_ARGUMENTS;
                }
                flags.step = 1;
                break;
            case 'M':
                strncpy(args.axis, optarg, 128);
                if (!strcmp(args.axis, "x"))
                {
                    flags.xFlag = 1;
                    args.xFlag = 1;
                }
                else if (!strcmp(args.axis, "y"))
                {
                    flags.yFlag = 1;
                    args.yFlag = 1;
                }
                else if (!strcmp(args.axis, "xy"))
                {
                    flags.xyFlag = 1;
                    args.xyFlag = 1;
                }
                else
                {
                    fprintf(stderr, "Error: invalid axis format\n");
                    return INVALID_ARGUMENTS;
                }
                break;
        }
    }

    if (flags.help == 1)
    {
        return HELP;
    }
    if (flags.info == 1)
    {
        *argsToParse = args;
        return INFO;
    }

    if (optind != argc)
    {
        fprintf(stderr, "Error: invalid count of arguments\n");
        return INVALID_ARGUMENTS;
    }

    if (!flags.input)
    {
        flags.input = 1;
        strcpy(args.inputFile, argv[argc - 1]);
    }
    if (!flags.output)
    {
        flags.output = 1;
        strcpy(args.outputFile, "out.bmp");
    }
    if (strlen(args.inputFile) == 0)
    {
        fprintf(stderr, "Error: missing input file\n");
        return INVALID_ARGUMENTS;
    }
    if (!strcmp(args.inputFile, args.outputFile))
    {
        fprintf(stderr, "Error: input and output files can't be the same");
        return INVALID_ARGUMENTS;
    }
    if (flags.rect + flags.ornament + flags.rotate > 1)
    {
        fprintf(stderr, "Error: only one function can be used\n");
        return INVALID_ARGUMENTS;
    }
    if (flags.rect)
    {
        if (!flags.leftUp || !flags.rightDown || !flags.thickness ||
            !flags.color)
        {
            fprintf(stderr, "Error: missing argumnets for rectangle\n");
            return INVALID_ARGUMENTS;
        }
        else if (flags.fill && !flags.fillColor)
        {
            fprintf(stderr, "Error: missing argumnets for rectangle\n");
            return INVALID_ARGUMENTS;
        }
    }
    else if (flags.ornament)
    {
        if (!flags.pattern || !flags.color || !flags.thickness || !flags.count)
        {
            fprintf(stderr, "Error: missing argumnets for ornament\n");
            return INVALID_ARGUMENTS;
        }
        if (!strcmp(args.pattern, "semicircles") ||
            !strcmp(args.pattern, "rectangle"))
        {
            if (args.thickness <= 0)
            {
                fprintf(stderr, "Error: invalid value for thickness\n");
                return INVALID_ARGUMENTS;
            }
            if (args.count <= 0)
            {
                fprintf(stderr, "Erorr: invalid value for count\n");
                return INVALID_ARGUMENTS;
            }
        }
    }
    else if (flags.rotate)
    {
        if (!flags.leftUp || !flags.rightDown || !flags.angle)
        {
            fprintf(stderr, "Error: missing arguments for rectangle");
            return INVALID_ARGUMENTS;
        }
    }

    *argsToParse = args;

    return 0;
}

StackElement *createStackElement(int x, int y)
{
    StackElement *element = (StackElement *)malloc(sizeof(StackElement));
    element->x = x;
    element->y = y;
    element->next = NULL;

    return element;
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->head = createStackElement(0, 0);
    stack->sizeOfStack = 0;

    return stack;
}

void push(Stack *stack, int x, int y)
{
    if (stack->sizeOfStack == 0)
    {
        stack->head->x = x;
        stack->head->y = y;
    }
    else
    {
        StackElement *elementToPush = createStackElement(x, y);
        elementToPush->next = stack->head;
        stack->head = elementToPush;
    }
    stack->sizeOfStack++;
}

void pop(Stack *stack)
{
    if (stack->sizeOfStack > 1)
    {
        StackElement *temp = stack->head;
        stack->head = temp->next;
        free(temp);
    }

    stack->sizeOfStack--;
}

void clearStack(Stack *stack)
{
    free(stack->head);
}

void freeImage(Rgb **image, int heightOfImage)
{
    for (int y = 0; y < heightOfImage; y++)
    {
        free(image[y]);
    }
    free(image);
}

int readBmp(Rgb ***image, char *fileNameToRead, BitmapFileHeader *bmfh,
            BitmapInfoHeader *bmih)
{
    FILE *f = fopen(fileNameToRead, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Error: file %s doesn't exist\n", fileNameToRead);
        return ERROR_OPEN_FILE;
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmih, 1, sizeof(BitmapInfoHeader), f);
    if (bmfh->signature != 0x4D42)
    {
        fprintf(stderr, "Error: file %s is not a BMP file\n", fileNameToRead);
        fclose(f);
        return NOT_BMP_FILE;
    }
    if (bmih->bitsPerPixel != 24 || bmih->compression != 0)
    {
        fprintf(stderr, "Error: BMP file %s is not supported\n",
                fileNameToRead);
        fclose(f);
        return NOT_SUPPORTED_FILE;
    }
    fseek(f, bmfh->pixelArrOffset, SEEK_SET);

    unsigned int height = bmih->height;
    unsigned int width = bmih->width;
    unsigned int padding = (width * sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;

    *image = malloc(height * sizeof(Rgb *));
    if (image == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return MEMORY_ALLOCATION;
    }
    for (int y = 0; y < height; y++)
    {
        (*image)[height - y - 1] = malloc(width * sizeof(Rgb) + padding);
        if ((*image)[height - y - 1] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            freeImage(*image, y);
            return MEMORY_ALLOCATION;
        }
        fread((*image)[height - y - 1], 1, width * sizeof(Rgb) + padding, f);
    }
    fclose(f);

    return 0;
}

int writeRgb(FILE **f, char *fileNameToWrite, Rgb **image,
             BitmapFileHeader bmfh, BitmapInfoHeader bmih)
{
    *f = fopen(fileNameToWrite, "wb");
    if (*f == NULL)
    {
        fprintf(stderr, "Error: file %s doesn't exist\n", fileNameToWrite);
        return ERROR_OPEN_FILE;
    }
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), *f);
    fwrite(&bmih, 1, sizeof(BitmapInfoHeader), *f);
    fseek(*f, bmfh.pixelArrOffset, SEEK_SET);

    unsigned int height = bmih.height;
    unsigned int width = bmih.width;
    unsigned int padding = (width * sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;

    for (int y = 0; y < height; y++)
    {
        fwrite(image[height - y - 1], 1, width * sizeof(Rgb) + padding, *f);
    }
    fclose(*f);

    return 0;
}

int createEmptyRgb(Rgb ***image, unsigned int height, unsigned int width,
                   int *colorOfPicture)
{
    unsigned int padding = (width * sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;

    *image = malloc(height * sizeof(Rgb *));
    if (image == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return MEMORY_ALLOCATION;
    }
    for (int y = 0; y < height; y++)
    {
        (*image)[height - y - 1] = malloc(width * sizeof(Rgb) + padding);
        if ((*image)[height - y - 1] == NULL)
        {
            fprintf(stderr, "Error: memory allocation failed\n");
            freeImage(*image, y);
            return MEMORY_ALLOCATION;
        }
        for (int x = 0; x < width; x++)
        {
            setPixel(*image, colorOfPicture, x, height - y - 1);
        }
    }

    return 0;
}

int *getPixel(Rgb **image, int x, int y)
{
    int *pixel = (int *)calloc(3, sizeof(int));
    pixel[0] = image[y][x].r;
    pixel[1] = image[y][x].g;
    pixel[2] = image[y][x].b;

    return pixel;
}

void setPixel(Rgb **image, int *newColor, int x, int y)
{
    image[y][x].r = *(newColor);
    image[y][x].g = *(newColor + 1);
    image[y][x].b = *(newColor + 2);
}

int *getInveretedColor(int *colorToInvert, int index)
{
    int *invertedColor = (int *)calloc(3, sizeof(int));
    for (int i = 0; i < 3; i++)
    {
        if (i != index)
        {
            invertedColor[i] = colorToInvert[i];
        }
        else
        {
            invertedColor[i] = 255 - colorToInvert[i];
        }
    }

    return invertedColor;
}

int colorCompare(int *colorWithCompare, int *colorToCompare)
{
    if (colorWithCompare[0] == colorToCompare[0] &&
        colorWithCompare[1] == colorToCompare[1] &&
        colorWithCompare[2] == colorToCompare[2])
    {
        return 1;
    }
    return 0;
}

int deleteEmptyPartsOfLine(int **coords, BitmapInfoHeader bmih, int x0, int y0,
                           int x1, int y1)
{
    const int deltaX = x1 - x0;
    const int deltaY = y1 - y0;
    const int height = bmih.height;
    const int width = bmih.width;

    if (deltaX != 0)
    {
        double k = deltaY / deltaX;
        if (x1 < 0 || x0 > width) return 0;
        if (k > 0 && y1 < 0) return 0;
        if (k < 0 && y0 < 0) return 0;
        if (k > 0 && y0 > height) return 0;
        if (k < 0 && y1 > height) return 0;

        if (k == 0)
        {
            int realValueOfX0 = x0 < 0 ? 0 : x0;
            int realValueOfX1 = x1 > width ? width - 1 : x1;

            (*coords)[0] = realValueOfX0;
            (*coords)[1] = y0;
            (*coords)[2] = realValueOfX1;
            (*coords)[3] = y1;
        }
        else
        {
            (*coords)[0] = x0;
            (*coords)[1] = y0;
            (*coords)[2] = x1;
            (*coords)[3] = y1;
        }
    }
    else
    {
        int realValueOfY0 = y0 < 0 ? 0 : y0;
        int realValueOfY1 = y1 < height ? y1 : height - 1;

        (*coords)[0] = x0;
        (*coords)[1] = realValueOfY0;
        (*coords)[2] = x1;
        (*coords)[3] = realValueOfY1;
    }

    return 1;
}

int isCircleCoverImage(int x0, int y0, int radius, int width, int height)
{
    int upperExtremePoint[] = {x0 > 0 ? 0 : width, height};
    int lowerExtremePoint[] = {x0 > 0 ? 0 : width, 0};
    int distancesToExtremePointsX[] = {abs(upperExtremePoint[0] - x0),
                                       abs(lowerExtremePoint[0] - x0)};
    int distancesToExtremePointsY[] = {abs(upperExtremePoint[1] - y0),
                                       abs(lowerExtremePoint[1] - y0)};

    distancesToExtremePointsX[0] *= distancesToExtremePointsX[0];
    distancesToExtremePointsX[1] *= distancesToExtremePointsX[1];
    distancesToExtremePointsY[0] *= distancesToExtremePointsY[0];
    distancesToExtremePointsY[1] *= distancesToExtremePointsY[1];
    radius *= radius;

    unsigned int distancesToExtremePoints[] = {
        distancesToExtremePointsX[0] + distancesToExtremePointsY[0],
        distancesToExtremePointsX[1] + distancesToExtremePointsY[1]};

    if (distancesToExtremePoints[0] <= radius &&
        distancesToExtremePoints[1] <= radius)
    {
        return 1;
    }
    return 0;
}

int rotatePartOfImage(Rgb **image, BitmapInfoHeader bmih, int x0, int y0,
                      int x1, int y1, int angleOfRotation)
{
    int tempX0 = MIN(x0, x1);
    int tempX1 = MAX(x0, x1);
    int tempY0 = MIN(y0, y1);
    int tempY1 = MAX(y0, y1);

    x0 = tempX0;
    x1 = tempX1;
    y0 = tempY0;
    y1 = tempY1;

    const int width = bmih.width;
    const int height = bmih.height;

    if (x1 == width) x1--;
    if (y1 == height) y1--;
    if (!isInImage(width, height, x0, y0)) return INVALID_ARGUMENTS;
    if (!isInImage(width, height, x1, y1)) return INVALID_ARGUMENTS;

    int *centralPoint = (int *)calloc(2, sizeof(int));
    centralPoint[0] = (x1 + x0) / 2;
    centralPoint[1] = (y1 + y0) / 2;

    Rgb **copiedAreaToRotate = copyArea(image, width, height, x0, y0, x1, y1);
    int widthOfCopiedArea = x1 - x0;
    int heightOfCopiedArea = y1 - y0;

    int widthOfRotatedPart = widthOfCopiedArea;
    int heightOfRotatedPart = heightOfCopiedArea;
    if (angleOfRotation != 180)
    {
        widthOfRotatedPart = heightOfCopiedArea;
        heightOfRotatedPart = widthOfCopiedArea;
    }

    int *nullColor = (int *)calloc(3, sizeof(int));
    Rgb **rotatedPart;
    int check = createEmptyRgb(&rotatedPart, heightOfRotatedPart,
                               widthOfRotatedPart, nullColor);
    if (check) return check;
    for (int y = 0; y < heightOfCopiedArea; y++)
    {
        for (int x = 0; x < widthOfCopiedArea; x++)
        {
            int *pixelToSet = getPixel(copiedAreaToRotate, x, y);
            switch (angleOfRotation)
            {
                case 90:
                    setPixel(rotatedPart, pixelToSet, y,
                             widthOfCopiedArea - 1 - x);
                    break;
                case 180:
                    setPixel(rotatedPart, pixelToSet, widthOfCopiedArea - 1 - x,
                             heightOfCopiedArea - 1 - y);
                    break;
                case 270:
                    setPixel(rotatedPart, pixelToSet,
                             heightOfCopiedArea - 1 - y, x);
                    break;
            }
            free(pixelToSet);
        }
    }
    pasteArea(image, rotatedPart, heightOfRotatedPart, widthOfRotatedPart,
              width, height, NULL, centralPoint[0] - widthOfRotatedPart / 2,
              centralPoint[1] - heightOfRotatedPart / 2);

    free(centralPoint);
    freeImage(rotatedPart, heightOfRotatedPart);
    freeImage(copiedAreaToRotate, heightOfCopiedArea);
    free(nullColor);

    return 0;
}

int isInImage(int widthOfImage, int heightOfImage, int xToCheck, int yToCheck)
{
    if (xToCheck >= 0 && xToCheck < widthOfImage && yToCheck >= 0 &&
        yToCheck < heightOfImage)
    {
        return 1;
    }
    return 0;
}

int isInside(Rgb **image, int width, int height, int *colorToFill, int x, int y)
{
    if (!isInImage(width, height, x, y))
    {
        return 0;
    }
    int *pixel = getPixel(image, x, y);
    if (colorCompare(pixel, colorToFill))
    {
        free(pixel);
        return 0;
    }

    free(pixel);
    return 1;
}

void fill(Rgb **image, int width, int height, int *colorToFill, int x, int y)
{
    Stack *stack = createStack();
    if (!isInside(image, width, height, colorToFill, x, y))
    {
        clearStack(stack);
        return;
    }
    push(stack, x, y);
    while (stack->sizeOfStack != 0)
    {
        x = stack->head->x;
        y = stack->head->y;
        pop(stack);

        if (isInside(image, width, height, colorToFill, x, y))
        {
            setPixel(image, colorToFill, x, y);
            if (isInside(image, width, height, colorToFill, x - 1, y))
            {
                push(stack, x - 1, y);
            }
            if (isInside(image, width, height, colorToFill, x + 1, y))
            {
                push(stack, x + 1, y);
            }
            if (isInside(image, width, height, colorToFill, x, y - 1))
            {
                push(stack, x, y - 1);
            }
            if (isInside(image, width, height, colorToFill, x, y + 1))
            {
                push(stack, x, y + 1);
            }
        }
    }

    clearStack(stack);
}

void pasteArea(Rgb **image, Rgb **areaToPaste, int heightOfAreaToPaste,
               int widthOfAreaToPaste, int width, int height,
               int *invertedColor, int x0, int y0)
{
    for (int y = y0; y < y0 + heightOfAreaToPaste; y++)
    {
        for (int x = x0; x < x0 + widthOfAreaToPaste; x++)
        {
            if (x > width)
            {
                break;
            }
            else if (y > height)
            {
                return;
            }
            else if (isInImage(widthOfAreaToPaste, heightOfAreaToPaste, x - x0,
                               y - y0) &&
                     isInImage(width, height, x, y))
            {
                int *pixel = getPixel(areaToPaste, x - x0, y - y0);
                if (invertedColor != NULL && colorCompare(pixel, invertedColor))
                {
                    free(pixel);
                    continue;
                }
                setPixel(image, pixel, x, y);
                free(pixel);
            }
        }
    }
}

Rgb **copyArea(Rgb **image, int widthOfImage, int heightOfImage, int x0, int y0,
               int x1, int y1)
{
    int stratY = y0 > 0 ? y0 : 0;
    int startX = x0 > 0 ? x0 : 0;
    int endY = y1 > heightOfImage ? heightOfImage : y1;
    int endX = x1 > widthOfImage ? widthOfImage : x1;

    int *nullColor = (int *)calloc(3, sizeof(int));
    Rgb **areaToCopy;
    createEmptyRgb(&areaToCopy, y1 - y0, x1 - x0, nullColor);
    for (int y = stratY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            int *pixel = getPixel(image, x, y);
            if (pixel != NULL)
            {
                setPixel(areaToCopy, pixel, x - startX, y - stratY);
            }
            free(pixel);
        }
    }

    free(nullColor);
    return areaToCopy;
}

int MIN(int a, int b)
{
    int c = a;
    if (a > b)
    {
        c = b;
    }

    return c;
}

int MAX(int a, int b)
{
    int c = a;
    if (a < b)
    {
        c = b;
    }

    return c;
}

void dyeImageIntoNewColor(Rgb **image, int width, int height, int *colorToFill)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            setPixel(image, colorToFill, x, y);
        }
    }
}

void drawLine(Rgb **image, BitmapInfoHeader bmih, int x0, int y0, int x1,
              int y1, int *color)
{
    int tempX0 = MIN(x0, x1);
    int tempX1 = MAX(x0, x1);
    int tempY0 = MIN(y0, y1);
    int tempY1 = MAX(y0, y1);

    x0 = tempX0;
    x1 = tempX1;
    y0 = tempY0;
    y1 = tempY1;

    int *coords = (int *)malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++)
    {
        coords[i] = -1;
    }
    if (deleteEmptyPartsOfLine(&coords, bmih, x0, y0, x1, y1) == 1)
    {
        const int deltaX = coords[2] - coords[0];
        const int deltaY = coords[3] - coords[1];
        const int absDeltaX = abs(deltaX);
        const int absDeltaY = abs(deltaY);
        const int height = bmih.height;
        const int width = bmih.width;
        int accretion = 0;

        if (absDeltaX >= absDeltaY)
        {
            int y = coords[1];
            const int direction = deltaY != 0 ? (deltaY > 0 ? 1 : -1) : 0;

            for (int x = coords[0];
                 coords[2] + 1 > width ? x < width : x < coords[2] + 1; x++)
            {
                if (isInImage(width, height, x, y))
                {
                    setPixel(image, color, x, y);
                }
                accretion += absDeltaY;

                if (accretion >= absDeltaX)
                {
                    accretion -= absDeltaX;
                    y += direction;
                }
            }
        }
        else
        {
            int x = coords[0];
            const int direction = deltaX != 0 ? (deltaX > 0 ? 1 : -1) : 0;

            for (int y = coords[1];
                 coords[3] + 1 > height ? y < height : y < coords[3] + 1; y++)
            {
                if (isInImage(width, height, x, y))
                {
                    setPixel(image, color, x, y);
                }
                accretion += absDeltaX;

                if (accretion >= absDeltaY)
                {
                    accretion -= absDeltaY;
                    x += direction;
                }
            }
        }
    }
    free(coords);
}

void drawLineWithThicknessForVerticalHorizontal(Rgb **image,
                                                BitmapInfoHeader bmih, int x0,
                                                int y0, int x1, int y1,
                                                int thickness, int *color)
{
    const int absDeltaX = abs(x1 - x0);

    if (thickness % 2 == 1)
    {
        if (absDeltaX == 0)
        {
            for (int i = -(thickness / 2); i < (thickness / 2) + 1; i++)
            {
                drawLine(image, bmih, x0 + i, y0, x1 + i, y1, color);
            }
        }
        else
        {
            for (int i = -(thickness / 2); i < (thickness / 2) + 1; i++)
            {
                drawLine(image, bmih, x0, y0 + i, x1, y1 + i, color);
            }
        }
    }
    else
    {
        if (absDeltaX == 0)
        {
            for (int i = -(thickness / 2) + 1; i < (thickness / 2) + 1; i++)
            {
                drawLine(image, bmih, x0 + i, y0, x1 + i, y1, color);
            }
        }
        else
        {
            for (int i = -(thickness / 2) + 1; i < (thickness / 2) + 1; i++)
            {
                drawLine(image, bmih, x0, y0 + i, x1, y1 + i, color);
            }
        }
    }
}

void drawLineWithThicknessForRectangle(Rgb **image, BitmapInfoHeader bmih,
                                       int x0, int y0, int x1, int y1,
                                       int thickness, int *color)
{
    for (int i = (-thickness / 2); i < (thickness / 2) + 1; i++)
    {
        if (abs(x1 - x0) == 0)
        {
            drawLine(image, bmih, x0 + i, y0, x1 + i, y1, color);
        }
        else
        {
            drawLine(image, bmih, x0, y0 + i, x1, y1 + i, color);
        }
    }
}

void drawRectangle(Rgb **image, BitmapInfoHeader bmih, int x0, int y0, int x1,
                   int y1, int thickness, int isFill, int *borderColor,
                   int *colorToFill)
{
    int tempX0 = MIN(x0, x1);
    int tempX1 = MAX(x0, x1);
    int tempY0 = MIN(y0, y1);
    int tempY1 = MAX(y0, y1);

    x0 = tempX0;
    x1 = tempX1;
    y0 = tempY0;
    y1 = tempY1;

    const int height = bmih.height;
    const int width = bmih.width;

    if (isInImage(width, height, x0 + thickness / 2, y0 + thickness / 2) ||
        isInImage(width, height, x0 - thickness / 2, y0 - thickness / 2) ||
        isInImage(width, height, x0 - thickness / 2, y0 + thickness / 2) ||
        isInImage(width, height, x0 + thickness / 2, y0 - thickness / 2))
    {
        drawRound(image, width, height, x0, y0, thickness / 2, borderColor);
    }
    if (isInImage(width, height, x1 - thickness / 2, y1 - thickness / 2) ||
        isInImage(width, height, x1 + thickness / 2, y1 + thickness / 2) ||
        isInImage(width, height, x1 - thickness / 2, y1 + thickness / 2) ||
        isInImage(width, height, x1 + thickness / 2, y1 - thickness / 2))
    {
        drawRound(image, width, height, x1, y1, thickness / 2, borderColor);
    }
    if (isInImage(width, height, x0 + thickness / 2, y1 + thickness / 2) ||
        isInImage(width, height, x0 - thickness / 2, y1 - thickness / 2) ||
        isInImage(width, height, x0 - thickness / 2, y1 + thickness / 2) ||
        isInImage(width, height, x0 + thickness / 2, y1 - thickness / 2))
    {
        drawRound(image, width, height, x0, y1, thickness / 2, borderColor);
    }
    if (isInImage(width, height, x1 - thickness / 2, y0 - thickness / 2) ||
        isInImage(width, height, x1 + thickness / 2, y0 + thickness / 2) ||
        isInImage(width, height, x1 - thickness / 2, y0 + thickness / 2) ||
        isInImage(width, height, x1 + thickness / 2, y0 - thickness / 2))
    {
        drawRound(image, width, height, x1, y0, thickness / 2, borderColor);
    }

    drawLineWithThicknessForRectangle(image, bmih, x0, y0, x1, y0, thickness,
                                      borderColor);
    drawLineWithThicknessForRectangle(image, bmih, x0, y1, x1, y1, thickness,
                                      borderColor);
    drawLineWithThicknessForRectangle(image, bmih, x0, y0, x0, y1, thickness,
                                      borderColor);
    drawLineWithThicknessForRectangle(image, bmih, x1, y0, x1, y1, thickness,
                                      borderColor);

    if (isFill)
    {
        int minY = y0 + thickness / 2 + 1 > 0 ? y0 + thickness / 2 + 1 : 0;
        int maxY = y1 - thickness / 2 > height ? height : y1 - thickness / 2;
        int minX = x0 + thickness / 2 + 1 > 0 ? x0 + thickness / 2 + 1 : 0;
        int maxX = x1 - thickness / 2 > width ? width : x1 - thickness / 2;

        for (int y = minY; y < maxY; y++)
        {
            for (int x = minX; x < maxX; x++)
            {
                setPixel(image, colorToFill, x, y);
            }
        }
    }
}

void drawRectangleForPattern(Rgb **image, BitmapInfoHeader bmih, int x0, int y0,
                             int x1, int y1, int thickness, int *borderColor)
{
    int tempX0 = MIN(x0, x1);
    int tempX1 = MAX(x0, x1);
    int tempY0 = MIN(y0, y1);
    int tempY1 = MAX(y0, y1);

    x0 = tempX0;
    x1 = tempX1;
    y0 = tempY0;
    y1 = tempY1;

    if (thickness % 2 == 1)
    {
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x0, y0 - thickness / 2, x0, y1 + thickness / 2,
            thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(image, bmih, x0, y0, x1, y0,
                                                   thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x1, y0 - thickness / 2, x1, y1 + thickness / 2,
            thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(image, bmih, x0, y1, x1, y1,
                                                   thickness, borderColor);
    }
    else
    {
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x0 - 1, y0 - thickness / 2, x0 - 1,
            y1 + thickness / 2 - 1, thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x0, y0 - 1, x1, y0 - 1, thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x1 - 1, y0 - thickness / 2, x1 - 1,
            y1 + thickness / 2 - 1, thickness, borderColor);
        drawLineWithThicknessForVerticalHorizontal(
            image, bmih, x0, y1 - 1, x1, y1 - 1, thickness, borderColor);
    }
}

void drawCircle(Rgb **image, int widthOfImage, int heightOfImage, int x0,
                int y0, int radius, int *borderColor)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y)
    {
        if (isInImage(widthOfImage, heightOfImage, x + x0, y + y0))
        {
            setPixel(image, borderColor, x + x0, y + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, y + x0, x + y0))
        {
            setPixel(image, borderColor, y + x0, x + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, -x + x0, y + y0))
        {
            setPixel(image, borderColor, -x + x0, y + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, -y + x0, x + y0))
        {
            setPixel(image, borderColor, -y + x0, x + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, -x + x0, -y + y0))
        {
            setPixel(image, borderColor, -x + x0, -y + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, -y + x0, -x + y0))
        {
            setPixel(image, borderColor, -y + x0, -x + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, x + x0, -y + y0))
        {
            setPixel(image, borderColor, x + x0, -y + y0);
        }
        if (isInImage(widthOfImage, heightOfImage, y + x0, -x + y0))
        {
            setPixel(image, borderColor, y + x0, -x + y0);
        }
        y++;

        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void drawCircleWithThickness(Rgb **image, int widthOfImage, int heightOfImage,
                             int x0, int y0, int radius, int thickness,
                             int *borderColor)
{
    if (isCircleCoverImage(x0, y0, radius - thickness / 2, widthOfImage,
                           heightOfImage))
    {
        return;
    }
    if (thickness > 1 && thickness < 4)
    {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;
        while (x >= y)
        {
            drawRound(image, widthOfImage, heightOfImage, x + x0, y + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, y + x0, x + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, -x + x0, y + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, -y + x0, x + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, -x + x0, -y + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, -y + x0, -x + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, x + x0, -y + y0,
                      thickness / 2, borderColor);
            drawRound(image, widthOfImage, heightOfImage, y + x0, -x + y0,
                      thickness / 2, borderColor);
            y++;

            if (radiusError < 0)
            {
                radiusError += 2 * y + 1;
            }
            else
            {
                x--;
                radiusError += 2 * (y - x + 1);
            }
        }
    }
    else
    {
        int *invertedColor = getInveretedColor(borderColor, 1);
        unsigned int height = 2 * (radius + (thickness / 2)) + 1;
        unsigned int width = 2 * (radius + (thickness / 2)) + 1;
        Rgb **tempImage;
        createEmptyRgb(&tempImage, height, width, invertedColor);

        drawCircle(tempImage, width, height, width / 2, height / 2,
                   radius + (thickness / 2), borderColor);
        drawCircle(tempImage, width, height, width / 2, height / 2,
                   radius - (thickness / 2), borderColor);
        fill(tempImage, width, height, borderColor, width / 2,
             (height / 2) + radius);
        pasteArea(image, tempImage, height, width, widthOfImage, heightOfImage,
                  invertedColor, x0 - radius - thickness / 2,
                  y0 - radius - thickness / 2);
        freeImage(tempImage, height);
        free(invertedColor);
    }
}

void drawRound(Rgb **image, int widthOfImage, int heightOfImage, int x0, int y0,
               int radius, int *colorToFill)
{
    if (isCircleCoverImage(x0, y0, radius, widthOfImage, heightOfImage))
    {
        dyeImageIntoNewColor(image, widthOfImage, heightOfImage, colorToFill);
    }
    else
    {
        int *invertedColor = getInveretedColor(colorToFill, 1);
        unsigned int height = 2 * radius + 1;
        unsigned int width = 2 * radius + 1;
        Rgb **tempImage;
        createEmptyRgb(&tempImage, height, width, invertedColor);

        drawCircle(tempImage, width, height, radius, radius, radius,
                   colorToFill);
        fill(tempImage, width, height, colorToFill, radius, radius);
        pasteArea(image, tempImage, height, width, widthOfImage, heightOfImage,
                  invertedColor, x0 - radius, y0 - radius);

        freeImage(tempImage, height);
        free(invertedColor);
    }
}

void drawRectangleAsPattern(Rgb **image, BitmapInfoHeader bmih, int thickness,
                            int count, int *colorOfPattern)
{
    unsigned int height = bmih.height;
    unsigned int width = bmih.width;
    int index = 0;
    int x0 = thickness / 2;
    int y0 = thickness / 2;
    int x1 =
        thickness % 2 == 0 ? width - thickness / 2 : width - thickness / 2 - 1;
    int y1 = thickness % 2 == 0 ? height - thickness / 2
                                : height - thickness / 2 - 1;

    int widthOfSpan = 2 * thickness;

    while (index != count)
    {
        drawRectangleForPattern(image, bmih, x0, y0, x1, y1, thickness,
                                colorOfPattern);
        index++;
        x0 += widthOfSpan;
        y0 += widthOfSpan;
        x1 -= widthOfSpan;
        y1 -= widthOfSpan;
        if (x0 > width / 2 || y0 > height / 2) return;
    }
}

void drawCentralCircleAsPattern(Rgb **image, BitmapInfoHeader bmih,
                                int *colorOfPattern)
{
    unsigned int width = bmih.width;
    unsigned int height = bmih.height;

    unsigned int x0 = width / 2;
    unsigned int y0 = height / 2;
    unsigned int radius = width > height ? y0 + 1 : x0 + 1;

    drawCircle(image, width, height, x0, y0, radius, colorOfPattern);
    fill(image, width, height, colorOfPattern, 0, 0);
    fill(image, width, height, colorOfPattern, width - 1, height - 1);
    fill(image, width, height, colorOfPattern, 0, height - 1);
    fill(image, width, height, colorOfPattern, width - 1, 0);
}

void drawSemiciclesAsPattern(Rgb **image, BitmapInfoHeader bmih, int thickness,
                             int count, int *colorOfPattern)
{
    unsigned int width = bmih.width;
    unsigned int height = bmih.height;

    unsigned int radiusForHorizontal = width % (2 * count) == 0
                                           ? width / (2 * count)
                                           : width / (2 * count) + 1;
    unsigned int radiusForVertical = height % (2 * count) == 0
                                         ? height / (2 * count)
                                         : height / (2 * count) + 1;

    unsigned int widthForHorizontal =
        2 * (radiusForHorizontal + thickness / 2) + 1;
    unsigned int heigthForHorizontal =
        2 * (radiusForHorizontal + thickness / 2) + 1;
    unsigned int widthForVertical = 2 * (radiusForVertical + thickness / 2) + 1;
    unsigned int heigthForVertical =
        2 * (radiusForVertical + thickness / 2) + 1;
    int *inveretedColor = getInveretedColor(colorOfPattern, 0);

    int x0ForHorizontal = radiusForHorizontal + thickness / 2;
    int y0ForHorizontal = radiusForHorizontal + thickness / 2;
    int x0ForVertical = radiusForVertical + thickness / 2;
    int y0ForVertical = radiusForVertical + thickness / 2;

    Rgb **circleForHorizontal;
    createEmptyRgb(&circleForHorizontal, heigthForHorizontal,
                   widthForHorizontal, inveretedColor);
    drawCircleWithThickness(circleForHorizontal, widthForHorizontal,
                            heigthForHorizontal, x0ForHorizontal,
                            y0ForHorizontal, radiusForHorizontal, thickness,
                            colorOfPattern);

    Rgb **circleForVertical;
    createEmptyRgb(&circleForVertical, heigthForVertical, widthForVertical,
                   inveretedColor);
    drawCircleWithThickness(circleForVertical, widthForVertical,
                            heigthForVertical, x0ForVertical, y0ForVertical,
                            radiusForVertical, thickness, colorOfPattern);

    for (int i = 1; i < 2 * count + 1; i += 2)
    {
        pasteArea(image, circleForHorizontal, heigthForHorizontal,
                  widthForHorizontal, width, height, inveretedColor,
                  i * radiusForHorizontal - x0ForHorizontal,
                  height - y0ForHorizontal);
        pasteArea(image, circleForHorizontal, heigthForHorizontal,
                  widthForHorizontal, width, height, inveretedColor,
                  i * radiusForHorizontal - x0ForHorizontal, -y0ForHorizontal);
        pasteArea(image, circleForVertical, heigthForVertical, widthForVertical,
                  width, height, inveretedColor, width - x0ForVertical,
                  i * radiusForVertical - y0ForVertical);
        pasteArea(image, circleForVertical, heigthForVertical, widthForVertical,
                  width, height, inveretedColor, -x0ForVertical,
                  i * radiusForVertical - y0ForVertical);
    }

    freeImage(circleForHorizontal, heigthForHorizontal);
    freeImage(circleForVertical, heigthForVertical);
}

void binarizateImage(Rgb **image, BitmapInfoHeader bmih, int threshold)
{
    const int height = bmih.height;
    const int width = bmih.width;

    int whiteColor[3] = {255, 255, 255};
    int blackColor[3] = {0, 0, 0};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int *pixelToCheck = getPixel(image, x, y);
            if (pixelToCheck[0] + pixelToCheck[1] + pixelToCheck[2] >=
                threshold)
            {
                setPixel(image, whiteColor, x, y);
            }
            else
            {
                setPixel(image, blackColor, x, y);
            }
            free(pixelToCheck);
        }
    }
}

void shiftTheImage(Rgb **image, BitmapInfoHeader bmih, int step, int xFlag,
                   int yFlag, int xyFlag)
{
    const int width = bmih.width;
    const int height = bmih.height;

    Rgb **copyImage = copyArea(image, width, height, 0, 0, width, height);
    if (xFlag)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int *pixelToGetMoves = (int *)calloc(3, sizeof(int));
                if (isInImage(width, height, x + step, y))
                {
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, x + step, y);
                }
                else
                {
                    int newCoordForX = (x + step) % width;
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, newCoordForX, y);
                }
                free(pixelToGetMoves);
            }
        }
    }
    else if (yFlag)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                int *pixelToGetMoves = (int *)calloc(3, sizeof(int));
                if (isInImage(width, height, x, y + step))
                {
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, x, y + step);
                }
                else
                {
                    int newCoordForY = (y + step) % height;
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, x, newCoordForY);
                }
                free(pixelToGetMoves);
            }
        }
    }
    else if (xyFlag)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int *pixelToGetMoves = (int *)calloc(3, sizeof(int));
                if (isInImage(width, height, x + step, y + step))
                {
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, x + step, y + step);
                }
                else
                {
                    int newCoordForX = (x + step) % width;
                    int newCoordForY = (y + step) % height;
                    pixelToGetMoves = getPixel(copyImage, x, y);
                    setPixel(image, pixelToGetMoves, newCoordForX,
                             newCoordForY);
                }
                free(pixelToGetMoves);
            }
        }
    }

    freeImage(copyImage, height);
}
