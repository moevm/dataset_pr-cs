#ifndef MAIN_FUNCS_H
#define MAIN_FUNCS_H
#define PI 3.14159265
#include <stdbool.h>
#include <math.h>
#include "signatures.h"

bool check_colors(color_t color) {
    if ((color.r < 0) || (color.r > 255) || (color.g < 0) || (color.g > 255) || (color.b < 0) || (color.b > 255)) {
        return false;
    }
    return true;
}

bool check_coords(png_t* image, ipoint_t point) {
    const int width = image->width;
    const int height = image->height;
    if ((point.x < 0) || (point.x >= width) || (point.y < 0) || (point.y >= height)) {
        return false;
    }
    return true;
}

void set_pixel(png_t* image, ipoint_t point, color_t color) {
    if (check_coords(image, point)) {
        png_byte* row = image->row_pointers[point.y];
        png_byte* ptr = &(row[point.x * 3]);
        ptr[0] = color.r;
        ptr[1] = color.g;
        ptr[2] = color.b;
    }
}

void draw_line(png_t* image, ipoint_t point1, ipoint_t point2, color_t color) {
    int dx =  abs(point2.x - point1.x);
    int sign_x = point1.x < point2.x ? 1 : -1;

    int dy = -abs(point2.y - point1.y);
    int sign_y = point1.y < point2.y ? 1 : -1;

    int err = dx + dy;
    int e2;
 
    while(1) {
        set_pixel(image, point1, color);

        if (point1.x == point2.x && point1.y == point2.y) {
            break;
        }

        e2 = 2 * err;

        if (e2 >= dy) {
            err += dy; 
            point1.x += sign_x; 
        }

        if (e2 <= dx) { 
            err += dx;
            point1.y += sign_y;
        }
   }
}

void draw_thick_line(png_t* image, ipoint_t point1, ipoint_t point2, color_t color, int thickness) {
    int dx =  abs(point2.x - point1.x);
    int sign_x = point1.x < point2.x ? 1 : -1;

    int dy = -abs(point2.y - point1.y);
    int sign_y = point1.y < point2.y ? 1 : -1;

    int err = dx + dy;
    int e2;
 
    while(1) {
        draw_circle(image, point1, thickness, color);

        if (point1.x == point2.x && point1.y == point2.y) {
            break;
        }

        e2 = 2 * err;

        if (e2 >= dy) {
            err += dy; 
            point1.x += sign_x; 
        }

        if (e2 <= dx) { 
            err += dx;
            point1.y += sign_y;
        }
   }
}

void draw_smooth_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t color, int thickness) {
    if (thickness <= 0) {
        fprintf(stderr, "wrong thickness\n");
        exit(thickness_error);
    }

    thickness = thickness / 2;

    if (point1.x > point2.x) {
        int tmp = point1.x;
        point1.x = point2.x;
        point2.x = tmp;
    }

    if (point1.y > point2.y) {
        int tmp = point1.y;
        point1.y = point2.y;
        point2.y = tmp;
    }

    if (point1.x >= image->width || point1.y >= image->height) {
        fprintf(stderr, "wrong coords\n");
        exit(coords_error);
    }

    ipoint_t point21 = {point2.x, point1.y};
    ipoint_t point12 = {point1.x, point2.y};

    if (thickness == 1) {
        draw_line(image, point1, point21, color);
        draw_line(image, point12, point2, color);

        draw_line(image, point1, point12, color);
        draw_line(image, point21, point2, color);
    }

    else {
        draw_thick_line(image, point1, point21, color, thickness);
        draw_thick_line(image, point12, point2, color, thickness);

        draw_thick_line(image, point1, point12, color, thickness);
        draw_thick_line(image, point21, point2, color, thickness);
    }
}

