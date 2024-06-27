#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


#define fmin(a, b) (((a) < (b)) ? (a) : (b))
#define fmax(a, b) (((a) > (b)) ? (a) : (b))
#define HELP "--help / -h (about  prog)\n--info / -f (info about BMP pict)\n\nfunc (1) drow triangle\n--triangle\n    * Флаг --points, значение задаётся в формате `x1.y1.x2.y2.x3.y3\n    * Флаг `--thickness`. На вход принимает число больше 0 (толщина линий)\n    * Флаг `--color` цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb (цвет линии)\n    *--fill (заливка)\n    * --fill_color` (работает аналогично флагу `--color`) (цвет заливки)\n\nfunc(2) biggest rect (Находит самый большой прямоугольник заданного цвета и перекрашивает его в другой цвет.)\n--biggest_rect\n    * --old_color\n    * --new_color\n\nfunc (3) collage\n--collage\n    * --number_x\n    * --number_y"

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
    printf(HELP);
}


//(1) drow triangle --------------------------------------------------------------

int check_points(int x, int y,unsigned int H,unsigned int W){
    return (x >= 0 && y >= 0 && x < H && y < W);
}


void drawPixel(BMP* arr, int x, int y, RGB color) {
    // Установка цвета пикселя в массиве arr по координатам (x, y)
    if (x >=0 && y>=0 && x < arr->bmih.width && y <  arr->bmih.height){    
        arr->canvas[y][x].r = color.r;
        arr->canvas[y][x].g = color.g;
        arr->canvas[y][x].b = color.b;
    }
}

void drawFieldCircle(BMP* img, int x0, int y0, int radius, RGB color){
    if (radius <= 0){
        drawPixel(img, x0, y0, color);
        return;
    }

    if(radius == 1 || radius == 2){
        drawPixel(img, x0, y0, color);
        drawPixel(img, x0 + 1, y0, color);
        drawPixel(img, x0, y0 + 1, color);
        drawPixel(img, x0 - 1, y0, color);
        drawPixel(img, x0, y0-  1, color);

        if(radius==2){
            drawPixel(img, x0 + 1, y0 + 1, color);
            drawPixel(img, x0 + 1, y0 - 1, color);
            drawPixel(img, x0 - 1, y0 + 1, color);
            drawPixel(img, x0 - 1, y0 - 1, color);
            drawPixel(img, x0 + 2, y0, color);
            drawPixel(img, x0, y0 + 2, color);
            drawPixel(img, x0 - 2, y0, color);
            drawPixel(img, x0, y0 - 2, color);
        }
        return;
    }
   
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        drawPixel(img, x0 + x, y0 + y, color);
		drawPixel(img, x0 + x, y0 - y, color);
		drawPixel(img, x0 - x, y0 + y, color);
		drawPixel(img, x0 - x, y0 - y, color);
        drawPixel(img, x0 + y, y0 + x, color);
		drawPixel(img, x0 + y, y0 - x, color);
		drawPixel(img, x0 - y, y0 + x, color);
		drawPixel(img, x0 - y, y0 - x, color);
        error = 2*(delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            x++;
            delta += 2*x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            y--;
            delta -= 2*y + 1;
            continue;
        }
        x++;
        y--;
        delta += 2*(x - y);
    }
    drawFieldCircle(img, x0, y0, radius/2, color);
}


void drow_line(BMP* image, int x1, int y1, int x2, int y2, RGB color, int wd)
{ /* plot an anti-aliased line of width wd */
    int delta_x= abs(x2 - x1);
    int delta_y = abs(y2 - y1);
    int sign_x = -1;
    int sign_y = -1;
    
    if (x1 < x2)
        sign_x = 1;
    
    if (y1 < y2)
        sign_y = 1;

    int second_error;
    int first_error = delta_x - delta_y;
    drawFieldCircle(image, x2, y2, wd, color);
    while(x1 != x2 || y1 != y2){
        drawFieldCircle(image, x1, y1, wd, color);
        second_error = first_error * 2;
        if(second_error > -delta_y) {
            first_error -= delta_y;
            x1 += sign_x;
        }
        if(second_error < delta_x) {
            first_error += delta_x;
            y1 += sign_y;
        }
    }
}

