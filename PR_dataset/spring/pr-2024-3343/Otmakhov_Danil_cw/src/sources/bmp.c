#include "bmp.h"
#include "errors.h"


void checkBMPFileFormat(BitmapFileHeader bmfhdr)
{
    if (bmfhdr.signature != 0x4D42) {
        raiseError(incorrect_file_format, ERROR_INCORRECT_FILE_FORMAT);
    }
}


void printFileHeader(BitmapFileHeader header)
{
    printf("  signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("  filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("  reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("  reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("  pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header)
{
    printf("  headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("  width: \t%x (%u)\n", header.width, header.width);
    printf("  height: \t%x (%u)\n", header.height, header.height);
    printf("  planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("  bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("  compression:\t%x (%u)\n", header.compression, header.compression);
    printf("  imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("  xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("  yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("  colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("  importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void printBMPFileInfo(BMP* bmp_file)
{
    printf("File %s:\n", bmp_file->fileName);
    printFileHeader(bmp_file->bmfhdr);
    printInfoHeader(bmp_file->bmihdr);
}


BMP* readBMPFile(char file_name[])
{
    FILE* file = fopen(file_name, "rb");
    if (!file)
        raiseError(can_not_read_the_file, ERROR_FILE_READ_FAILURE);
    BMP* bmp_file = (BMP*)malloc(sizeof(BMP));
    bmp_file->fileName = file_name;
    fread(&bmp_file->bmfhdr, 1, sizeof(BitmapFileHeader), file);
    checkBMPFileFormat(bmp_file->bmfhdr);
    fread(&bmp_file->bmihdr, 1, sizeof(BitmapInfoHeader), file);
    unsigned int H = bmp_file->bmihdr.height;
    unsigned int W = bmp_file->bmihdr.width;
    bmp_file->pixel_array = (RGB**)malloc(sizeof(RGB*) * H);
    for (int i = 0; i < H; i++) {
        bmp_file->pixel_array[i] = (RGB*)malloc(sizeof(RGB) * W + (4 - (sizeof(RGB) * W) % 4) % 4);
        fread(bmp_file->pixel_array[i], 1, sizeof(RGB) * W + (4 - (sizeof(RGB) * W) % 4) % 4, file);
    }
    fclose(file);
    return bmp_file;
}


bool compareColor(RGB first_color, RGB second_color)
{
    if (first_color.r == second_color.r && first_color.g == second_color.g && first_color.b == second_color.b)
        return true;
    return false;
}


void setColor(BMP* bmp_file, int x, int y, RGB new_color)
{
    if (x < 0 || x >= bmp_file->bmihdr.width || y < 0 || y >= bmp_file->bmihdr.height)
        return;

    bmp_file->pixel_array[y][x].r = new_color.r;
    bmp_file->pixel_array[y][x].g = new_color.g;
    bmp_file->pixel_array[y][x].b = new_color.b;
}


void colorReplace(BMP* bmp_file, CommandLineOptions* options)
{
    RGB old_color = convertStringToRGB(options->oldColor);
    RGB new_color = convertStringToRGB(options->newColor);

    unsigned int W = bmp_file->bmihdr.width;
    unsigned int H = bmp_file->bmihdr.height;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (compareColor(bmp_file->pixel_array[y][x], old_color)) {
                setColor(bmp_file, x, y, new_color);
            }
        }
    }
}


void rgbFilter(BMP* bmp_file, CommandLineOptions* options)
{
    if (strcmp(options->componentName, "red") && strcmp(options->componentName, "green") && strcmp(options->componentName, "blue"))
        raiseError(invalid_rgb_component_name, ERROR_INVALID_ARGUMENT);

    if (options->componentValue < 0 || options->componentValue > 255)
        raiseError(invalid_rgb_component_value, ERROR_INVALID_ARGUMENT);

    unsigned int H = bmp_file->bmihdr.height;
    unsigned int W = bmp_file->bmihdr.width;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (strcmp(options->componentName, "red") == 0) {
                bmp_file->pixel_array[y][x].r = options->componentValue;
            }
            else if (strcmp(options->componentName, "green") == 0) {
                bmp_file->pixel_array[y][x].g = options->componentValue;
            }
            else if (strcmp(options->componentName, "blue") == 0) {
                bmp_file->pixel_array[y][x].b = options->componentValue;
            }
        }
    }
}


void split(BMP* bmp_file, CommandLineOptions* options)
{
    unsigned int W = bmp_file->bmihdr.width;
    unsigned int H = bmp_file->bmihdr.height;

    if (options->numberX <= 1 || options->numberX > W || options->numberY <= 1 || options->numberY > H)
        raiseError(invalid_parts_number, ERROR_INVALID_ARGUMENT);

    RGB color = convertStringToRGB(options->color);

    if (options->thickness <= 0)
        raiseError(invalid_thickness, ERROR_INVALID_ARGUMENT);

    unsigned int step_x = W / options->numberY;
    unsigned int step_y = H / options->numberX;

    for (int x = 0 + step_x; x < W; x += step_x) {
        for (int y = H - 1; y >= 0; y--) {
            for (int i = 0; i < options->thickness; i++)
                setColor(bmp_file, x + i, y, color);
        }
    }

    for (int y = H - 1 - step_y; y >= 0; y -= step_y) {
        for (int x = 0; x < W; x++) {
            for (int j = 0; j < options->thickness; j++)
                setColor(bmp_file, x, y - j, color);
        }
    }
}

/*
void swapInt(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


RGB** copy(BMP* bmp_file, int x0, int y0, int x1, int y1)
{
    unsigned int H = bmp_file->bmihdr.height;
    unsigned int W = bmp_file->bmihdr.width;

    if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 || x0 > W || y0 > H || x1 > W || y1 > H)
        exit(0);

    RGB** buf = (RGB**)malloc(sizeof(RGB*) * (y1 - y0 + 1));
    for (int i = 0; i < y1 - y0 + 1; i++)
        buf[i] = (RGB*)malloc(sizeof(RGB) * (x1 - x0 + 1));

    y0 = H - y0 - 1;
    y1 = H - y1 - 1;

    swapInt(&y0, &y1);

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            buf[y - y0][x - x0] = bmp_file->pixel_array[y][x];
        }
    }

    return buf;
}

void paste(BMP* bmp_file, int x0, int y0, RGB** buf, int buf_h, int buf_w)
{
    y0 = bmp_file->bmihdr.height - y0 - buf_h;

    for (int x = 0; x < buf_w; x++) {
        for (int y = 0; y < buf_h; y++) {
            setColor(bmp_file, x0 + x, y0 + y, buf[y][x]);
        }
    }
}


void shift(BMP* bmp_file, CommandLineOptions* options)
{
    if (options->step < 0)
        raiseError(invalid_axis, ERROR_INVALID_ARGUMENT);

    if (!strcmp(options->axis, "x") && !strcmp(options->axis, "y") && !strcmp(options->axis, "xy"))
        raiseError(invalid_axis, ERROR_INVALID_ARGUMENT);

    unsigned int H = bmp_file->bmihdr.height;
    unsigned int W = bmp_file->bmihdr.width;

    if (strcmp(options->axis, "x")) {
        if (options->step > W)
            raiseError(invalid_axis, ERROR_INVALID_ARGUMENT);

        RGB** buf_left = copy(bmp_file, 0, 0, options->step - 1, H - 1);
        RGB** buf_right = copy(bmp_file, options->step, 0, W - 1, H - 1);

        paste(bmp_file, 0, 0, buf_right, H, W - options->step);
        paste(bmp_file, W - options->step, 0, buf_left, H, options->step);
    } else if (strcmp(options->axis, "y")) {
        if (options->step > H)
            raiseError(invalid_axis, ERROR_INVALID_ARGUMENT);

        RGB** buf_up = copy(bmp_file, 0, 0, W - 1, H - options->step - 1);
        RGB** buf_down = copy(bmp_file, 0, H - options->step, W - 1, H - 1);

        paste(bmp_file, 0, 0, buf_down, options->step, W);
        paste(bmp_file, 0, options->step, buf_up, H - options->step, W);
    } else {
        if (options->step > H || options->step > W)
            raiseError(invalid_axis, ERROR_INVALID_ARGUMENT);

        RGB** buf_1 = copy(bmp_file, 0, 0, W - options->step - 1, H - options->step - 1);
        RGB** buf_2 = copy(bmp_file, W - options->step, H - options->step, W - 1, H - 1);
        RGB** buf_3 = copy(bmp_file, 0, options->step, options->step - 1, H - 1);
        RGB** buf_4 = copy(bmp_file, options->step, 0, W - 1, options->step - 1);

        paste(bmp_file, 0, 0, buf_1, H - options->step, W - options->step);
*/




void binarization(BMP* bmp_file, CommandLineOptions* options)
{
    if (options->threshold <= 0)
        raiseError(invalid_threshold, ERROR_INVALID_ARGUMENT);

    unsigned int W = bmp_file->bmihdr.width;
    unsigned int H = bmp_file->bmihdr.height;

    RGB white_color = {255, 255, 255};
    RGB black_color = {0, 0, 0};

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (bmp_file->pixel_array[y][x].r + bmp_file->pixel_array[y][x].g + bmp_file->pixel_array[y][x].b >= options->threshold)
                setColor(bmp_file, x, y, white_color);
            else
                setColor(bmp_file, x, y, black_color);
        }
    }
}



void writeBMPFile(char file_name[], BMP* bmp_file)
{
    FILE* file = fopen(file_name, "wb");
    if (!file)
        raiseError(can_not_write_to_the_file, ERROR_FILE_WRITE_FAILURE);
    fwrite(&bmp_file->bmfhdr, 1, sizeof(BitmapFileHeader), file);
    fwrite(&bmp_file->bmihdr, 1, sizeof(BitmapInfoHeader), file);
    unsigned int H = bmp_file->bmihdr.height;
    unsigned int W = bmp_file->bmihdr.width;
    for (int i = 0; i < H; i++)
        fwrite(bmp_file->pixel_array[i], 1, sizeof(RGB) * W + (4 - (sizeof(RGB) * W) % 4) % 4, file);
    fclose(file);
}


void freeBMPFile(BMP* bmp_file)
{
    if(bmp_file) {
        if(bmp_file->pixel_array) {
            for (int i = 0; i < bmp_file->bmihdr.height; i++)
                free(bmp_file->pixel_array[i]);
            free(bmp_file->pixel_array);
        }
    free(bmp_file);
    }
}
