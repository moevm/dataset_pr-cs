#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp_structs.h"

Rgb** change_colour(Rgb** pixels, int y, int x,  Rgb color, unsigned int H, unsigned int W)
{
    if ( (x < W) && (x >= 0 )&& (y < H) && (y >=0))
    {
    pixels[y][x].r = color.r;
    pixels[y][x].g = color.g;
    pixels[y][x].b = color.b;
    }
    return pixels;
}

Rgb** draw(Rgb** pixels,  int x0,  int y0,  int x,  int y, Rgb color, unsigned int H, unsigned int W)
{
    pixels = change_colour(pixels, y0+y, x0+x, color, H, W);
    pixels = change_colour(pixels, y0+y, x0-x, color, H, W);
    pixels = change_colour(pixels, y0-y, x0+x, color, H, W);
    pixels = change_colour(pixels, y0-y, x0-x, color, H, W);
    pixels = change_colour(pixels, y0+x, x0+y, color, H, W);
    pixels = change_colour(pixels, y0+x, x0-y, color, H, W);
    pixels = change_colour(pixels, y0-x, x0+y, color, H, W);
    pixels = change_colour(pixels, y0-x, x0-y, color, H, W);
    return pixels;
}


Rgb** draw_filled_circle(Rgb** pixels, int x0, int y0, unsigned int r, Rgb color, unsigned int H, unsigned int W)
{
    int x = 0, y = r;
    int d = 5 - 4*r;
    while( x <= y )
    {
        for( int xx = x0-y; xx <= x0+y; xx++)
        {
            pixels = change_colour(pixels, y0+x, xx, color, H, W);
            pixels = change_colour(pixels, y0-x, xx, color, H, W);    
        }
        if ( d > 0 )
        {
            for( int xx = x0-x; xx <= x0+x; xx++)
            {
                pixels= change_colour(pixels, y0-y, xx, color, H, W);
                pixels = change_colour(pixels, y0+y, xx, color, H, W);
            }
            y--;
            d -= 8*y;
        }
        x++;
        d += 8*x + 4;
    }
    return pixels;   
}

Rgb** draw_cross(Rgb** pixels, int x0, int y0, Rgb color, unsigned int H, unsigned int W)
{
    pixels =  change_colour(pixels, y0, x0, color, H, W);
    pixels = change_colour(pixels, y0+1, x0, color, H, W);
    pixels = change_colour(pixels, y0-1, x0, color, H, W);
    pixels = change_colour(pixels, y0, x0+1, color, H, W);
    pixels = change_colour(pixels, y0, x0-1, color, H, W);
    return pixels;
}

Rgb** draw_octagon_filled_circle(Rgb** pixels, int x0, int y0, int x, int y, unsigned int r, Rgb color, unsigned int H, unsigned int W)
{
    if (x0+x + r <= W || y0+ y + r <= H) pixels = draw_filled_circle(pixels, x0+x, y0+y, r, color, H, W);
    if (x0-x + r <= W || y0+ y + r <= H) pixels = draw_filled_circle(pixels, x0-x, y0+y, r, color, H, W);
    if (x0+x + r <= W || y0 - y + r <= H) pixels = draw_filled_circle(pixels, x0+x, y0-y, r, color, H, W);
    if (x0-x + r <= W || y0 - y + r <= H) pixels = draw_filled_circle(pixels, x0-x, y0-y, r, color, H, W);
    if (x0+y + r <= W || y0 + x + r <= H) pixels = draw_filled_circle(pixels, x0+y, y0+x, r, color, H, W);
    if (x0-y + r <= W || y0 + x + r <= H) pixels = draw_filled_circle(pixels, x0-y, y0+x, r, color, H, W);
    if (x0+y + r <= W || y0 - x + r <= H) pixels = draw_filled_circle(pixels, x0+y, y0-x, r, color, H, W);
    if (x0-y + r <= W || y0 - x + r <= H) pixels = draw_filled_circle(pixels, x0-y, y0-x, r, color, H, W);
    return pixels;
}

Rgb** draw_octagon_cross(Rgb** pixels, int x0, int y0, int x, int y, Rgb color, unsigned int H, unsigned int W)
{
    pixels = draw_cross(pixels, x0+x, y0+y, color, H, W);
    pixels = draw_cross(pixels, x0-x, y0+y, color, H, W);
    pixels = draw_cross(pixels, x0+x, y0-y, color, H, W);
    pixels = draw_cross(pixels, x0-x, y0-y, color, H, W);
    pixels = draw_cross(pixels, x0+y, y0+x, color, H, W);
    pixels = draw_cross(pixels, x0-y, y0+x, color, H, W);
    pixels = draw_cross(pixels, x0+y, y0-x, color, H, W);
    pixels = draw_cross(pixels, x0-y, y0-x, color, H, W);
    return pixels;
}


Rgb** draw_circle(Rgb** pixels, int x0, int y0, unsigned int r, unsigned int t, Rgb color, unsigned int H, unsigned int W)
{
    int x = 0, y = r;
    int d = 5 - 4*r;
    while( x <= y )
    {
        if (t == 1)
        {
            pixels = draw_octagon_cross(pixels, x0, y0, x, y, color, H, W);
        } else pixels = draw_octagon_filled_circle(pixels, x0, y0, x, y, t/2, color, H, W);
        if ( d > 0 )
        {
            y--;
            d -= 8*y;
        }
        x++;
        d += 8*x + 4;
    }
    return pixels;      
}


Rgb** function_1(Rgb** pixels, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, int x0, int y0, unsigned int r, unsigned int t, Rgb color, int flag, Rgb fill_color)
{
    unsigned int W = bmif->width;
    unsigned int H = bmif->height;
    if (flag)
    {
        pixels = draw_filled_circle(pixels, x0, y0, r, fill_color, H, W);
        pixels = draw_circle(pixels, x0, y0, r, t, color, H, W);
    } else pixels = draw_circle(pixels, x0, y0, r, t, color, H, W);
    return pixels;
}

