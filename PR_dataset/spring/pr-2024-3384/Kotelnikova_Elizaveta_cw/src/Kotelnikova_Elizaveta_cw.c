#include <ctype.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <getopt.h>
#include <string.h>
#include <stdint.h>


#pragma pack (push, 1)
typedef struct { 
    unsigned short signature;
    unsigned int filesize; 
    unsigned short reserved1; 
    unsigned short reserved2; 
    unsigned int pixelArrOffset; 
} Filefead;


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
} FileInfo;

typedef struct { 
    unsigned char b; 
    unsigned char g; 
    unsigned char r; 
} Rgb;
#pragma pack(pop)

typedef struct circl{
    long int center_x;
    long int center_y;
    long int radius;
    long int thick;
    long int color[3];
    long int fill;
    long int fill_color[3];
}circl;

typedef struct filter{
    char* comp_name;
    long int comp_val;
}filter;

typedef struct shift{
    long int step;
    char* axis;
}shift;

typedef struct zach{
    long int porog;
}zach;

typedef struct splt{
    long int numb_x;
    long int numb_y;
    long int thick;
    long int color[3];
}splt;

Rgb **read_bmp(char filename[], Filefead* bmfh, FileInfo* bmif){ //звездочки нa bmfh, bmif чтобы изменить МНОЖЕСТВО значений
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Error opening the file.\n");
        exit(40);
    }
    fread(bmfh, 1, sizeof(Filefead), f); 
    if (bmfh->signature != 0x4D42){
        printf("Error opening\n");
        exit(40);
    }
    fread(bmif, 1, sizeof(FileInfo), f); 
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

void col_pix(Rgb** arr, int x, int y, long int* color){
    arr[y][x].r = color[0];
    arr[y][x].g = color[1];
    arr[y][x].b = color[2];
}

void ssh(Rgb** arr, unsigned int H, unsigned int W, long int step, char* axis){
    long int h = (long int)H;
    long int w = (long int)W;
    if (step > 0){
        for(long int i = 0; i<w; ++i){
            for (long int j = 0; j<h; ++j){
                long int new_i = (i+step)%w;
                long int new_j = (j+step)%h;
                long int c_r = arr[j][i].r;
                long int c_g = arr[j][i].b;
                long int c_b = arr[j][i].g;
                if (strcmp(axis, "x") == 0){
                    arr[j][i].r = arr[j][new_i].r;
                    arr[j][i].g = arr[j][new_i].g; 
                    arr[j][i].b = arr[j][new_i].b;  
                    arr[j][new_i].r = c_r;
                    arr[j][new_i].g = c_g;
                    arr[j][new_i].b = c_b;
                }
                else if (strcmp(axis, "y") == 0){
                    arr[j][i].r = arr[new_j][i].r;
                    arr[j][i].g = arr[new_j][i].g; 
                    arr[j][i].b = arr[new_j][i].b;
                    arr[new_j][i].r = c_r;
                    arr[new_j][i].g = c_g;
                    arr[new_j][i].b = c_b;
                }
                else if(strcmp(axis, "xy") == 0){
                    arr[j][i].r = arr[new_j][new_i].r;
                    arr[j][i].g = arr[new_j][new_i].g; 
                    arr[j][i].b = arr[new_j][new_i].b;
                    arr[new_j][new_i].r = c_r;
                    arr[new_j][new_i].g = c_g;
                    arr[new_j][new_i].b = c_b;
                }
            }
        }
    }
    else{
        for(long int i = 0; i<w; ++i){
            for (long int j = 0; j<h; ++j){
                long int new_i = (i-step+w)%w;
                long int new_j = (j-step+h)%h;
                long int c_r = arr[j][i].r;
                long int c_g = arr[j][i].b;
                long int c_b = arr[j][i].g;
                if (strcmp(axis, "x") == 0){
                    arr[j][i].r = arr[j][new_i].r;
                    arr[j][i].g = arr[j][new_i].g; 
                    arr[j][i].b = arr[j][new_i].b;  
                    arr[j][new_i].r = c_r;
                    arr[j][new_i].g = c_g;
                    arr[j][new_i].b = c_b;
                }
                else if (strcmp(axis, "y") == 0){
                    arr[j][i].r = arr[new_j][i].r;
                    arr[j][i].g = arr[new_j][i].g; 
                    arr[j][i].b = arr[new_j][i].b;
                    arr[new_j][i].r = c_r;
                    arr[new_j][i].g = c_g;
                    arr[new_j][i].b = c_b;
                }
                else if(strcmp(axis, "xy") == 0){
                    arr[j][i].r = arr[new_j][new_i].r;
                    arr[j][i].g = arr[new_j][new_i].g; 
                    arr[j][i].b = arr[new_j][new_i].b;
                    arr[new_j][new_i].r = c_r;
                    arr[new_j][new_i].g = c_g;
                    arr[new_j][new_i].b = c_b;
                }
            }
        }
    }
}