/* Checks if the point (x, y) is inside the triangle ABC */
int check_in_triangle(int x, int y, int xA, int yA, int xB, int yB, int xC, int y3)
{
    int as_x = x - xA;
    int as_y = y - yA;

    int s_ab = (xB - xA) * as_y - (yB - yA) * as_x > 0;

    if (((xC - xA) * as_y - (y3 - yA) * as_x > 0) == s_ab)
        return 0;
    if (((xC - xB) * (y - yB) - (y3 - yB) * (x - xB) > 0) != s_ab)
        return 0;
    return 1;
}


// Draw points inside triangle
void fill_triangle(BMP* bmp, int x1, int y1, int x2, int y2, int x3, int y3, RGB fill)
{
    int xMax = fmax(x1, fmax(x2, x3)); // max of x
    int yMax = fmax(y1, fmax(y2, y3)); // max of y
    int xMin = fmin(x1, fmin(x2, x3)); // min of x
    int yMin = fmin(y1, fmin(y2, y3)); // min of y

    // Fill pixels inside triangle
    for (int i = xMin; i < xMax; i++) {
        for (int j = yMin; j < yMax; j++) {
            if (check_in_triangle(i, j, x1, y1, x2, y2, x3, y3)) {
                drawPixel(bmp, i, j, fill);
            }
        }
    }
}



void drow_triangle_fill(BMP immage, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, RGB color, RGB fill_color){
    
    fill_triangle(&immage, x1, y1, x2, y2, x3, y3, fill_color);
    drow_line(&immage, x1, y1, x2, y2, color, thickness);
    drow_line(&immage, x3, y3, x2, y2,color, thickness);
    drow_line(&immage, x1, y1, x3, y3,color, thickness);

}
void drow_triangle(BMP immage, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, RGB color){

    drow_line(&immage, x1, y1, x2, y2,color, thickness);
    drow_line(&immage, x3, y3, x2, y2,color, thickness);
    drow_line(&immage, x1, y1, x3, y3,color, thickness);
}


void drow_sq(BMP immage, int x, int y,int s, RGB color){
    
    int x1 = x + s, y1 = y + s; 
    int x2 = x - s, y2 = y + s;
    int x3 = x, y3 = y+ s*2;

    /*int x1 = x + 40, y1 = y +  40; 
    int x2 = x - 40, y2 = y +  40;
    int x3 = x, y3 = y + 80;*/

    fill_triangle(&immage, x, y, x1, y1, x2, y2, color);
    fill_triangle(&immage, x3, y3, x1, y1, x2, y2, color);
    

}





//(2) change collor bigest rect --------------------------------------------------
int is_color(int* arr){
    for (int i = 0; i < 3; i++){
        if (!(0 <= arr[i] && arr[i] <= 255))
            return 0;
    }
    return 1;
}

int colorCmp(RGB first, RGB second){
    return first.r == second.r && first.g == second.g && first.b == second.b;
}

int isRect(BMP* bmp, RGB targetColor, int x1, int y1, int x2, int y2) {
    for (size_t y = y1; y <= y2; y++) {
        for (size_t x = x1; x <= x2; x++) {
            if (!colorCmp(bmp->canvas[y][x], targetColor)){
                return 0;
            }
        }
    }
    return 1;
}

