#include <stdio.h>  
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <png.h>

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

typedef struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
}Png;

typedef struct triangles{
    int x[3];
    int y[3];
    int thickness;
    int color[3];
    int fill;
    int fill_color[3];
}triangles;


typedef struct biggest_color{
    int old_color[3];
    int new_color[3];
}big_color;


typedef struct collages{
    int number_x;
    int number_y;
}collages;


typedef struct outsides{
    int x[2];
    int y[2];
    int color[3];
}outsides;


void read_png_file(char* file_name, Png *image){
    int y;
    char header[8];  //длина заголовка 8
    FILE *fp = fopen(file_name, "rb"); // открываем файл
    if (!fp){
        printf("Cannot read file.\n");
        exit(43);
    }
    fread(header, 1, 8, fp); //считываем заголовок
    if (png_sig_cmp((const unsigned char *)header, 0, 8)){ //проверка, что заголовок соответсвует пнг формату
        printf("probably, is not a png.\n");
        exit(43);
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        printf("error in png structure\n");
        exit(43);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("error in png info-structure\n");
        exit(43);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("image reading error.\n");
        exit(43);
    } 
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8); //устанавливает количество байт
    png_read_info(image->png_ptr, image->info_ptr); //считывает ширину, высоту, информацию о цвете
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr,image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height); //выделение памяти для массива указателей
    for (y = 0; y < image->height; y++){
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr,image->info_ptr)); //для каждой строки выделяет память
    }
    png_read_image(image->png_ptr, image->row_pointers); //считывает картинку
    fclose(fp);
}

void set_pixel(Png* image, int x, int y, int* color){
    if(x >= 0 && y >= 0 && x < image -> width && y < image -> height){
        png_byte *row = image->row_pointers[y];
        png_byte *ptr = &(row[x * 3]);
        ptr[0] = color[0];  
        ptr[1] = color[1];  
        ptr[2] = color[2];
    }
}

void outside_rect(Png* image, int* x, int* y, int* color){
    for(int i = 0; i < image -> width; i++){
        for(int j = 0; j < image -> height; j++){
            if((i < x[0] || j < y[0] || i > x[1] || j > y[1])){
                set_pixel(image, i, j, color);
            }
        }
    }
}

void draw_circle(Png* image, int x, int y, int thicknes, int* color){
    int r = thicknes / 2;
    for(int i = x - r; i < x + r; i++){
        for(int j = y - r; j < y + r; j++){
            if((x - i) * (x - i) + (y - j) * (y - j) <= r * r){
                set_pixel(image, i, j, color);
            }
        }
    }
}

void draw_line(Png* image, int x1,  int y1, int x2, int y2, int thicknes, int* color){
    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int error = deltax - deltay;
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int x_i = x1;
    int y_i = y1;
    if(thicknes != 1){
        draw_circle(image, x2, y2, thicknes, color);
    }
    else{
        set_pixel(image, x2, y2, color);
        }
    while(x_i != x2|| y_i != y2){
        if(thicknes != 1){
            draw_circle(image, x_i, y_i, thicknes, color);
        }
        else{
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

void check_triangle(int x1, int y1, int x2, int y2, int x3, int y3){
    if(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) + sqrt((x1-x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) <= sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))){
        printf("It is impossible to draw a triangle.\n");
        exit(40);
    }
}

double triangle_area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return 0.5 * abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
}

int is_inside_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){
    double A = triangle_area(x1, y1, x2, y2, x, y);
    double B = triangle_area(x2, y2, x3, y3, x, y);
    double C = triangle_area(x3, y3, x1, y1, x, y);
    return (A + B + C) == triangle_area(x1, y1, x2, y2, x3, y3);
}

void draw_triangle(Png* image, int* x, int* y, int thicknes, int* color, int fill, int* fill_color){
    check_triangle(x[0], y[0], x[1], y[1], x[2], y[2]);
    check_triangle(x[1], y[1], x[2], y[2], x[0], y[0]);
    check_triangle(x[2], y[2], x[0], y[0], x[1], y[1]);
    if(fill){
        int maxX = MAX(x[0], MAX(x[1], x[2]));
        int maxY = MAX(y[0], MAX(y[1], y[2]));
        int minX = MIN(x[0], MIN(x[1], x[2]));
        int minY = MIN(y[0], MIN(y[1], y[2]));
        for (int y_i = minY; y_i <= maxY; y_i++){
            for (int x_i = minX; x_i <= maxX; x_i++){
                if(is_inside_triangle(x[0], y[0], x[1], y[1], x[2], y[2], x_i, y_i)){
                    set_pixel(image, x_i, y_i, fill_color);
                }
            }
        }
    }
    draw_line(image, x[0], y[0], x[1], y[1], thicknes, color);
    draw_line(image, x[1], y[1], x[2], y[2], thicknes, color);
    draw_line(image, x[2], y[2], x[0], y[0], thicknes, color);
}

