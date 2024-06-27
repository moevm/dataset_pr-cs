#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include <png.h>

typedef struct Png{
    int width, height;
    png_byte color_type; // type of pallete
    png_byte bit_depth;  // rgb-3 or rgba-4
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

typedef struct lines{ // arguments of line
    int start[2];
    int end[2];
    int color[3];
    int thickness;
} lines;

typedef struct inv{ // arguments of circle to inverse
    int center[2];
    int radius;
} inv;

typedef struct trims{ // arguments for area to trim
    int left_coords[2];
    int right_coords[2];
} trims;

typedef struct component{
    float alpha;
    int beta;
} component;

void read_png_file(char *file_name, struct Png *image){
    int x, y;
    unsigned char header[8]; // 8 is the maximum size that can be checked
    FILE *fp = fopen(file_name, "rb"); // open file
    if (!fp){
        printf("File could not be opened.");
        exit(40);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){ // checks whether the given number of bytes match the PNG signature
        printf("File is not recognized as a PNG");
        exit(40);
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        printf("Png_create_read_struct failed.");
        exit(40);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Png_create_info_struct failed.");
        exit(40);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io.");
        exit(40);
    }
    png_init_io(image->png_ptr, fp); // start of reading file
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during read_image.");
        exit(40);
    }
    image->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}

 
void write_png_file(char *file_name, struct Png *image){
    int x, y;
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf("File could not be opened.");
        exit(40);
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        printf("Structure could not be created.");
        exit(40);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Structure could not be created.");
        exit(40);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io.");
        exit(40);
    }
    png_init_io(image->png_ptr, fp);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing header.");
        exit(40);
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing bytes.");
        exit(40);
    }
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during end of write.");
        exit(40);
    }
    png_write_end(image->png_ptr, NULL);
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);
}

void set_pixel(Png *image, int x, int y, int *color){ // colors a pixel
    if ((x >= 0 && x < image->width) && (y >= 0 && y < image->height)){
        png_bytep pixel = &(image->row_pointers[y][x * 3]);
        pixel[0] = color[0];
        pixel[1] = color[1];
        pixel[2] = color[2];
    }
}

void get_pixel(Png *image, int x, int y, int *color){
    if ((x >= 0 && x < image->width) && (y >= 0 && y < image->height)){
        png_bytep pixel = &(image->row_pointers[y][x * 3]);
        color[0] = pixel[0];
        color[1] = pixel[1];
        color[2] = pixel[2];
        return;
    }
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

int digit(char *str){
    if (*str == '-') {
        str++;
    }
    while (*str){
        if (!isdigit(*str))
            return 1;
        str++;
    }
    return 0;
}

void save_coordinates(char *optarg, int *value){
    char *token;
    int i = 0;
    int flag = 1;
    token = strtok(optarg, ".");
    if (token == NULL){
        exit(41);
    }
    while (token != NULL){
        flag = 1;
        if (i >= 2){
            printf("Too many values.");
            exit(41);
        }
        if (token[0] == '-'){
            flag = -1;
            token++;
        }
        if (!digit(token)){
            value[i] = atoi(token) * flag;
            i++;
            token = strtok(NULL, ".");
        } else {
            printf("Value must be a number.");
            exit(41);
        }
    }
    if (i < 2){
        exit(41);
    }
}

void save_color(char *optarg, int *value){
    char *token;
    int i = 0;
    token = strtok(optarg, ".");
    while (token != NULL){
        if (i >= 3){
            printf("Too many values.");
            exit(41);
        }
        if (!digit(token)){
            int digit = atoi(token);
            if (digit >= 0 && digit <= 255){
                value[i] = digit;
                i++;
                token = strtok(NULL, ".");
            } else {
                printf("Values for colors must be between 0 and 255.");
                exit(41);
            }
        } else {
            printf("Value must be a number.");
            exit(41);
        }
    }
}

void save_digit(char *optarg, int *value){
    if (!digit(optarg)){
        int digit = atoi(optarg);
        if (digit > 0){
            *value = atoi(optarg);
        } else {
            printf("Value must be a positive number.");
            exit(41);
        }
    } else {
        printf("Value must be a number.");
        exit(41);
    }
}

void draw_circle(Png *image, int x0, int y0, int thickness, int* color){
    int xmin = x0 - thickness;
    int xmax = x0 + thickness;
    int ymin = y0 - thickness;
    int ymax = y0 + thickness;
    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= image->width) xmax = image->width - 1;
    if (ymax >= image->height) ymax = image->height - 1;
    for(int x = xmin; x <= xmax; x++){
        for(int y = ymin; y <= ymax; y++){
            if ((x-x0)*(x-x0) + (y-y0)*(y-y0) <= thickness*thickness)
                set_pixel(image, x, y, color);
        }
    }
}

