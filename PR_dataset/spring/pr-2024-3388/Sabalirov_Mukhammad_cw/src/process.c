#include "process.h"
#include <math.h>

void set_pixel(png_t* img, int x, int y, int* color){
    png_bytep row, ptr;
    if (y >= 0 && y < img->height && x >= 0 && x < img->width){
        row = img->row_pointers[y];
        ptr = &(row[(x)*PIXEL_PARAMS_COUNT]);
        ptr[0] = color[0];
        ptr[1] = color[1];
        ptr[2] = color[2];
    }
}

void draw_field_circle(png_t* img, const int centre_x, const int centre_y, int radius, int* color) {
    
    if (radius == 0){
        set_pixel(img, centre_x, centre_y, color);
        return;
    }
   
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        set_pixel(img, centre_x + x, centre_y + y, color);
		set_pixel(img, centre_x + x, centre_y - y, color);
		set_pixel(img, centre_x - x, centre_y + y, color);
		set_pixel(img, centre_x - x, centre_y - y, color);
        set_pixel(img, centre_x + y, centre_y + x, color);
		set_pixel(img, centre_x + y, centre_y - x, color);
		set_pixel(img, centre_x - y, centre_y + x, color);
		set_pixel(img, centre_x - y, centre_y - x, color);



        error = 2*(delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 *(++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 *(--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }

    draw_field_circle(img, centre_x, centre_y, radius/2, color);
}

void draw_line(png_t* img, func_params_t* params,int first_x, int first_y, int second_x, int second_y){
    int delta_x= abs(second_x - first_x);
    int delta_y = abs(second_y - first_y);
    int sign_x = first_x < second_x ? 1 : -1;
    int sign_y = first_y < second_y ? 1 : -1;
    int second_error;
    int first_error = delta_x - delta_y;

    int* color = malloc(3*sizeof(int));
    color[0] = params->color_r;
    color[1] = params->color_g;
    color[2] = params->color_b;
    draw_field_circle(img, second_x, second_y, params->thickness/THICK_K, color);
    while(first_x != second_x || first_y != second_y){
        draw_field_circle(img, first_x, first_y, params->thickness/THICK_K, color);
        second_error = first_error * 2;
        if(second_error > -delta_y) {
            first_error -= delta_y;
            first_x += sign_x;
        }
        if(second_error < delta_x) {
            first_error += delta_x;
            first_y += sign_y;
        }
    }

    free(color);
}

void print_png_info(png_t* img){
    printf(PNG_INFO_TEMPLATE, img->width, img->height, img->color_type, img->bit_depth);
}

void mirror_img(png_t* img, func_params_t* params){
    int left_up_x, left_up_y, right_down_x, right_down_y;
    png_bytep row, mirror_row, ptr, mirror_ptr;
    png_byte tmp;

    left_up_x = params->left_up_x;
    left_up_y = params->left_up_y;

    if (params->right_down_x > img->width){
        right_down_x = img->width;
        left_up_x += params->right_down_x - img->width;
    }
    else{
        right_down_x = params->right_down_x;
    }

    if (params->right_down_y > img->height){
        right_down_y = img->height;
        left_up_y += params->right_down_y - img->height;
    }else{
        right_down_y = params->right_down_y;
    }

    if (params->axis == X_AXIS_INT){
        for (size_t y = left_up_y; y < right_down_y; ++y) {
            row = img->row_pointers[y];
            for (size_t x = left_up_x; x < ((right_down_x - left_up_x)/2 + left_up_x); ++x) {
                ptr = &(row[x*PIXEL_PARAMS_COUNT]);
                mirror_ptr = &(row[(right_down_x - x + left_up_x)*PIXEL_PARAMS_COUNT]);
                
                for (size_t i = 0; i < PIXEL_PARAMS_COUNT; ++i){
                    tmp = ptr[i];
                    ptr[i] = mirror_ptr[i];
                    mirror_ptr[i] = tmp;
                }
            }
        }
    }
    else{
        for (size_t y = left_up_y; y < ((right_down_y - left_up_y)/2 + left_up_y); ++y) {
            row = img->row_pointers[y];
            mirror_row = img->row_pointers[right_down_y - y + left_up_y];
            for (size_t x = left_up_x; x < right_down_x; ++x) {
                ptr = &(row[x*PIXEL_PARAMS_COUNT]);
                mirror_ptr = &(mirror_row[x*PIXEL_PARAMS_COUNT]);
                for (size_t i = 0; i < PIXEL_PARAMS_COUNT; ++i){
                    tmp = ptr[i];
                    ptr[i] = mirror_ptr[i];
                    mirror_ptr[i] = tmp;
                }
            }
        }
    }
}

void rect_img(png_t* img, func_params_t* params){
    draw_line(img, params, params->left_up_x, params->left_up_y, params->left_up_x, params->right_down_y);
    draw_line(img, params, params->left_up_x, params->left_up_y, params->right_down_x, params->left_up_y);
    draw_line(img, params, params->right_down_x, params->right_down_y, params->left_up_x, params->right_down_y);
    draw_line(img, params, params->right_down_x, params->right_down_y, params->right_down_x, params->left_up_y);
}

void circle_img(png_t* img, func_params_t* params){
    int x = 0;
    int y = params->radius;
    int delta = 1 - 2 * params->radius;
    int error = 0;

    int* color = malloc(3*sizeof(int));
    color[0] = params->color_r;
    color[1] = params->color_g;
    color[2] = params->color_b;
    int centre_x = params->center_x;
    int centre_y = params->center_y;

    while (y >= x){
        
        draw_field_circle(img, centre_x + x, centre_y + y, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x + x, centre_y - y, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x - x, centre_y + y, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x - x, centre_y - y, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x + y, centre_y + x, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x + y, centre_y - x, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x - y, centre_y + x, params->thickness/THICK_K, color);
        draw_field_circle(img, centre_x - y, centre_y - x, params->thickness/THICK_K, color);
    
        error = 2*(delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 *(++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 *(--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }
    
    free(color);
}

void pentagram_img(png_t* img, func_params_t* params){
    int angel_count = 5;
    int x[angel_count];
    int y[angel_count];
    for (size_t i = 0; i < angel_count; ++i){
        x[i] = params->center_x - (int)(params->radius*(sin(2*PI*i/angel_count)));
        y[i] = params->center_y - (int)(params->radius*(cos(2*PI*i/angel_count)));
    }

    draw_line(img, params, x[0], y[0], x[2], y[2]);
    draw_line(img, params, x[0], y[0], x[2], y[2]);
    draw_line(img, params, x[1], y[1], x[3], y[3]);
    draw_line(img, params, x[1], y[1], x[4], y[4]);
    draw_line(img, params, x[4], y[4], x[2], y[2]);
    draw_line(img, params, x[3], y[3], x[0], y[0]);
    

    circle_img(img, params);
}

double line_equation(int x, int x1, int y1, int x2, int y2){
    return ((y2 - y1)*x -(y2 - y1)*x1 + (x2 - x1)*y1)/(1.0*(x2 - x1));
}

void hexagon_img(png_t* img, func_params_t* params){
    png_bytep row, ptr;
    int angel_count = 6;
    int x[angel_count];
    int y[angel_count];
    int flag;
    
    for (size_t i = 0; i < angel_count; ++i){
        x[i] = params->center_x - (int)(params->radius*(cos(2*PI*i/angel_count)));
        y[i] = params->center_y - (int)(params->radius*(sin(2*PI*i/angel_count)));
        
    }
    
    if (params->fill){
        for (size_t y_c = 0; y_c < img->height; ++y_c){
            row = img->row_pointers[y_c];
            for (size_t x_c = 0; x_c < img->width; ++x_c){
                ptr = &(row[x_c*PIXEL_PARAMS_COUNT]);
                flag = 1;

                flag *= (int)(line_equation(x_c, x[5], y[5], x[0], y[0]) > y_c);
                flag *= (int)(line_equation(x_c, x[0], y[0], x[1], y[1]) < y_c);
                flag *= (int)(line_equation(x_c, x[1], y[1], x[2], y[2]) < y_c);
                flag *= (int)(line_equation(x_c, x[2], y[2], x[3], y[3]) < y_c);
                flag *= (int)(line_equation(x_c, x[3], y[3], x[4], y[4]) > y_c);
                flag *= (int)(line_equation(x_c, x[4], y[4], x[5], y[5]) > y_c);

                if (flag){
                        ptr[0] = params->fill_color_r;
                        ptr[1] = params->fill_color_g;
                        ptr[2] = params->fill_color_b;
                    }
            }
        }
    }

    draw_line(img, params, x[0], y[0], x[1], y[1]);
    draw_line(img, params, x[1], y[1], x[2], y[2]);
    draw_line(img, params, x[2], y[2], x[3], y[3]);
    draw_line(img, params, x[3], y[3], x[4], y[4]);
    draw_line(img, params, x[4], y[4], x[5], y[5]);
    draw_line(img, params, x[5], y[5], x[0], y[0]);
}

void fill_rect(png_t* img, func_params_t* params){
    int left_up_x, left_up_y, right_down_x, right_down_y;
    int min_x, min_y, max_x, max_y;
    png_bytep row, ptr;
    
    if (params->left_up_x > img->width){
        left_up_x = img->width;
    }
    else{
        left_up_x = params->left_up_x;
    }

    if (params->left_up_y > img->height){
        left_up_y = img->height;
    }else{
        left_up_y = params->left_up_y;
    }
    
    if (params->right_down_x > img->width){
        right_down_x = img->width;
    }
    else{
        right_down_x = params->right_down_x;
    }

    if (params->right_down_y > img->height){
        right_down_y = img->height;
    }else{
        right_down_y = params->right_down_y;
    }

    min_y = left_up_y; 
    max_y = left_up_y;
    min_x = left_up_x;
    max_x = left_up_x;

    if (right_down_y <= left_up_y)
        min_y = right_down_y;
    if (right_down_y >= left_up_y)
        max_y = right_down_y;
    
    if (right_down_x <= left_up_x)
        min_x = right_down_x;
    if (right_down_x >= left_up_x)
        max_x = right_down_x;
    
    min_x *= (int)(min_x >= 0);
    min_y *= (int)(min_y >= 0);

    for (size_t y = min_y; y < max_y; ++y) {
        row = img->row_pointers[y];
        for (size_t x = min_x; x < max_x; ++x) {
            ptr = &(row[x*PIXEL_PARAMS_COUNT]);
            ptr[0] = params->fill_color_r;
            ptr[1] = params->fill_color_g;
            ptr[2] = params->fill_color_b;
        }
    }
}
void paving(png_t* img, func_params_t* params){
    int left_up_x, left_up_y, right_down_x, right_down_y;
    int min_x, min_y, max_x, max_y;
    png_bytep row, ptr;
    int*** pavv;
    
    if (params->left_up_x > img->width){
        left_up_x = img->width;
    }
    else{
        left_up_x = params->left_up_x;
    }

    if (params->left_up_y > img->height){
        left_up_y = img->height;
    }else{
        left_up_y = params->left_up_y;
    }
    
    if (params->right_down_x > img->width){
        right_down_x = img->width;
    }
    else{
        right_down_x = params->right_down_x;
    }

    if (params->right_down_y > img->height){
        right_down_y = img->height;
    }else{
        right_down_y = params->right_down_y;
    }

    min_y = left_up_y; 
    max_y = left_up_y;
    min_x = left_up_x;
    max_x = left_up_x;
    if (right_down_y <= left_up_y)
        min_y = right_down_y;
    if (right_down_y >= left_up_y)
        max_y = right_down_y;
    
    if (right_down_x <= left_up_x)
        min_x = right_down_x;
    if (right_down_x >= left_up_x)
        max_x = right_down_x;

    min_x *= (int)(min_x >= 0);
    min_y *= (int)(min_y >= 0);

    pavv = calloc(max_y-min_y, sizeof(int**));
    int y_len = max_y-min_y;
    int x_len = max_x-min_x;
    printf("%d %d\n", min_y, max_y);
    for (size_t y = min_y; y < max_y; ++y) {
        row = img->row_pointers[y];
        pavv[y - min_y] = calloc(max_x-min_x, sizeof(int*));
        for (size_t x = min_x; x < max_x; ++x) {
            ptr = &(row[x*PIXEL_PARAMS_COUNT]);
            pavv[y - min_y][x - min_x] = calloc(3, sizeof(int));
            pavv[y - min_y][x - min_x][0] = ptr[0];
            pavv[y - min_y][x - min_x][1] = ptr[1];
            pavv[y - min_y][x - min_x][2] = ptr[2];
        }
    }
    for (size_t y = 0; y < img->height; ++y) {
        row = img->row_pointers[y];
        for (size_t x = 0; x < img->width; ++x) {
            ptr = &(row[x*PIXEL_PARAMS_COUNT]);
            ptr[0] = pavv[y%y_len][(x%x_len)][0];
            ptr[1] = pavv[y%y_len][(x%x_len)][1];
            ptr[2] = pavv[y%y_len][(x%x_len)][2];
        }
    }
}
png_t* process_img(png_t* img, func_params_t* params, int* write_flag){
    *write_flag = 1;

    if (params->info){
        *write_flag = 0;
        print_png_info(img);
    }

    if (png_get_color_type(img->png_ptr, img->info_ptr) != PNG_COLOR_TYPE_RGB) {
        panic(NOT_RGB);
    }

    if (params->mirror){
        mirror_img(img, params);
    }

    if (params->pentagram){
        pentagram_img(img, params);
    }

    if (params->rect){
        if (params->fill){
            fill_rect(img, params);
        }

        rect_img(img, params);
    }

    if (params->hexagon){
        hexagon_img(img, params);
    }

    if (params->paving){
        paving(img, params);
    }

    return img;
}