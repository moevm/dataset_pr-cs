#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>

#define PI 3.14159265

#pragma pack (push, 1)
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

void print_author_info(){
    printf("Course work for option 4.8, created by Ivan Rodnov.\n");
}

void p_help(){
	printf("--help, -h: get info, how to use programm\n");
	printf("--info, -I: print info about file\n");
	printf("--input, -i: name of input file\n");
	printf("--output, -o: name of output file\n");
	printf("--line, -l: function of drawing line\n");
	printf("--start, -s: coords(x0, yo), where function start draw line\n");
	printf("--end, -e: coords(x1, y1)< where function end draw line\n");
	printf("--color, -c: color of line or petagram in circle'\n");
	printf("--thickness, -t: the thickness of line of pentagram\n");
	printf("--mirror, -m: function of mirroring the area on picture\n");
	printf("-axis, -a: the axis of mirroring\n");
	printf("--left_up, L: left_up coords of area to mirror\n");
	printf("--right_down, -r: right_down coords of area to mirror\n");
	printf("--pentagram, -p: function which draws pentagram in circle\n");
	printf("--center, -C: coords(xc, yc) of circle\n");
    printf("--radius, -R: radius of circle\n");
}

void printFileHeader(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header)
{
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

int check_bmp(BitmapFileHeader bmfh, BitmapInfoHeader bmif){
    if(bmfh.signature != 0x4D42 || bmif.headerSize != 40 || bmif.bitsPerPixel != 24 || bmif.compression != 0){
        printf("Error: file has not BMP format\n");
        return 0;
    }
    return 1;
}

void read_bitmap(const char *input_filename, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb ***arr){
    FILE *f = fopen(input_filename, "rb");
    if (f == NULL){
        perror("Error opening file");
        exit(40);
    }

    fread(bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(bmif, sizeof(BitmapInfoHeader), 1, f);

    if(!check_bmp(*bmfh, *bmif)){
        exit(40);
    }

    unsigned int H = bmif->height;
    unsigned int W = bmif->width;

    *arr = malloc(H * sizeof(Rgb *));
    if(arr == NULL){
		printf("Memory error\n");
		exit(42);
	}
    for (int i = H-1; i >= 0; i--){
        (*arr)[i] = malloc(W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4);
        if((*arr)[i] == NULL){
		    printf("Memory error\n");
		    exit(42);
	    }
        fread((*arr)[i], 1, W * sizeof(Rgb) + (4- (W * sizeof(Rgb)) % 4) % 4, f);
    }

    fclose(f);
}

void write_bitmap(const char *output_filename, BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb ***arr, int H, int W){
    FILE *ff = fopen(output_filename, "wb");
    if (ff == NULL)
    {
        perror("Error opening output file");
        exit(40);
    }

    bmif.height = H;
    bmif.width = W;
    fwrite(&bmfh, sizeof(BitmapFileHeader), 1, ff);
    fwrite(&bmif, sizeof(BitmapInfoHeader), 1, ff);

    int padding = (4 - (W * 3) % 4) % 4;
	uint8_t padding_bytes[3] = { 0 };
    for (int i = H-1; i >= 0; i--)
    {
        fwrite((*arr)[i], sizeof(Rgb), W, ff);
		fwrite(padding_bytes, sizeof(uint8_t), padding, ff);
    }

    if(!check_bmp(bmfh, bmif)){
        exit(40);
    }

    fclose(ff);
}

int get_number(char* str){
    if(strlen(str) == 1 && str[0] == '-'){
        printf("Error, wrong arg");
        exit(40);
    }
    for(int i = 0; i <strlen(str); i++){
    if(isdigit(str[i]) == 0 && str[i] != '-'){
            printf("Error, wrong arg");
            exit(40);
        }
    }
    int tmp = atoi(str);
    return tmp;
}

int* pars_args(char* str, int c_args){
    int* args = malloc(c_args+1 * sizeof(int));
    if(args == NULL){
        printf("Memory error\n");
		exit(42);
    }
    char* token;
    int i = 0;
    size_t str_len = strlen(str);
    char *str_copy = malloc((str_len + 1) * sizeof(char));
    if(str_copy == NULL){
        printf("Memory error\n");
		exit(42);
    }
    strcpy(str_copy, str);

    token = strtok(str_copy, ".");

    while(token != NULL && i < c_args){
        args[i++] = get_number(token);
        token = strtok(NULL, ".");
    }
    free(str_copy);
    if(i != c_args){
        printf("Error: wrong args format");
        exit(40);
    }
    return args;
}

Rgb pars_color(char* str, int c_args){
    Rgb color;
    int i = 0;
    char* token;
    size_t str_len = strlen(str);
    char *str_copy = malloc((str_len + 1) * sizeof(char));
    if(str_copy == NULL){
        printf("Memory error\n");
		exit(42);
    }
    strcpy(str_copy, str);

    token = strtok(str_copy, ".");
    while(token != NULL && i < c_args){
        switch(i){
            case 0: {
                int r = get_number(token);
                if(r > 255 || r < 0){
                    printf("Error, wrong color");
                    exit(40);
                }
                color.r = r;
                break;
            }
            case 1: {
                int g = get_number(token);
                if(g > 255 || g < 0){
                    printf("Error, wrong color");
                    exit(40);
                }
                color.g = g;
                break;
            }
            case 2: {
                int b = get_number(token);
                if(b > 255 || b < 0){
                    printf("Error, wrong color");
                    exit(40);
                }
                color.b = b;
                break;
            }
        }
        i++;
        token = strtok(NULL, ".");
    }
    free(str_copy);
    if(i != c_args){
        printf("Error: wrong args format");
        exit(40);
    }
    return color;
}

//ФУНКИЯ 1(ОТРЕЗОК)
void check_borders_circ(int* xmax, int* xmin, int* ymax, int* ymin, int H, int W){
    if (*xmin < 0) *xmin = 0;
    if (*ymin < 0) *ymin = 0;
    if (*xmax >= W) *xmax = W - 1;
    if (*ymax >= H) *ymax = H - 1;
}

void fill_circle(Rgb **arr, int xc, int yc, int radius, Rgb color, int H, int W){
    int xmin = xc - radius;
    int xmax = xc + radius;
    int ymin = yc - radius;
    int ymax = yc + radius;

    check_borders_circ(&xmax, &xmin, &ymax, &ymin, H, W);

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= radius*radius){
                if(x >= 0 && y >= 0 && x < W && y < H){
                    arr[y][x] = color;
                }
            }
        }
    }
}

