#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#define FILE_NOT_FOUND_ERROR 40

#define WRITE_FILE_ERROR 42

#define INCORRECT_BMP_FORMAT_ERROR 43

#define INSUFFICIENT_ARGUMENTS_ERROR 44

#define MEMORY_ALLOCATION_ERROR 45

#define UNKNOWN_OPTION_ERROR 46

#define INVALID_OPTION_ARG_ERROR 47

#define RGBMAX 255

#pragma pack(push, 1)
 
typedef struct {
    unsigned char ID[2] ;
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
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;

#pragma pack(pop)

typedef struct BMPFile {
    BitmapFileHeader header;
    BitmapInfoHeader info;
    RGB** data;
} BMPFile;

void printFileHeader(BitmapFileHeader header);
void printInfoHeader(BitmapInfoHeader header);
int calculateOffset(unsigned int width);

BMPFile loadBMPImg(char* fileName);
int checkBmpFile(BMPFile* img);
void saveBMP(char* fileName, BMPFile img);

RGB invertPixels(RGB pixel);
void invertColors(BMPFile* img);

int sumOfTwoComponents(unsigned char firstPixel,unsigned char secondPixel);
void changeComponentColor(BMPFile* img, const char* pixelComponent);

// void printDetails(BMPFile* img);
int CalculateNewValue(int oldColorValue,float value);
void ChangeGamma(BMPFile* img, float value);

void freeBMPFile(BMPFile img);
void printHelp();

int main(int argc, char* argv[]) {
    if (argc < 3){
        if (argc < 2){
            puts("Not enough arguments to run the program. Use -h (--help) key to read the instructions.");
            exit(INSUFFICIENT_ARGUMENTS_ERROR);
        }

        else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            printHelp();
            exit(EXIT_SUCCESS);
        }

        puts("Incorrect key. Use -h (--help) key to read the instructions.");
        exit(UNKNOWN_OPTION_ERROR);
    }

    const char* short_options = "c:o:i:v:hfIsg";

    const struct option long_options[] = {
		{ "help", no_argument, NULL, 'h' },
        { "info", no_argument, NULL, 'f' },
		{ "inverse", no_argument, NULL, 'I' },
		{ "component_sum", no_argument, NULL, 's' },
		{ "component_name", required_argument, NULL, 'c' },

		{ "gamma", no_argument, NULL, 'g' },
		{ "value", required_argument, NULL, 'v' },

		{ "output", required_argument, NULL, 'o' },
		{ "input", required_argument, NULL, 'i' },
		{ NULL, 0, NULL, 0 }
	};

    int opt;
	int optIndex;
    char* inputFileName = "";
    char* outputFileName = "";
    int invertColorFlag = 0;
    int componentSumFlag = 0;
    int infoFlag = 0;
    char* componentToChange = "";

    int gammaFlag = 0;
    float gammaValue = -1.0;

    opterr = 0;

	opt = getopt_long(argc, argv,short_options, long_options, &optIndex);

    while(opt != -1){
        switch (opt){
            case 'h':
                puts("Error: Too many arguments for 'help' function");
                exit(UNKNOWN_OPTION_ERROR);
            case 'f':
                infoFlag = 1;
                break;
            case 'I':
                invertColorFlag = 1;
                break;
            case 's':
                componentSumFlag = 1;
                break;
            case 'c':
                componentToChange = optarg;
                break;
            case 'g':
                gammaFlag = 1;
                break;
            case 'v':
                sscanf(optarg,"%f",&gammaValue);
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'i':
                inputFileName = optarg;
                break;
            case '?': default: {
				printf("found unknown option\n");
				exit(UNKNOWN_OPTION_ERROR);
			};
        }
        opt = getopt_long(argc, argv,short_options, long_options, &optIndex);
    }

    if(strcmp(inputFileName, "") == 0){
        printf("no file name\n");
        exit(FILE_NOT_FOUND_ERROR);
    }

    if(strcmp(inputFileName, outputFileName) == 0){
        printf("Input/Output FileName are the same\n");
        exit(WRITE_FILE_ERROR);
    }
    
    // CHECK HOW MANY REQUASTED OPERATION
    if((invertColorFlag && componentSumFlag) || (invertColorFlag && gammaFlag) || (componentSumFlag && gammaFlag)){
       puts("Error : too many operation. please choose one operation at time\n");
       exit(UNKNOWN_OPTION_ERROR);
    }

    // LOAD BMP FILE
    BMPFile NewBmpFile = loadBMPImg(inputFileName);

    // CHECK VALIDITY OF BMP FILE
    if (checkBmpFile(&NewBmpFile)){
        printf("BMP FILE CHECK FAILS\n");
        exit(INCORRECT_BMP_FORMAT_ERROR);
    }

    if(infoFlag){
        printFileHeader(NewBmpFile.header);
        printInfoHeader(NewBmpFile.info);
        return 0;
    }

    if(invertColorFlag){
        invertColors(&NewBmpFile);
    }

    if (componentSumFlag){        
        if(strcmp(componentToChange, "") != 0){
            changeComponentColor(&NewBmpFile,componentToChange);
        }else{
            puts("Error: Missing argument for --component_name\n");
            freeBMPFile(NewBmpFile);
            exit(INVALID_OPTION_ARG_ERROR);
        }
    }

    if(gammaFlag){
        if(gammaValue > 0){
            ChangeGamma(&NewBmpFile,gammaValue);
        }else{
            puts("Error: Missing argument for --value\n");
            freeBMPFile(NewBmpFile);
            exit(INVALID_OPTION_ARG_ERROR);
        }   
    }

    // SAVE BMP FILE
    if(strcmp(outputFileName, "") != 0){
        saveBMP(outputFileName, NewBmpFile);
    }else{
        saveBMP("out.bmp", NewBmpFile);
    }

    freeBMPFile(NewBmpFile);
    return 0;
}

