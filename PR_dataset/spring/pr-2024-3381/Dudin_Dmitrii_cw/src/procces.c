#include "procces.h"

int color_cmp(rgb_t first, rgb_t second){
    return first.r == second.r && first.g == second.g && first.b == second.b;
}

int check_filled_area(img_t *img, rgb_t color, int x1, int y1, int x2, int y2) {
    for (size_t y = y1; y <= y2; y++) {
        for (size_t x = x1; x <= x2; x++) {
            if (!color_cmp(img->pixels[y][x], color)){
                return 0;
            }
        }
    }
    return 1;
}

void set_pixel(img_t* img, int x, int y, rgb_t color){
    if (x < img->info_header->width && x >= 0 && y < img->info_header->height && y >= 0){
        img->pixels[y][x].r = color.r;
        img->pixels[y][x].g = color.g;
        img->pixels[y][x].b = color.b;
    }
}

void draw_field_circle(img_t* img, int x0, int y0, int radius, rgb_t color){
    if (radius == 0){
        set_pixel(img, x0, y0, color);
        return;
    }

    if(radius == 1 || radius == 2){
        set_pixel(img, x0, y0, color);
        set_pixel(img, x0 + 1, y0, color);
        set_pixel(img, x0, y0 + 1, color);
        set_pixel(img, x0 - 1, y0, color);
        set_pixel(img, x0, y0-  1, color);

        if(radius==2){
            set_pixel(img, x0 + 1, y0 + 1, color);
            set_pixel(img, x0 + 1, y0 - 1, color);
            set_pixel(img, x0 - 1, y0 + 1, color);
            set_pixel(img, x0 - 1, y0 - 1, color);
            set_pixel(img, x0 + 2, y0, color);
            set_pixel(img, x0,y0+2, color);
            set_pixel(img, x0 - 2, y0, color);
            set_pixel(img, x0, y0 - 2, color);
        }

        return;
    }
   
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        set_pixel(img, x0 + x, y0 + y, color);
		set_pixel(img, x0 + x, y0 - y, color);
		set_pixel(img, x0 - x, y0 + y, color);
		set_pixel(img, x0 - x, y0 - y, color);
        set_pixel(img, x0 + y, y0 + x, color);
		set_pixel(img, x0 + y, y0 - x, color);
		set_pixel(img, x0 - y, y0 + x, color);
		set_pixel(img, x0 - y, y0 - x, color);

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

    draw_field_circle(img, x0, y0, radius/2, color);
}

void draw_line(img_t* img, rgb_t color, int thickness, int x1, int y1, int x2, int y2){
    int delta_x= abs(x2 - x1);
    int delta_y = abs(y2 - y1);
    int sign_x = x1 < x2 ? 1 : -1;
    int sign_y = y1 < y2 ? 1 : -1;
    int second_error;
    int first_error = delta_x - delta_y;
    thickness /= 2;
    draw_field_circle(img, x2, y2, thickness, color);
    while(x1 != x2 || y1 != y2){
        draw_field_circle(img, x1, y1, thickness, color);
        second_error = first_error * 2;
        if(second_error > -delta_y) {
            first_error -= delta_y;
            x1 += sign_x;
        }
        if(second_error < delta_x) {
            first_error += delta_x;
            y1 += sign_y;
        }
    }
}

void paint_biggest_rect(img_t *img, params_t* params){
    coords_t left_up;
    coords_t right_down;


    int max_area = 0;
    int max_x1, max_y1, max_x2, max_y2, cur_x_max, cur_y_max, area;
    for (int y = 0; y < img->info_header->height; y++){
        for (int x = 0; x < img->info_header->width; x++){
            if (color_cmp(img->pixels[y][x], params->old_color)){
                cur_x_max = x;
                cur_y_max = y;
                while (cur_y_max < img->info_header->height && color_cmp(img->pixels[cur_y_max][x], params->old_color)) {
                    cur_y_max++;
                }
                while (cur_x_max < img->info_header->width && color_cmp(img->pixels[y][cur_x_max], params->old_color)) {
                    cur_x_max++;
                }
                cur_y_max--;
                cur_x_max--;
                area = (cur_x_max - x + 1) * (cur_y_max - y + 1);
                if (area > max_area) {
                    if (check_filled_area(img, params->old_color, x, y, cur_x_max, cur_y_max)) {
                        max_area = area;
                        max_x1 = x;
                        max_y1 = y;
                        max_x2 = cur_x_max;
                        max_y2 = cur_y_max;
                    }
                }
            }
        }
    }

    if (max_area != 0) {
        for (int y = max_y1; y <= max_y2; y++) {
            for (int x = max_x1; x <= max_x2; x++) {
                set_pixel(img, x, y, params->new_color);
            }
        }
    }
}

