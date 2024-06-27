#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#pragma pack(push, 1) // выравнивание в 1 байт для структур

typedef struct BMPHeader{
    char ID[2];
    uint32_t file_size;
    uint16_t reversed1;
    uint16_t reversed2;
    uint32_t  pixel_offset;
}BMPHeader;

typedef struct RGB{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} RGB;

typedef struct DIBHeader{
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t color_planes;
    uint16_t bit_per_pixel;
    uint32_t comp; // признак наличия сжатия
    uint32_t data_size;
    uint32_t pwidth;
    uint32_t pheight;
    uint32_t colors_palette;
    uint32_t imp_color_count;
}DIBHeader;

typedef struct BMPFile{
    BMPHeader bheader;
    DIBHeader dheader;
    RGB** data;
}BMPFile;

#pragma pack(pop)

BMPFile* loadBMPfile(char* file_name){
    FILE* fp = fopen(file_name, "rb");
    
    if (!fp){
        printf("File didn't be open");
        exit(45);
    }

    BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile)); // выделяем память для основной структуры
    fread(&(bmp_file->bheader), sizeof(BMPHeader), 1, fp); // считываем заголовки
    fread(&(bmp_file->dheader), sizeof(DIBHeader), 1, fp);
    
    bmp_file->bheader.ID[2] = '\0';
    if (strcmp(bmp_file->bheader.ID, "BM")) {
        printf("File doesn't have ID BM\n");
        exit(45);

    }  

    if (bmp_file->dheader.bit_per_pixel != 24 || bmp_file->dheader.comp != 0) {
        // printf("Error of bit_per_pixel or compression\n");
        exit(45);
    }


    int w = bmp_file->dheader.width;
    int h = bmp_file->dheader.height;
    bmp_file->data = (RGB**)malloc(h * sizeof(RGB*));
    for (int i = 0; i < h; i++){
        int padding = (4 - (w*sizeof(RGB)) % 4) % 4;
        bmp_file->data[i] = (RGB*)malloc(w * sizeof(RGB) + padding);
        fread(bmp_file->data[i], 1, w * sizeof(RGB) + padding, fp);
    }
    fclose(fp);
    return bmp_file;
    
}


void writeBMPfile(char* name_file, BMPFile* input_file){
    FILE* file = fopen(name_file, "wb");
    fwrite(&input_file->bheader, sizeof(BMPHeader), 1, file);
    fwrite(&input_file->dheader, sizeof(DIBHeader), 1, file);
    int width = input_file->dheader.width;
    int height = input_file->dheader.height;
    uint8_t padding = (4 - (width * sizeof(RGB)) % 4) % 4;
    uint8_t paddingBytes[3] = {0};
    for (int i = 0; i < height; i++) {
        fwrite(input_file->data[i], sizeof(RGB), width, file);
        fwrite(paddingBytes, sizeof(uint8_t), padding, file); // Записываем выравнивающие байты
    }
    fclose(file);
}

int cmp_color(RGB color1, RGB color2){
    return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
}

RGB rgb(int r, int g, int b){
    RGB tmp;
    tmp.r = r;
    tmp.g = g;
    tmp.b = b;
    return tmp;
}

void set_color(RGB* cell, RGB color){
    cell->r = color.r;
    cell->g = color.g;
    cell->b = color.b;
}

void fill_circle(BMPFile* bmp_file, RGB color, int x0, int y0, int radius){ 
    // в функцию подаются уже исправленные координаты (x, y) -> (x, h - y)
    // (0, 0) -> (0, h)
    int h = bmp_file->dheader.height;
    int w = bmp_file->dheader.width;
    for (int i = -radius; i <= radius; i++){
        for (int j = -radius; j <= radius; j++){
            int x_r = x0 + j;
            int y_r = y0 - i;
            if (i * i + j * j <= radius * radius &&
            x_r >= 0 && x_r < w && y_r >= 0 && y_r < h){
                set_color(&((bmp_file->data)[y_r][x_r]), color);
            }
        }
    }

}