int color_comparison(Png* image, int x, int y, int* old_color){
    png_byte *row = image->row_pointers[y];
    png_byte *ptr = &(row[x * 3]);
    if(ptr[0] == old_color[0] && ptr[1] == old_color[1] && ptr[2] == old_color[2]){
        return 1;
    }
    else{
        return 0;
    }
}


void biggest_rect(Png* image, int* old_color, int* new_color){
    int max_area= 0;
    int coordinates[4];
    for(int i = 0; i < image -> width; i++){
        for(int j = 0; j < image -> height; j++){
            if(color_comparison(image, i, j, old_color)){
                int x = i;
                int y = j;
                while(x < image -> width && color_comparison(image, x, y, old_color) == 1){
                    x++;
                    while(y < image -> height && color_comparison(image, x, y, old_color) == 1){
                        y++;
                        if((x - i) * (y - j) > max_area){
                            max_area = (x - i) * (y - j);
                            coordinates[0] = i;
                            coordinates[1] = j;
                            coordinates[2] = x;
                            coordinates[3] = y;
                        }
                    }
                    y = j;
                }
            }
        }
    }
    if(!(coordinates[0] > image -> width || coordinates[0] < 0)){
        for(int k = coordinates[0]; k <= coordinates[2]; k++){
            for(int l = coordinates[1]; l <= coordinates[3]; l++){
                set_pixel(image, k, l, new_color);
            }
        }
    }
}


void copy_img(Png* new_image, Png* old_image, int x_0, int y_0, int x_1, int y_1, int x_i, int y_i){
    int color[3];
    for(int i = x_0; i < x_1; i++){
        for(int j = y_0; j < y_1; j++){
            png_byte *row = old_image->row_pointers[j - old_image -> height * y_i];
            png_byte *ptr = &(row[(i - old_image -> width * x_i) * 3]);
            color[0] = ptr[0];
            color[1] = ptr[1];
            color[2] = ptr[2];
            set_pixel(new_image, i, j, color);
        }
    }
}

void collage_img(Png *new_image, Png *old_image, int x, int y){
    new_image -> width = old_image -> width * x;
    new_image -> height = old_image -> height * y;
    new_image -> color_type = old_image -> color_type;
    new_image -> bit_depth = old_image -> bit_depth;
    new_image -> number_of_passes = old_image -> number_of_passes;
    new_image -> png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!new_image->png_ptr){
        printf("error in png structure\n");
        exit(43);
    }
    new_image->info_ptr = png_create_info_struct(new_image->png_ptr);
    if (!new_image->info_ptr){
        printf("error in png info-structure\n");
        exit(43);
    }
    png_read_update_info(new_image->png_ptr, new_image->info_ptr);
    new_image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * new_image->height); //выделение памяти для массива указателей
    for (int i = 0; i < new_image->height; i++){
        new_image->row_pointers[i] = (png_byte*)malloc((png_get_rowbytes(old_image->png_ptr, old_image->info_ptr) / old_image -> width) * new_image -> width); //для каждой строки выделяет память
    }
    for(int x_i = 0; x_i < x; x_i++){
        for(int y_i = 0; y_i < y; y_i++){
            copy_img(new_image, old_image, x_i * old_image -> width, y_i * old_image -> height, (x_i + 1) * old_image -> width, (y_i + 1) * old_image -> height, x_i, y_i);
        }
    }
}

void inf(Png* image){
    printf("width - %d.\n", image -> width);
    printf("height - %d.\n", image -> height);
    printf("color type - %u.\n", image -> color_type);
    printf("bit_depth - %u.\n", image -> bit_depth);
}

void write_png_file(char *file_name, Png *image) {
    int y;
    FILE *fp = fopen(file_name, "wb");
    if(!fp){
        printf("The file could not be opened.\n");
        exit(43);
    }
    image -> png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!image -> png_ptr){
        printf("Failed to create a structure.\n");
        exit(43);
    }
    image -> info_ptr = png_create_info_struct(image -> png_ptr);
    if (!image -> info_ptr){
        printf("Failed to create a structure.\n");
        exit(43);
    }
    if(setjmp(png_jmpbuf(image->png_ptr))){

    }
    png_init_io(image->png_ptr, fp);
    if(setjmp(png_jmpbuf(image->png_ptr))){
       printf("image recording error.\n");
       exit(43);
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE); //устанавливается заголовок
    png_write_info(image->png_ptr, image->info_ptr); //записывается заголовок
    if(setjmp(png_jmpbuf(image->png_ptr))){
       printf("image recording error.\n");
       exit(43);
    }
    png_write_image(image->png_ptr, image->row_pointers); //записываются данные изображения
    if(setjmp(png_jmpbuf(image->png_ptr))){
       printf("image recording error.\n");
       exit(43);
    }
    png_write_end(image->png_ptr, NULL);
    for (y = 0; y < image->height; y++){
        free(image->row_pointers[y]);
    }
    free(image->row_pointers);
    fclose(fp);
}