void paint_triangle(img_t* img, params_t* params){
    if (params->fill){
        int first_sign, second_sign, third_sign;

        for (size_t i = 0; i < img->info_header->width; i++){
            for (size_t j = 0; j < img->info_header->height; j++){
                first_sign = (params->points[0].x - i) * (params->points[1].y - params->points[0].y) -
                    (params->points[1].x - params->points[0].x) * (params->points[0].y - j);

                second_sign = (params->points[1].x - i) * (params->points[2].y - params->points[1].y) -
                    (params->points[2].x - params->points[1].x) * (params->points[1].y - j);

                third_sign = (params->points[2].x - i) * (params->points[0].y - params->points[2].y) -
                    (params->points[0].x - params->points[2].x) * (params->points[2].y - j);

                first_sign = (first_sign >= 0)? 1 : -1;
                second_sign = (second_sign >= 0)? 1 : -1;
                third_sign = (third_sign >= 0)? 1 : -1;

                if (first_sign == second_sign && first_sign == third_sign && second_sign == third_sign){
                    set_pixel(img, i, j, params->fill_color);
                }
            }
        }
        
    }

    for (size_t i = 0; i < 3; i++){
        draw_line(img, params->color, params->thickness, params->points[i].x, params->points[i].y, params->points[(i+1)%3].x, params->points[(i+1)%3].y);
    }

}

void make_collage(img_t* img, params_t* params){
    int new_image_size, new_file_size;
    rgb_t** new_pixels = malloc(sizeof(rgb_t*) * img->info_header->height * params->number_y);
    for (size_t i = 0; i < img->info_header->height * params->number_y; i++){
        new_pixels[i] = malloc(sizeof(rgb_t) * img->info_header->width * params->number_x);
    }

    for (size_t i = 0; i < img->info_header->height * params->number_y; i++){
        for (size_t j = 0; j < img->info_header->width * params->number_x; j++){
            new_pixels[i][j] = img->pixels[i%img->info_header->height][j%img->info_header->width];
        }
    }
    
    for (size_t i = 0; i < img->info_header->height; i++){
        free(img->pixels[i]);
    }
    free(img->pixels);

    new_image_size = img->info_header->image_size * params->number_x * params->number_y;
    new_file_size = img->file_header->file_size - img->info_header->image_size + new_image_size;
    img->info_header->image_size = new_image_size;
    img->file_header->file_size = new_file_size;
    img->info_header->width = img->info_header->width * params->number_x;
    img->info_header->height = img->info_header->height * params->number_y;
    img->pixels = new_pixels;
}

void do_gamma(img_t* img, params_t* params){
    for (size_t i = 0; i < img->info_header->height; i++){
        for (size_t j = 0; j < img->info_header->width; j++){
            img->pixels[i][j].r = powf(img->pixels[i][j].r/255.0, params->value)*255;
            img->pixels[i][j].g = powf(img->pixels[i][j].g/255.0, params->value)*255;
            img->pixels[i][j].b = powf(img->pixels[i][j].b/255.0, params->value)*255;
        }
    }
}   

void edit_image(img_t *img, params_t* params){
    if (params->info_flag){
        print_info_header(*img->info_header);
        print_file_header(*img->file_header);
        exit(0);
    }

    if (params->biggest_rect){
        paint_biggest_rect(img, params);
    }

    if (params->triangle){
        paint_triangle(img, params);
    }

    if (params->collage){
        make_collage(img, params);
    }

    if (params->gamma) {
        do_gamma(img, params);
    }
}   