void draw_line(BMPFile* bmp_file, RGB color, 
            int x1, int y1, int x2, int y2, int thickness){
    thickness = thickness - 1;
    if (thickness < 0){
        printf("Error sign of thickness");
        exit(45);
        return;
    }

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    set_color(&((bmp_file->data)[y2][x2]), color);
    fill_circle(bmp_file, color, x2, y2, thickness);
    while(x1 != x2 || y1 != y2) 
    {
        set_color(&((bmp_file->data)[y1][x1]), color);
        fill_circle(bmp_file, color, x1, y1, thickness);
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }

}

void draw_rectangle(BMPFile* bmp_file, RGB color, int x0, int y0, 
                    int x1, int y1, int th, int is_fill, RGB color_fill){
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    for (int i = 0; i < th; i++){
        draw_line(bmp_file, color, x0 + i, y0 - i, x0 + dx - i, y0 - i, 1); // top
        draw_line(bmp_file, color, x0 + i, y0 - i, x0 + i, y0 - dy + i, 1); // left
        draw_line(bmp_file, color, x0 + i, y0 - dy + i, x0 + dx - i, y0 - dy + i, 1); // bottom
        draw_line(bmp_file, color, x0 - i + dx, y0 - i, x0 + dx - i, y0 - dy + i, 1); // right
    }
    
    if (is_fill == 1){
        for (int y = y0 - th; y >= (y1 + th); y--){
            for (int x = x0 + th; x <= (x1 - th); x++){
                set_color(&((bmp_file->data)[y][x]), color_fill);
            }
        }
    }
    else if (is_fill == 2){
        int h = bmp_file->dheader.height;
        int w = bmp_file->dheader.width;
        for (int y = 0; y < h; y++){
            for (int x = 0; x < w; x++){
                if (!(x > x0 && y < y0 && x < x1 && y > y1)){
                    set_color(&((bmp_file->data)[y][x]), color_fill);
                }
            }
        }
    }
}

void draw_8pixels(BMPFile* bmp_file, int64_t x0, int64_t y0,
                  int64_t x, int64_t y, int32_t thickness, RGB color)
{
    fill_circle(bmp_file, color, x + x0, y + y0, thickness);
    fill_circle(bmp_file, color ,x + x0, -y + y0, thickness);
    fill_circle(bmp_file, color, -x + x0, -y + y0, thickness);
    fill_circle(bmp_file, color, -x + x0, y + y0, thickness);
    fill_circle(bmp_file, color, y + x0, x + y0, thickness);
    fill_circle(bmp_file, color, y + x0, -x + y0, thickness);
    fill_circle(bmp_file, color, -y + x0, -x + y0, thickness);
    fill_circle(bmp_file, color, -y + x0, x + y0, thickness);
}

void draw_circle(BMPFile* bmp_file, int64_t x0, int64_t y0, int32_t radius,
                 int32_t thickness, RGB color,
                 uint8_t is_fill, RGB fill_color){
    int64_t dist;

    int64_t x = 0;
    int64_t y = radius;
    if (thickness % 2 == 0){
        thickness = (thickness) / 2;
    }
    else{
       thickness = (thickness + 1) / 2; 
    }

    if (thickness < 0){
        printf("Error sign of thickness");
        return;
    }


    if (is_fill == 1) {
        fill_circle(bmp_file, fill_color, x0, y0, radius);
    }
    else if (is_fill == 2){
        int h = bmp_file->dheader.height;
        int w = bmp_file->dheader.width;
        for (int i = 0; i < w; i++){
            for (int j = 0; j < h; j++){
                if (!((i - x0) * (i - x0)  + (j - y0) * (j - y0) <= radius * radius)){
                set_color(&((bmp_file->data)[j][i]), fill_color);
                }
            }
        }
    }
   
    dist = 3 - 2 * y;
    while (x <= y) {
        draw_8pixels(bmp_file, x0, y0, x, y, thickness, color);
        if (dist < 0)
            dist = dist + 4 * x + 6;
        else {
            dist = dist + 4 * (x - y) + 10;
            y--;
        }
        x++; 
    }
}

void draw_circle_ornament(BMPFile* bmp_file, RGB color){
    int h = bmp_file->dheader.height;
    int w = bmp_file->dheader.width;
    int x0 = (int)(w / 2);
    int y0 = (int)(h / 2);
    int r;
    int radius1 = (int)(h / 2);
    int radius2 = (int)(w / 2);
    if (radius1 < radius2){
        r = radius1;
    }
    else{
        r = radius2;
    }
    draw_circle(bmp_file, x0, y0, r, 1, color, 2, color);
}