void draw_line(Rgb **arr, int H, int W, int x0, int x1, int y0, int y1, Rgb color, int thickness) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x0 >= 0 && x0 < W && y0 >= 0 && y0 < H) {
            if (thickness == 1) arr[y0][x0] = color;
				arr[y0][x0] = color; 
        }
        if(thickness > 1 && x0 - (thickness/2) < W && y0 - (thickness/2) < H && x0 + (thickness/2) >= 0 && y0 + (thickness/2) >= 0){
            fill_circle(arr, x0, y0, thickness / 2, color, H, W);
        }

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

//2
void x_mirror(Rgb **arr, int H, int W, int xlup, int ylup, int xrd, int yrd, int y_mid, int x_mid){
    int y_copy = yrd;
    int x_copy = xlup;

    for(int i = ylup; i <= y_mid; i++){
        for(int j = xlup; j <= xrd; j++){
            Rgb tmp = arr[i][j];
            arr[i][j] = arr[y_copy][x_copy];
            arr[y_copy][x_copy] = tmp;
            x_copy++;
        }
        y_copy--;
        x_copy = xlup;
    }
}

void y_mirror(Rgb **arr, int H, int W, int xlup, int ylup, int xrd, int yrd, int y_mid, int x_mid){
    int y_copy = ylup;
    int x_copy = xrd;

    for(int i = ylup; i <= yrd; i++){
        for(int j = xlup; j <= x_mid; j++){
            Rgb tmp = arr[i][j];
            arr[i][j] = arr[y_copy][x_copy];
            arr[y_copy][x_copy] = tmp;
            x_copy--;
        }
        y_copy++;
        x_copy = xrd;
    }
}

void check_borders_mirror(int H, int W, int *xlup, int *ylup, int *xrd, int *yrd){
    if(*xlup < 0){
        *xlup = 0;
    }
    else if(*xlup >= W){
        *xlup = W-1;
    }
    if(*xrd < 0){
        *xrd = 0;
    }
    else if(*xrd >= W){
        *xrd = W;
    }
    if(*ylup < 0){
        *ylup = 0;
    }
    else if(*ylup >= H){
        *ylup = H-1;
    }
    if(*yrd < 0){
        *yrd = 0;
    }
    else if(*yrd >= H){
        *yrd = H-1;
    }
}

