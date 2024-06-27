#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#pragma pack (push, 1)

typedef struct BitmapFileHeader {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader; 


typedef struct BitmapInfoHeader {
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
} RGB;

#pragma pack(pop)


typedef struct BMP {
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB ** canvas;
} BMP;


//input output ------------------------------------------------------------------
BMP read_bmp(char * file_name) {
    FILE * f = fopen(file_name, "rb");
    if (!f){
        printf("File not found\n");
        exit(41);
    }
    BMP image;
    fread(&image.bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&image.bmih, 1, sizeof(BitmapInfoHeader), f);
    if (image.bmih.headerSize != 40 || image.bmih.bitsPerPixel != 24 || image.bmfh.signature != 0x4D42 || image.bmih.compression != 0) {
        printf("This bmp format is not supported by the program\n");
        exit(41);
    }
    unsigned int W = image.bmih.width;
    unsigned int H = image.bmih.height;
    image.canvas = calloc(1, H * sizeof(RGB*));
    for (int i = 0; i < H; i ++) {
        image.canvas[H - i - 1] = calloc(1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4);
        fread(image.canvas[H - i - 1], 1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4, f);
    }
    fclose(f);
    return image;
} 



void write_bmp(char * file_name, BMP image) {
    FILE * f = fopen(file_name, "wb");
    fwrite(&image.bmfh, 1, sizeof(BitmapFileHeader), f);
    fwrite(&image.bmih, 1, sizeof(BitmapInfoHeader), f);
    unsigned int W = image.bmih.width;
    unsigned int H = image.bmih.height;
    for (int i = 0; i < H; i ++) {
        fwrite(image.canvas[H - i - 1], 1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4, f);
    }
    fclose(f);
}





//--info, print_info , help-------------------------------------------------------

void print_file_header(BitmapFileHeader header) {
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}


void print_info_header(BitmapInfoHeader header) {
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


void print_info(BMP image) {
    print_file_header(image.bmfh);
    print_info_header(image.bmih);
}


void print_help(){
    puts(
        "usage: cw OPTIONS\n"
        "options:\n"
        "    -h | --help:           print help message\n"
        "    -i | --info:           print image info\n"
        "    -r | --rgbfilter:      set component to min/max\n"
        "    -f | --fill:           fill image with inputed color\n"
        "    -i | --input:          input image\n"
        "    -o | --output:         output image"
    );
}

int is_color(int* arr){
    for (int i = 0; i < 3; i++){
        if (!(0 <= arr[i] && arr[i] <= 255))
            return 0;
    }
    return 1;
}


void filter(BMP* image, int fl_m, char c){
    unsigned int width = image->bmih.width;
    unsigned int height = image->bmih.height;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (c == 'r')
                image->canvas[y][x].r = fl_m;
            else if (c == 'g')
                image->canvas[y][x].g = fl_m;
            else if (c == 'b')
                image->canvas[y][x].b = fl_m;
            else{
                puts("Error color input, Available: red, green, blue");
                exit(41);
            }
        }
    }
}

void gamma_change(BMP* image, float value){
    unsigned int width = image->bmih.width;
    unsigned int height = image->bmih.height;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            image->canvas[y][x].r = (unsigned char)(pow((image->canvas[y][x].r/ 255.0), value) * 255);
            image->canvas[y][x].g = (unsigned char)(pow((image->canvas[y][x].g/ 255.0), value) * 255);
            image->canvas[y][x].b = (unsigned char)(pow((image->canvas[y][x].b/ 255.0), value) * 255);
        }
    }
}

void fl(BMP* image, RGB color){
    unsigned int width = image->bmih.width;
    unsigned int height = image->bmih.height;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            image->canvas[y][x].r = color.r;
            image->canvas[y][x].g = color.g;
            image->canvas[y][x].b = color.b;
        }
    }
}

struct option long_options[] = {
        //флаги основных функций 
    {"rgbfilter", no_argument, 0, 'r'},
    {"fill", no_argument, 0, 'f'},
    {"gamma", no_argument, 0,'g'},

        //ввод-ввывод-инфо
    {"input",required_argument ,0, 'i'},
    {"output",required_argument ,0, 'o'},
    {"help",no_argument ,0, 'h'},
    {"info",no_argument ,0, 'l'},
    
        
    //доп фдаги

    {"component_name", required_argument, 0, 1},
    {"max", no_argument, 0, 2},
    {"min", no_argument, 0, 3},
    {"color", required_argument, 0, 4},
    {"value", required_argument,0,5},

    {0, 0, 0, 0}
};


int main(int argc, char ** argv) {
    puts("Course work for option 3.3, created by Dubinin Andrei");
    char input_filename[1024];
    char output_filename[1024];
    strcpy(output_filename, "out.bmp");


    int tmp_clr[3] = {-1, -1, -1};

    int flag_help = 0, flag_info = 0, flag_input = 0;


//========================================================
    int flag_rgbf = 0;
    int flag_fl = 0;
    int flag_g = 0;
    float value;
    char comp[7];
    int fl_m = -1;
    RGB color;

//=======================================================
    BMP image;

    const char* options = "fri:o:h";
    int option;

    while ((option = getopt_long(argc, argv, options, long_options, NULL)) != -1){
        switch (option){

            //================================================================================================
            case 1:
                if(!strcpy(comp, optarg)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                break;
            case 2:
                fl_m = 255;
                break;
            case 3:
                fl_m = 0;
                break;
            case 4:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                color.r = tmp_clr[0]; color.g = tmp_clr[1]; color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 5:
                sscanf(optarg, "%f", &value);
                break;

            case 'r':
                flag_rgbf = 1;
                break;
            case 'f':
                flag_fl = 1;
                break;
            case 'g':
                flag_g = 1;
                break;
            //================================================================================================   


            case 'h':
                flag_help = 1;
                break;
            case 'i':
                flag_input = 1;
                strcpy(input_filename, optarg);
                break;
            case 'o':
                strcpy(output_filename, optarg);
                break;
                break;
            case 'l':
                flag_info = 1;                
                break;
            default:
                printf("No such flags exists\nWhat about Help?)\n");
                print_help();
                exit(41);
                break;
        }
    }

    if(flag_input == 1){
        image = read_bmp(input_filename);
    }
    else{
        print_help();
        return 0;
    }


    if (flag_help == 1){
        print_help(); 
    }
    else if(flag_info){
        print_info(image);
    }

    //===========================================
    else if(flag_rgbf){
        filter(&image, fl_m, comp[0]);
    }
    else if(flag_fl){
        fl(&image, color);
    }
    else if(flag_g){
        gamma_change(&image, value);
    }

    
    write_bmp(output_filename, image);
    

    return 0;
}