void draw_rectangle_ornament(BMPFile* bmp_file, int thickness, RGB color, int cnt){
    int h = bmp_file->dheader.height;
    int w = bmp_file->dheader.width;
    int m = h < w ? h : w;
    int count = m / (4 * thickness);
    if (cnt < count){
        count = cnt;
    }
    h--; 
    w--;
    int start_x = 0;
    int start_y = h;
    int end_x = w;
    int end_y = 0;
    for (int i = 0; i < count; i++){
        draw_rectangle(bmp_file, color, start_x, start_y, end_x, end_y, thickness, 0, rgb(0, 0, 0));
        start_x += thickness * 2;
        start_y -= thickness * 2;
        end_x -= thickness * 2;
        end_y += thickness * 2;
    }

}

void draw_semicircles_ornament(BMPFile* bmp_file, RGB color, int thickness, int count){
    int h = bmp_file->dheader.height;
    int w = bmp_file->dheader.width;
    float tb_side = (float)w / (float)count;
    float lr_side = (float)h / (float)count;
    tb_side = (tb_side - (int)tb_side) != 0 ? tb_side + 1 : (int)tb_side;
    lr_side = (lr_side - (int)lr_side) != 0 ? lr_side + 1 : (int)lr_side;
    int tb_radius =  (int)(tb_side / 2);
    int lr_radius =  (int)(lr_side / 2);
    for (int i = 0; i < count; i++){
        draw_circle(bmp_file, tb_radius + (2 * tb_radius * i), 0, 
                    tb_radius, thickness, color, 0, rgb(0, 0, 0));
        draw_circle(bmp_file, tb_radius + (2 * tb_radius * i), h - 1, 
                    tb_radius, thickness, color, 0, rgb(0, 0, 0));
        draw_circle(bmp_file, 0, lr_radius + (2 * lr_radius * i), 
                    lr_radius, thickness, color, 0, rgb(0, 0, 0));
        draw_circle(bmp_file, w - 1, lr_radius + (2 * lr_radius * i), 
                    lr_radius, thickness, color, 0, rgb(0, 0, 0));
    }
}

int get_height(BMPFile* bmp_file, int x0, int y0, RGB color){
    int count = 0;
    for (int i = y0; i >= 0; i--){
        if (cmp_color(bmp_file->data[i][x0], color)){
            count++;
        }
        else{
            return count;
        }
    }
    return count;
}

int get_width(BMPFile* bmp_file, int x0, int y0, RGB color){
    int count = 0;
    for (int i = x0; i < bmp_file->dheader.width; i++){
        if (cmp_color(bmp_file->data[y0][i], color)){
            count++;
        }
        else{
            return count;
        }
    }
    return count;
}

int check_rect(int coords[][4], int len, int x, int y){
    for (int i = 0; i < len; i++){
            if (coords[i][0] <= x && x <= coords[i][2] &&
                coords[i][1] >= y && y >= coords[i][3]){
                    return 0;
            }
        }
    return 1;
}

void find_and_border_rectangle(BMPFile* bmp_file, RGB find_color, RGB border_color, int thickness){
    int coords[100][4];
    int w = bmp_file->dheader.width;
    int h = bmp_file->dheader.height;
    int count = 0;
    for (int y = h - 1; y >= 0; y--){
        for (int x = 0; x < w; x++){
            if (cmp_color((bmp_file->data[y][x]), find_color) &&
                check_rect(coords, count, x, y)){
                coords[count][0] = x - 1;
                coords[count][1] = y + 1;
                coords[count][2] = x + get_width(bmp_file, x, y, find_color);
                coords[count][3] = y - get_height(bmp_file, x, y, find_color);
                count++;
            }
        }
    }
    for (int i = 0; i < count; i++){
        draw_rectangle(bmp_file, border_color, coords[i][0], coords[i][1],
                                coords[i][2], coords[i][3], thickness, 0, rgb(0, 0, 0));
    }
}

