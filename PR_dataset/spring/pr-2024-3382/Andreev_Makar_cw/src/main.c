#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <math.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsInColorTable;
    uint32_t importantColorCount;
} BitmapInfoHeader;

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} RGB;
#pragma pack(pop)

typedef struct {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    RGB *pixels;
} BitmapImage;

int readBMP(BitmapImage *image, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 0;
    }

    fread(&image->fileHeader, sizeof(BitmapFileHeader), 1, file);
    if (image->fileHeader.signature != 0x4D42) {
        fprintf(stderr, "Error: Invalid BMP file\n");
        fclose(file);
        return 0;
    }

    fread(&image->infoHeader, sizeof(BitmapInfoHeader), 1, file);

    fseek(file, image->fileHeader.pixelArrOffset, SEEK_SET);

    int width = image->infoHeader.width;
    int height = abs(image->infoHeader.height);
    int padding = (4 - (width * sizeof(RGB)) % 4) % 4;

    image->pixels = (RGB *)malloc(width * height * sizeof(RGB));
    if (!image->pixels) {
        fprintf(stderr, "Error: Could not allocate memory for pixels\n");
        fclose(file);
        return 0;
    }

    for (int y = 0; y < height; ++y) {
        fread(image->pixels + y * width, sizeof(RGB), width, file);
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return 1;
}

void writeBMP(BitmapImage *image, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        return;
    }

    fwrite(&image->fileHeader, sizeof(BitmapFileHeader), 1, file);
    fwrite(&image->infoHeader, sizeof(BitmapInfoHeader), 1, file);

    int width = image->infoHeader.width;
    int height = abs(image->infoHeader.height);
    int padding = (4 - (width * sizeof(RGB)) % 4) % 4;
    char paddingData[3] = {0, 0, 0};

    for (int y = 0; y < height; ++y) {
        fwrite(image->pixels + y * width, sizeof(RGB), width, file);
        fwrite(paddingData, 1, padding, file);
    }

    fclose(file);
}

void freeImage(BitmapImage *image) {
    free(image->pixels);
}

void colorReplace(BitmapImage *image, RGB oldColor, RGB newColor) {
    int width = image->infoHeader.width;
    int height = abs(image->infoHeader.height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB *pixel = &image->pixels[y * width + x];
            if (pixel->r == oldColor.r && pixel->g == oldColor.g && pixel->b == oldColor.b) {
                *pixel = newColor;
            }
        }
    }
}

void componentMax(BitmapImage *image) {
    int width = image->infoHeader.width;
    int height = abs(image->infoHeader.height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB *pixel = &image->pixels[y * width + x];
            uint8_t maxComponent = (pixel->r > pixel->g) ? (pixel->r > pixel->b ? pixel->r : pixel->b) : (pixel->g > pixel->b ? pixel->g : pixel->b);
            pixel->r = pixel->g = pixel->b = maxComponent;
        }
    }
}

void gamma(BitmapImage *image, float gamma){
    int width=image->infoHeader.width;
    int height=abs(image->infoHeader.height);

    for (int y=0; y<height; ++y){
        for (int x=0; x<width;++x){
            RGB *pixel = &image->pixels[y*width+x];
            pixel->r=(uint8_t)(pow(((pixel->r)/255.0),gamma)*255);
            pixel->g=(uint8_t)(pow(((pixel->g)/255.0),gamma)*255);
            pixel->b=(uint8_t)(pow(((pixel->b)/255.0),gamma)*255);
        }
    }
}

void printInfo(const BitmapImage *image) {
    printf("File Size: %u\n", image->fileHeader.filesize);
    printf("Image Width: %d\n", image->infoHeader.width);
    printf("Image Height: %d\n", image->infoHeader.height);
    printf("Bits Per Pixel: %u\n", image->infoHeader.bitsPerPixel);
    printf("Image Size: %u\n", image->infoHeader.imageSize);
}

void printHelp() {
    printf("Usage: cw OPTIONS\n");
    printf("Options:\n");
    printf("  -h, --help            Show help message\n");
    printf("  -i, --info            Show image information\n");
    printf("  -r, --color_replace   Replace a color with another color\n");
    printf("  -m, --component_max   Set pixel color to the maximum of the components\n");
    printf("  -I, --input FILE      Specify input BMP file\n");
    printf("  -o, --output FILE     Specify output BMP file\n");
    printf("  --old_color R.G.B     Old color to be replaced (for color_replace)\n");
    printf("  --new_color R.G.B     New color to replace with (for color_replace)\n");
    printf("  -g, --gamma Apply gamma correction\n");
    printf("  --value VALUE Specify gamma value\n");
}

struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"info", no_argument, NULL, 'i'},
    {"color_replace", no_argument, NULL, 'r'},
    {"component_max", no_argument, NULL, 'm'},
    {"input", required_argument, NULL, 'I'},
    {"output", required_argument, NULL, 'o'},
    {"old_color", required_argument, NULL, 1},
    {"new_color", required_argument, NULL, 2},
    {"gamma", no_argument, NULL,'g'},
    {"value",required_argument,NULL,3},
    {NULL, 0, NULL, 0}
};

int main(int argc, char *argv[]) {
    printf("Course work for option 3.1, created by Andreev Makar\n");
    BitmapImage image;
    char *inputFile = NULL;
    char *outputFile = NULL;
    RGB oldColor = {0, 0, 0};
    RGB newColor = {0, 0, 0};
    int action = 0;
    float gammaValue;

    int opt;
    while ((opt = getopt_long(argc, argv, "hirI:o:mg", longopts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 'i':
                action = 'i';
                break;
            case 'r':
                action = 'r';
                break;
            case 'm':
                action = 'm';
                break;
            case 'g':
                action='g';
                break;
            case 'I':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 1:
                sscanf(optarg, "%hhu.%hhu.%hhu", &oldColor.r, &oldColor.g, &oldColor.b);
                break;
            case 2:
                sscanf(optarg, "%hhu.%hhu.%hhu", &newColor.r, &newColor.g, &newColor.b);
                break;
            case 3:
                gammaValue=atof(optarg);
                if (gammaValue<=0){
                    fprintf(stderr,"Error: Incorrect gamma value");
                    return 1;
                }
                break;
            default:
                printHelp();
                return 1;
        }
    }

    if (!inputFile || !outputFile) {
        fprintf(stderr, "Error: Input and output files must be specified\n");
        printHelp();
        return 1;
    }

    if (!readBMP(&image, inputFile)) {
        return 1;
    }

    switch (action) {
        case 'i':
            printInfo(&image);
            break;
        case 'r':
            colorReplace(&image, oldColor, newColor);
            break;
        case 'm':
            componentMax(&image);
            break;
        case 'g':
            gamma(&image, gammaValue);
            break;
        default:
            fprintf(stderr, "Error: No action specified\n");
            printHelp();
            freeImage(&image);
            return 1;
    }

    writeBMP(&image, outputFile);
    freeImage(&image);

    return 0;
}
