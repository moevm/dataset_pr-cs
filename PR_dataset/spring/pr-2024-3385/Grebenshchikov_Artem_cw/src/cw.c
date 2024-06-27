#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <png.h>
#include "cw.h"



void print_help() {
    FILE *file = fopen("help", "r");
    if (!file) {
        fprintf(stderr, "Help_info_file is not found.\n");
        exit(40);
    }
    char ch = (char) fgetc(file);
    while (ch != EOF) {
        printf("%c", ch);
        ch = (char) fgetc(file);
    }
    fclose(file);
}

void read_png_file(char *file_name, Png *image) {
    unsigned char header[8];
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        fprintf(stderr, "Error in read_png_file function: file could not be opened.\n");
        exit(41);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        fprintf(stderr, "Error in read_png_file function: file is not recognized as a PNG.\n");
        exit(42);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        fclose(fp);
        fprintf(stderr, "Error in read_png_file function: png_create_read_struct failed.\n");
        exit(43);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        fclose(fp);
        fprintf(stderr, "Error in read_png_file function: png_create_info_struct failed.\n");
        exit(44);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        fprintf(stderr, "Error in read_png_file function: error during init_io.\n");
        exit(45);
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);
    if (image->color_type != PNG_COLOR_TYPE_RGB) {
        fclose(fp);
        fprintf(stderr, "The program supports working only with the PNG_COLOR_TYPE_RGB\n");
        exit(46);
    }
    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        fprintf(stderr, "Error in read_png_file function: error during read_image.\n");
        exit(47);
    }
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; y++) {
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}

void write_png_file(char *file_name, Png *image) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        fprintf(stderr, "Error in write_png_file function: file could not be opened.\n");
        exit(41);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: png_create_write_struct failed.\n");
        exit(42);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: png_create_info_struct failed.\n");
        exit(43);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: error during init_io.\n");
        exit(44);
    }
    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: error during writing header.\n");
        exit(45);
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: error during writing bytes.\n");
        exit(46);
    }
    png_write_image(image->png_ptr, image->row_pointers);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        fprintf(stderr, "Error in write_png_file function: error during writing end of file.\n");
        exit(47);
    }
    png_write_end(image->png_ptr, NULL);
    fclose(fp);
}

void free_image_data(Png *img) {
    for (int y = 0; y < img->height; y++) {
        free(img->row_pointers[y]);
    }
    free(img->row_pointers);
}

void print_png_info(Png *img) {
    printf("Image Width: %d\n", img->width);
    printf("Image Height: %d\n", img->height);
    printf("Image Bit Depth: %d\n", img->bit_depth);
    printf("Image Channels: %d\n", img->channels);
    printf("Image Colour Type: RGB\n");
}

int* string_tok(char* string_arg, int size) {
    char * sch = strtok(string_arg, ".");
    int* arr = (int*)malloc(sizeof(int) * size);
    int ind = 0;
    if (sch == NULL) {
        fprintf(stderr, "The argument was submitted incorrectly.\n");
        exit(41);
    }
    while (sch != NULL) {
        if (is_digit(sch)) {
            printf("An incorrectly submitted number\n");
            exit(42);
        }
        if (ind == size) {
            printf("Incorrect number of arguments.\n");
            exit(43);
        }
        arr[ind] = atoi(sch);
        sch = strtok (NULL, ".");
        ind++;
    }
    if (ind != size) {
        printf("Incorrect number of arguments.\n");
        exit(44);
    }
    return arr;    
}

void check_extra_arg(char* str, char* flag, int number_arguments, int next_ind, int max_ind, int flag_input_file) {
    if ((next_ind < (max_ind - 1)) || (flag_input_file && (next_ind == (max_ind - 1)))) {
        int is_flag;
        if ((strlen(str) == 2) && (str[0] == '-') && isalpha(str[1])) {
            is_flag = 0;
        } else if ((strlen(str) > 2) && (str[0] == '-') && (str[1] == '-')) {
            is_flag = 0;
        } else {
            is_flag = 1;
        }
        if ((number_arguments == 0) && is_flag) {
            printf("The '%s' argument is ignored because the '%s' flag does not accept arguments\n", str, flag);
            exit(40);
        }
        if (number_arguments && is_flag) {
            printf("The '%s' argument is ignored because the '%s' flag takes one argument\n", str, flag);
            exit(40);
        }
    }
}

int is_digit(char* string_digit) {
    if(!strlen(string_digit)) 
        return 1;
    if(string_digit[0] == '0' &&  (strlen(string_digit) > 1)) 
        return 1;
    int ind;
    if (string_digit[0] == '-' &&  (strlen(string_digit) >= 2) && string_digit[1] != '0'){
        ind = 1;
    }else{
        ind = 0;
    }
    while(string_digit[ind] != '\0'){
        if(!isdigit(string_digit[ind])){
            return 1;
        }
        ind++;
    }
    return 0;
}

int is_pixel_in_img(Png *img, int x, int y) {
    if (y >= 0 && y < img->height && x >= 0 && x < img->width) {
        return 1;
    }
    return 0;
}

