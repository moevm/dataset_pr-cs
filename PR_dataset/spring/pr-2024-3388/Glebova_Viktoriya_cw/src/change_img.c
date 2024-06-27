#include "change_img.h"

void set_pixel(png_t* img, int x, int y, rgb_t color){
    png_bytep row, row_pointer;
    if (y >= 0 && y < img->height && x >= 0 && x < img->width){
        row = img->row_pointers[y];
        row_pointer = &(row[(x)*PIXEL_PARAMS_COUNT]);
        row_pointer[0] = color.r;
        row_pointer[1] = color.g;
        row_pointer[2] = color.b;
    }
}

void set_pixels_for_circle(png_t* img, int center_x, int center_y, int x, int y, rgb_t color){
    set_pixel(img, center_x + x, center_y + y, color);
    set_pixel(img, center_x + x, center_y - y, color);
    set_pixel(img, center_x - x, center_y + y, color);
    set_pixel(img, center_x - x, center_y - y, color);
    set_pixel(img, center_x + y, center_y + x, color);
    set_pixel(img, center_x + y, center_y - x, color);
    set_pixel(img, center_x - y, center_y + x, color);
    set_pixel(img, center_x - y, center_y - x, color);
}

void draw_field_circle(png_t* img, int center_x, int center_y, int radius, rgb_t color){
    if (radius <= 0){
        set_pixel(img, center_x, center_y, color);
        return;
    }
   
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        set_pixels_for_circle(img, center_x, center_y, x, y, color);
        error = 2*(delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            x++;
            delta += 2*x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            y--;
            delta -= 2*y + 1;
            continue;
        }
        x++;
        y--;
        delta += 2*(x - y);
    }
    draw_field_circle(img, center_x, center_y, radius/2, color);
}

void set_pixels_for_thickness_circle(png_t* img, int center_x, int center_y, int x, int y, int thickness, rgb_t color){
    draw_field_circle(img, center_x + x, center_y + y, thickness, color);
    draw_field_circle(img, center_x + x, center_y - y, thickness, color);
    draw_field_circle(img, center_x - x, center_y + y, thickness, color);
    draw_field_circle(img, center_x - x, center_y - y, thickness, color);
    draw_field_circle(img, center_x + y, center_y + x, thickness, color);
    draw_field_circle(img, center_x + y, center_y - x, thickness, color);
    draw_field_circle(img, center_x - y, center_y + x, thickness, color);
    draw_field_circle(img, center_x - y, center_y - x, thickness, color);
}

void draw_accurate_filed_circle(png_t* img, params_t* params, int center_x, int center_y, int radius){
    for (int y = 0; y < radius; y++){
        for (int x = 0; x < radius; x++){
            if (x*x + y*y <= radius*radius + radius){
                set_pixels_for_circle(img, center_x, center_y, x, y, params->fill_color);
            }
        }
    }
}

void draw_line(png_t* img, params_t* params, int start_x, int start_y, int end_x, int end_y){
    int delta_x= abs(end_x - start_x);
    int delta_y = abs(end_y - start_y);
    int sign_x = -1;
    int sign_y = -1;
    
    if (start_x < end_x)
        sign_x = 1;
    
    if (start_y < end_y)
        sign_y = 1;

    int second_error;
    int first_error = delta_x - delta_y;
    draw_field_circle(img, end_x, end_y, params->thickness, params->color);
    while(start_x != end_x || start_y != end_y){
        draw_field_circle(img, start_x, start_y, params->thickness, params->color);
        second_error = first_error * 2;
        if(second_error > -delta_y) {
            first_error -= delta_y;
            start_x += sign_x;
        }
        if(second_error < delta_x) {
            first_error += delta_x;
            start_y += sign_y;
        }
    }
}

void draw_circle(png_t* img, params_t* params){
    int x = 0;
    int y = params->radius;
    int delta = 1 - 2 * params->radius;
    int error = 0;

    int center_x = params->center.x;
    int center_y = params->center.y;

    while (y >= x){
        
        set_pixels_for_thickness_circle(img, center_x, center_y, x, y, params->thickness, params->color);
        error = 2*(delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            x++;
            delta += 2 *x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            y--;
            delta -= 2 *y + 1;
            continue;
        }
        x++;
        y--;
        delta += 2 * (x - y);
    }
}

void do_rgb_filter(png_t* img, params_t* params){
    png_bytep row, row_pointer;
    int color_idx = 0 + (int)!strcmp(GREEN_VAL, params->component_name)*1 + (int)!strcmp(BLUE_VAL, params->component_name)*2;
    for (int y = 0; y < img->height; y++){
        row = img->row_pointers[y];
        for (int x = 0; x < img->width; x++){
            row_pointer = &(row[x * PIXEL_PARAMS_COUNT]);
            row_pointer[color_idx] = params->component_value;
        }
    }
}

void do_split(png_t* img, params_t* params){
    int vertical_step = img->width/params->number_x;
    int horizontal_step = img->height/params->number_y;

    for (int x = 1; x < params->number_x; x += 1)
        draw_line(img, params, x*vertical_step, 0, x*vertical_step, img->height);

    for (int y = 1; y < params->number_y; y += 1)
        draw_line(img, params, 0, y*horizontal_step, img->width, y*horizontal_step);
}
void do_gamma(png_t* img, params_t* params){
    png_bytep row, row_pointer;
    
    for (int y = 0; y < img->height; y++){
        row = img->row_pointers[y];
        for (int x = 0; x < img->width; x++){
            row_pointer = &(row[x * PIXEL_PARAMS_COUNT]);
            row_pointer[0] = powf((row_pointer[0]/(MAX_COMPONENT_VAL*1.0)), params->value) * MAX_COMPONENT_VAL;
            row_pointer[1] = powf((row_pointer[1]/(MAX_COMPONENT_VAL*1.0)), params->value) * MAX_COMPONENT_VAL;
            row_pointer[2] = powf((row_pointer[2]/(MAX_COMPONENT_VAL*1.0)), params->value) * MAX_COMPONENT_VAL;
        }
    }
}

void change_img(png_t* img, params_t* params){
    if (params->circle){
        if (params->fill){
            draw_accurate_filed_circle(img, params, params->center.x, params->center.y, params->radius);
        }
        draw_circle(img, params);
    }

    if (params->rgb_filter)
        do_rgb_filter(img, params);

    if (params->split)
        do_split(img, params);

    if (params->info_flag){
        print_img_info(img);
        exit(0);
    }
    if (params->gamma){
        do_gamma(img, params);
    }
}