void printFileHeader(BitmapFileHeader header) {
    printf("signature:\t%c (%c)\n", header.ID[0], header.ID[1]);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header) {
    printf("\nheaderSize:\t%x (%u)\n", header.headerSize, header.headerSize);
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

int calculateOffset(unsigned int width) {
    int offset = (width*3)%4;
    offset = offset ? 4-offset : 0;
    return offset;
}

BMPFile loadBMPImg(char* fileName){
    FILE *BmpImg = fopen(fileName, "rb");

    if (BmpImg == NULL){
        puts("Error: file not found.");
        exit(FILE_NOT_FOUND_ERROR);
    }

    BMPFile NewBmpImg;

    fread(&NewBmpImg.header,1,sizeof(BitmapFileHeader),BmpImg);
    fread(&NewBmpImg.info,1,sizeof(BitmapInfoHeader),BmpImg);

    unsigned int height = NewBmpImg.info.height;
    unsigned int width = NewBmpImg.info.width;

    int offset = calculateOffset(width);

    NewBmpImg.data = malloc(sizeof(RGB*)*height);

    if (NewBmpImg.data == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    for(int i=0; i<height; i++) {
        NewBmpImg.data[i] = malloc(width * sizeof(RGB) + offset);
        if (NewBmpImg.data[i] == NULL) {
            printf("Error: cannot allocate memory!\n");
            exit(MEMORY_ALLOCATION_ERROR);
        }
        fread(NewBmpImg.data[i],1,width * sizeof(RGB) + offset,BmpImg);
    }

    fclose(BmpImg);
    return NewBmpImg;
}

int checkBmpFile(BMPFile* img){
    if(img->header.ID[0] != 'B' || img->header.ID[1] != 'M'){puts("Incorrect signature format (not 'BM')."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.headerSize != 40){puts("Error: Incorrect header size."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->header.pixelArrOffset != 54){puts("Error: Incorrect pixels' offset."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.width == 0){puts("Error: Unable to work with image (zero width size)."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.height == 0){puts("Error: Unable to work with image (zero height size)."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.planes != 1){puts("Error: Incorrect color planes (only 1 is available)."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.bitsPerPixel != 24){puts("Error: Incorrect BMP format (only 24-bits per pixel format is available).\nUse -h (--help) keys to watch the instructions."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    if(img->info.compression != 0){puts("Error: Function doesn't work with compressed BMP files."); exit(INCORRECT_BMP_FORMAT_ERROR);}

    return 0;
}

void saveBMP(char* fileName, BMPFile img) {
    FILE* fp = fopen(fileName, "wb");

    if(!fp) {
        puts("Error: something went wrong while creating/opening file.");
        exit(WRITE_FILE_ERROR);
    }

    int offset = calculateOffset(img.info.width);

    fwrite(&img.header, 1, sizeof(BitmapFileHeader), fp);
    fwrite(&img.info, 1, sizeof(BitmapInfoHeader), fp);

    size_t height = img.info.height;
    size_t width = img.info.width;

    for(size_t i = 0; i < height; i++) {
        fwrite(img.data[i], 1, sizeof(RGB) * width + offset, fp);
    }

    fclose(fp);
}

RGB invertPixels(RGB pixel) {
    pixel.b = RGBMAX - pixel.b;
    pixel.g = RGBMAX - pixel.g;
    pixel.r = RGBMAX - pixel.r;

    return pixel;
}

void invertColors(BMPFile* img) {
    for(int i = 0; i < img->info.height; i++) {
        for(int j = 0; j < img->info.width; j++) {
            // Invert the RGB values of each pixel
            img->data[i][j] = invertPixels(img->data[i][j]);
        }
    }
}

int sumOfTwoComponents(unsigned char firstPixel,unsigned char secondPixel) {
    int res = firstPixel + secondPixel;
    return res <= 255 ? res : 255;
}

void changeComponentColor(BMPFile* img, const char* pixelComponent) {
    if (strcmp(pixelComponent, "red") == 0) {
        for(int i = 0; i < img->info.height; i++) {
            for(int j = 0; j < img->info.width; j++) {
                img->data[i][j].r = sumOfTwoComponents(img->data[i][j].g,img->data[i][j].b);
            }
        }
    } else if (strcmp(pixelComponent, "green") == 0) {
        for(int i = 0; i < img->info.height; i++) {
            for(int j = 0; j < img->info.width; j++) {
                img->data[i][j].g = sumOfTwoComponents(img->data[i][j].b,img->data[i][j].r);
            }
        }
        
    } else if (strcmp(pixelComponent, "blue") == 0) {
        for(int i = 0; i < img->info.height; i++) {
            for(int j = 0; j < img->info.width; j++) {
                img->data[i][j].b = sumOfTwoComponents(img->data[i][j].r,img->data[i][j].g);
            }
        }
    } else {
        printf("ERROR: Unknown color\n");
        exit(INVALID_OPTION_ARG_ERROR);
    }
}

// void printDetails(BMPFile* img){
//     for(int i =0; i < img->info.height; i++){
//         for(int j =0; j < img->info.width;j++){
//             printf("%d %d %d\n",img->data[i][j].r,img->data[i][j].g,img->data[i][j].b);
//         }
//         printf("\n");
//     }
// }

int CalculateNewValue(int oldColorValue,float value){
    return (int)floor(pow((oldColorValue / 255.0),value) * 255.0);
}

void ChangeGamma(BMPFile* img, float value){
    for(int i =0; i < img->info.height; i++){
        for(int j =0; j < img->info.width;j++){
            img->data[i][j].r = CalculateNewValue(img->data[i][j].r,value);
            img->data[i][j].g = CalculateNewValue(img->data[i][j].g,value);
            img->data[i][j].b = CalculateNewValue(img->data[i][j].b,value);
        }
    }
}

void freeBMPFile(BMPFile img){
    for (size_t i = 0; i < img.info.height; i++){
        free(img.data[i]);
    }
    free(img.data);
}

void printHelp(){
    puts("Course work for option 3.2, created by Belaid Farouk.\n\n");
    puts("\t --help (-h): key-function for calling instructions\n");
    puts("\t --inverse (-i): key-function for Color inversion on the whole image\n");
    puts("\t --component_sum (-s): key-function for Setting the color component as \n \t  the sum of the other two\n\n");
    puts("\t --component_name (-c): key-function for choosing Which component needs\n \t to be changed\n\n");
    puts("\t --input (-o): key-function for choosing input file name\n");
    puts("\t --output (-o): key-function for choosing output file name\n");
    puts("\t --info (-o): key-function for printing image info\n");

    puts("You can use these functions:\n");

    puts("\t(1) Color inversion on the whole image:\n");
    puts("\t\t(*)Structure of correct input: <./a.out> <work_file> --inverse\n");
    puts("\t\t(*)Example: ./main.out inpute.bmp --inverse\n\n");

    puts("\t(2) Set the color component as the sum of the other two:\n");
    puts("\t\t(*)Structure of correct input: \n\t\t<./main.out> <work_file> --component_sum <X>,<Y> --component_name <component>\n");
    puts("\t\t(*)Example: ./main.out inpute.bmp --component_sum 0,0 --component_name green\n\n");

}