void draw_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t border_color, color_t fill_color, int thickness) {
    if (thickness <= 0) {
        fprintf(stderr, "wrong thickness\n");
        exit(thickness_error);
    }

    thickness = thickness / 2;

    if (point1.x > point2.x) {
        int tmp = point1.x;
        point1.x = point2.x;
        point2.x = tmp;
    }

    if (point1.y > point2.y) {
        int tmp = point1.y;
        point1.y = point2.y;
        point2.y = tmp;
    }

    if (point1.x >= image->width || point1.y >= image->height) {
        fprintf(stderr, "wrong coords\n");
        exit(coords_error);
    }

    for (int y = point1.y - thickness; y <= point2.y + thickness; y++) {
        for (int x = point1.x - thickness; x <= point2.x + thickness; x++) {
            ipoint_t cur_p = {x, y};
            if (((cur_p.x - point1.x) <= thickness) || ((cur_p.y - point1.y) <= thickness) || ((point2.x - cur_p.x) <= thickness) || ((point2.y - cur_p.y) <= thickness)) {
                set_pixel(image, cur_p, border_color);
            }
            else if (!color_cmp(border_color, fill_color)) {
                set_pixel(image, cur_p, fill_color);
            }
        }
    }
}

color_t get_pixel(png_t* image, ipoint_t point) {
    color_t color;
    if (!check_coords(image, point)) {
        color.r = -1;
        color.g = -1;
        color.b = -1;
        return color;
    }
    png_byte* row = image->row_pointers[point.y];
    png_byte* ptr = &(row[point.x * 3]);
    color.r = ptr[0];
    color.g = ptr[1];
    color.b = ptr[2];
    return color;
}

bool color_cmp (color_t c1, color_t c2) {
    if ((c1.r != c2.r) || (c1.g != c2.g) || (c1.b != c2.b)){
        return false;
    }
    return true;
} 

void flood_fill(png_t* image, ipoint_t point, color_t fill_color, color_t borders_color) {
    if (!check_coords(image, point)) {
        return;
    }

    color_t current_color = get_pixel(image, point);

    if (color_cmp(current_color, borders_color) || color_cmp(current_color, fill_color)) {
        return;
    }

    ipoint_t* stack = (ipoint_t*)malloc(sizeof(ipoint_t) * image->width * image->height);
    int stack_size = 0;
    
    stack[stack_size++] = point;

    while (stack_size > 0) {
        ipoint_t p = stack[--stack_size];
        
        set_pixel(image, p, fill_color);

        if (p.x + 1 < image->width) {
            ipoint_t tmp = {p.x + 1, p.y};
            current_color = get_pixel(image, tmp);
            if (!color_cmp(current_color, borders_color) && !color_cmp(current_color, fill_color)) {
                stack[stack_size++] = tmp;
            }
        }

        if (p.x - 1 >= 0) {
            ipoint_t tmp = {p.x - 1, p.y};
            current_color = get_pixel(image, tmp);
            if (!color_cmp(current_color, borders_color) && !color_cmp(current_color, fill_color)) {
                stack[stack_size++] = tmp;
            }
        }

        if (p.y + 1 < image->height) {
            ipoint_t tmp = {p.x, p.y + 1};
            current_color = get_pixel(image, tmp);
            if (!color_cmp(current_color, borders_color) && !color_cmp(current_color, fill_color)) {
                stack[stack_size++] = tmp;
            }
        }

        if (p.y - 1 >= 0) {
            ipoint_t tmp = {p.x, p.y - 1};
            current_color = get_pixel(image, tmp);
            if (!color_cmp(current_color, borders_color) && !color_cmp(current_color, fill_color)) {
                stack[stack_size++] = tmp;
            }
        }
    }
    free(stack);
}

