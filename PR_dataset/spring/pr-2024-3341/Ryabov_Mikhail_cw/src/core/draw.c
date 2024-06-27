#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/draw.h"
#include "../headers/utils.h"

Rgb** drawSquare(BitmapInfoHeader* BMPInfo, Rgb** arr, SquareProperty sp)
{
    if(sp.sumStatusKeys == 1)
    {
        fillingSquare(BMPInfo, arr, sp);
        drawLineByBrezenhem(arr, sp.left, sp.up, sp.left+sp.side_size, sp.up, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left+sp.side_size, sp.up, sp.left+sp.side_size, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left, sp.up+sp.side_size, sp.left+sp.side_size, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left, sp.up, sp.left, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
    }
    else
    {
        drawLineByBrezenhem(arr, sp.left, sp.up, sp.left+sp.side_size, sp.up, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left+sp.side_size, sp.up, sp.left+sp.side_size, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left, sp.up+sp.side_size, sp.left+sp.side_size, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
        drawLineByBrezenhem(arr, sp.left, sp.up, sp.left, sp.up+sp.side_size, BMPInfo, sp.thickness, sp.color);
    }
    return arr;
}

void fillingSquare(BitmapInfoHeader* BMPInfo, Rgb** arr, SquareProperty sp)
{
    const int left = sp.left;
    const int side = sp.left + sp.side_size;
    const int up = sp.up;
    const int sideUp = sp.up + sp.side_size;
    for(int i = left; i < side; i++)
    {
        for(int j = up; j < sideUp; j++)
        {
            drawPoint(i, j, sp.fill_color, arr, BMPInfo->width, BMPInfo->height);
        }
    }
}

void drawLineByBrezenhem(Rgb** pixels, int x0, int y0, int x1, int y1, BitmapInfoHeader* bifh, int thick, Rgb color)
{
    int radius;
    if(thick == 1) radius = 0;
    else if (thick % 2 == 1) radius = (int)(thick+1)/2;
    else radius = (int)thick/2;
    const int deltaX = abs(x1 - x0);
    const int deltaY = abs(y1 - y0);
    const int signX = x0 < x1 ? 1 : -1;
    const int signY = y0 < y1 ? 1 : -1;
    int error = deltaX - deltaY;
    drawCircle(x1, y1, radius, color, pixels, bifh->width, bifh->height);
    while(x0 != x1 || y0 != y1)
    {
        drawCircle(x0, y0, radius, color, pixels, bifh->width, bifh->height);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x0 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y0 += signY;
        }
    }
}

void drawCircle(int x0, int y0, int radius, Rgb color, Rgb** pixels, int width, int height)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y)
    {
        drawPoint(x + x0, y + y0, color, pixels, width, height);
        drawPoint(y + x0, x + y0, color, pixels, width, height);
        drawPoint(-x + x0, y + y0, color, pixels, width, height);
        drawPoint(-y + x0, x + y0, color, pixels, width, height);
        drawPoint(-x + x0, -y + y0, color, pixels, width, height);
        drawPoint(-y + x0, -x + y0, color, pixels, width, height);
        drawPoint(x + x0, -y + y0, color, pixels, width, height);
        drawPoint(y + x0, -x + y0, color, pixels, width, height);
        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
    for(int cury=-radius; cury<=radius; cury++)
        for(int curx=-radius; curx<=radius; curx++)
            if(curx*curx+cury*cury <= radius*radius)
                drawPoint(x0+curx, y0+cury, color, pixels, width, height);
}

