#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//errors
void error_flag_rep(){
    fprintf(stderr, "<ERROR> FLAG REPETITION\n");
    exit(40);
}

void error_arg(){
    fprintf(stderr, "<ERROR> BAD ARGUMENT\n");
    exit(41);
}

void error_bad_flag(){
    fprintf(stderr, "<ERROR> BAD FLAG\n");
    exit(42);
}

void error_lack_of_flags(){
    fprintf(stderr, "<ERROR> NOT ENOUGH REQUIRED FLAGS\n");
    exit(43);
}

void error_invalid_format(){
    fprintf(stderr, "<ERROR> INVALID FORMAT\n");
    exit(44);
}

void error_no_memory(){
    fprintf(stderr, "<ERROR> NO MEMORY");
    exit(45);
}

void error_cant_read_file(){
    fprintf(stderr, "<ERROR> CAN'T READ FILE");
    exit(46);
}

// drawing
#pragma pack(push, 1)
typedef struct Header{
    unsigned char ID[2];
    unsigned int file_size;
    unsigned char unused[4];
    unsigned int pixel_offset;
    
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short color_panels;
    unsigned short bits_per_pixel;
    unsigned int comp;
    unsigned int data_size;
    unsigned int pwidth;
    unsigned int pheight;
    unsigned int color_count;
    unsigned int imp_colors_count;
}Header;

typedef struct rgb_t{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} rgb_t;

typedef struct BMPFile{
    Header header;
    rgb_t ** data; // double array y rows x
}BMPFile;
#pragma pack(pop)

int padding(int line){
    return (4 - (line % 4)) % 4;
}

void read_pixels(FILE * fp, BMPFile * image){
    int line_no_padding = sizeof(rgb_t)*image->header.width;
    int line_padding = padding(line_no_padding); // callculating bmp padding
    int line_length = line_no_padding + line_padding;
    /*
    x x x x x x x x <- line 2
    x x x x x x x x <- line 1
    */
    fseek(fp, image->header.pixel_offset, SEEK_SET); // moving pointer to a pixel data(array);
    image->data = (rgb_t **)malloc(image->header.height*sizeof(rgb_t *));
    for(int y = 0; y < image->header.height; y++){
        image->data[y] = (rgb_t *) malloc(line_length*sizeof(rgb_t));
        unsigned char line[line_length]; // reading pixel bytes
        if(image->data[y] == NULL){
            error_no_memory();
        }
        fread(line, 1, line_length, fp);
        for(int x = 0; x != line_no_padding; x+=3){ // pixel bytes to structure rgb_t
            image->data[y][x/3].b = line[x];
            image->data[y][x/3].g = line[x+1];
            image->data[y][x/3].r = line[x+2];
        }
    }
}

void free_image(BMPFile * image){
    for(int i = 0; i != image->header.height; i++){
        free(image->data[i]);
    }
    free(&image->header);
}

BMPFile * read_bmp(char * fname){
    FILE * fp = fopen(fname, "rb");
    if(fp == NULL){
        error_cant_read_file();
    }
    BMPFile * image = (BMPFile *)malloc(sizeof(BMPFile)); // memort for headers
    fread(&image->header, sizeof(Header), 1, fp); // read header
    if ((image->header.ID[0] != 'B' || image->header.ID[1] != 'M')|| image->header.comp != 0 
    || image->header.bits_per_pixel != 24 || image->header.color_panels != 1)
    {
        fclose(fp);
        error_invalid_format();
    }
    read_pixels(fp, image);
    fclose(fp);
    return image;
}

void write_bmp(char * fname, BMPFile * image){
    FILE *ff = fopen(fname, "wb"); 
    if (ff == NULL) {
        error_cant_read_file();
    }
    fwrite(&image->header, 1, sizeof(Header), ff);
    fseek(ff, image->header.pixel_offset, SEEK_SET);
    int line_no_padding = sizeof(rgb_t)*image->header.width;
    int line_padding = padding(line_no_padding); // callculating bmp padding
    int line_length = line_no_padding + line_padding;
    for(size_t i = 0; i < image->header.height; i++){ 
        fwrite(image->data[i], 1, line_length, ff); 
    } 
    fclose(ff);
    free_image(image);
}

