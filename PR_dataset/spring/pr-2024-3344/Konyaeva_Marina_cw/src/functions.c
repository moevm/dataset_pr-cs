#include "functions.h"
#include "input.h"


int is_pixel_part_of_img(struct Png *img, int x, int y){
    if (y >= 0 && y < img->height && x >= 0 && x < img->width){
        return 1;
    }
    return 0;
}

void set_pixel(struct Png *img, int x, int  y, int* color_arr){
    if (is_pixel_part_of_img(img, x, y) == 0){
        return;
    }
    img->row_pointers[y][x * img->channels + 0] = color_arr[0];
    img->row_pointers[y][x * img->channels + 1] = color_arr[1];
    img->row_pointers[y][x * img->channels + 2] = color_arr[2];
}

void fill_circle(struct Png *img, int xc, int yc, int r, int *color_arr) {
    int minX = xc - r;
    int minY = yc - r;
    int maxX = xc + r;
    int maxY = yc + r;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= r * r) {
                set_pixel(img, x, y, color_arr);
            }
        }
    }
}

void draw_thick_circle(struct Png *img, int xc, int yc, int r, int th, int *color_arr) {
    int newth = th;
    if (r < th){
        newth = r;
    }
    int minX = xc - r - th;
    int minY = yc - r - th;
    int maxX = xc + r + th;
    int maxY = yc + r + th;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= (r + th - 0.5)*(r + th - 0.5) && (x - xc)*(x - xc) + (y - yc)*(y - yc) >= (r - newth - 0.75)*(r - newth - 0.75)) {
                set_pixel(img, x, y, color_arr);
            }
        }
    }
}

void draw_in_octants(struct Png *img, int xc, int yc, int x, int y, int *color_arr) {
    set_pixel(img, xc+x, yc+y, color_arr);
    set_pixel(img, xc-x, yc+y, color_arr);
    set_pixel(img, xc+x, yc-y, color_arr);
    set_pixel(img, xc-x, yc-y, color_arr);
    set_pixel(img, xc+y, yc+x, color_arr);
    set_pixel(img, xc-y, yc+x, color_arr);
    set_pixel(img, xc+y, yc-x, color_arr);
    set_pixel(img, xc-y, yc-x, color_arr);
}

void draw_contour_circle(struct Png *img, int xc, int yc, int r, int *color_arr) {
    int x = 0;
    int y =  r;
    int d = 3 - 2 * r;
    draw_in_octants(img, xc, yc, x, y, color_arr);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        draw_in_octants(img, xc, yc, x, y, color_arr);
    }
}

void draw_line(struct Png *img, int x1, int y1, int x2, int y2,  int *color_arr){
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    while (x1 != x2 || y1 != y2) {
        // Draw pixel at current position
        set_pixel(img, x1, y1, color_arr);
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
    set_pixel(img, x1, y1, color_arr);
}

void draw_thick_line(struct Png *img, int x1, int y1, int x2, int y2, int thick, int *color_arr){
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;


    while (x1 != x2 || y1 != y2) {
        // Draw pixel at current position
        fill_circle(img, x1, y1, thick, color_arr);
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

void draw_circle(struct Png* img, int* center, int r, int thick, int* th_color, int flag_fill, int* fill_color){
    thick = thick/2;
    int newthick = thick;
    int x = center[0];
    int y = center[1];

    if (flag_fill){
        fill_circle(img, x, y, r, fill_color);
    }
    if (r < thick){
        newthick = r;
    }
    
    draw_contour_circle(img, x, y, r + thick, th_color);
    draw_contour_circle(img, x, y, r - newthick, th_color);
    draw_thick_circle(img, x, y, r, thick, th_color);

}

void switch_filter(struct Png* img, char* comp_name, int comp_value){
    if (comp_value < 0 || comp_value > 255){
        printf("Error in switch_filter: incorrect component_value.\n");
        exit(40);
    }

    if (strcmp(comp_name, "red") == 0){
        for (int x = 0; x < img->width; x++){
            for (int y = 0; y < img->height; y++){
                img->row_pointers[y][x * img->channels + 0] = comp_value;
            }
        }
    }
    else if (strcmp(comp_name, "green") == 0){
        for (int x = 0; x < img->width; x++){
            for (int y = 0; y < img->height; y++){
                img->row_pointers[y][x * img->channels + 1] = comp_value;
            }
        }
    }
    else if (strcmp(comp_name, "blue") == 0){
        for (int x = 0; x < img->width; x++){
            for (int y = 0; y < img->height; y++){
                img->row_pointers[y][x * img->channels + 2] = comp_value;
            }
        }
    }else{
        printf("Error in switch_filter function: Component name is incorrect\n");
        exit(40);
    }
}

void divide_image(struct Png* img, int N, int M, int thick, int* color_arr){
    if (N < 0 || M < 0){
        printf("Error in divide_image: number_x or number_y is incorrect\n");
        exit(41);
    }

    int seg_width = img->width / M;
    int seg_height = img->height / N;

    // Draw vertical lines
    for (int i = 1; i < M; ++i) {
        for (int k = 0; k < thick; k++){
            int x = i * seg_width - thick / 2  + k;
            draw_line(img, x, 0, x, img->height, color_arr); 
        }
    }

    // Draw horizontal lines
    for (int i = 1; i < N; ++i) {
        for (int k = 0; k < thick; k++){
            int y = i * seg_height - thick / 2 + k;
            draw_line(img, 0, y, img->width, y, color_arr); 
        }
    }
}

void draw_square(struct Png* img, int* center, int side, int thick, int* color_arr, int fill, int* fill_color){
    thick = thick/2 ;
    int x = center[0];
    int y = center[1];
    
    if (fill){
        for (int i = 0; i < img->width; i++){
            for (int j = 0; j < img->height; j++){
                if (i > x && i < x + side + 1 && j > y && j < y + side + 1){
                    set_pixel(img, i, j, fill_color);
                }
            }
        }
    }

    draw_thick_line(img, x, y, x + side, y, thick, color_arr);
    draw_thick_line(img, x, y + side, x + side, y + side, thick, color_arr);
    draw_thick_line(img, x, y, x, y + side, thick, color_arr);
    draw_thick_line(img, x + side, y, x + side, y + side, thick, color_arr);


    draw_thick_line(img, x, y, x + side, y + side, thick, color_arr);
    draw_thick_line(img, x + side, y, x, y + side, thick, color_arr);

}

int is_point_in_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x0, int y0) {
    int size1 = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
    int size2 = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
    int size3 = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);

    if ((size1 > 0 && size2 > 0 && size3 > 0) || (size1 < 0 && size2 < 0 && size3 < 0)) {
        return 1;
    }
    return 0;
}
void test(struct Png* img, int x1, int y1, int x2, int y2, int x3, int y3, int* color){

    int arr_x[3] = {x1, x2, x3};
    int arr_y[3] = {y1, y2, y3};

    for (int x = 0; x < img->width; x++) {
        for (int y = 0; y < img->height; y++) {
            if (is_point_in_triangle(x1, y1, x2, y2, x3, y3, x, y)) {
                set_pixel(img, x, y, color);
            }
        }
    }

}
