#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#pragma pack (push, 1)

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

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

void print_file_header(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

Rgb **read_bmp(char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif){
    FILE *f = fopen(file_name, "rb");

    if (!f){
        fprintf(stderr, "Не удалось открыть входной файл.\n");
        exit(40);
    }

    fread(bmfh, 1, sizeof(BitmapFileHeader), f);

    if(bmfh->signature != 0x4d42){
        fprintf(stderr, "Только bmp файлы!");
        exit(41);
    }

    fread(bmif, 1, sizeof(BitmapInfoHeader), f);

    if(bmif->bitsPerPixel != 24){
        fprintf(stderr, "Только 24 битные изображения!!!");
        exit(42);
    }

    if(bmif->compression !=0){
        fprintf(stderr, "Кажется, Ваш файл использует сжатие.");
        exit(43);
    }

    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    Rgb **arr = malloc(H * sizeof(Rgb*));
    int padd = 4 - (W*sizeof(Rgb))%4;
    for(unsigned int i = 0; i < H; i++){
        arr[i] = malloc(W * sizeof(Rgb) + padd%4);
        fread(arr[i], 1, W * sizeof(Rgb) + padd%4, f);
    }
    fclose(f);
    return arr;
}

void swap(unsigned char *a, unsigned char *b){
    char t = *a;
    *a = *b;
    *b = t;
}

Rgb **swap_channels(Rgb **arr, int H, int W){
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            swap(&arr[i][j].r, &arr[i][j].g);
        }
    }
    return arr;
}

Rgb** replace_color(Rgb **arr, int old_c[3], int new_c[3], int H, int W){
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(arr[i][j].r == old_c[0] && arr[i][j].g == old_c[1] && arr[i][j].b == old_c[2]){
                arr[i][j].r = new_c[0];
                arr[i][j].g = new_c[1];
                arr[i][j].b = new_c[2];
            }
        }
    }
    return arr;
}

Rgb** rgb_filt(Rgb** arr, char* name, int value, int H, int W){
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){

            if (strcmp(name, "red") == 0){
                arr[i][j].r = value;
            }

            if (strcmp(name, "green") == 0){
                arr[i][j].g = value;
            }

            if (strcmp(name, "blue") == 0){
                arr[i][j].b = value;
            }
        }
    }
    return arr;
}

Rgb** split_pic(Rgb** arr, int c_x, int c_y, int th, int color[3], int H, int W){

    if(c_x > W || c_x * th > W){
        fprintf(stderr, "Некоректные данные.\n");
        exit(40);
    }

    if(c_y > H || c_y * th > H){
        fprintf(stderr, "Некоректные данные.\n");
        exit(41);
    }

    if(th > H || th > H){
        fprintf(stderr, "Некоректные данные.\n");
        exit(42);
    }

    int pix_x = th * (c_x - 1);
    int ch = (W - pix_x)/c_x + 1;
    for(int i = 0; i < (c_x - 1); i++){
        for(int j = ch; j < ch + th; j++){
            for(int k = 0; k < H; k++){
                arr[k][j].r = color[0];
                arr[k][j].g = color[1];
                arr[k][j].b = color[2];
            }
        }
        ch = ch + th + (W - pix_x)/c_x;
    }

    int pix_y = th * (c_y - 1);
    ch = (H - pix_y)/c_y + 1;
    for(int i = 0; i < (c_y - 1); i++){
        for(int j = ch; j < ch + th; j++){
            for(int k = 0; k < W; k++){
                arr[j][k].r = color[0];
                arr[j][k].g = color[1];
                arr[j][k].b = color[2];
            }
        }
        ch = ch + th + (H - pix_y)/c_y;
    }

    return arr;
}

void write_bmp(char file_name[], Rgb **arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif){
    FILE *ff = fopen(file_name, "wb");
    if(ff == NULL){
        fprintf(stderr, "Не удалось открыть файл.\n");
        exit(40);
    }
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    int padd = 4 - (W*sizeof(Rgb))%4;
    for(int i = 0; i < H; i++){
        fwrite(arr[i], 1, W * sizeof(Rgb) + padd%4, ff);
    }
    fclose(ff);
}

void help(){
    puts("List of option:\n"
         "  --color_replace - Replaces all pixels of one specified color with another color.\n"
         "  --rgbfilter - The tool allows you to set the value of a given component in the range from 0 to 255 for the entire image.\n"
         "  --split - Divides the image into N*M parts.\n"
         "  --help - print help message."
         );
}

Rgb** blur(Rgb** arr, int H, int W, int size){
    if(size % 2 == 0) size++;

    Rgb** new_arr = malloc(H * sizeof(Rgb*));
    for(int i = 0; i < H; i++){
        new_arr[i] = malloc(W * sizeof(Rgb));
    }

    int offset = size/2;

    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;

            for(int y = -offset; y <= offset; y++){
               for(int x = -offset; x <= offset; x++){
                   int ny = i + y;
                   int nx = j + x;

                   if(ny >= 0 && ny < H && nx >= 0 && nx < W){
                       r_sum += arr[ny][nx].r;
                       g_sum += arr[ny][nx].g;
                       b_sum += arr[ny][nx].b;
                       count++;
                   }
               }
            }

            new_arr[i][j].r = r_sum / count;
            new_arr[i][j].g = g_sum / count;
            new_arr[i][j].b = b_sum / count;
        }
    }

    for(int i = 0; i < H; i++){
        free(arr[i]);
    }

    return new_arr;
}