void change_color(BMPFile* input_file, RGB old_color, RGB new_color){
    for (int i = 0; i < input_file->dheader.height; i++){
        for (int j = 0; j < input_file->dheader.width; j++){
            RGB rgb = (input_file->data)[i][j];
            if (cmp_color(rgb, old_color)){
                set_color(&((input_file->data)[i][j]), new_color);
            } 
        }
    }
}

void print_help_info(char* file_name){
    printf("Usage: %s [OPTIONS] FILE\n", file_name);
    printf("%4s  %-40s\n\t %-30s\n",
           "-h,", "--help", "print this help and exit");
    printf("%4s  %-40s\n\t %-30s\n",
           "-r,", "--color_repalce", "to repace pixel in new color");
    printf("%4s  %-40s\n\t %-30s\n",
           "-d,", "--old_color", "arg to set old_color");
    printf("%4s  %-40s\n\t %-30s\n",
           "-n,", "--new_color", "arg to set new color");
    printf("%4s  %-40s\n\t %-30s\n",
           "-o,", "--ornament", "func to draw ornament");
    printf("%4s  %-40s\n\t %-30s\n",
           "-a,", "--pattern", "arg to set type of pattern");
    printf("%4s  %-40s\n\t %-30s\n",
           "-c,", "--color", "arg to set color");
    printf("%4s  %-40s\n\t %-30s\n",
           "-k,", "--thickness", "arg to set thickness");
    printf("%4s  %-40s\n\t %-30s\n",
           "-u,", "--count", "arg to set count");
    printf("%4s  %-40s\n\t %-30s\n",
           "-f,", "--filled_rects", "func to find and border filled rects");
    printf("%4s  %-40s\n\t %-30s\n",
           "-b,", "--border_color", "arg to set border color");
    printf("%4s  %-40s\n\t %-30s\n",
           "-i,", "--input", "name of input file");
    printf("%4s  %-40s\n\t %-30s\n",
           "-o,", "--output", "name of output file");
}

void contrast(BMPFile* bmp_file, float alpha, int beta){
    int h = bmp_file->dheader.height;
    int w = bmp_file->dheader.width;
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            int r, g, b;
            RGB old_color = bmp_file->data[y][x];
            r = ((alpha * old_color.r) + beta);
            if (r >= 256){r = 255;}
            g = ((alpha * old_color.g) + beta);
            if (g >= 256){g = 255;}
            b = ((alpha * old_color.b) + beta);
            if (b >= 256){b = 255;}
            set_color(&(bmp_file->data[y][x]), rgb(r, g, b));
        }
    }
}