void chbb(Rgb** arr, unsigned int H, unsigned int W, long int porog){
    long int h = (long int)H;
    long int w = (long int)W;
    for(long int i = 0; i < w; ++i){
        for(long int j = 0; j<h; ++j){
            long int col = arr[j][i].r +arr[j][i].g +arr[j][i].b;
            if (col >= porog){
                long int color1[] = {255,255,255};
                col_pix(arr, i, j, color1);
            }
            else{
                long int color2[] = {0,0,0};
                col_pix(arr, i, j, color2);
            }
        }
    }
    //printf("0\n");
}

void write_circle(Rgb** arr, unsigned int H, unsigned int W, long int x, long int y, long int r, long int thick, long int* color, int fill, long int* fill_color){
    long int h = (long int)H;
    long int w = (long int)W;
    long int r1 = r+thick;
    y = h - y - 1;
    if (fill == 1){
        for (long int i1 = x - r1; i1 < x + r1; i1++){
            for (long int j_1 = y - r1; j_1 < y + r1; j_1++){
                if (i1 >= 0 && j_1 >= 0 && i1 < w && j_1 < h){
                    if ((x - i1) * (x - i1) + (y - j_1) * (y - j_1) < ((r - thick / 2) * (r - thick / 2))){
                        col_pix(arr, i1, j_1, fill_color);
                    }
                }
                else if (i1 < 0 || j_1 < 0 || i1 > h || j_1 > w){
                    continue;
                }
            }
        }
    }
    for (long int i = x - r1; i < x + r1; i++){
        for (long int j = y - r1; j < y + r1; j++){
            if (i >= 0 && j >= 0 && i < w && j < h){
                if(r - thick/2 > 0){
                    if (((x - i) * (x - i) + (y - j) * (y - j) < ((r1 - thick / 2) * (r1 - thick / 2))) && ((x - i) * (x - i) + (y - j) * (y - j) >= (((r - thick / 2)) * ((r - thick / 2))))){
                        col_pix(arr, i,j, color);
                    }
                }
                else{
                    if((x - i) * (x - i) + (y - j) * (y - j) < ((r1 - thick / 2) * (r1 - thick / 2))){
                        col_pix(arr, i,j, color);
                    }
                }
            }
            else if (i < 0 || j < 0 || i > h || j > w){
                continue;
            }
        }
    }
}

void rgbfilt(Rgb** arr, unsigned int H, unsigned int W, char* comp_name, long int comp_val){
    int h = (int) H;
    int w = (int)W;
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            if (strcmp(comp_name, "red") == 0){
                arr[i][j].r = comp_val;
            }
            else if (strcmp(comp_name, "blue") == 0){
                arr[i][j].b = comp_val;
            }
            else{
                arr[i][j].g = comp_val;
            }
        }
    }
}

void split_picture(Rgb** arr, unsigned int H, unsigned int W, long int numb_x, long int numb_y, long int* color, long int thick){
    long int h = (long int)H;
    long int w = (long int)W;
    long int part_y = h / numb_x; 
    long int part_x = w / numb_y; 
    if(numb_x * thick >= h || numb_y * thick >= w){
        for(long int i = 0; i < h; i++){
            for(long int j = 0; j < w; j++){
                col_pix(arr, j, i, color);
            }
        }
        return;
    }
    long int count = 0;
    long int count1 = 0;
    while (count < numb_x-1){
        if (thick % 2 != 0){
            for (long int j = 0; j < thick/2 + 1; ++j){
                for(long int i = 0; i < w; ++i){
                    col_pix(arr, i, part_y+count*part_y+j, color);
                    col_pix(arr, i, part_y+count*part_y-j, color);
                }
            }
        }
        else{
            long int j_copy = 0;
            for (long int j = 0; j < thick/2; ++j){
                for(long int i = 0; i < w; ++i){
                    j_copy = j;
                    col_pix(arr, i, part_y+count*part_y+j, color);
                    col_pix(arr, i, part_y+count*part_y-j, color);
                }
            }
            for(long int i = 0; i < w; ++i){
                col_pix(arr, i, part_y+count*part_y+j_copy+1, color);
            }
        }
        count += 1;
    }

    while(count1 < numb_y - 1){
        if (thick % 2 != 0){
            for(long int j1 = 0; j1 < thick/2 + 1; ++j1){
                for (long int i1 = 0; i1 < h; ++i1){
                    col_pix(arr, part_x+count1*part_x+j1, i1, color);
                    col_pix(arr, part_x+count1*part_x-j1, i1, color);
                }
            }
        }
        else{
            long int j_copy1 = 0;
            for(long int j1 = 0; j1 < thick/2; ++j1){
                for (long int i1 = 0; i1 < h; ++i1){
                    j_copy1 = j1;
                    col_pix(arr, part_x+count1*part_x+j1, i1, color);
                    col_pix(arr, part_x+count1*part_x-j1, i1, color);
                }
            }
            for (long int i1 = 0; i1 < h; ++i1){
                col_pix(arr, part_x+count1*part_x+j_copy1+1, i1, color);
            }
        }
        count1 += 1;
    }
}