void mirror_picture(Rgb **arr, int H, int W, char* axis, int xlup, int ylup, int xrd, int yrd){
    check_borders_mirror(H, W, &xlup, &ylup, &xrd, &yrd);
    int y_mid = (ylup + yrd) / 2;
    int x_mid = (xlup + xrd) / 2;

    if(strcmp(axis, "y")) {
        y_mirror(arr, H, W, xlup, ylup, xrd, yrd, y_mid, x_mid);
    } else if(strcmp(axis,"x")) {
        x_mirror(arr, H, W, xlup, ylup, xrd, yrd, y_mid, x_mid);
    } else {
        printf("Error: Axis doesn`t exist");
        exit(40);
    }
}

//3
void find_vertices(int center[2], int radius, int vertices[5][2]) {
    double angle = 0.0;
    double angle_increment = 2 * PI / 5;
    for (int i = 0; i < 5; i++){
        vertices[i][1] = center[1] - (int)(radius * cos(angle));
        vertices[i][0] = center[0] + (int)(radius * sin(angle));
        angle += angle_increment;
    }
}

void draw_star(Rgb **arr, int xc, int yc, int r, int H, int W, Rgb color, int thickness){
    int center[2] = {xc, yc};
    int vertices[5][2];
    find_vertices(center, r, vertices);
    draw_line(arr, H, W, vertices[0][0], vertices[2][0], vertices[0][1], vertices[2][1], color, thickness);
    draw_line(arr, H, W, vertices[2][0], vertices[4][0], vertices[2][1], vertices[4][1], color, thickness);
    draw_line(arr, H, W, vertices[4][0], vertices[1][0], vertices[4][1], vertices[1][1], color, thickness);
    draw_line(arr, H, W, vertices[1][0], vertices[3][0], vertices[1][1], vertices[3][1], color, thickness);
    draw_line(arr, H, W, vertices[3][0], vertices[0][0], vertices[3][1], vertices[0][1], color, thickness);
}

void draw_circle(Rgb **arr, int xc, int yc, int R, int r, Rgb color, int H, int W){
    int xmin = xc - R;
    int xmax = xc + R;
    int ymin = yc - R;
    int ymax = yc + R;

    check_borders_circ(&xmax, &xmin, &ymax, &ymin, H, W);

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            int is_inside_big =
                (x - xc)*(x - xc) + (y - yc)*(y - yc) <= R*R;
            int is_outside_small =
                (x - xc)*(x - xc) + (y - yc)*(y - yc) >= r*r;
            
            if (is_inside_big && is_outside_small){
                if(x >= 0 && y >= 0 && x < W && y < H){
                    arr[y][x] = color;
                }
            }
        }
    }
}

void draw_pentagram(Rgb **arr, int H, int W, int xc, int yc, int radius, Rgb color, int thickness) {
    draw_circle(arr, xc, yc, radius + thickness/2, radius - thickness/2, color, H, W);
    draw_star(arr, xc, yc, radius, H, W, color, thickness);
}


void romb(Rgb** arr, int H, int W, Rgb color, int x0, int y0, int size){
    int diagonal = 0;
    diagonal = (int) (sqrt(size*size + size*size));
    int rx = x0;
    int ry = y0+diagonal/2;
    while(diagonal >= 0){
        for(int y = 0; y < H; y++){
            for(int x = 0; x < W; x++){
                if((abs(x-rx) + abs(y-ry)) == diagonal/2){
                    if(x >= 0 && x < W && y >= 0 && y < H){
                        arr[y][x] = color;
                    }
                }
            }
        }
        diagonal--;      
    }
}