void drawPoint(int x0, int y0, Rgb color, Rgb** pixels, int width, int height)
{
    if(x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
    {
        pixels[y0][x0].r = color.r;
        pixels[y0][x0].g = color.g;
        pixels[y0][x0].b = color.b;
    }
}

Rgb** exchangeAreas(BitmapInfoHeader* BMPinfo, char* typeExchange, int left, int up, int right, int down, Rgb** pixels)
{
    checkCorrectPlacement(&left, &up, &right, &down, BMPinfo->width, BMPinfo->height);
    if(abs(right - left) <= 1 || abs(down - up) <= 1)
        return pixels;
    const int widthArea = (int)(right - left)/2;
    const int heightArea = (int)(down - up)/2;
    const int type = isCorrectType(typeExchange);
    if(!type) callError(45);

    Rgb** leftUp = (Rgb**)malloc(sizeof(Rgb**) * heightArea);
    Rgb** leftDown = (Rgb**)malloc(sizeof(Rgb**) * heightArea);
    Rgb** rightUp = (Rgb**)malloc(sizeof(Rgb**) * heightArea);
    Rgb** rightDown = (Rgb**)malloc(sizeof(Rgb**) * heightArea);

    copyArea(leftUp, widthArea, heightArea, left, up, pixels);
    copyArea(leftDown, widthArea, heightArea, left, up+heightArea, pixels);
    copyArea(rightUp, widthArea, heightArea, left + widthArea, up, pixels);
    copyArea(rightDown, widthArea, heightArea, left + widthArea, up+heightArea, pixels);

    if(type == 2){
        pasteArea(leftUp, pixels, widthArea, heightArea, left, up+heightArea);
        pasteArea(leftDown, pixels, widthArea, heightArea, left+widthArea, up+heightArea);
        pasteArea(rightUp, pixels, widthArea, heightArea, left, up);
        pasteArea(rightDown, pixels, widthArea, heightArea, left+widthArea, up);
    }
    if(type == 1){
        pasteArea(leftUp, pixels, widthArea, heightArea, left+widthArea, up);
        pasteArea(leftDown, pixels, widthArea, heightArea, left, up);
        pasteArea(rightUp, pixels, widthArea, heightArea, left+widthArea, up+heightArea);
        pasteArea(rightDown, pixels, widthArea, heightArea, left, up+heightArea);
    }
    if(type == 3){
        pasteArea(leftUp, pixels, widthArea, heightArea, left+widthArea, up+heightArea);
        pasteArea(leftDown, pixels, widthArea, heightArea, left+widthArea, up);
        pasteArea(rightUp, pixels, widthArea, heightArea, left, up+heightArea);
        pasteArea(rightDown, pixels, widthArea, heightArea, left, up);
    }

    return pixels;
}

void pasteArea(Rgb** area, Rgb** pixels, const int width, const int height, const int left, const int up)
{
    int y = 0;
    for(int i = up; i < up + height; i++){
        int x = 0;
        for(int j = left; j < left + width; j++){
            pixels[i][j] = area[y][x];
            x++;
        }
        y++;
    }
}

void copyArea(Rgb** area, const int widthArea, const int heightArea, const int left, const int up, Rgb** pixels)
{
    for(int i = 0; i < heightArea; i++)
        area[i] = (Rgb*)malloc(sizeof(Rgb) * widthArea);

    int y = 0, x;
    for(int i = up; i < up + heightArea; i++){
        x = 0;
        for(int j = left; j < left + widthArea; j++){
            //printf("x - %d y - %d i - %d j - %d\n", x, y, i, j);
            area[y][x] = pixels[i][j];
            x++;
        }
        y++;
    }
}

Rgb** findAndReplaceColor(BitmapInfoHeader *BMPInfo, Rgb** pixels, Rgb color, char* img){
    const int width = BMPInfo->width;
    const int height = BMPInfo->height;
    Rgb primeCol = getPrimeColor(img);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++) {
            if(isColorEqual(pixels[y][x], primeCol)){
                pixels[y][x].r = color.r;
                pixels[y][x].g = color.g;
                pixels[y][x].b = color.b;
            }
        }
    }
    return pixels;
}

Rgb getPrimeColor(char *FILE_NAME)
{
    Rgb primecolor = {0, 0, 0};
    unsigned char hdr[54];

    unsigned long *counts;
    unsigned long max_count = 0;

    unsigned short w, h;
    unsigned short i, j;

    FILE* fp = fopen(FILE_NAME, "rb");

    counts = calloc(256 * 256 * 256, sizeof(*counts));

    fread(hdr, sizeof(hdr), 1, fp);
    w = (hdr[19] << 8) | hdr[18];
    h = (hdr[23] << 8) | hdr[22];

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            Rgb rgb;
            unsigned long idx;

            if (fread(&rgb, 3, 1, fp) < 1) {
                fprintf(stderr, "Unexpected end of file.\n");
                exit(48);
            }
            idx = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
            if (++counts[idx] > max_count) {
                max_count = counts[idx];
                primecolor = rgb;
            }
        }
        j = 3 * w;
        while (j++ % 4) getc(fp);
    }

    free(counts);
    fclose(fp);

    return primecolor;
}

int isColorEqual(Rgb firColor, Rgb secColor){
    if(firColor.r == secColor.r && firColor.g == secColor.g && firColor.b == secColor.b)
        return 1;
    return 0;
}

Rgb** gammedPixels(BitmapInfoHeader *BMPInfo,Rgb** pixels,double value){
    for(int y = 0; y < BMPInfo->height; y++){
        for(int x = 0; x < BMPInfo->width; x++){
            int newR = (int)(pow((double)pixels[y][x].r / 255, value) * 255);
            int newG = (int)(pow((double)pixels[y][x].g / 255, value) * 255);
            int newB = (int)(pow((double)pixels[y][x].b / 255, value) * 255);
            //printf("r - %d newR - %d, value - %f\n", pixels[y][x].r, newR, value*255);
            if(newR > 255)
                newR = 255;
            if(newG > 255)
                newG = 255;
            if(newB > 255)
                newB = 255;
            if(newR < 0)
                newR = 0;
            if(newG < 0)
                newG = 0;
            if(newB < 0)
                newB = 0;
            pixels[y][x].r = newR;
            pixels[y][x].g = newG;
            pixels[y][x].b = newB;
        }
    }
    return pixels;
}