void write_bmp(char file_name[], Rgb **arr, unsigned int H, unsigned int W, Filefead bmfh, FileInfo bmif){
    FILE *ff = fopen(file_name, "wb"); 
    if (ff == NULL) {
        printf("Error opening the file.\n");
        exit(40);
    }
    fwrite(&bmfh, 1, sizeof(Filefead), ff); 
    fwrite(&bmif, 1, sizeof(FileInfo), ff); 
    int padd = 4 - (W*sizeof(Rgb))%4;
    for(size_t i = 0; i < H; i++){ 
        fwrite(arr[i], 1, W * sizeof(Rgb) + padd%4, ff); 
    } 
    fclose(ff); 
}

int Isdigit(char* oparg){
    if (strtol(oparg, NULL, 10) == 0 && strcmp(oparg, "0") != 0){
        return 0;
    }
    return 1;
}


void inf(FileInfo bmif, Filefead bmfh){
    printf("headerSize:\t%x (%u)\n", bmif.headerSize, bmif.headerSize); 
    printf("width: \t%x (%u)\n", bmif.width, bmif.width); 
    printf("height: \t%x (%u)\n", bmif.height, bmif.height); 
    printf("planes: \t%x (%hu)\n", bmif.planes, bmif.planes); 
    printf("bitsPerPixel:\t%x (%hu)\n", bmif.bitsPerPixel, bmif.bitsPerPixel); 
    printf("compression:\t%x (%u)\n", bmif.compression, bmif.compression); 
    printf("imageSize:\t%x (%u)\n", bmif.imageSize, bmif.imageSize); 
    printf("xPixelsPerMeter:\t%x (%u)\n", bmif.xPixelsPerMeter, bmif.xPixelsPerMeter); 
    printf("yPixelsPerMeter:\t%x (%u)\n", bmif.yPixelsPerMeter, bmif.yPixelsPerMeter); 
    printf("colorsInColorTable:\t%x (%u)\n", bmif.colorsInColorTable, bmif.colorsInColorTable); 
    printf("importantColorCount:\t%x (%u)\n", bmif.importantColorCount, bmif.importantColorCount); 

    printf("signature:\t%x (%hu)\n", bmfh.signature, bmfh.signature); 
    printf("filesize:\t%x (%u)\n", bmfh.filesize, bmfh.filesize); 
    printf("reserved1:\t%x (%hu)\n", bmfh.reserved1, bmfh.reserved1); 
    printf("reserved2:\t%x (%hu)\n", bmfh.reserved2, bmfh.reserved2); 
    printf("pixelArrOffset:\t%x (%u)\n", bmfh.pixelArrOffset, bmfh.pixelArrOffset); 
}
 