int main(int argc, char* argv[]){
    const char* short_options = "hIi:o:ls:e:c:t:ma:L:r:pC:R:HU:F:S:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"line", no_argument, NULL, 'l'},
        {"start", required_argument, NULL, 's'},
        {"end", required_argument, NULL, 'e'},
        {"color", required_argument, NULL, 'c'},
        {"thickness", required_argument, NULL, 't'},
        {"mirror", no_argument, NULL, 'm'},
        {"axis", required_argument, NULL, 'a'},
        {"left_up", required_argument, NULL, 'L'},
        {"right_down", required_argument, NULL, 'r'},
        {"pentagram", no_argument, NULL, 'p'},
        {"center", required_argument, NULL, 'C'},
        {"radius", required_argument, NULL, 'R'},
        {"square_rhombus", no_argument, NULL, 'H'},
        {"upper_vertex", required_argument, NULL, 'U'},
        {"fill_color", required_argument, NULL, 'F'},
        {"size", required_argument, NULL, 'S'}
    };

	int opt;
	int option_index;
    int option = -1;
    int print_file_info = 0;

    char* start = NULL;
    char* end = NULL;
    char* vertex = NULL;
    char* fill_color = NULL;
    char* color = NULL;
    int thickness = 0;
    char* axis = NULL;
    char* left_up = NULL;
    char* right_down = NULL;
    char* center = NULL;
    int radius = 0;
    int size = 0;
    char* output_filename = NULL;
    char* input_filename = NULL;

    while((opt=getopt_long(argc,argv,short_options, long_options, &option_index))!=-1){
        switch(opt){
            case 'h': {
                print_author_info();
                p_help();
                exit(0);
                break;
            };
            case 'I': {
                print_file_info = 1;
                break;
            };
            case 'i': {
                input_filename = optarg;
                break;
            };
            case 'o': {
                output_filename = optarg;
                break;
            };
            case 'l': {
                option = 1;
                break;
            };
            case 's': {
                start = optarg;
                break;
            };
            case 'e': {
                end = optarg;
                break;
            };
            case 'c': {
                color = optarg;
                break;
            };
            case 't': {
                thickness = get_number(optarg);
                if(thickness <= 0){
                    printf("Error: wrong thickness");
                    exit(40);
                }
                break;
            };
            case 'm': {
                option = 2;
                break;
            };
            case 'a': {
                axis = optarg;
                break;
            };
            case 'L': {
                left_up = optarg;
                break;
            };
            case 'r': {
                right_down = optarg;
                break;
            };
            case 'p': {
                option = 3;
                break;
            };
            case 'C': {
                center = optarg;
                break;
            };
            case 'R': {
                radius = get_number(optarg);
                if(radius <= 0){
                    printf("Error, wrong radius");
                    exit(40);
                }
                break;
            };
            case 'H': {
                option = 4;
                break;
            }
            case 'U': {
                vertex = optarg;
                break;
            }
            case 'F': {
                fill_color = optarg;
                break;
            }
            case 'S': {
                size = get_number(optarg);
                break;
            }
            case '?': {
                printf("unknown option\n");
                exit(0);
                break;
            };
        }
    }
    
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;
    Rgb **arr;

    read_bitmap(input_filename, &bmfh, &bmif, &arr);

    if(print_file_info == 1){
        printFileHeader(bmfh);
        printInfoHeader(bmif);
        exit(0);
    }

    unsigned int H = bmif.height;
    unsigned int W = bmif.width;

    switch (option){
        case 1: {
            int* starts = pars_args(start, 2);
            int* ends = pars_args(end, 2);
            Rgb parsed_color = pars_color(color, 3);
            draw_line(arr, H, W, starts[0], ends[0], starts[1], ends[1], parsed_color, thickness);
            free(starts);
            free(ends);
            break;
        }
        case 2: {
            int* left_ups = pars_args(left_up, 2);
            int* right_downs = pars_args(right_down, 2);
            mirror_picture(arr, H, W, axis, left_ups[0], left_ups[1], right_downs[0], right_downs[1]);
            free(left_ups);
            free(right_downs);
            break;
        }
        case 3: {
            int* centers = pars_args(center, 2);
            Rgb parsed_color = pars_color(color, 3);
            draw_pentagram(arr, H, W, centers[0], centers[1], radius, parsed_color, thickness);
            free(centers);
            break;
        }
        case 4: {
            int* u_vertex = pars_args(vertex, 2);
            Rgb parsed_color = pars_color(fill_color, 3);
            romb(arr, H, W, parsed_color, u_vertex[0], u_vertex[1], size);
            free(u_vertex);
            break;
        }
        default:
            break;
    }

    write_bitmap(output_filename, bmfh, bmif, &arr, H, W);

    for (int i = 0; i < H; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