int check_pixel_color(Png *img, int x, int y, int* color_arr) {
    if ((img->row_pointers[y][x * img->channels + 0] == color_arr[0] && img->row_pointers[y][x * img->channels + 1] == color_arr[1] &&
        img->row_pointers[y][x * img->channels + 2] == color_arr[2])) {
        return 1;
    }
    return 0;
}

void put_pixel(Png *img, int x, int y, int *color_arr) {
    if (!is_pixel_in_img(img, x, y)){
        return;
    }
    img->row_pointers[y][x * img->channels + 0] = color_arr[0];
    img->row_pointers[y][x * img->channels + 1] = color_arr[1];
    img->row_pointers[y][x * img->channels + 2] = color_arr[2];
}

void draw_in_octants(Png *img, int xc, int yc, int x, int y, int *color_arr) {
    put_pixel(img,xc+x, yc+y, color_arr);
    put_pixel(img, xc-x, yc+y, color_arr);
    put_pixel(img, xc+x, yc-y, color_arr);
    put_pixel(img, xc-x, yc-y, color_arr);
    put_pixel(img, xc+y, yc+x, color_arr);
    put_pixel(img, xc-y, yc+x, color_arr);
    put_pixel(img, xc+y, yc-x, color_arr);
    put_pixel(img, xc-y, yc-x, color_arr);
}

void fill_circle(Png *img, int xc, int yc, int r, int *color_arr) {
    int min_x = xc - r;
    int min_y = yc - r;
    int max_x = xc + r;
    int max_y = yc + r;
    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            if (pow(x - xc, 2) + pow(y - yc, 2) <= pow(r, 2)) {
                put_pixel(img, x, y, color_arr);
            }
        }
    }
}

void draw_filled_circle(Png *img, int xc, int yc, int r, int *color_arr) {  
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
    fill_circle(img, xc, yc, r, color_arr);
}

void draw_line(Png *img, int x1, int y1, int x2, int y2, int *color_arr) {
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    put_pixel(img, x2, y2, color_arr);
    while (x1 != x2 || y1 != y2) {
        put_pixel(img, x1, y1, color_arr);
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

void draw_thick_odd_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    draw_line(img, x1, y1, x2, y2, color_arr);
    if (thickness == 1) {
        return;
    }
    if (abs(y2 - y1) >= abs(x2 - x1)) {
        for (int i = 1; i <= (thickness - 1) / 2; i++) {
            draw_line(img, x1 + i, y1, x2 + i, y2, color_arr);
            draw_line(img, x1 - i, y1, x2 - i, y2, color_arr);
        }
    } else {
        for (int i = 1; i <= (thickness - 1) / 2; i++) {
            draw_line(img, x1, y1 + i, x2, y2 + i, color_arr);
            draw_line(img, x1, y1 - i, x2, y2 - i, color_arr);
        }
    }
}

void draw_thick_even_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    draw_thick_odd_line(img, x1, y1, x2, y2, thickness - 1, color_arr);
    if (abs(y2 - y1) >= abs(x2 - x1)) {
        draw_line(img, x1 + thickness / 2, y1, x2 + thickness / 2, y2, color_arr);
    } else {
        draw_line(img, x1, y1 + thickness / 2, x2, y2 + thickness / 2, color_arr);
    }
}

int is_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    double ab = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double ac = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    double bc = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
    if (ab + ac > bc && ab + bc > ac && ac + bc > ab) {
        return 1;
    }
    return 0;
}

int is_point_in_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x0, int y0) {
    int prod_1 = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
    int prod_2 = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
    int prod_3 = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
    if ((prod_1 > 0 && prod_2 > 0 && prod_3 > 0) || (prod_1 < 0 && prod_2 < 0 && prod_3 < 0)) {
        return 1;
    }
    return 0;
}

int check_filled_rect(Png* img, int x1, int y1, int x2, int y2, int *color_arr) {
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            if (is_pixel_in_img(img, x, y)) {
                if (!check_pixel_color(img, x, y, color_arr)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void make_empty_image(Png* img, Png* new_img, int height, int width) {
    new_img->width = width;
    new_img->height = height;
    new_img->color_type = img->color_type;
    new_img->bit_depth = img->bit_depth;
    new_img->channels = img->channels;
    new_img->number_of_passes = img->number_of_passes;
    new_img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!new_img->png_ptr) {
        fprintf(stderr, "Error in make_empty_image function: png_create_read_struct failed.\n");
        exit(41);
    }
    new_img->info_ptr = png_create_info_struct(new_img->png_ptr);
    if (!new_img->info_ptr) {
        png_destroy_read_struct(&new_img->png_ptr,(png_infopp)NULL, (png_infopp)NULL);
        fprintf(stderr, "Error in make_empty_image function: png_create_info_struct failed.\n");
        exit(42);
    }
    png_read_update_info(new_img->png_ptr, new_img->info_ptr);
    new_img->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * new_img->height);
    for (int y = 0; y < new_img->height; y++) {
        new_img->row_pointers[y] = (png_byte *) malloc((png_get_rowbytes(img->png_ptr, img->info_ptr) / img->width) * new_img->width);
    }
}

void insert_part_of_image(Png* img, Png* new_img, int x_offset, int y_offset){
    int color_arr[3];
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            color_arr[0] = img->row_pointers[y][x * img->channels + 0];
            color_arr[1] = img->row_pointers[y][x * img->channels + 1];
            color_arr[2] = img->row_pointers[y][x * img->channels + 2];
            put_pixel(new_img, x + x_offset, y + y_offset, color_arr);
        }
    }
}