void draw_line(Png* image, int x1,  int y1, int x2, int y2, int* color, int thickness){
    thickness = thickness / 2;
    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int error = deltax - deltay;
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int x_i = x1;
    int y_i = y1;
    if(thickness != 1){
        draw_circle(image, x2, y2, thickness, color);
    } else{
        set_pixel(image, x2, y2, color);
        }
    while(x_i != x2|| y_i != y2){
        if(thickness != 1){
            draw_circle(image, x_i, y_i, thickness, color);
        } else{
            set_pixel(image, x_i, y_i, color);
        }
        int error2 = error * 2;
        if(error2 > -deltay){
            error -= deltay;
            x_i += signX;
        }
        if(error2 < deltax){
            error += deltax;
            y_i += signY;
        }
    }
}

// void draw_line(Png *image, int start_x, int start_y, int end_x, int end_y, int *color, int thickness){   
//     int dx = abs(end_x - start_x);
//     int dy = abs(end_y - start_y);
//     int sign_x = (start_x < end_x) ? 1 : -1;
//     int sign_y = (start_y < end_y) ? 1 : -1;
//     int error = dx - dy;
//     while (1){
//         for (int i = -thickness / 2; i <= thickness / 2; i++){
//             for (int j = -thickness / 2; j <= thickness / 2; j++){
//                 int x = start_x + i;
//                 int y = start_y + j;
//                 set_pixel(image, x, y, color);
//             }
//         }
//         if (start_x == end_x && start_y == end_y){
//             break;
//         }
//         int error2 = 2 * error;
//         if (error2 > -dy){
//             error -= dy;
//             start_x += sign_x;
//         }
//         if (error2 < dx){
//             error += dx;
//             start_y += sign_y;
//         }
//     }
// }


void inverse_circle(Png *image, int x0, int y0, int radius){
    if (radius >= image->width || radius >= image->width){
        printf("Radius is bigger than image height or image width");
        exit(43);
    }
    for (int y = 0; y < image->height; y++){
        for (int x = 0; x < image->width; x++){
            int x1 = x - x0;
            int y1 = y - y0;
            double distance = sqrt(x1 * x1 + y1 * y1);
            if (distance <= radius){
                png_bytep pixel = &(image->row_pointers[y][x * 3]);
                pixel[0] = 255 - pixel[0];
                pixel[1] = 255 - pixel[1];
                pixel[2] = 255 - pixel[2];
            }
        }
    }
}

void trim(Png *image, int left, int up, int right, int down) {
    int width = right - left;
    int height = down - up;
    if (left > right || up > down) {
        printf("Invalid area");
        exit(44);
    }
    unsigned char **data = malloc(sizeof(unsigned char*) * height);
    for (int i = 0; i < height; i++) {
        data[i] = malloc(sizeof(unsigned char) * width*3);
    }
    for (int x = left; x < right; x++) {
        for (int y = up; y < down; y++) {
            int color[3];
            get_pixel(image, x, y, color);
            data[y - up][(x - left) * 3] = color[0];
            data[y - up][(x - left) * 3 + 1] = color[1];
            data[y - up][(x - left) * 3 + 2] = color[2];
        }
    }
    image->height = height;
    image->width = width;
    //free(image->row_pointers)
    image->row_pointers = data;
    png_set_IHDR(image->png_ptr, image->info_ptr,
        width,
        height,
        image->bit_depth,
        image->color_type,
        png_get_interlace_type(image->png_ptr, image->info_ptr),
        png_get_compression_type(image->png_ptr, image->info_ptr),
        png_get_filter_type(image->png_ptr, image->info_ptr)
    );
}

void contrasts(Png *image, float alpha, int beta){
    for (int y = 0; y < image -> height; y++){
        for (int x = 0; x < image -> width; x++){
            png_bytep row = image -> row_pointers[y];
            for (int i = 0; i < 3; i++){
                int old = row[x * 3 + i];
                int new = (alpha * old + beta);
                if (new > 255){
                    new = 255;
                }
                row[x * 3 + i] = new;
            }
        }
    }
}