void findAndColorRectangle(BMP* bmp, RGB targetColor, RGB newColor){
    int width = bmp->bmih.width;
    int height = bmp->bmih.height;
    int maxRectX = 0;
    int maxRectY = 0;

    int max_area = 0;
    int max_x1, max_y1, max_x2, max_y2, cur_x_max, cur_y_max, area;
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (colorCmp(bmp->canvas[y][x], targetColor)){
                cur_x_max = x;
                cur_y_max = y;
                while (cur_y_max < height && colorCmp(bmp->canvas[cur_y_max][x], targetColor)) {
                    cur_y_max++;
                }
                while (cur_x_max < width && colorCmp(bmp->canvas[y][cur_x_max], targetColor)) {
                    cur_x_max++;
                }
                cur_y_max--;
                cur_x_max--;
                area = (cur_x_max - x + 1) * (cur_y_max - y + 1);
                if (area > max_area) {
                    if (isRect(bmp, targetColor, x, y, cur_x_max, cur_y_max)) {
                        max_area = area;
                        max_x1 = x;
                        max_y1 = y;
                        max_x2 = cur_x_max;
                        max_y2 = cur_y_max;
                    }
                }
            }
        }
    }

    if (max_area != 0) {
        for (int y = max_y1; y <= max_y2; y++) {
            for (int x = max_x1; x <= max_x2; x++) {
                drawPixel(bmp, x, y, newColor);
            }
        }
    }
    
}

//(3) make callage----------------------------------------------------------------
void collage(BMP* picture, unsigned int n, unsigned int m) {
    // Создание коллажа размера N*M
    unsigned int width = picture->bmih.width;
    unsigned int height = picture->bmih.height;
    unsigned int collageWidth = width * n;
    unsigned int collageHeight = height * m;
    
    // Выделение памяти для коллажа
    RGB** collagePixels = malloc(sizeof(RGB*) * collageHeight);
    for (int i = 0; i < collageHeight; i++) {
        collagePixels[i] = malloc(sizeof(RGB) * collageWidth);
    }
    for (int i = 0; i < collageHeight; i++) {
        int row = i % height;
        for (int j = 0; j < collageWidth; j++) {
            int column = j % width;
            collagePixels[i][j] = picture->canvas[row][column];
        }
    }

    // Освобождение памяти старых пикселей
    for (int i = 0; i < height; i++) {
        free(picture->canvas[i]);
    }
    free(picture->canvas);

    unsigned int newImageSize = picture->bmih.imageSize * n *m;

    picture->bmih.width = collageWidth;   // Обновление информации о коллаже
    picture->bmih.height = collageHeight;
    picture->bmfh.filesize = sizeof(BMP) + sizeof(RGB) * collageWidth * collageHeight;
    picture->bmih.imageSize = newImageSize;
    //picture->bmfh.pixelArrOffset = sizeof(BMP);
    picture->canvas = collagePixels;     // Присваивание новых пикселей коллажу
}







//================================================================================

struct option long_options[] = {
        //флаги основных функций 
    {"triangle",no_argument ,0, 't'},
    {"biggest_rect",no_argument,0 , 'b'},
    {"collage",no_argument,0 ,'c'},
    {"square_rhombus", no_argument, 0, 's'},


        //ввод-ввывод-инфо
    {"input",required_argument ,0, 'i'},
    {"output",required_argument ,0, 'o'},
    {"help",no_argument ,0, 'h'},
    {"info",no_argument ,0, 'f'},
        
    //доп фдаги
    {"points", required_argument, 0, 1},
    {"thickness", required_argument, 0, 2},
    {"color", required_argument, 0, 3},
    {"fill", no_argument, 0, 4},
    {"fill_color", required_argument, 0, 5},
    {"old_color", required_argument, 0, 6},
    {"new_color", required_argument, 0, 7},
    {"number_y", required_argument, 0, 8},
    {"number_x", required_argument, 0, 9},

    {"upper_vertex", required_argument, 0, 10},
    {"size", required_argument, 0, 11},
    {"fill_color", required_argument, 0, 12},

    {0, 0, 0, 0}
};


