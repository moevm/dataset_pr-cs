#include "draw.h"

// Устанавливает цвет указанного пикселя
void put_pixel(pixel* pix, color* clr) 
{
    if (pix == NULL || clr == NULL) 
        return;
   
    pix->byte[0] = (png_byte)clr->R;
    pix->byte[1] = (png_byte)clr->G;
    pix->byte[2] = (png_byte)clr->B;
}

// Возвращает указатель на пиксель изображения по указанным координатам
pixel *get_pixel(image *img, double x, double y)
{
    if (img == NULL || img->bytes == NULL)
        return NULL;
    
    int ix = (int)x;
    int iy = (int)y;
    if ((ix < 0) || (ix >= img->width) || (iy < 0) || (iy >= img->height))
        return NULL;

    point *pos = init_point(ix, iy);
    png_bytep byte = img->bytes[iy] + ix * 3;
    return init_pixel(pos, byte);
}

// Преобразует структуру пикселя в структуру цвета
color *pixel_to_color(pixel *pix)
{
    return init_color(pix->byte[0], pix->byte[1], pix->byte[2]);
}