void draw_filled_rectangle(png_t* image, ipoint_t point1, ipoint_t point2, color_t border_color, color_t fill_color, int thickness) {
    draw_smooth_rectangle(image, point1, point2, border_color, thickness);

    ipoint_t tmp = {(point2.x + point1.x) / 2, (point2.y + point1.y) / 2};

    if (tmp.x >= 0 && tmp.x < image->width && tmp.y >= 0 && tmp.y < image->height) {
        flood_fill(image, tmp, fill_color, border_color);
    }
    
    else {
        ipoint_t closest_point;
        closest_point.x = (tmp.x < 0) ? 0 : (tmp.x >= image->width) ? image->width - 1 : tmp.x;
        closest_point.y = (tmp.y < 0) ? 0 : (tmp.y >= image->height) ? image->height - 1 : tmp.y;
        flood_fill(image, closest_point, fill_color, border_color);
    }
}

void draw_hexagon(png_t* image, ipoint_t center, float radius, color_t color, int thickness) {
    if ((thickness <= 0)) {
        fprintf(stderr, "wrong thickness\n");
        exit(thickness_error);
    }

    thickness = thickness / 2;
    
    const int nsides = 6;

    float angle = 0.0f;
    float incr = 2.0f * PI / nsides;

    ipoint_t new_point = {radius * cos(angle) + center.x, radius * sin(angle) + center.y};
    for (int i = 0; i < nsides; ++i){
        ipoint_t old_point = {new_point.x, new_point.y};

        angle += incr;

        new_point.x = radius * cos(angle) + center.x;
        new_point.y = radius * sin(angle) + center.y;

        if (thickness == 1) {
            draw_line(image, old_point, new_point, color);
        }
        else {
            draw_thick_line(image, old_point, new_point, color, thickness);
        }
    }
}

void draw_filled_hexagon(png_t* image, ipoint_t center, float radius, color_t border_color, color_t fill_color, int thickness) {
    draw_hexagon(image, center, radius, border_color, thickness);
    ipoint_t tmp = (ipoint_t){center.x + 1, center.y + 1};
    flood_fill(image, tmp, fill_color, border_color);
}

void draw_circle(png_t* image, ipoint_t center, int radius, color_t color) { 
    for(int y = -radius; y <= radius; y++) {
        for(int x = -radius; x <= radius; x++){
            if(x*x + y*y <= radius*radius) {
                ipoint_t tmp = {center.x + x, center.y + y};
                set_pixel(image, tmp, color);
            }
        }
    }
}

void copy(png_t* image, ipoint_t left_up, ipoint_t right_down, ipoint_t dest) {

    int copy_width = right_down.x - left_up.x + 1;
    int copy_height = right_down.y - left_up.y + 1;

    color_t** tmp = (color_t**)malloc(sizeof(color_t*) * copy_height);

    for (int i = 0; i < copy_height; i++) {
        tmp[i] = (color_t*)malloc(sizeof(color_t) * copy_width);
    }

    for (int y = left_up.y; y <= right_down.y; y++) {
        for (int x = left_up.x; x <= right_down.x; x++) {
            ipoint_t p = {x, y};
            tmp[y - left_up.y][x - left_up.x] = get_pixel(image, p);
        }
    }

    ipoint_t new_right_down = {dest.x + copy_width - 1 , dest.y + copy_height - 1};
    put_pixel_arr(image, dest, new_right_down, tmp);
}

void put_pixel_arr(png_t* image, ipoint_t left_up, ipoint_t right_down, color_t** pix_arr) {
    for (int y = left_up.y; y <= right_down.y; y++) {
        for (int x = left_up.x; x <= right_down.x; x++) {
            ipoint_t p = {x, y};
            set_pixel(image, p, pix_arr[y - left_up.y][x - left_up.x]);
        }
    }
}

void binarization(png_t* image, int threshold) {
    color_t white = {255, 255, 255};
    color_t black = {0, 0, 0};
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            ipoint_t cur_p = {x, y};
            color_t pix = get_pixel(image, cur_p);
            if ((pix.r + pix.g + pix.b) >= threshold) {
                set_pixel(image, cur_p, white);
            }
            else {
                set_pixel(image, cur_p, black);
            }
        }
    }
}

#endif