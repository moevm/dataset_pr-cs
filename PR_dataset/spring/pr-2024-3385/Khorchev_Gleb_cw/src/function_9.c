#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp_structs.h"
#include "help_functions.h"


Rgb** getblur(Rgb** new_pixels,Rgb** pixels, int x, int y, int size, int H, int W)
{
    int sum_r = 0, sum_g = 0, sum_b =0;
    int count =0;
    int err = size/2;
    for(int temp_y = y-err; temp_y <= y+err; temp_y++)
    {
        for(int temp_x= x-err; temp_x <= x+err; temp_x++)
        {
            if (temp_y < H && temp_y >= 0 && temp_x >= 0 && temp_x < W)
            {
            count++;
            sum_r += pixels[temp_y][temp_x].r;
            sum_g += pixels[temp_y][temp_x].g;
            sum_b += pixels[temp_y][temp_x].b;
            } 
        }
    }
    sum_r /= (count);
    sum_g /= (count);
    sum_b /= (count);
    new_pixels[y][x].r = sum_r;
    new_pixels[y][x].g = sum_g;
    new_pixels[y][x].b = sum_b;
    return new_pixels;
}

Rgb** function_9(Rgb** new_pixels, Rgb** old_pixels, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, int size)
{
    int H = bmif->height;
    int W = bmif->width;
    for(size_t y = 0; y<H; y++)
    {
        for(size_t x=0; x<W; x++)
        {
            new_pixels = getblur(new_pixels, old_pixels, x, y, size, H, W);
        }
    }
    if (old_pixels != NULL)
    {
        int H = 0;
        if ( bmif != NULL) H = bmif->height;
        {
            for ( size_t i=0; i < H; i++) free(old_pixels[i]);
        }
    }
    free(old_pixels);
    return new_pixels;
}