#include <cstdlib>
#include <string>
#include <iostream>

#include "BMP.hpp"
#include "functions.hpp"
#include "secondary_functions.hpp"

using namespace std;


void
mirrorFunc (Rgb** arr, char axis, int left, int up, int right, int down, int H, int W) {
    unsigned char r, g, b;
    Rgb a;

    if (axis == 'y') {
        for (size_t y = H - 1 - down; y < (H - 1) - (up + down) / 2; y++) {
            for (size_t x = left; x < right + 1; x++) {
                a = arr[y][x];
                arr[y][x] = arr[2 * (H - 1) - up - down - y][x];
                arr[2 * (H - 1) - up - down - y][x] = a;
            }
        }
    } else if (axis == 'x') {
        for (size_t y = H - 1 - down; y < H - up; y++) {
            for (size_t x = left; x < (left + right) / 2 + 1; x++) {
                a = arr[y][x];
                arr[y][x] = arr[y][right + left - x];
                arr[y][right + left - x] = a;
            }
        }
    }
}


void
copyFunc(Rgb** arr, int left, int up, int right, int down, int newLeft, int newUp, int H, int W) {

    if (left >= right || up <= down) return;

    Rgb** temporaryArr = new Rgb* [up - down];

    for (size_t i = 0; i < up - down; i++) {
        temporaryArr[i] = new Rgb [right - left];
        for (size_t j = 0; j < right - left; j++) {
            temporaryArr[i][j] = arr[up - i][left + j];
        }
    }

    for (size_t i = 0; i < up - down; i++) {
        for (size_t j = 0; j < right - left; j++) {
            if (newUp - i >= H || newUp - i < 0 || newLeft + j >= W || newLeft + j < 0) continue;
            arr[newUp - i][newLeft + j] = temporaryArr[i][j];
        }
        delete [] temporaryArr[i];
    }
    delete [] temporaryArr;
}


void
replaceFunc(Rgb** arr, int r, int g, int b, int newR, int newG, int newB, int H, int W) {
    for (size_t y = 0; y < H; y++) {
        for (size_t x = 0; x < W; x++) {
            if (arr[y][x].r == r && arr[y][x].b == b && arr[y][x].g == g) {
                arr[y][x].r = newR;
                arr[y][x].g = newG;
                arr[y][x].b = newB;
            }
        }
    }
}


void
filterFunc(Rgb** arr, std::string component, int compVal, int H, int W) {
    for (size_t y = 0; y < H; y++) {
        for (size_t x = 0; x < W; x++) {
            if (component == "red") {
                arr[y][x].r = compVal;
            } else if (component == "blue") {
                arr[y][x].b = compVal;
            } else if (component == "green") {
                arr[y][x].g = compVal;
            }
        }
    }
}


void 
circleFunc(Rgb** arr, int x, int y, int radius, int r, int g, int b, int H, int W) {
    int xStart, yStart, xEnd, yEnd;
    xStart = (x >= radius) ? x - radius : 0;
    xEnd = (x + radius < W) ? x + radius : W - 1;
    yStart = (y >= radius) ? H - (y - radius) - 1 : H - 1;
    yEnd = (y + radius < H) ? H - (y + radius) - 1 : 0;

    for (size_t j = yEnd; j <= yStart; j++) {
        for (size_t i = xStart; i <= xEnd; i++) {
            if (( (i - x) * (i - x) + (j - (H - y - 1)) * (j - (H - y - 1)) ) <= radius * radius) {
                arr[j][i].r = r;
                arr[j][i].g = g;
                arr[j][i].b = b;
            }
        }
    }
}


void 
lineFunc(Rgb** arr, int x1, int y1, int x2, int y2, int r, int g, int b, int thickness, int H, int W) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    circleFunc(arr, x2, y2, thickness / 2, r, g, b, H, W);
    while(x1 != x2 || y1 != y2) 
   {
        circleFunc(arr, x1, y1, thickness / 2, r, g, b, H, W);
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


void
AFunc(Rgb** arr, int r, int g, int b, int thickness, BitmapInfoHeader bmif, BitmapFileHeader bmfh, std::string file) {
    Rgb** newArr = new Rgb* [bmif.height + thickness * 2];

    for (size_t i = 0; i < bmif.height + thickness * 2; i++) {
        newArr[i] = new Rgb [bmif.width + thickness * 2];
        for (size_t j = 0; j < bmif.width + thickness * 2; j++) {
            if (i < thickness || i >= bmif.height + thickness) {
                newArr[i][j].r = r;
                newArr[i][j].g = g;
                newArr[i][j].b = b;
            } else {
                if (j < thickness || j >= bmif.width + thickness) {
                    newArr[i][j].r = r;
                    newArr[i][j].g = g;
                    newArr[i][j].b = b;
                } else {
                    newArr[i][j] = arr[i - thickness][j - thickness];
                }
            }
        }
    }
    bmif.height += 2 * thickness;
    bmif.width += 2 * thickness;

    writeBMP(file, newArr, bmif.height, bmif.width, bmfh, bmif);
}


void
printHelp () {
    std::cout << "Course work for option 5.10, created by Artem Khannanov\n\n";
    std::cout << "Описание функций:\n\n\
    --mirror - отражение заданной области;\n\
        --axis - ось, по которой будет отражение\n\
        --left_up - верхняя левая координата области\n\
        --right_down - правая нижняя координата области\n\
    --copy - копирование заданной области и вставка её в впо другим координатам;\n\
        --left_up - верхняя левая координата области\n\
        --right_down - правая нижняя координата области\n\
        --dest_left_up - верхняя левая координата новой области\n\
    --color_replace - замена одного цвета на другой по всему изображению;\n\
        --old_color - старый цвет\n\
        --new_color - новый цвет\n\
    --rgbfilter - замена компонента цвета на заданное значение по всему изображению;\n\
        --component_name - название компоненты\n\
        --component_value - новое значение компоненты\n";
}