void draw_triangle(Png* img, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int *line_color, int fill, int* fill_color) {
    if (fill) {
        int arr_x[3] = {x1, x2, x3};
        int arr_y[3] = {y1, y2, y3};
        int min_x = 0, max_x= 0, min_y = 0, max_y = 0;
        for (int i = 0; i < 3; i++) {
            if (min_x> arr_x[i]) {
                min_x= arr_x[i];
            }
            if (max_x< arr_x[i]) {
                max_x= arr_x[i];
            }
            if (min_y > arr_y[i]) {
                min_y = arr_y[i];
            }
            if (max_y < arr_y[i]) {
                max_y = arr_y[i];
            }
        }
        for (int y = min_y; y <= max_y; y++) {
            for (int x = min_x; x <= max_x; x++) {
                if (is_point_in_triangle(x1, y1, x2, y2, x3, y3, x, y)) {
                    put_pixel(img, x, y, fill_color);
                }
            }
        }
    }
    draw_thick_line(img, x1, y1, x2, y2, thickness, line_color);
    draw_thick_line(img, x1, y1, x3, y3, thickness, line_color);
    draw_thick_line(img, x2, y2, x3, y3, thickness, line_color);
    if (thickness > 3) {
        draw_filled_circle(img, x1, y1, thickness / 2, line_color);
        draw_filled_circle(img, x2, y2, thickness / 2, line_color);
        draw_filled_circle(img, x3, y3, thickness / 2, line_color);
    }
}

void recolor_max_rectangle(Png* img, int* old_color, int* new_color) {
    int area_rect, max_area_rect = 0;
    int min_x1, min_y1, max_x2, max_y2, xw, yh;
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if (check_pixel_color(img, x, y, old_color)) {
                xw = x;
                yh = y;
                while (xw < img->width && check_pixel_color(img, xw, y, old_color)) {
                    xw++;
                }
                while (yh < img->height && check_pixel_color(img, x, yh, old_color)) {
                    yh++;
                }
                xw--;
                yh--;
                area_rect = (xw - x + 1) * (yh - y + 1);
                if (area_rect > max_area_rect) {
                    if (check_filled_rect(img, x, y, xw, yh, old_color)) {
                        max_area_rect = area_rect;
                        min_x1 = x;
                        min_y1 = y;
                        max_x2 = xw;
                        max_y2 = yh;
                    }
                }
            }
        }
    }
    if (max_area_rect!=0) {
        for (int y = min_y1; y <= max_y2; y++) {
            for (int x = min_x1; x <= max_x2; x++) {
                put_pixel(img, x, y, new_color);
            }
        }
    } else {
        printf("There are no rectangles of the specified color in the image.\n");
    }
}

void make_collage(Png* img, Png* new_img, int number_y, int number_x) {
    make_empty_image(img, new_img, img->height * number_y, img->width * number_x);
    int y_offset = img->height;
    int x_offset = img->width;
    for (int y = 0; y < number_y; y++) {
        for(int x = 0; x < number_x; x++) {
            insert_part_of_image(img, new_img, x * x_offset, y * y_offset);
        }
    }
}

void draw_thick_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    if (thickness % 2 == 1) {
        draw_thick_odd_line(img, x1, y1, x2, y2, thickness, color_arr);
    } else {
        draw_thick_even_line(img, x1, y1, x2, y2, thickness, color_arr);
    }
}

void comr(Png* img, Png* img2, int t){
    int h = floor(img->height/t);
    int w = floor(img->width/t);
    int color_arr[3];
    make_empty_image(img, img2, h, w);
    
    for (int y = 0; y < (img->height - t+1); y = y + t) {
        for (int x = 0; x < (img->width - t+1); x = x + t) {
            for (int j = 0; j < 3; j++){
                color_arr[j] = 0;
            }
            for (int y2 = 0; y2 < t; y2++) {
                for(int x2 = 0; x2 < t; x2++) {
                    color_arr[0] += img->row_pointers[y+y2][(x + x2) * img->channels + 0];
                    color_arr[1] += img->row_pointers[y+y2][(x + x2) * img->channels + 1];
                    color_arr[2] += img->row_pointers[y+y2][(x + x2) * img->channels + 2];
                }
            }
            for (int i = 0; i < 3; i++){

                color_arr[i] = floor(color_arr[i] / (t*t));

            }
            
            put_pixel(img2, x/t, y/t, color_arr);
        }
    }



}