int main(int argc, char ** argv) {
    puts("Course work for option 4.7, created by Miller Sergei.");

    char input_filename[1024];
    char output_filename[1024];
    strcpy(output_filename, "out.bmp");

    int flag_triangle = 0;
    int flag_biggest_rect = 0;
    int flag_collage = 0;

    int tmp_clr[3] = {-1, -1, -1};

    int flag_help = 0, flag_info = 0, flag_input = 0;
    //1-------------------------
    int x1, x2, x3, y1, y2, y3;
    int thickness;
    RGB color;
    int fill = 0;
    RGB fill_color;
    //2-------------------------
    RGB old_color;
    RGB new_color;
    //3-------------------------
    int num_x;
    int num_y;



    //4
    int flag_sq = 0;

    int x, y;
    int size;
    RGB fl_color;



    BMP image;

    const char* options = "tbsci:o:h";
    int option;

    while ((option = getopt_long(argc, argv, options, long_options, NULL)) != -1){
        switch (option){
            case 1:
                if(sscanf(optarg, "%d.%d.%d.%d.%d.%d", &x1, &y1, &x2, &y2, &x3, &y3) != 6){
                    puts("ERROR!: strange argument((\nRead Help!))");
                    exit(41);
                }
                break;
            case 2:
                if(sscanf(optarg, "%d", &thickness)){
                    if (thickness <= 0){
                        puts("ERROR!: thickness need >0, read HELP!!!");
                        exit(41);
                    }
                }
                else{puts("ERROR!: strange argument((\nRead Help!))"); exit(41);}
                break;
            case 3:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                color.r = tmp_clr[0]; color.g = tmp_clr[1]; color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 4:
                fill++;
                break;
            case 5:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                fill_color.r = tmp_clr[0]; fill_color.g = tmp_clr[1]; fill_color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 6:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                //old_color = (RGB){tmp_clr[0], tmp_clr[1], tmp_clr[2]};
                old_color.r = tmp_clr[0]; old_color.g = tmp_clr[1]; old_color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 7:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                new_color.r = tmp_clr[0]; new_color.g = tmp_clr[1]; new_color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 8:

                if (sscanf(optarg, "%d", &num_y) != 1 || num_y <= 0){
                    printf("Error (41): Unknown option argument1\n");
                    exit(41);
                }
                break;
            case 9:
                if (sscanf(optarg, "%d", &num_x) != 1 || num_x <= 0){
                    printf("Error (41): Unknown option argument2\n");
                    exit(41);
                }
                break;


            case 10:
                if(sscanf(optarg, "%d.%d", &x, &y) != 2){
                    puts("ERROR!: strange argument((\nRead Help!))");
                    exit(41);
                }
                break;
            case 11:
                if (sscanf(optarg, "%d", &size) != 1 || size <= 0){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                break;
            case 12:
                if (sscanf(optarg, "%d.%d.%d", &tmp_clr[0], &tmp_clr[1], &tmp_clr[2]) != 3 || !is_color(tmp_clr)){
                    printf("Error (41): Unknown option argument\n");
                    exit(41);
                }
                fl_color.r = tmp_clr[0]; fl_color.g = tmp_clr[1]; fl_color.b = tmp_clr[2];
                tmp_clr[0] = -1; tmp_clr[1] = -1; tmp_clr[2] = -1;
                break;
            case 's':
                flag_sq = 1;
                break;





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
            case 't':
                flag_triangle = 1;
                break;
            case 'b':
                flag_biggest_rect = 1;
                break;
            case 'c':
                flag_collage = 1;
                break;
            case 'f':
                flag_info = 1;                
                break;
            default:
                printf("No such flags exists\nWhat about Help?)\n");
                print_help();
                exit(41);
                break;
        }
    }

    thickness /= 2;

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
    else if(flag_triangle){
        if (fill){
            drow_triangle_fill(image, x1, y1, x2, y2, x3, y3, thickness, color, fill_color);
        }
        else{
            drow_triangle(image, x1, y1, x2, y2, x3, y3, thickness, color);
        }
    }
    else if(flag_biggest_rect == 1){
        findAndColorRectangle(&image, old_color, new_color);
    }
    else if(flag_collage){
        collage(&image, num_x, num_y);
    }
    else if (flag_sq){
        int s = (size / 2) * sqrt(2);
       
        drow_sq(image, x, y, s, fill_color);
    }
    
    write_bmp(output_filename, image);
    

    return 0;
}