int is_digit(char* token){
    int flag = 1;
    for(size_t i = 0; i < strlen(token); i++){
        if(!isdigit(token[i])){
            if(i == 0 && token[i] == '-'){
                continue;
            }
            flag = 0;
        }
    }
    if(flag){
        return (int)strtol(token, NULL, 10);
    }
    else{
        printf("The argument must be int.\n");
        exit(40);
    }
}

int* input_rgb(char* optarg){
    int* color = malloc(3 * sizeof(int));
    char* token = strtok(optarg, ".");
    int j = 0;
    while (token != NULL){
        if(j == 3){
            printf("There are too many arguments.\n");
            exit(40);
        }
        color[j] = is_digit(token);
        token = strtok(NULL, ".");
        j++;
    }
    if(j != 3){
        printf("An incorrectly specified argument, the argument should look like rrr.ggg.bbb.\n");
        exit(40);
    }
    if(color[0] < 0 || color[1] < 0 || color[2] < 0 || color[0] > 255 || color[1] > 255 || color[2] > 255){
        printf("The color is set by a number from 0 to 255.\n");
        exit(40);
    }
    return color;
}

int main(int argc, char *argv[]){
    puts("Course work for option 4.19, created by Dmitrii Bayandin");
    int flags;
    int i;
    char* token_K;
    char* token_V;
    char* token_Z;
    char* name_img;
    int* result_old_color;
    int* result_new_color;
    int* result_color;
    int first_flag;
    int input_flag = 1;
    int summ_triangle = 0;
    int summ_biggest_rect = 0;
    int summ_collage = 0;
    int fill_flag = 0;
    char* out_name = malloc(sizeof(char)*8);
    strcpy(out_name, "out.png");
    triangles triangle;
    big_color colors;
    collages collage;
    outsides outside;
    int option_index = 0;
    triangle.fill = 0;
    struct option long_options[] = {
        {"triangle", no_argument, 0, 't'},
        {"points", required_argument, 0, 'P'},
        {"thickness", required_argument, 0, 'K'},
        {"color", required_argument, 0, 'L'},
        {"fill", no_argument, 0, 'F'},
        {"fill_color", required_argument, 0, 'R'},
        {"biggest_rect", no_argument, 0, 'b'},
        {"old_color", required_argument, 0, 'D'},
        {"new_color", required_argument, 0, 'N'},
        {"collage", no_argument, 0, 'c'},
        {"number_y", required_argument, 0, 'M'},
        {"number_x", required_argument, 0, 'X'},
        {"outside_rect", no_argument, 0, 'Q'},
        {"left_up", required_argument, 0, 'V'},
        {"right_down", required_argument, 0, 'Z'},
        {"help", no_argument, 0, 'h'},
        {"info", no_argument, 0, 'T'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };
    while((flags = getopt_long(argc, argv, "tbcThQFi:o:P:K:L:R:D:N:M:X:V:Z:", long_options, &option_index)) != -1){
        switch (flags)
            {
            case 'P':
                token_K = strtok(optarg, ".");
                i = 0;
                while (token_K != NULL){
                    if(i == 3){
                        printf("There are too many arguments.\n");
                        exit(40);
                    }
                    triangle.x[i] = is_digit(token_K);
                    token_K = strtok(NULL, ".");
                    if(token_K == NULL){
                        printf("An incorrectly specified argument, the argument should look like x1.y1.x2.y2.x3.y3.\n");
                        exit(40);
                    }
                    triangle.y[i] = is_digit(token_K);
                    token_K = strtok(NULL, ".");
                    i++;
                }
                if(i != 3){
                    printf("An incorrectly specified argument, the argument should look like x1.y1.x2.y2.x3.y3.\n");
                    exit(40);
                }
                summ_triangle++;
                break;
            case 'K':
                triangle.thickness = is_digit(optarg);
                if(triangle.thickness <= 0){
                    printf("The line thickness must be greater than 0.\n");
                    exit(40);
                }
                summ_triangle++;
                break;
            case 'L':
                result_color = input_rgb(optarg);
                memcpy(triangle.color, result_color, sizeof(int) * 3);
                memcpy(outside.color, result_color, sizeof(int) * 3);
                free(result_color);
                summ_triangle++;
                break;
            case 'F':
                triangle.fill = 1;
                break;
            case 'R':
                fill_flag = 1;
                int* result_fill_color = input_rgb(optarg);
                memcpy(triangle.fill_color, result_fill_color, sizeof(int) * 3);
                free(result_fill_color);
                break;
            case 'i':
                input_flag = 0;
                name_img = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(name_img, optarg);
                break;
            case 'o':
                out_name = realloc(out_name, sizeof(char)*(strlen(optarg)+1));
                strcpy(out_name, optarg);
                break;
            case 'D':
                result_old_color = input_rgb(optarg);
                memcpy(colors.old_color, result_old_color, sizeof(int) * 3);
                free(result_old_color);
                summ_biggest_rect++;
                break;
            case 'N':
                result_new_color = input_rgb(optarg);
                memcpy(colors.new_color, result_new_color, sizeof(int) * 3);
                free(result_new_color);
                summ_biggest_rect++;
                break;
            case 'M':
                collage.number_y = is_digit(optarg);
                if(collage.number_y <= 0){
                    printf("The number must be greater than 0.\n");
                    exit(40);
                }
                summ_collage++;
                break;
            case 'X':
                collage.number_x = is_digit(optarg);
                if(collage.number_x <= 0){
                    printf("The number must be greater than 0.\n");
                    exit(40);
                }
                summ_collage++;
                break;
            case 'V':
                token_V = strtok(optarg, ".");
                outside.x[0] = is_digit(token_V);
                token_V = strtok(NULL, ".");
                outside.y[0] = is_digit(token_V);
                break;
            case 'Z':
                token_Z = strtok(optarg, ".");
                outside.x[1] = is_digit(token_Z);
                token_Z = strtok(NULL, ".");
                outside.y[1] = is_digit(token_Z);
                break;
            case 't':
                first_flag = 't';
                break;
            case 'b':
                first_flag = 'b';
                break;
            case 'c':
                first_flag = 'c';
                break;
            case 'T':
                first_flag = 'T';
                break;
            case 'h':
                puts("error 40 - incorrect arguments");
                puts("error 41 - incorrect flags");
                puts("error 42 - incorrect file");
                puts("error 43 - the problem of working with images");
                puts("The program can perform 3 actions: draw a triangle, find and repaint the largest rectangle of a given color, create a collage of N into M parts.");
                puts("");
                puts("The triangle drawing function accepts the following arguments for drawing: the coordinates of the three vertices of the triangle, the thickness of the line, the color of the line, whether to paint the triangle and what color.");
                puts("");
                puts("--triangle --points x1.y1.x2.y2.x3.y3 -thickness x --color rrr.ggg.bbb --fill --fill_color rrr.ggg.bbb");
                puts("");
                puts("The function of finding the maximum rectangle of a given color and repainting it in a different color takes the following arguments: the old color of the rectangle and the new color of the rectangle.");
                puts("");
                puts("--biggest_rect --old_color rrr.ggg.bbb --old_color rrr.ggg.bbb");
                puts("");
                puts("The collage function accepts the following arguments: the number of images on the Y axis and on the X axis");
                puts("");
                puts("--collage --number_y x ----number_x x");
                exit(0);
                break;
            case 'Q':
                first_flag = 'Q';
                break;
            default:
                printf("Invalid flag.\n");
                exit(41);
                break;
            }
    }
    if(input_flag){
        int extra_flag = 0;
        if(argv[optind] == NULL){
            printf("There was no name for the image.\n");
            exit(40);
        }
        name_img = malloc(sizeof(char)*(strlen(argv[optind])+1));
        strcpy(name_img, argv[optind]);
    }
    Png image;
    read_png_file(name_img, &image);
    switch (first_flag)
    {
    case 't':
        if(triangle.fill == 0 && fill_flag == 1){
            printf("The fill flag is not entered.\n");
            exit(41);
        }
        if(summ_triangle == 3){
            draw_triangle(&image, triangle.x, triangle.y, triangle.thickness, triangle.color, triangle.fill, triangle.fill_color);
            write_png_file(out_name, &image);
        }
        else{
            printf("The flag is missing.\n");
            exit(41);
        }
        break;
    case 'b':
        if(summ_biggest_rect == 2){
            biggest_rect(&image, colors.old_color, colors.new_color);
            write_png_file(out_name, &image);
        }
        else{
            printf("The flag is missing.\n");
            exit(41);           
        }
        break;
    case 'c':
        if(summ_collage == 2){
            Png image_collage;
            collage_img(&image_collage, &image, collage.number_x, collage.number_y);
            write_png_file(out_name, &image_collage);
        }
        else{
            printf("The flag is missing.\n");
            exit(41);           
        }
        break;
    case 'T':
        inf(&image);
        exit(0);
    case 'Q':
        outside_rect(&image, outside.x, outside.y, outside.color);
        write_png_file(out_name, &image);
        break;
    default:
        break;
    }
}
