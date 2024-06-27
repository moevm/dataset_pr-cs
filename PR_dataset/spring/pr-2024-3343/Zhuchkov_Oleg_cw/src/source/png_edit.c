#include <png_edit.h>


rgb_t int_to_rgb(int r, int g, int b){
    rgb_t color;
    color.r = (png_byte)r;
    color.g = (png_byte)g;
    color.b = (png_byte)b;
    return color;
}

rgb_t png_byte_to_rgb(png_byte r, png_byte g, png_byte b){
    rgb_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

bool check_coords(png_t* image, int x, int y){
    return ((x < 0 || x >= image->width) || (y < 0 || y >= image->height));
}

void set_pixel(png_t* image, int x, int y, rgb_t rgb){
    if (check_coords(image, x, y)) return;
    png_bytep pixel = (png_bytep)(image->rows)[y]+x*3;
    pixel[0] = rgb.r;
    pixel[1] = rgb.g;
    pixel[2] = rgb.b;
}

rgb_t get_pixel(png_t* image,int x, int y){
    png_byte r,g,b;
    r = ((png_bytep)(image->rows[y]))[x*3];
    g = ((png_bytep)(image->rows[y]))[x*3+1];
    b = ((png_bytep)(image->rows[y]))[x*3+2];
    return png_byte_to_rgb(r,g,b);
}

void copy_pixel_to(png_t* image, int x0, int y0, int x1, int y1){
    if (check_coords(image, x0, y0) || check_coords(image, x1, y1)) return;
    rgb_t color;
    color = get_pixel(image, x0, y0);
    set_pixel(image,x1,y1,color);
}

rgb_t get_blurred_pixel(png_t* image, int x, int y, int size){
    int x0 = x - size / 2, x1 = x + size / 2, y0 = y - size / 2, y1 = y + size / 2;
    float sumR = 0.0, sumG = 0.0, sumB = 0.0;
    int cnt = 0;
    rgb_t temp;
    for (int xx = x0; xx <= x1; xx++)
        for (int yy = y0; yy <= y1; yy++)
            if(!check_coords(image,xx,yy))
        {
            temp = get_pixel(image, xx, yy);
            sumR += temp.r;
            sumG += temp.g;
            sumB += temp.b;
            cnt++;
        }
            else
        {
            sumR += 0;
            sumG += 0;
            sumB += 0;
            cnt++;
        }
    int r = round(sumR / cnt), g = round(sumG / cnt), b = round(sumB / cnt);
    temp = int_to_rgb(r,g,b);
    return temp;
}

//Defence task
void blur(png_t* image, int size){
    if (size % 2 == 0) size++;
    rgb_t** blurred = malloc(sizeof(rgb_t*) * image->height);
    for (int y = 0; y < image->height; y++)
        blurred[y] = malloc(sizeof(rgb_t) * image->width);
    for (int y = 0; y < image->height; y++)
        for (int x = 0; x < image->width; x++)
            blurred[y][x] = get_blurred_pixel(image, x, y, size);
    for (int y=0; y < image->height; y++)
        for (int x=0; x < image->width; x++)
            set_pixel(image,x,y,blurred[y][x]);         
}