void draw_pixel(int x, int y, rgb_t col, BMPFile * image){
    if((0 <= y && y < image->header.height) && (0 <= x && x < image->header.width)){
        image->data[y][x] = col;
        }

}

void draw_circle(int x, int y, int thickness, rgb_t col, BMPFile * img){
    int radius = thickness/2;
    if(radius < 0 && thickness != 0){
        radius = 1;
    }
    for(int i = x-radius; i <= x+radius; i++){
        for(int j = y-radius; j <= y+radius; j++){
            if((x-i)*(x-i) + (y-j)*(y-j) < radius*radius){
                draw_pixel(i, j, col, img);
            }
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, int thickness, rgb_t col, BMPFile *image) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        if((x0 > 0 && x0 < image->header.width)&&(y0 > 0 && y0 < image->header.height) )
        draw_circle(x0, y0, thickness, col, image);
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    if((x0 > 0 && x0 < image->header.width)&&(y0 > 0 && y0 < image->header.height) )
    draw_circle(x1, y1, thickness, col, image);
}

int max(int * m, int size){ 
    int maxi = m[0];
    for(int i = 0; i!=size; i++){
        if(maxi < m[i]){
            maxi = m[i];
        }
    }
    return maxi;
}
int min(int * m, int size){
    int mini = m[0];
    for(int i = 0; i!=size; i++){
        if(mini > m[i]){
            mini = m[i];
        }
    }
    return mini;
}
int triangle_square(int x0, int x1, int x2, int y0, int y1, int y2){
   return 0.5 * abs((x1-x0)*(y2-y0) - (x2-x0)*(y1-y0));
}
int is_in_triangle(int i, int j, int * x, int * y, int s){
    int s1 = triangle_square(i, x[1], x[2], j, y[1], y[2]);
    int s2 = triangle_square(x[0], i, x[2], y[0], j, y[2]);  
    int s3 = triangle_square(x[0], x[1], i, y[0], y[1], j);
    return abs(s1+s2+s3-s) < 2;
}
void draw_triangle(int * points, int thick, int * col, int fill, int * fill_col, char * input, char * output){
    BMPFile * image = read_bmp(input);
    rgb_t color;
    color.r = col[0]; color.g = col[1]; color.b = col[2];
    int x[3] = {points[0], points[2], points[4]};
    int y[3] = {image->header.height-points[1], image->header.height-points[3], image->header.height-points[5]};
    if(fill){
        int s = triangle_square(x[0], x[1], x[2], y[0], y[1], y[2]);
        int min_x = min(x, 3); int max_x = max(x, 3);
        int min_y = min(y, 3); int max_y = max(y, 3);
        rgb_t fill_color;
        fill_color.r = fill_col[0]; fill_color.g = fill_col[1]; fill_color.b = fill_col[2]; 
        for(int i=min_x; i!=max_x; i++){
            for(int j=min_y; j!=max_y; j++){
                if(is_in_triangle(i, j, x, y, s)){
                    draw_pixel(i, j, fill_color, image);
            }}
        }
    }
    draw_line(x[0], y[0], x[1], y[1], thick, color, image);
    draw_line(x[1], y[1], x[2], y[2], thick, color, image);
    draw_line(x[2], y[2], x[0], y[0], thick, color, image);
    write_bmp(output, image);
}
int compare_color(int y, int x, int * color, BMPFile * image){
    return (image->data[y][x].r == color[0])&&(image->data[y][x].g == color[1])&&(image->data[y][x].b == color[2]);
}

void big_rect(int * old_color, int * new_color, char * input, char * output){
    BMPFile * image = read_bmp(input);
    int max_area = 0;
    int * biggest_rect = (int *)calloc(0, sizeof(int)*4);
    for(int y = 0; y < image->header.height; y++){
        for(int x = 0; x < image->header.width; x++){
            if(compare_color(y, x, old_color, image)){
            int min_width = image->header.width;
            for(int i = y;(i < image->header.height)&&compare_color(i, x, old_color, image); i++){
                
                int rec_width = 0;
                for(int j = x;((j < image->header.width)&&compare_color(i, j, old_color, image)); j++){
                    rec_width = j;
                    int rect_area = (x-j+1)*(y-i+1);
                    if(rec_width > min_width){
                        rect_area = (x - min_width + 1)*(y - i + 1);
                    }
                    
                    if(rect_area > max_area){
                        max_area = rect_area;
                        biggest_rect[0] = y; biggest_rect[1] = i; biggest_rect[2] = x; biggest_rect[3] = j;
                    }
                }
                if(rec_width < min_width){
                    min_width = rec_width;
                }
            }
            }
        }
    }
    rgb_t color;
    color.r = new_color[0]; color.g = new_color[1]; color.b = new_color[2];
    for(int y = biggest_rect[0]; y <= biggest_rect[1]; y++){
        for(int x = biggest_rect[2]; x <= biggest_rect[3]; x++){
            draw_pixel(x, y, color, image);
        }
    }
    write_bmp(output, image);
    free(biggest_rect);
}

void copy_image(int y, int x, BMPFile * image, BMPFile * new_image){
    for(int i = 0; i != image->header.height; i++){
        for(int j = 0; j != image->header.width; j++){
            new_image->data[y+i][x+j] = image->data[i][j];
        }
    }
}

void collage(int number_y, int number_x, char * input, char * output){
    if(number_x < 0 || number_y < 0)
        error_invalid_format();
    BMPFile * image = read_bmp(input);
    BMPFile * new_image = (BMPFile *)malloc(sizeof(BMPFile));
    memcpy(&new_image->header, &image->header, sizeof(Header));
    new_image->header.height = image->header.height*number_y;
    new_image->header.width = image->header.width*number_x;
    new_image->data = (rgb_t **)malloc(new_image->header.height*sizeof(rgb_t *));
    for(int i = 0; i != new_image->header.height; i++){
        new_image->data[i] = (rgb_t *)malloc(new_image->header.width*sizeof(rgb_t));
    }
    for(int y = 0; y != number_y; y++){
        for(int x = 0; x != number_x; x++){
            copy_image(y*image->header.height, x*image->header.width, image, new_image);
        }
    }
    write_bmp(output, new_image);
    free_image(image);
}

void circle_pixel(int * color_int, int * circle_color_int, int size, char * input, char * output){
    BMPFile * image = read_bmp(input);
    rgb_t circle_color;
    circle_color.r = circle_color_int[0]; circle_color.g = circle_color_int[1]; circle_color.b = circle_color_int[2];
    for(int y = 0; y!= image->header.height; y++){
        for(int x = 0; x != image->header.width; x++){
            if(compare_color(y, x, color_int, image)){
                for(int i = y-size; i != y+size; i++){
                    for(int j = x-size; j != x+size; j++){
                        if(j != x && i != y){
                            if(((0 <= i && i < image->header.height) && (0 <= j && j < image->header.width))&&!compare_color(i, j, color_int, image)){
                                draw_pixel(j, i, circle_color, image);
                                }
                        }
                    }
                }
            }
        }
    }
    write_bmp(output, image);
}

// flags
struct option long_opts[]={

        {"help", no_argument, NULL, 'h'},
        
        {"triangle", no_argument, NULL, 'T'},
        {"points", required_argument, NULL, 'p'},
        {"thickness", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
        {"fill", no_argument, NULL, 'f'},
        {"fill_color", required_argument, NULL, 'F'},
        
        {"biggest_rect", no_argument, NULL, 'B'},
        {"old_color", required_argument, NULL, 'O'},
        {"new_color",required_argument, NULL, 'n'},
        
        {"collage", no_argument, NULL, 'C'},
        {"number_y", required_argument, NULL, 'y'},
        {"number_x", required_argument, NULL, 'x'},

        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},

        {"info", no_argument, NULL, 'I'},

        {"circle_pixel", no_argument, NULL, 'P'},
        {"circle_color", required_argument, NULL, 'l'},
        {"size", required_argument, NULL, 's'},

        {NULL, 0, NULL, 0}

    };

void alpha_str_check(char * str){
    for(int i = 0; i != strlen(str); i++){
        if(!isdigit(str[i])){
            if((strlen(str)!=1 && i == 0)&&(str[i])=='-')
                continue;
            error_arg();
        }}
}
int * dots(char * str, int req_size) { // работает если точка на конце
    int size = 0;
    int * ints = (int *)malloc(sizeof(int) * 10);
    char *sep_str;
    if(strstr(str, "..") != NULL)
        error_arg();
    sep_str = strtok(str, ".");
    while (sep_str != NULL) {
        alpha_str_check(sep_str);
        ints[size] = strtol(sep_str, NULL, 10);
        size++;
        sep_str = strtok(NULL, ".");
    }
    if(size != req_size){
        error_arg();
    }
    return ints;
}

void info(BMPFile* image){
    printf("Width: %d\n", image->header.width);
    printf("Height: %d\n", image->header.height);
    printf("Color panels: %u\n", image->header.color_panels);
    printf("Bits per pixel: %u\n", image->header.bits_per_pixel);
}

void print_help(){
    puts(
            "Error 40 - FLAG REPETITION\n"
            "Error 41 - BAD ARGUMENT\n"
            "Error 42 - BAD FLAG\n"
            "Error 43 - NOT ENOUGH REQUIRED FLAGSa\n"
            "Error 44 - INVALID FORMAT\n"
            "Error 45 - NO MEMORY\n"
            "Error 46 - CAN'T READ FILE\n\n"
            "The program can perform 3 actions: draw a triangle, find and repaint the largest rectangle of a given color, create a collage of N into M parts.\n"
            "The triangle drawing function accepts the following arguments for drawing: the coordinates of the three vertices of the triangle, the thickness of the line, the color of the line, whether to paint the triangle and what color.\n"
            "--triangle --points x1.y1.x2.y2.x3.y3 -thickness x --color rrr.ggg.bbb --fill --fill_color rrr.ggg.bbb\n"
            "The function of finding the maximum rectangle of a given color and repainting it in a different color takes the following arguments: the old color of the rectangle and the new color of the rectangle.\n"
            "--biggest_rect --old_color rrr.ggg.bbb --old_color rrr.ggg.bbb\n"
            "The collage function accepts the following arguments: the number of images on the Y axis and on the X axis\n"
            "--collage --number_y x ----number_x x\n");
}


void flags(int argc, char ** argv){
    char short_opts_string[] = "hTBCp:t:c:fF:i:o:O:n:i:o:y:x:i:o:IPl:s:";
    int opt;

    int f_triangle = 0; int f_big_rect = 0; int f_collage = 0;
    int * points; int thickness; int * color; int fill = 0; int * fill_color = NULL;
    int * old_color; int * new_color;
    int number_y; int number_x;
    char * input = (char *)malloc(100); char * output = (char *)malloc(100);
    strcpy(output, "out.bmp");
    
    char * opts = (char *)malloc(10);
    int triangle_flags_req = 0; int triangle_flags_not_req = 0; int big_rect_flags = 0; int collage_flags = 0;
    int output_flag = 0; int input_flag = 0;

    int info_flag = 0;

    int circle_pixel_flag = 0; int * circle_color = 0; int circle_pixel_flags = 0; int size = 0;

    for(int i = 0; (opt =getopt_long(argc, argv, short_opts_string, long_opts, 0))!=-1; i++){
        if(opt == '?' || opt == ':'){
            error_bad_flag();
        }
        else if(opt == 'h'){
            print_help();
            return;
        }
        else if (strchr(opts, opt) != NULL)
            error_flag_rep();  
        //main flags
        else if(opt == 'T'){
            f_triangle++;
        }
        else if(opt == 'B'){
            f_big_rect++;
        }
        else if(opt == 'C'){
            f_collage++;
        }
        //triangle flags
        else if(opt == 'p'){
            points = dots(optarg, 6);
            triangle_flags_req++;
        }
        else if(opt == 't'){
            alpha_str_check(optarg);
            thickness = strtol(optarg, NULL, 10);
            triangle_flags_req++;
        }
        else if(opt == 'c'){
            color = dots(optarg, 3);
            triangle_flags_req++;
        }
        else if(opt == 'F'){ //АУЕ
                fill_color = dots(optarg, 3);
                triangle_flags_not_req++;
            }
        else if(opt == 'f'){
            fill = 1;
            triangle_flags_not_req++;
        }
        // big rect flags
        else if(opt == 'O'){
            old_color = dots(optarg, 3);
            big_rect_flags++;
        }
        else if(opt == 'n'){
            new_color = dots(optarg, 3);
            big_rect_flags++;
        }
        // collage flags
        else if(opt == 'y'){
            alpha_str_check(optarg);
            number_y = strtol(optarg, NULL, 10);
            collage_flags++;
        }
        else if(opt == 'x'){
            alpha_str_check(optarg);
            number_x = strtol(optarg, NULL, 10);
            collage_flags++;
        }
        // input output flags
        else if(opt == 'i'){
            strcpy(input, optarg);
            input_flag++;
        }
        else if(opt == 'o'){
            strcpy(output, optarg);
            output_flag++;
        }
        // info flag
        else if(opt == 'I'){
            info_flag = 1;
        }
        else if(opt == 'P'){
            circle_pixel_flag = 1;
        }
        else if(opt == 'l'){
            circle_color = dots(optarg, 3);
            circle_pixel_flags++;
        }
        else if(opt == 's'){
            alpha_str_check(optarg);
            size = strtol(optarg, NULL, 10);
            circle_pixel_flags++;
        }

        opts[i] = opt;
        opts[i+1] = '\0';

    }
    if(f_triangle+f_big_rect+f_collage+info_flag+circle_pixel_flag != 1 || !input_flag){
        error_bad_flag();
        }
    
    if(info_flag){
        if(!input_flag){
            error_lack_of_flags();
        }
        BMPFile * image = read_bmp(input);
        info(image);
        free_image(image);
    }
    
    else if(circle_pixel_flag){
        //printf("%d\n", circle_pixel_flags);
        if(triangle_flags_not_req + triangle_flags_req + big_rect_flags 
        + collage_flags + circle_pixel_flags != 3 || circle_pixel_flags != 2 || triangle_flags_req != 1){
                error_bad_flag();
        }
        circle_pixel(color, circle_color, size, input, output); 
    }

    else if(f_triangle){
        if(triangle_flags_req + big_rect_flags + collage_flags != 3 || triangle_flags_req != 3){    
            error_bad_flag();
            
            }
        draw_triangle(points, thickness, color, fill, fill_color, input, output);
    }
    else if(f_big_rect){
        if(triangle_flags_not_req + triangle_flags_req + big_rect_flags + collage_flags != 2 || big_rect_flags != 2)
            error_bad_flag();
        big_rect(old_color, new_color, input, output);
    }
    else if(f_collage){
        if(triangle_flags_not_req + triangle_flags_req + big_rect_flags + collage_flags != 2 || collage_flags != 2){
            printf("%d\n", collage_flags);
            error_bad_flag();
            }
        collage(number_y, number_x, input, output);
    }
}


int main(int argc, char **argv) {
    puts("Course work for option 4.7, created by Vadim Pozdeev.");
    flags(argc, argv);
        
    return 0;
}

