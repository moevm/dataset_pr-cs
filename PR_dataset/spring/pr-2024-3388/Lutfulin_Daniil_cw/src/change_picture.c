#include "change_picture.h"

void get_right_coords(pixels_t *pixels, point_t* left_up, point_t* right_down){
    if(left_up->x > right_down->x)
        swap_int(&left_up->x, &right_down->x);

    if(left_up->y > right_down->y)
        swap_int(&right_down->y, &left_up->y);

    left_up->x = max(left_up->x, 0);
    left_up->y =  max(left_up->y,0);

    right_down->x =  min(right_down->x, pixels->width-1);
    right_down->y =  min(right_down->y, pixels->height-1);
}

void mirror_field(pixels_t* pixels, point_t left_up, point_t right_down, char axis){

    get_right_coords(pixels, &left_up, &right_down);

    if(axis == 'x'){
        int field_width = right_down.x - left_up.x + 1;
        for(int y = left_up.y; y <= right_down.y; y++){
            for(int x = 0; x < field_width/2; x++){
                swap_rgb(&pixels->arr[y][left_up.x+x], &pixels->arr[y][right_down.x-x]);
            }
        }
    }

    else if(axis == 'y'){
        int field_height = right_down.y - left_up.y + 1;
        for(int y = 0; y <= field_height/2; y++){
            for(int x = left_up.x; x <= right_down.x; x++){
                swap_rgb(&pixels->arr[left_up.y + y][x], &pixels->arr[right_down.y - y][x]);
            }
        }
    }   
}

rgb_t** get_copy_arr(rgb_t **source, point_t left_up, int copy_height, int copy_width){

    rgb_t **copy_arr = (rgb_t**)malloc(copy_height * sizeof(rgb_t*));
    for(int y = 0; y < copy_height; y++){
        copy_arr[y] = (rgb_t*)malloc(copy_width * sizeof(rgb_t));
        for (int x = 0; x < copy_width; x++){
            copy_arr[y][x] = source[left_up.y + y][left_up.x + x];
        }
    }
    return copy_arr;
}

void copy_field(pixels_t *pixels, point_t left_up, point_t right_down, point_t dest_left_up){
    get_right_coords(pixels, &left_up, &right_down);

    int copy_height = (right_down.y - left_up.y + 1);
    int copy_width = (right_down.x - left_up.x + 1);
    rgb_t **copy_arr = get_copy_arr(pixels->arr, left_up, copy_height, copy_width);
    for(int y = 0; y < copy_height; y++){
        for (int x = 0; x < copy_width; x++){
            set_pixel(pixels, dest_left_up.y + y,  dest_left_up.x + x, copy_arr[y][x]);
        }
        free(copy_arr[y]);
    }
    free(copy_arr);
}

void draw_horisontal_strip(pixels_t *pixels, int y, int x, size_t thickness, rgb_t color){
    if(thickness%2){
        for(int i = x - ((int)thickness / 2); i <= x + ((int)thickness / 2); i++){
            set_pixel(pixels, y, i, color);
        }
    }else{
        for(int i = x - ((int)thickness / 2); i < x + ((int)thickness / 2); i++){
            set_pixel(pixels, y, i, color);
        }
    }
}

void draw_vertical_strip(pixels_t *pixels, int y, int x, size_t thickness, rgb_t color){
    if(thickness%2){
        for(int i = y - ((int)thickness / 2); i <= y + ((int)thickness / 2); i++){
            set_pixel(pixels, i, x, color);
        }
    }else{
        for(int i = y - ((int)thickness / 2); i <= y + ((int)thickness / 2); i++){
            set_pixel(pixels, i, x, color);
        }
    }
}

void draw_horisontal_line(pixels_t *pixels, int y, int x_start, int x_end, size_t thickness, rgb_t color){
    for(int x = x_start; x < x_end; x++){
        draw_vertical_strip(pixels, y, x, thickness, color);
    }
}

void draw_vertical_line(pixels_t *pixels, int y_start, int y_end, int x, size_t thickness, rgb_t color){
    for(int y = y_start; y < y_end; y++){
        draw_horisontal_strip(pixels, y, x, thickness, color);
    }
}

void replace_color(pixels_t* pixels, rgb_t old_color, rgb_t new_color){
    for(int y = 0; y < pixels->height; y++){
        for(int x = 0; x < pixels->width; x++){
            if(pixels->arr[y][x].r == old_color.r && pixels->arr[y][x].g == old_color.g && pixels->arr[y][x].b == old_color.b)
            set_pixel(pixels,y,x,new_color);
        }
    }
}

void split_image(pixels_t *pixels, size_t number_x, size_t number_y, size_t thickness, rgb_t color){

    float x_space = (float)pixels->width/number_x;
    float y_space = (float)pixels->height/number_y;

    for(size_t i = 1; i < number_x; i++){
        int x = (int)(i*x_space*2 - (int)(i*x_space));
        draw_vertical_line(pixels, 0, pixels->height, x, thickness, color);
    }

    for(size_t j = 1; j < number_y; j++){
        int y = (int)(j*y_space*2 - (int)(j*y_space));
        draw_horisontal_line(pixels, y, 0, pixels->width, thickness, color);
    }

}

void binarization(pixels_t *pixels, int treshold){
    for (size_t y = 0; y < pixels->height; y++){
        for (size_t x = 0; x < pixels->width; x++){
            if (pixels->arr[y][x].r + pixels->arr[y][x].g + pixels->arr[y][x].b >= treshold){
                pixels->arr[y][x] = (rgb_t){MAX_COLOR, MAX_COLOR, MAX_COLOR};
            }
            else{
                pixels->arr[y][x] = (rgb_t){0, 0, 0};
            }
        }
    }
}

void make_ornament(pixels_t *pixels, rgb_t color, int thickness, bmp_info_header_t* info_header, bmp_file_header_t* file_header){
    rgb_t** arr = malloc((info_header->height + thickness*2) * sizeof(rgb_t*));
    size_t padd = (4 - ((info_header->width + thickness*2) * sizeof(rgb_t)) % 4) % 4;
    for(int i = info_header->height + thickness*2 -1 ; i >= 0; i--){
        arr[i] = malloc((info_header->width + thickness*2) * sizeof(rgb_t) + padd);
    }
    for(int y = 0; y < info_header->height + thickness*2; y++){
        for (int x = 0; x < info_header->width + thickness*2; x++){
            arr[y][x] = color;
        }
    }

    for(int y = thickness; y < info_header->height + thickness; y++){
        for (int x = thickness; x < info_header->width + thickness; x++){
            arr[y][x] = pixels->arr[y-thickness][x-thickness];
        }
    }
    pixels->arr = arr;
    info_header->width += thickness*2;
    info_header->height += thickness*2;
    pixels->width = info_header->width;
    pixels->height = info_header->height;
}


void change_picture(pixels_t *pixels, pargs_t *pargs, bmp_info_header_t* info_header, bmp_file_header_t* file_header){
    if(pargs->mirror)
        mirror_field(pixels, pargs->left_up, pargs->right_down, pargs->mirror_axis);
    if(pargs->copy)
        copy_field(pixels, pargs->left_up, pargs->right_down, pargs->dest_left_up);
    if(pargs->color_replace)
        replace_color(pixels,pargs->old_color, pargs->new_color);
    if(pargs->split)
        split_image(pixels, pargs->number_x, pargs->number_y, pargs->thickness, pargs->color);
    if(pargs->info){
        print_file_header(*file_header);
        print_info_header(*info_header);
    }
    if(pargs->ornament)
        make_ornament(pixels, pargs->color, pargs->thickness, info_header, file_header);
}