int main(int argc, char *argv[])
{
    puts("Course work for option 4.2, created by Khalzev Aleksandr.");
    BitmapFileHeader Fh;
    BitmapInfoHeader Ih;
    int opt_ind, opt, repl_c = 0, rgb_comp = 0,  old_c[3], new_c[3], value = 0, splt = 0, c_x, c_y, th, cl[3], inf = 0, cont = 0, siz;
    char name[10];
    char* inp = NULL;
    char* out = NULL;
    struct option opt_long[]={
        {"color_replace", no_argument, 0, 'c'},
        {"old_color", required_argument, 0, 'p'},
        {"new_color", required_argument, 0, 'n'},
        {"rgbfilter", no_argument, 0, 'f'},
        {"component_name", required_argument, 0, 'i'},
        {"component_value", required_argument, 0, 'z'},
        {"split", no_argument, 0, 's'},
        {"number_x", required_argument, 0, 'x'},
        {"number_y", required_argument, 0, 'y'},
        {"thickness", required_argument, 0, 't'},
        {"color", required_argument, 0, 'l'},
        {"output", required_argument, 0, 'o'},
        {"input", required_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"info", no_argument, 0, 'g'},
        {"blur", no_argument, 0, 'r'},
        {"size", required_argument, 0, 'd'},
        {0, 0, 0, 0}
    };
    while ((opt=getopt_long(argc, argv, "co:n:fi:z:sx:y:t:l:hvgrd:u:", opt_long, &opt_ind))!=-1){
        switch(opt){
            case 'r':
                cont = 1;
                break;
            case 'd':
                sscanf(optarg, "%d", &siz);
                break;
            case 'c':
                repl_c = 1;
                break;
            case 'p':
                if(sscanf(optarg, "%d.%d.%d", &old_c[0], &old_c[1], &old_c[2]) != 3){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(40);
                }
                if(old_c[0] > 255 || old_c[1] > 255 || old_c[2] > 255 || old_c[0] < 0 || old_c[1] < 0 || old_c[2] < 0){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(40);
                }
                break;
            case 'n':
                if(sscanf(optarg, "%d.%d.%d", &new_c[0], &new_c[1], &new_c[2]) != 3){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(40);
                }
                if(new_c[0] > 255 || new_c[1] > 255 || new_c[2] > 255 || new_c[0] < 0 || new_c[1] < 0 || new_c[2] < 0){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(41);
                }
                break;
            case 'f':
                rgb_comp = 1;
                break;
            case 'i':
                sscanf(optarg, "%s", name);
                if(strcmp(name, "red") != 0 && strcmp(name, "green") != 0 && strcmp(name, "blue") != 0){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(42);
                }
                break;
            case 'z':
                sscanf(optarg, "%d", &value);
                if(value > 255 || value < 0){
                    fprintf(stderr, "Недопустимое значение для цвета.\n");
                    exit(43);
                }
                break;
            case 's':
                splt = 1;
                break;
            case 'x':
                sscanf(optarg, "%d", &c_x);
                if(c_x <= 1){
                    fprintf(stderr, "Недопустимое значение.\n");
                    exit(44);
                }
                break;
            case 'y':
                sscanf(optarg, "%d", &c_y);
                if(c_y <= 1){
                    fprintf(stderr, "Недопустимое значение.\n");
                    exit(45);
                }
                break;
            case 't':
                sscanf(optarg, "%d", &th);
                if(th <= 0){
                    fprintf(stderr, "Недопустимое значение.\n");
                    exit(46);
                }
                break;
            case 'l':
                if(sscanf(optarg, "%d.%d.%d", &cl[0], &cl[1], &cl[2]) != 3){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(40);
                }
                if(cl[0] > 255 || cl[1] > 255 || cl[2] > 255 || cl[0] < 0 || cl[2] < 0 || cl[2] < 0){
                    fprintf(stderr, "Недопустимые значения для цветовой палитры.\n");
                    exit(47);
                }
                break;
            case 'v':
                inp = optarg;
                break;
            case 'o':
                out = optarg;
                break;
            case 'h':
                help();
                return 0;
                break;
            case 'g':
                inf = 1;
                break;
        }
    }

    if (optind < argc && inp == NULL) {
        inp = argv[optind];
    }

    if(out == NULL){
        out = "out.bmp";
    }

    if(strcmp(inp, out) == 0){
        fprintf(stderr, "Названия файлов должны отличаться.\n");
        exit(48);
    }

    Rgb** arr_c = read_bmp(inp, &Fh, &Ih);

    if(inf == 1){
        print_file_header(Fh);
        print_info_header(Ih);
        return 0;
    }

    if(repl_c == 1){
        arr_c = replace_color(arr_c, old_c, new_c, Ih.height, Ih.width);
    }

    if(rgb_comp == 1){
        arr_c = rgb_filt(arr_c, name, value, Ih.height, Ih.width);
    }

    if(splt == 1){
        arr_c = split_pic(arr_c, c_x, c_y, th, cl, Ih.height, Ih.width);
    }

    if(cont == 1){
        arr_c = blur(arr_c, Ih.height, Ih.width, siz);
    }

    write_bmp(out, arr_c, Ih.height, Ih.width, Fh, Ih);
    return 0;
}
