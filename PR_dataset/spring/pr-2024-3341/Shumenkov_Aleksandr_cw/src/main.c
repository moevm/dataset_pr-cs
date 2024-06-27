#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX(x, y) (((x) < (y)) ? (x) : (y))

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
    unsigned char b, g, r;
} Rgb;

#pragma pack(pop)

typedef struct {
    int r, g, b;
} Rgb_int;

enum RGB{
    R,
    G,
    B,
};

void printFileHeader(BitmapFileHeader header) {
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header) {
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:     \t%x (%u)\n", header.width, header.width);
    printf("height:    \t%x (%u)\n", header.height, header.height);
    printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void print_help() {
    printf("Next options available:\n");
    printf("-i, --input: input image filename.\n");
    printf("-o, --output: output image file name.\n");
    printf("-h, --help: this message.\n");
    printf("--info: information about BMP file.\n");
    printf("--inverse: color inversion across the entire image.\n");
    printf("--component_sum: set a color component as the sum of two others.\n");
    printf("--component_name: which component needs to be changed `red`, `green` and `blue`.\n");
    exit(0);
}


enum Commands {
    NONE,  
    INFO,
    INVERSE,
    SUM,
    GAM,
};

Rgb **read_bmp(char file_name[], BitmapFileHeader *bmfh, BitmapInfoHeader *bmif) {
    FILE *f = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb **arr = malloc(H * sizeof(Rgb *));
    for (int i = 0; i < H; i++) {
        arr[i] = malloc(W * sizeof(Rgb) + (4 - (W * 3) % 4) % 4);
        fread(arr[i], 1, W * sizeof(Rgb) + (4 - (W * 3) % 4) % 4, f);
    }
    fclose(f);
    return arr;
}

void write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif) {
    FILE *ff = fopen(file_name, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    for (int i = 0; i < H; i++) {
        fwrite(arr[i], 1, W * sizeof(Rgb) + (4 - (W * 3) % 4) % 4, ff);
    }
    fclose(ff);
}

enum Commands read_opts(int argc, char *argv[],
                        char **filename_input,
                        char **filename_output,
                        char **component_name,
                        char **value_txt) {
    enum Commands command = NONE;
    const struct option long_options[] = {
            {"input",           required_argument,  NULL,       'i'},
            {"output",          required_argument,  NULL,       'o'},
            {"help",            no_argument,        NULL,       'h'},
            {"info",            no_argument,        (int *)&command,   INFO},
            {"inverse",   no_argument,        (int *)&command,   INVERSE},
            {"component_sum",   no_argument,        (int *)&command,   SUM},
            {"component_name",       required_argument,  NULL,       0},
            {"gamma",   no_argument,        (int *)&command,   GAM},
            {"value",       required_argument,  NULL,       0},
            {NULL, 0, NULL, 0}};
    int c;
    int option_index;
    while ((c = getopt_long(argc, argv, "i:o:h", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                exit(0);
                break;
            case 'o':
                *filename_output = optarg;
                break;
            case 'i':
                *filename_input = optarg;
                break;
            case 0:
                if (strcmp(long_options[option_index].name, "component_name") == 0){
                    *component_name = optarg;
                }else if(strcmp(long_options[option_index].name, "value") == 0){
                    *value_txt = optarg;
                }
                break;
            case '?':
            default:
                exit(40);
                break;
        };
    };
    if (command == NONE)
        print_help();
    if (!*filename_output)
        *filename_output = "out.bmp";
    if (!*filename_input && argc > optind && (optind + 1 == argc)) {
        *filename_input = argv[optind];
    } else if (!*filename_input) {
        printf("Missing input file\n");
        exit(40);
    }
    if (strcmp(*filename_output, *filename_input) == 0) {
        printf("output should not be same as input");
        exit(40);
    }
    return command;
}

void run_command(enum Commands command, Rgb **arr, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char *component_name, char* value_txt) {
    switch (command) {
        case INFO:
            printFileHeader(bmfh);
            printInfoHeader(bmif);
            exit(0);
            break;
        case INVERSE:
            for(int i=0; i<bmif.height; i++){
                for(int j=0; j<bmif.width; j++){
                    arr[i][j].r = 255 - arr[i][j].r;
                    arr[i][j].g = 255 - arr[i][j].g;
                    arr[i][j].b = 255 - arr[i][j].b;
                }
            }
            break;
        case GAM:{
            float value;
            if(sscanf(value_txt, "%f" , &value) != 1){
                exit(40);
            }
            if(value < 0){
                exit(40);
            }
            for(int i = 0; i < bmif.height; i++){
                for(int j = 0; j < bmif.width; j++){
                    arr[i][j].r = MAX(floor(pow(arr[i][j].r / 255.0, value) * 255), 255);
                    arr[i][j].g = MAX(floor(pow(arr[i][j].g / 255.0, value) * 255), 255);
                    arr[i][j].b = MAX(floor(pow(arr[i][j].b / 255.0, value) * 255), 255);
                }
            }
        }
            break;
        case SUM:{
            enum RGB component;
            if (strcmp(component_name, "red") == 0){
                component = R;
            }else if (strcmp(component_name, "green") == 0){
                component = G;
            }else if(strcmp(component_name, "blue") == 0){
                  component = B;
            }else{
              printf("Wrong component name\n");
              exit(40);
            }
            if(component == R){
                for(int i = 0; i < bmif.height; i++){
                    for(int j = 0; j < bmif.width; j++){
                        int summ = arr[i][j].g + arr[i][j].b;
                        if(summ > 255) summ = 255;
                        arr[i][j].r = summ;
                    }
                }
            }

            if(component == G){
                for(int i = 0; i < bmif.height; i++){
                    for(int j = 0; j < bmif.width; j++){
                        int summ = arr[i][j].r + arr[i][j].b;
                        if(summ > 255) summ = 255;
                        arr[i][j].g = summ;
                    }
                }
            }

            if(component == B){
                for(int i = 0; i < bmif.height; i++){
                    for(int j = 0; j < bmif.width; j++){
                        int summ = arr[i][j].r + arr[i][j].g;
                        if(summ > 255) summ = 255;
                        arr[i][j].b = summ;
                    }
                }
            }
        }
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    char *filename_input = NULL;
    char *filename_output = NULL;
    char *component_name = NULL;
    char *value_txt = NULL;


    printf("Course work for option 3.2, created by Shumenkov Aleksandr\n");

    enum Commands command = read_opts(argc, argv, &filename_input, &filename_output, &component_name, &value_txt);

    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;

    Rgb **arr = read_bmp(filename_input, &bmfh, &bmif);

    if (bmfh.signature != 0x4D42 || bmif.bitsPerPixel != 24 || bmif.headerSize != 40) {
        printf("not a valid BMP\n");
        exit(40);
    }

    run_command(command, arr, bmfh, bmif, component_name, value_txt);

    write_bmp(filename_output, arr, bmif.height, bmif.width, bmfh, bmif);

    return 0;
}