int main(int argc, char **argv){
    circl circle;
    filter rgb;
    splt split;
    zach zach;
    shift shift;
    FileInfo* bmif = malloc(sizeof(FileInfo));  
    Filefead* bmfh = malloc(sizeof(Filefead));  
    int c = 0; 
    int opt_ind = 0; 
    opterr = 0;
    int flag = 0;
    int flag_input = 0;
    int flag_out = 0;
    int cir = 0;
    int rgbb = 0;
    int spl = 0;
    int i = 0;
    int j = 0;
    int summ = 0;
    int chb = 0;
    int sh = 0;
    char* istr;
    char* istr1;
    char* filename = malloc(sizeof(char) * (100 + 1));
    char* file_output = malloc(sizeof(char) * (100 + 1));
    printf("Course work for option 4.11, created by Elizaveta Kotelnikova\n");
    struct option long_options1[] = { 
        {"circle", no_argument, 0, 'c'}, 
        {"rgbfilter", no_argument, 0, 'r'},
        {"split", no_argument, 0, 's'}, 
        {"center", required_argument, 0, 'e'},  
        {"radius", required_argument, 0, 'R'},  
        {"thickness", required_argument, 0, 't'},  
        {"color", required_argument, 0, 'l'},  
        {"fill", no_argument, 0, 'f'},  
        {"fill_color", required_argument, 0, 'F'},
        {"component_name", required_argument, 0, 'n'},  
        {"component_value", required_argument, 0, 'v'},
        {"number_x", required_argument, 0, 'x'}, 
        {"number_y", required_argument, 0, 'y'}, 
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"info", no_argument, 0, 'I'},
        {"help", no_argument, 0, 'h'},
        {"threshold", required_argument, 0, 'T'},
        {"binarization", no_argument, 0, 'B'},
        {"shift", no_argument, 0, 'S'},
        {"step", required_argument, 0, 'P'},
        {"axis", required_argument, 0, 'A'},
        {0, 0, 0, 0} 
    }; 
    
    while ((c = getopt_long(argc, argv, "crseO:R:t:l:fF:n:v:x:y:i:o:IhBT:SP:A:", long_options1, &opt_ind)) != -1){ 
        switch(c){
            case 'c':
                cir = 1;
                break;
            case 'r':
                rgbb = 1;
                break;
            case 's':
                spl = 1;
                break;
            case 'B':
                chb = 1;
                break;
            case 'S':
                sh = 1;
                break;
            case 'A':
                shift.axis = optarg;
                break;
            case 'P':
                shift.step = strtol(optarg, NULL, 10);
                break;
            case 'T':
                zach.porog = strtol(optarg, NULL, 10);
                break;
            case 'e': 
                if (strstr(optarg, ".") == NULL){ 
                    printf("1 Invalid input value\n");
                    return 40;
                }
                circle.center_x = strtol(strtok(optarg, "."), NULL, 10);
                circle.center_y = strtol(strtok(NULL, "."), NULL, 10);
                summ += 1;
                break;
            case 'R':
                if (strtol(optarg, NULL, 10) < 0 || Isdigit(optarg) == 0){
                    printf("2 Invalid input value\n");
                    return 40;
                }
                circle.radius = strtol(optarg, NULL, 10);
                summ += 1;
                break;
            case 't':
                if (strtol(optarg, NULL, 10) < 0 || strcmp(optarg, "0") == 0){
                    printf("3 Invalid input value\n");
                    return 40;
                }
                circle.thick = strtol(optarg, NULL, 10);
                split.thick = strtol(optarg, NULL, 10);
                summ += 1;
                break;
            case 'l':
                if (strstr(optarg, ".") == NULL){
                    printf("66 Invalid input value\n");
                    return 40;
                }
                istr = strtok(optarg, ".");
                int count = 1;
                while(istr != NULL){
                    if (strtol(istr, NULL, 10) < 0 || strtol(istr, NULL, 10) > 255 || (strtol(istr, NULL, 10) == 0 && strcmp(istr, "0") != 0)){
                        printf("51 Invalid input value\n");
                        return 40;
                    }
                    circle.color[i] = strtol(istr, NULL, 10);
                    split.color[i] = strtol(istr, NULL, 10);
                    i += 1;
                    istr = strtok(NULL, ".");
                    count += 1;
                    if (istr == NULL && count != 4){
                        printf("6 Invalid input value\n");
                        return 40;
                    }
                }
                summ += 1;
                break;
            case 'f':
                flag = 1;
                break;
            case 'F':
                if (strstr(optarg, ".") == NULL){
                    printf("9 Invalid input value\n");
                    return 40;
                }
                istr1 = strtok(optarg, ".");
                int count1 = 1;
                while(istr1 != NULL){
                    if (strtol(istr1, NULL, 10) < 0 || strtol(istr1, NULL, 10) > 255 || (strtol(istr1, NULL, 10) == 0 && strcmp(istr1, "0") != 0)){ //(strtol(istr, NULL, 10) == 0 && strcmp(istr, "0") != 0)
                        printf("10 Invalid input value\n");
                        return 40;
                    }
                    circle.fill_color[j] = strtol(istr1, NULL, 10);
                    j += 1;
                    istr1 = strtok(NULL, ".");
                    count1 += 1;
                    if (istr1 == NULL && count1 != 4){
                        printf("88 Invalid input value\n");
                        return 40;
                    }
                }
                break;
            case 'n':
                if (strcmp(optarg, "red") != 0 && strcmp(optarg, "green") != 0 && strcmp(optarg, "blue") != 0){
                    printf("45 Invalid input value\n");
                    return 40;
                }
                rgb.comp_name = optarg;
                summ += 1;
                break;
            case 'v':
                if (strtol(optarg, NULL, 10) < 0 || strtol(optarg, NULL, 10) > 255 || Isdigit(optarg) == 0){
                    printf("99 Invalid input value\n");
                    return 40;
                }
                rgb.comp_val = strtol(optarg, NULL, 10);
                summ += 1;
                break;
            case 'x':
                if (strtol(optarg, NULL, 10) < 1 || Isdigit(optarg) == 0){
                    printf("Invalid input value\n");
                    return 40;
                }
                split.numb_x = strtol(optarg, NULL, 10);
                summ += 1;
                break;
            case 'y':
                if (strtol(optarg, NULL, 10) < 1 || Isdigit(optarg) == 0){
                    printf("8989 Invalid input value\n");
                    return 40;
                }
                split.numb_y = strtol(optarg, NULL, 10);
                summ += 1;
                break; 
            case 'h':
                printf("The (circle) flag draws a circle centered at the point (center) and with a radius (radius). The thickness and color of the circle are set using the (thickness) and (color) flags, respectively. You can also color the circle separately using the (file) and (fill_color) flags.\n");
                printf("The flag (rgbfilter) allows you to change the shade of the color that is set by the flag (component_name) to the shade that is set in the flag (component_value)");
                printf("The (split) flag allows you to divide the image into N*M parts, where the number N is set by the flag (number_x) - the number of parts along the vertical axis, and M is set by the flag (number_y) - the number of parts along the X axis. Also, the (thickness) and (color) flags set the thickness and color of the lines, respectively");
                return 0;
            case 'I':
                inf(*bmif, *bmfh);
                return 0;
            case 'i':
                strcpy(filename, optarg);
                filename = realloc(filename, (strlen(optarg)+1)*sizeof(char));
                flag_input = 1;
                break;
            case 'o':
                strcpy(file_output, optarg);
                file_output = realloc(file_output, sizeof(char) * (strlen(optarg)+1));
                flag_out = 1;
                if (strcmp(filename, file_output) == 0){
                    printf("12 Invalid input value, the name of the input and output files are the same");
                    return 40;
                }
                break;
            default:
                printf("Unknown option or missing argument\n");
                return 44;
        }
    }
    if (flag_input == 0 || flag_out == 0){//имя входного последнее!!!
        if (flag_input == 0 && flag_out != 0){
            strcpy(filename, argv[optind]);
            filename = realloc(filename, (strlen(argv[optind]) + 1) * sizeof(char));
        }
        else if (flag_input != 0 && flag_out == 0){
            strcpy(file_output, "out.bmp");
            file_output = realloc(file_output, (7 + 1) * sizeof(char));
        }
        else{
            strcpy(file_output, "out.bmp");
            strcpy(filename, argv[optind]);
            filename = realloc(filename, (strlen(argv[optind]) + 1) * sizeof(char));
            file_output = realloc(file_output, (7 + 1) * sizeof(char));
        }
        if (strcmp(filename, file_output) == 0){
            printf("Invalid input value, the name of the input and output files are the same");
            return 40;
        }
    }
        Rgb** image = read_bmp(filename, bmfh, bmif); //передали указатель на первый байт в памяти
        if (cir > 0){
            printf("%ld\t%ld\t%ld\n", circle.color[0], circle.color[1], circle.color[2]);
            printf("%ld\t%ld\n", circle.center_x, circle.center_y);
            printf("%ld\t%ld\t%ld\n", circle.fill_color[0], circle.fill_color[1], circle.fill_color[2]);
            write_circle(image, bmif->height, bmif->width, circle.center_x, circle.center_y, circle.radius, circle.thick, circle.color, flag, circle.fill_color);
        }
        else if (rgbb > 0){
            rgbfilt(image, bmif -> height, bmif -> width, rgb.comp_name, rgb.comp_val);
        }
        else if(spl > 0){
            split_picture(image, bmif -> height, bmif -> width, split.numb_x, split.numb_y, split.color, split.thick);
        }
        else if(chb > 0){
            chbb(image, bmif -> height, bmif -> width, zach.porog);
        }
        else if(sh > 0){
            ssh(image, bmif -> height, bmif -> width, shift.step, shift.axis);
        }
        write_bmp(file_output, image, bmif->height, bmif->width, *bmfh, *bmif);
        free(filename);
        free(file_output);
        for (unsigned int k = 0; k < bmif->height; ++k){
            free(image[k]);
        }
    free(image);
    free(bmfh);
    free(bmif);
    return 0;
}
