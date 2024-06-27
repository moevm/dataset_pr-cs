#include "bmp_functions.h"
#include <math.h>
void free_BMP(BMP* bmp) {
    if (!bmp)
        return;
    if (bmp->pixels) {
        for (size_t i = 0; i < bmp->bmih->height; i++)
            free(bmp->pixels[i]);
        free(bmp->pixels);
    }
    if (bmp->bmfh)
        free(bmp->bmfh);
    if (bmp->bmih)
        free(bmp->bmih);
    free(bmp);
}
BMP* read_BMP(const char* input_name){
    FILE* f = fopen(input_name, "rb");
    if (!f) {
        printf("Ошибка: Изображение с названием %s не было найдено\n", input_name);
        exit(40);
    }
    BMP* bmp = (BMP*)malloc(sizeof(BMP));
    bmp->bmfh = (BMP_FileHeader*)malloc(sizeof(BMP_FileHeader));
    bmp->bmih = (BMP_InfoHeader*)malloc(sizeof(BMP_InfoHeader));
    fread(bmp->bmfh, sizeof(BMP_FileHeader), 1, f);
    fread(bmp->bmih, sizeof(BMP_InfoHeader), 1, f);
    if (bmp->bmfh->signature != 0x4D42){
        printf("Ошибка: Файл %s не является файлом формата BMP\n", input_name);
        free_BMP(bmp);
        fclose(f);
        exit(40);
    }
    size_t H = bmp->bmih->height, W = bmp->bmih->width;
    size_t padding = (4 - (W*sizeof(RGB))%4)%4;
    if (bmp->bmih->compression != 0 || bmp->bmih->bitsPerPixel != 24 || bmp->bmih->headerSize != 40) {
        printf("Ошибка: Неподдерживаемый формат BMP-файла\n");
        free_BMP(bmp);
        fclose(f);
        exit(40);
    }
    bmp->pixels = (RGB**)malloc(H * sizeof(RGB*));
    for (size_t i = 0; i < H; i++){
        bmp->pixels[i] = (RGB*)malloc(W * sizeof(RGB) + padding);
        fread(bmp->pixels[i], 1, W * sizeof(RGB) + padding, f);
    }
    fclose(f);
    return bmp;
}
void write_BMP(const char* output_name, BMP* bmp) {
    FILE* f = fopen(output_name, "wb");
    if (!f) {
        printf("Ошибка: Не удалось открыть файл для записи\n");
        exit(40);
    }
    fwrite(bmp->bmfh, sizeof(BMP_FileHeader), 1, f);
    fwrite(bmp->bmih, sizeof(BMP_InfoHeader), 1, f);
    size_t H = bmp->bmih->height, W = bmp->bmih->width;
    size_t padding = (4 - (W*sizeof(RGB))%4)%4;
    for (size_t i = 0; i < H; i++) {
        fwrite(bmp->pixels[i], sizeof(RGB), W, f);
        // if (padding > 0) {
        //     unsigned char p[3] = {0, 0, 0};
        //     fwrite(p, 1, padding, f);
        // }
        fwrite("\0\0\0", padding, 1, f);
    }
    free_BMP(bmp);
    fclose(f);
}
BMP* create_BMP(int height, int width, RGB fill_color){
    BMP* bmp = (BMP*)malloc(sizeof(BMP));
    bmp->bmfh = (BMP_FileHeader*)malloc(sizeof(BMP_FileHeader));
    bmp->bmih = (BMP_InfoHeader*)malloc(sizeof(BMP_InfoHeader));
    size_t padding = (4 - (width*sizeof(RGB))%4)%4;
    size_t row_size = padding + width*sizeof(RGB);
    bmp->bmfh->signature = 0x4D42; 
    bmp->bmfh->filesize = sizeof(BMP_FileHeader) + sizeof(BMP_InfoHeader) + row_size;
    bmp->bmfh->reserved1 = 0;
    bmp->bmfh->reserved2 = 0;
    bmp->bmfh->pixelArrOffset = sizeof(BMP_FileHeader) + sizeof(BMP_InfoHeader);
    bmp->bmih->headerSize = sizeof(BMP_InfoHeader);
    bmp->bmih->width = width;
    bmp->bmih->height = height;
    bmp->bmih->planes = 1;
    bmp->bmih->bitsPerPixel = 24;
    bmp->bmih->compression = 0;
    bmp->bmih->imageSize = height * row_size;
    bmp->bmih->xPixelsPerMeter = 0;
    bmp->bmih->yPixelsPerMeter = 0;
    bmp->bmih->colorsInColorTable = 0;
    bmp->bmih->importantColorCount = 0;
    bmp->pixels = (RGB**)malloc(sizeof(RGB*) * height);
    for (size_t i = 0; i < height; i++){
        bmp->pixels[i] = (RGB*)malloc(sizeof(RGB) * row_size);
        for (size_t j = 0; j < width; j++)
            bmp->pixels[i][j] = fill_color;
        memset((unsigned char*)bmp->pixels[i] + width*sizeof(RGB), 0, row_size - width*sizeof(RGB));
    }
    return bmp;
}
void rgb_filter(char component, int value, BMP* picture) {
    for (size_t i = 0; i < picture->bmih->height; i++) {
        for (size_t j = 0; j < picture->bmih->width; j++) {
            switch (component) {
                case 'r':
                    picture->pixels[i][j].r = (unsigned char)value;
                    break;
                case 'g':
                    picture->pixels[i][j].g = (unsigned char)value;
                    break;
                case 'b':
                    picture->pixels[i][j].b = (unsigned char)value;
                    break;
            }
        }
    }
}
RGB** copy_area(BMP* bmp, int left, int up, int right, int down) {
    int W = right - left, H = down - up;
    RGB** copy = (RGB**)malloc(H * sizeof(RGB*));
    for (int i = 0; i < H; i++)
        copy[i] = (RGB*)malloc(W * sizeof(RGB));
    for (int i = 0; i < H && i + up < bmp->bmih->height; i++)
        for (int j = 0; j < W && left + j < bmp->bmih->width; j++) 
            copy[(H-1) - i][j] = bmp->pixels[(bmp->bmih->height - 1) - (up + i)][left + j];
    return copy;
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void rotate(BMP *bmp , int left, int up, int right, int down, int angle){
    int W = bmp->bmih->width;
    int H = bmp->bmih->height;
    if (left < 0) {left = 0;}
    if (up < 0) {up = 0;}
    if (right > W) {right = W;}
    if (down > H) {down = H;}
    if (left > right) {swap(&left, &right);}
    if (up > down) {swap(&up, &down);}
    int h = (down - up), w = (right - left);
    int new_up = (up + down)/2 - w/2;
    int new_left = (left + right)/2 - h/2;
    RGB **copy = copy_area(bmp, left, up, right, down);
    switch (angle){
        case 90:
            for (int i = 0; i < w && new_up + i < H; i ++)
                for (int j = 0; j < h && j + new_left < W; j++)
                    set_pixel(bmp, new_left + j, new_up + i, copy[(h-1) - j][(w-1) - i]);
            break;
        case 180:
            for (int i = 0; i < h && up + i < H; i++)
                for (int j = 0; j < w && left + j < W; j++)
                    set_pixel(bmp, left + j, up + i, copy[i][(w-1) - j]);
            break;
        case 270:
            for (int i = 0; i < w && new_up + i < H; i ++)
                for (int j = 0; j < h && j + new_left + j < W; j++)
                    set_pixel(bmp, new_left + j, new_up + i, copy[j][i]);
            break;
    }
    for (int i = 0; i < h; i++)
        free(copy[i]);
    free(copy);
}
void set_pixel(BMP *bmp, int x, int y, RGB color) {
    if (x < 0 || x >= bmp->bmih->width || y < 0 || y >= bmp->bmih->height)
        return;
    y = bmp->bmih->height - 1 - y;
    bmp->pixels[y][x] = color;
}
void set_circle(BMP* bmp, int xc, int yc, int radius, RGB color){
	for (int y = 0; y < bmp->bmih->height; y++)
		for(int x = 0; x < bmp->bmih->width; x++)
			if((x - xc) * (x - xc) + (y - yc) * (y - yc) <= radius * radius)
				set_pixel(bmp,x,y,color);
}
void draw_line(BMP* bmp, int x0, int y0, int x1, int y1, RGB color, int thickness) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;
    int error = dx - dy;
    set_circle(bmp, x1, y1, (thickness - 1)/2, color);
    while (x0 != x1 || y0 != y1) {
        set_circle(bmp, x0, y0, (thickness - 1)/2, color);
        int error2 = error * 2;
        if (error2 > -dy) {
            error -= dy;
            x0 += sign_x;
        }
        if (error2 < dx) {
            error += dx;
            y0 += sign_y;
        }
    }
}
void squared_lines(BMP* bmp, int left, int up, int side_size, int thickness, RGB color, int fill, RGB* fill_color) {
    int right = (left + side_size - 1), down = (up + side_size - 1);
    if (side_size > 0 && fill)
        for (int y = up; y < down; y++)
            for(int x = left; x < right; x++)
                set_pixel(bmp, x, y, *fill_color);
    draw_line(bmp, left, up, right, up, color, thickness);
    draw_line(bmp, left, up, left, down, color, thickness);
    draw_line(bmp, right, up, right, down, color, thickness);
    draw_line(bmp, left, down, right, down, color, thickness);
    draw_line(bmp, left, up, right,down, color, thickness);
    draw_line(bmp, left, down, right, up, color, thickness);
}
void square_rhombus(BMP* bmp, int x0, int y0, int side_size, RGB* fill_color){
    int H = bmp->bmih->height, W = bmp->bmih->width;
    int diag = side_size * sqrt(2);
    int xc = x0 , yc = y0 + diag/2;
    draw_line(bmp, x0, y0, x0 + diag/2,y0 + diag/2, *fill_color, 1);
    draw_line(bmp,x0, y0, x0-diag/2, y0+diag/2, *fill_color, 1);
    draw_line(bmp, x0, y0 + diag, x0 + diag/2, y0 + diag/2, *fill_color, 1);
    draw_line(bmp, x0-diag/2, y0+diag/2, x0 ,y0 +diag, *fill_color, 1);
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            double x_prime = x - xc;
            double y_prime = y - yc;
            double x_rot = (x_prime - y_prime) / sqrt(2);
            double y_rot = (x_prime + y_prime) / sqrt(2);
            if (abs(x_rot) <= diag / 2 && abs(y_rot) <= diag / 2) {
                set_pixel(bmp, x, y, *fill_color);
            }
        }
    }
}