void print_help(){
    printf("This programme allows to work with PNG file. There are a few functions that are supported.\n");
    printf("First function draws a line, it takes 4 values: the start point of line, the end pointof line, its color and thickness.\n");
    printf("Function template: --line --start x1.y1 --end x2.y2 --color rrr.ggg.bbb --thickness t\n");
    printf("Second function inverts the colors into a given circle, it takes 2 values: the center of circle anf it raduis.\n");
    printf("Function template: --inverse_circle --center x.y --radius r\n");
    printf("Third function crops the image, it takes 2 values: the coordinates of upper-left corner and lower-right corner.\n");
    printf("Function template: --trim --left_up x1.y1 --rigth_down x2.y2\n");
}

 
int main(int argc, char **argv){
    puts("Course work for option 4.18, created by Prokopovich Yana");
    Png image;
    char *input_name = "a.png";
    char *output_name = "out.png";
    lines line;
    inv inverse;
    trims crop;
    component comp;
    char *token;
    const char *short_options = "LIThns:e:c:t:o:r:l:g:O:i:";
    struct option long_options[] = {
        {"line", no_argument, 0, 'L'}, 
        {"start", required_argument, 0, 's'}, 
        {"end", required_argument, 0, 'e'}, 
        {"color", required_argument, 0, 'c'}, 
        {"thickness", required_argument, 0, 't'}, 
        {"inverse_circle", no_argument, 0, 'I'}, 
        {"center", required_argument, 0, 'o'}, 
        {"radius", required_argument, 0, 'r'}, 
        {"trim", no_argument, 0, 'T'}, 
        {"left_up", required_argument, 0, 'l'},
        {"right_down", required_argument, 0, 'g'},
        {"help", no_argument, 0, 'h'}, 
        {"info", no_argument, 0, 'n'}, 
        {"output", required_argument, 0, 'O'}, 
        {"input", required_argument, 0, 'i'},
        {"contrast", no_argument, 0, 'C'},
        {"alpha", required_argument, 0, 'a'}, 
        {"beta", required_argument, 0, 'b'},
        {NULL, 0, NULL, 0}};
    int opt;
    int long_index = 0;
    int first_flag = 0;
   while ((opt = getopt_long(argc, argv, short_options, long_options, &long_index)) != -1){
        switch (opt) {
        case 'L':
            first_flag = 'L';
            break;
        case 'I':
            first_flag = 'I';
            break;
        case 'T':
            first_flag = 'T';
            break;
        case 'C':
            first_flag = 'C';
            break;
        case 'h':
            print_help();
            exit(0);
            break;
        case 'n':
            printf("width - %d\nheight - %d\n", image.width, image.height);
            break;
        case 's':
            save_coordinates(optarg, line.start);
            break;
        case 'e':
            save_coordinates(optarg, line.end);
            break;
        case 'c':
            save_color(optarg, line.color);
            break;
        case 't':
            save_digit(optarg, &line.thickness);
            break;
        case 'o':
            save_coordinates(optarg, inverse.center);
            break;
        case 'r':
            save_digit(optarg, &inverse.radius);
            break;
        case 'g':
            save_coordinates(optarg, crop.right_coords);
            break;
        case 'l':
            save_coordinates(optarg, crop.left_coords);
            break;
        case 'O':
            output_name = optarg; // strcpy(output_name, optarg);
            break;
        case 'i':
            input_name = optarg; // strcpy(input_name, optarg);
            break;
        case 'a':
            if (optarg > 0){
                comp.alpha = atof(optarg);
            } else{
                exit(41);
            }
            break;
        case 'b':
            save_digit(optarg, &comp.beta);
            break;
        }
    }
    read_png_file(input_name, &image);
    switch (first_flag) {
        case 'L':
            draw_line(&image, line.start[0], line.start[1], line.end[0], line.end[1], line.color, line.thickness);
            write_png_file(output_name, &image);
            break;
        case 'I':
            inverse_circle(&image, inverse.center[0], inverse.center[1], inverse.radius);
            write_png_file(output_name, &image);
            break;
        case 'T':
            trim(&image, crop.left_coords[0], crop.left_coords[1], crop.right_coords[0], crop.right_coords[1]);
            write_png_file(output_name, &image);
            break;
        case 'C':
            contrasts(&image, comp.alpha, comp.beta);
            write_png_file(output_name, &image);
            break;
    }
    return 0;
}
