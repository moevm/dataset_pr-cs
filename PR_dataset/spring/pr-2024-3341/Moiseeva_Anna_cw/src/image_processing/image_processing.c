#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_processing.h"

Rgb check_color(int r, int g, int b) {
    if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0) {
        fprintf(stdout, "Значения цвета должны быть в диапазоне от 0 до 255.\n");
        exit(45);
    }
    Rgb color;
    color.r = (unsigned char)r;
    color.g = (unsigned char)g;
    color.b = (unsigned char)b;
    return color;
}

void color_pixel(int x, int y, Rgb **arr, Rgb color, unsigned int H, unsigned int W) {
    if (x >= 0 && x < (int)W && y >= 0 && y < (int)H) {
        arr[y][x].b = color.b;
        arr[y][x].g = color.g;
        arr[y][x].r = color.r;
    }
}

void draw_thick(int x, int y, Rgb **arr, int width, unsigned int H, unsigned int W, Rgb color) {
    for (int i = -width / 2; i <= width / 2; i++) {
        for (int j = -width / 2; j <= width / 2; j++) {
            color_pixel(x + i, y + j, arr, color, H, W);
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2, int width, unsigned int H, unsigned int W, Rgb **arr, Rgb color) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    draw_thick(x2, y2, arr, width, H, W, color);
    while (x1 != x2 || y1 != y2) {
        draw_thick(x1, y1, arr, width, H, W, color);
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int width, unsigned int H, unsigned int W, Rgb **arr, Rgb color) {
    draw_line(x1, y1, x2, y2, width, H, W, arr, color);
    draw_line(x2, y2, x3, y3, width, H, W, arr, color);
    draw_line(x1, y1, x3, y3, width, H, W, arr, color);
}

int check_tr(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
    int pr1 = (x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y);
    int pr2 = (x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y);
    int pr3 = (x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y);
    if ((pr1 >= 0 && pr2 >= 0 && pr3 >= 0) || (pr1 <= 0 && pr2 <= 0 && pr3 <= 0)) return 1;
    else return 0;
}

void fill_tr(Rgb **arr, Rgb color, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int H, unsigned int W) {
    for (int i = 0; i < (int)H; i++) {
        for (int j = 0; j < (int)W; j++) {
            if (check_tr(j, i, x1, y1, x2, y2, x3, y3)) {
                color_pixel(j, i, arr, color, H, W);
            }
        }
    }
}

void find_color_max_rect(unsigned int H, unsigned int W, Rgb **arr, Rgb color_find, Rgb color_fill) {
    int maxrectwidth = 0, maxrectheight = 0;
    int maxrectx = 0, maxrecty = 0;

    for (int i = 0; i < (int)H; i++) {
        for (int j = 0; j < (int)W; j++) {
            Rgb current_color = arr[i][j];
            if (color_find.b == current_color.b && color_find.g == current_color.g && color_find.r == current_color.r) {
                int rectwidth = 1;
                while (j + rectwidth < (int)W && color_find.b == arr[i][j + rectwidth].b && color_find.g == arr[i][j + rectwidth].g && color_find.r == arr[i][j + rectwidth].r) {
                    rectwidth++;
                }
                int rectheight = 1;
                int validRow;
                while (i + rectheight < (int)H) {
                    validRow = 1;
                    for (int k = 0; k < rectwidth; k++) {
                        Rgb temp_color = arr[i + rectheight][j + k];
                        if (color_find.b != temp_color.b || color_find.g != temp_color.g || color_find.r != temp_color.r) {
                            validRow = 0;
                            break;
                        }
                        }
                    if (!validRow) break;
                    rectheight++;
                }
                if (rectheight * rectwidth > maxrectheight * maxrectwidth) {
                    maxrectheight = rectheight;
                    maxrectwidth = rectwidth;
                    maxrectx = j;
                    maxrecty = i;
                }
            }
        }
    }

    for (int y = maxrecty; y < maxrecty + maxrectheight; y++) {
        for (int x = maxrectx; x < maxrectx + maxrectwidth; x++) {
            color_pixel(x, y, arr, color_fill, H, W);
        }
    }
}

Rgb** collage(int x, int y, unsigned int H, unsigned int W, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb **arr) {
    unsigned int collage_w = x * W;
    unsigned int collage_h = y * H;
    Rgb **temp = malloc(collage_h * sizeof(Rgb*));
    for (int i = 0; i < (int)collage_h; i++) {
        temp[i] = malloc(collage_w * sizeof(Rgb));
    }

    for (int i = 0; i < (int)collage_h; i++) {
        int row = i % H;
        for (int j = 0; j < (int)collage_w; j++) {
            int column = j % W;
            temp[i][j] = arr[row][column];
        }
    }

    for (int i = 0; i < (int)H; i++) {
        free(arr[i]);
    }
    free(arr);

    bmif->height = collage_h;
    bmif->width = collage_w;
    bmfh->filesize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + collage_h * collage_w * sizeof(Rgb);
    bmfh->pixelArrOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    return temp;
}

void do_bin(Rgb **arr, unsigned int H, unsigned int W, int porog) {
    int tmp1, tmp2, tmp3;
    for (int i = 0; i < (int)H; i++) {
        for (int j = 0; j < (int)W; j++) {
            tmp1 = (int)arr[i][j].r;
            tmp2 = (int)arr[i][j].g;
            tmp3 = (int)arr[i][j].b;
            if (tmp1 + tmp2 + tmp3 >= porog) {
                arr[i][j].r = 255;
                arr[i][j].g = 255;
                arr[i][j].b = 255;
            } else {
                arr[i][j].r = 0;
                arr[i][j].g = 0;
                arr[i][j].b = 0;
            }
        }
    }
}

void shift(Rgb **arr, unsigned int H, unsigned int W, int shift_x, int shift_y) {
    Rgb **temp = malloc(H * sizeof(Rgb*));
    for (int i = 0; i < (int)H; i++) {
        temp[i] = malloc(W * sizeof(Rgb));
    }

    for (int i = 0; i < (int)H; i++) {
        for (int j = 0; j < (int)W; j++) {
            int new_i = (i + shift_y) % H;
            int new_j = (j + shift_x) % W;
            if (new_j < 0) new_j += W;
            if (new_i < 0) new_i += H;
            temp[new_i][new_j] = arr[i][j];
        }
    }

    for (int i = 0; i < (int)H; i++) {
        for (int j = 0; j < (int)W; j++) {
            arr[i][j] = temp[i][j];
        }
        free(temp[i]);
    }
    free(temp);
}