int main(int argc, char* argv[]){
    printf("Course work for option 4.10, created by Georgii Kozlov\n");
    struct option long_option[] = {
        {"color_replace", no_argument,  0, 'r'},
        {"old_color",   required_argument, 0, 'd'},
        {"new_color",   required_argument, 0, 'n'},
        {"ornament", no_argument,  0, 'o'},
        {"pattern",   required_argument, 0, 'a'},
        {"color",   required_argument, 0, 'c'},
        {"thickness",   required_argument, 0, 'k'},
        {"count",   required_argument, 0, 'u'},
        {"filled_rects",   no_argument, 0, 'f'},
        {"border_color",   required_argument, 0, 'b'},
        {"input",   required_argument, 0, 'i'},
        {"output",   required_argument, 0, 'p'},
        {"help",   no_argument, 0, 'h'},
        {"alpha",   required_argument, 0, 'T'},
        {"beta",   required_argument, 0, 'M'},
        {"contrast",   no_argument, 0, 'C'},
        {"blur",   no_argument, 0, 'B'},
        {"size",   required_argument, 0, 'S'},
        {0, 0, 0, 0}
    };
    int opt;
    int option_index;
    char name_output_file[100] = "out.bmp";
    char name_of_input_file[100] = "insert.bmp";
    

    char figure[100];
    float alpha;
    int beta;
    int s_color_replace = 0;
    int s_ornament = 0;
    int s_filled_rects = 0;
    int contrast1 = 0;
    int help_info = 0;
    int input_name = 0;
    RGB old_color;
    RGB new_color;
    RGB border_color;
    RGB color;
    int thickness;
    int count;
    int r1, g1, b1;

    while ((opt = getopt_long(argc, argv, "rofhd:n:p:i:a:c:u:k:b:", long_option, &option_index)) != -1){
        switch(opt){
            case 'B': // contrast
                return 0;
                break;
            case 'C': // contrast
                contrast1 = 1;
                break;
            case 'r': // color_replace
                s_color_replace = 1;
                break;
            case 'o': // ornament
                s_ornament = 1;
                break;
            case 'f': // filled_rects
                s_filled_rects = 1;
                break;
            case 'h': // help_info
                help_info = 1;
                break;
            case 'd': // old_color
                sscanf(optarg, "%d.%d.%d", &r1, &g1, &b1);
                if (r1 < 0 || g1 < 0 || b1 < 0){
                    // printf("Error color\n");
                    exit(45);
                }
                old_color.r = r1;
                old_color.g = g1;
                old_color.b = b1;
                break;
            case 'n': // new_color
                sscanf(optarg, "%d.%d.%d", &r1, &g1, &b1);
                if (r1 < 0 || g1 < 0 || b1 < 0){
                    // printf("Error color\n");
                    exit(45);
                }
                new_color.r = r1;
                new_color.g = g1;
                new_color.b = b1;
                break;
            case 'p': // out_put_file
                sscanf(optarg, "./%s", name_output_file);
                break;
            case 'i': // input_file
                sscanf(optarg, "./%s", name_of_input_file);
                input_name = 1;
                break;
            case 'a': // name figure
                sscanf(optarg, "%s", figure);
                break;
            case 'c': // color
                sscanf(optarg, "%d.%d.%d", &r1, &g1, &b1);
                if (r1 < 0 || g1 < 0 || b1 < 0){
                    // printf("Error color\n");
                    exit(45);
                    }
                color.r = r1;
                color.g = g1;
                color.b = b1;
                break;
            case 'u': // count
                sscanf(optarg, "%d", &count);
                if (count < 0){
                    printf("Error count\n");
                    exit(45);
                }
                break;
            case 'k': // thickness
                sscanf(optarg, "%d", &thickness);
                if (thickness <= 0){
                    printf("Error thikness\n");
                    exit(45);
                }
                break;
            case 'b': // border_color
                sscanf(optarg, "%d.%d.%d", &r1, &g1, &b1);
                if (r1 < 0 || g1 < 0 || b1 < 0){
                    printf("Error color\n");
                    exit(45);
                }
                border_color.r = r1;
                border_color.g = g1;
                border_color.b = b1; 
                break;
            case 'T': // alpha
                sscanf(optarg, "%f", &alpha);
                if (alpha < 0){
                    exit(45);
                }
                break;
            case 'M': // alpha
                sscanf(optarg, "%d", &beta);
                if (beta < 0){
                    exit(45);
                }
                break;
        }

    }


    if (help_info){
        print_help_info(name_of_input_file);
        return 0;
    }

    if (!input_name && argc > 1){
        strcpy(name_of_input_file, argv[argc - 1]);
    }

    BMPFile* bmp_file =  loadBMPfile(name_of_input_file);


    if ((s_color_replace + s_ornament + s_filled_rects + help_info) > 1){
        printf("Error of keys\n");
        exit(45);
    }
    else if (contrast1){
        contrast(bmp_file, alpha, beta);
    }
    else if (s_color_replace){
        change_color(bmp_file, old_color, new_color);
    }
    else if (s_ornament){
        if (!strcmp(figure, "rectangle")){
            draw_rectangle_ornament(bmp_file, thickness, color, count);
        }
        else if (!strcmp(figure, "circle")){
            draw_circle_ornament(bmp_file, color);
        }
        else if (!strcmp(figure, "semicircles")){
            draw_semicircles_ornament(bmp_file, color, thickness, count);
        }
        else{
            printf("Error pattern!\n");
            exit(45);
        }
    }
    else if (s_filled_rects){
        find_and_border_rectangle(bmp_file, color, border_color, thickness);
    }
    else{
        printf("Error main flag!\n");
        printf("Функция для справки --help -h\n");
        exit(45);
    }
    writeBMPfile(name_output_file, bmp_file);
    return 0;
}
