#include "drawing.h"

Rgb check_color(int r, int g, int b){
    if(r>255 || g>255 || b>255 || r<0 || g<0 || b<0){
        fprintf(stderr, "Value Error: component values must be in the range 0 to 255\n");
        exit(42);
    }
    Rgb color;
    color.r = r;
    color.g = g;
    color.b = b; 
    return color;
}

void check_coord(BitmapInfoHeader *bmif, int *left_x, int *up_y, int *right_x, int *down_y) {
    int Height = bmif->height;
    int Width = bmif->width;
    if (*left_x > *right_x) {
        int tmp = *left_x;
	*left_x = *right_x;
	*right_x = tmp;
    }
    if (*up_y > *down_y) {
	int tmp = *up_y;
	*up_y = *down_y;
	*down_y = tmp;
    }
}

void inverse_color(Rgb *color){
    color->r = 255 - color->r;
    color->g = 255 - color->g;
    color->b = 255 - color->b;
}

void inverse(Rgb **arr, BitmapInfoHeader bmif, int left_x, int up_y, int right_x, int down_y){
    for (int y = up_y; y < down_y; y++){
        for (int x = left_x; x< right_x; x++){
            if ( 0<= y && y < bmif.height && 0<=x && x< bmif.width) {
                inverse_color(&arr[y][x]);
            }
        }
    }
}

void gray_color(Rgb *color){
    int grey = round(0.299*color->r + 0.587*color->g + 0.114 *color->b);
    color->r = grey;
    color->g = grey;
    color->b = grey;
}

void gray(Rgb **arr, BitmapInfoHeader bmif, int left_x, int up_y, int right_x, int down_y){
    for (int y = up_y; y < down_y; y++){
        for (int x = left_x; x< right_x; x++){
            if ( 0<= y && y < bmif.height && 0<=x && x< bmif.width) {
                gray_color(&arr[y][x]);
            }
        }
    }
}

void color_pixel(Rgb *pixel, Rgb color){
    pixel->b = color.b;
    pixel->g = color.g;
    pixel->r = color.r;
}

void color_bmp (Rgb **arr, BitmapInfoHeader* bmif, Rgb new_color){
    for (int y = 0; y < bmif->height; y++){
        for (int x = 0; x < bmif->width; x++){
            color_pixel(&arr[y][x], new_color);
        }
    }
}

Rgb** resize(Rgb **arr, BitmapInfoHeader* bmif, int left, int right, int below, int above, Rgb color){
    int old_H = bmif->height;
    int old_W = bmif->width;
    int new_H = old_H + above + below;
    int new_W = old_W + left + right;
    bmif->height = new_H;
    bmif->width = new_W;
    unsigned int padding = (new_H*sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;
    Rgb** new_arr = (Rgb**)calloc(new_H, sizeof(Rgb*));
    for (int y = new_H - 1; y>=0 ; y--) {
        new_arr[y] = (Rgb *) calloc(new_W*sizeof(Rgb)+padding, sizeof(Rgb));
    }
    color_bmp(new_arr, bmif, color);
    for (int y = 0; y < old_H; y++){
        for (int x = 0; x < old_W; x++){
            if ( y+above >= 0 && y+above < new_H && x+left >= 0 && x+left < new_W){
                new_arr[y+above][x+left] = arr[y][x];
            }
        }
    }
    return new_arr;
}

void color_pixel_check(Rgb** arr, BitmapInfoHeader* bmif, int x, int y, Rgb color){
    if (x >= 0 && x<bmif->width && y >= 0 && y<bmif->height){
        color_pixel(&arr[y][x], color);
    }
}

void fill_wide_circle(Rgb** arr, BitmapInfoHeader* bmif, int x_center, int y_center, int radius, Rgb color){
    int x = 0;
    int y = radius;
    int delta = 1 - 2*radius;
    int error = 0;
    while (y >= x){
        color_pixel_check(arr, bmif, x_center + x, y_center + y, color);
        color_pixel_check(arr, bmif, x_center - x, y_center + y, color);
        color_pixel_check(arr, bmif, x_center + x, y_center - y, color);
        color_pixel_check(arr, bmif, x_center - x, y_center - y, color);

        color_pixel_check(arr, bmif, x_center + y, y_center + x, color);
        color_pixel_check(arr, bmif, x_center - y, y_center + x, color);
        color_pixel_check(arr, bmif, x_center + y, y_center - x, color);
        color_pixel_check(arr, bmif, x_center - y, y_center - x, color);

        color_pixel_check(arr, bmif, x_center + x, y_center + y - 1, color);
        color_pixel_check(arr, bmif, x_center - x, y_center + y - 1, color);
        color_pixel_check(arr, bmif, x_center + x, y_center - y + 1, color);
        color_pixel_check(arr, bmif, x_center - x, y_center - y + 1, color);

        color_pixel_check(arr, bmif, x_center + y - 1, y_center + x, color);
        color_pixel_check(arr, bmif, x_center - y + 1, y_center + x, color);
        color_pixel_check(arr, bmif, x_center + y - 1, y_center - x, color);
        color_pixel_check(arr, bmif, x_center - y + 1, y_center - x, color);
        
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }
}

void draw_line(Rgb **arr, BitmapInfoHeader* bmif, int start_x, int start_y, int end_x, int end_y, int thickness, Rgb color) {
    int delta_x = abs(end_x - start_x); 
    int delta_y = abs(end_y - start_y);  
    int step_x;
    if (start_x < end_x){
        step_x = 1;
    } else {
        step_x = -1;
    }
    int step_y;
    if (start_y < end_y) {
        step_y = 1;
    } else {
        step_y = -1;
    }
    int val = delta_x-delta_y;

    while (1) {
        int coord_x = start_x - thickness / 2;
        int coord_y = start_y - thickness / 2;
        if (coord_x+thickness>=0 || coord_y+thickness>=0 || coord_x < bmif->width || coord_y < bmif->height){ 
            fill_wide_circle (arr, bmif, start_x, start_y, thickness/2, color);
        }
        if (start_x == end_x && start_y == end_y) break;
        int double_val = 2 * val;
        if (double_val > -delta_y) {
            val -= delta_y;
            start_x += step_x;
        }
        if (double_val < delta_x) {
            val += delta_x;
            start_y += step_y;
        }
    }

}

Rgb comp_color (Rgb ** arr, int N, int x, int y){
    int sum_r = 0;
    int sum_g = 0;
    int sum_b = 0;
    for (int i = N*y; i<N*(y+1); i++){
        for (int j = N*x; j<N*(x+1); j++){
            sum_r+=arr[i][j].r;
            sum_g+=arr[i][j].g;
            sum_b+=arr[i][j].b;
        }
    }
    Rgb color;
    int nk = N*N;
    color.r = sum_r/nk;
    color.g = sum_g/nk;
    color.b = sum_b/nk;
    return color;
}

Rgb** compress(Rgb** arr, int N, BitmapInfoHeader* bmif){
    int old_H = bmif->height;
    int old_W = bmif->width;
    int new_H = old_H/N;
    int new_W = old_W/N;
    bmif->height = new_H;
    bmif->width = new_W;
    unsigned int padding = (new_W*sizeof(Rgb)) % 4;
    if (padding) padding = 4 - padding;
    Rgb** new_arr = (Rgb**)calloc(new_H, sizeof(Rgb*));
    for (int i = new_H - 1; i>=0 ; i--) {
        new_arr[i] = (Rgb *) calloc(new_W*sizeof(Rgb)+padding, sizeof(Rgb));
    }
    for (int y = 0; y<new_H; y++){
        for (int x = 0; x<new_W; x++){
            Rgb new_color = comp_color(arr, N, x, y);
            new_arr[y][x].r=new_color.r;
            new_arr[y][x].g=new_color.g;
            new_arr[y][x].b=new_color.b;
        }
    }
    return new_arr;
}

