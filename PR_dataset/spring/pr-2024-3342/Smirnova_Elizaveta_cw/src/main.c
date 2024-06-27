#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <getopt.h>
#include <png.h>

struct Png {
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep* row_pointers;
};


void read_png_file(char* file_name, struct Png* image) {
    int y;
    unsigned char header[8];

    FILE* fp = fopen(file_name, "rb");
    if (!fp) {
        printf("Ошибка: не удалось открыть файл для чтения. Введите название файла с расширением '.png'\n");
        exit(40);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        printf("Ошибка: формат изображения не PNG.\n");
        exit(41);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        printf("Ошибка: не удалось создать структуру изображения.\n");
        exit(41);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        printf("Ошибка: не удалось создать структуру с информацией об изображении.\n");
        exit(41);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка инициализации.\n");
        exit(41);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка чтения изображения.\n");
        exit(41);
    }

    image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
    if (image->row_pointers == NULL) {
        printf("Ошибка выделения памяти.\n");
        exit(41);
    }
    for (y = 0; y < image->height; y++){
    
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
        if (image->row_pointers[y] == NULL){
            printf("Ошибка выделения памяти.\n");
            exit(41);
        }
    }
    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}


void write_png_file(char* file_name, struct Png* image) {
    int y;
    
    FILE* fp = fopen(file_name, "wb");
    if (!fp) {
        printf("Ошибка при создании файла итогового изображения.\n");
        exit(42);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) {
        printf("Ошибка при создании структуры итогового изображения.\n");
        exit(42);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        printf("Ошибка при создании структуры с информацией об итоговом изображении.\n");
        exit(42);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка инициализации\n");
        exit(42);
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка записи заголовка итогового файла.\n");
        exit(42);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
        image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка записи данных итогового файла.\n");
        exit(42);
    }

    png_write_image(image->png_ptr, image->row_pointers);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        printf("Ошибка при окончании записи итогового файла.\n");
        exit(42);
    }

    png_write_end(image->png_ptr, NULL);

    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}

void set_pixel(struct Png* image, int x, int y, int* color) {
    if (!(x >= image->width || y >= image->height || x < 0 || y < 0)){
        png_byte *row = image->row_pointers[y];
        png_byte *ptr = &(row[x * 3]);

        ptr[0]=color[0];
        ptr[1]=color[1];
        ptr[2]=color[2];
    }
}

void plot_circle(struct Png* image, int xm, int ym, float thickness, int* color){
    int x0 = xm - thickness/2, x1 = xm + thickness/2, y0 = ym - thickness/2, y1 = ym + thickness/2;

    for (int x = x0; x <= x1; x++){
        for (int y = y0; y <= y1; y++){
            if ((x-xm)*(x-xm) + (y-ym)*(y-ym) <= (thickness/2)*(thickness/2)){
                if (!(x >= image->width || y >= image->height || x < 0 || y < 0))
                    set_pixel(image, x, y, color);
            }
        }
    }
}

void fill_part(struct Png* image, int x, int x0, int x1, int y, bool fill, int* fill_color){
    int dx = x1 - x;
    int dx0 = x0 + 3 * (x1 - x0);

    for (int j = x; j <= x1; j++){
        if (fill && (j > x && j <= x1) ){
            set_pixel(image, j, y, fill_color);
        }
    }

    for (int j = dx0; j <= dx0 + dx; j++){
        if (fill && (j >= dx0 && j < dx0 + dx) ){
            set_pixel(image, j, y, fill_color);
        }
    }
	
}
void fill_rect(struct Png* image, int x0, int y0, int x1, int y1, bool fill, int* fill_color){

    for (int i = y0; i <= y1; i++){
		for (int j = x0; j <= x1; j++){
            if (fill && (j >= x0 && j <= x1) && (i >= y0 && i <= y1)) {
                set_pixel(image, j, i, fill_color);
            }
		}
	}
}

void draw_line1(struct Png* image, int x0, int y0, int x1, int y1, float r, float thickness, int* color, bool fill, int* fill_color) {//
    int dx = abs(x1 - x0), dy = (abs(y1 - y0));
    int d = 2 * dx - dy;
    int incrE = 2 * dx;
    int incrNE = 2 * (dx - dy);
    int x = x0, y = y0;
    
    while (y <= y1) {
        fill_part(image, x, x0, x1, y, fill, fill_color);
        set_pixel(image, x, y, color);
        if (d <= 0){
            d += incrE;
            y++;
        }
        else{
            d += incrNE;
            x++;
            y++;
        }
    }
    for (x = x0 - (thickness*sqrt(3)/4); x <= x0 + thickness*sqrt(3)/4; x++){
        draw_line1(image, x, y0 + thickness/4, x + r/2, y1 + thickness/4, 0, -1, color, false, fill_color);
    }
    for (x = x0; x <= x0 + (thickness*sqrt(3)/4); x++){
        draw_line1(image, x, y0 - thickness/4, x + r/2, y1 - thickness/4, 0, -1, color, false, fill_color);
    }
}

void draw_line2(struct Png* image, int x0, int y0, int x1, int y1, float thickness, int* color) {
    int dx = abs(x1 - x0), dy = (abs(y1 - y0));
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = x0, y = y0;
    
    while (x <= x1) {
        
        if (d <= 0){
            d += incrE;
            x++;
        }
        else{
            d += incrNE;
            x++;
            y++;
        }
    }
    for ( x = x0; x <= x1; x++){
        for (int y = y0 - thickness/2; y <= y0 + thickness/2; y++){
            set_pixel(image, x, y, color);
        }
    }
}

void draw_line3(struct Png* image, int x0, int y0, int x1, int y1, float r, float thickness, int* color, bool fill, int* fill_color) { //
    int dx = abs(x1 - x0), dy = (abs(y1 - y0));
    int d = 2 * dx - dy;
    int incrE = 2 * dx;
    int incrNE = 2 * (dx - dy);
    int x = x0, y = y0;
    
    while (y >= y1) {
        fill_part(image, x, x0, x1, y, fill, fill_color);
        set_pixel(image, x, y, color); 
        if (d <= 0){
            d += incrE;
            y--;
        }
        else{
            d += incrNE;
            y--;
            x++;
        }
    }
    for (x = x0 - (thickness*sqrt(3)/4); x <= x0 + thickness*sqrt(3)/4; x++){
        draw_line3(image, x, y0 - thickness/4, x + r/2, y1 -thickness/4, 0, -1, color, false, fill_color);
    }
    for (x = x0; x <= x0 + (thickness*sqrt(3)/4); x++){
        draw_line3(image, x, y0 + thickness/4, x + r/2, y1 + thickness/4, 0, -1, color, false, fill_color);
    }
}

void draw_rectangle(struct Png* image, int x0, int y0, int x1, int y1, float thickness, int* color, bool fill, int* fill_color) {
    if (thickness < 0 )  {
        printf("Введены некорретные данные: "
               "ширина линий не может иметь"
               " отрицательное значение\n");
        exit(45);
    }
    if (x0 >= x1){
        int tmpx = x0;
        x0 = x1;
        x1 = tmpx;
    }
    if (y0 >= y1){
        int tmpy = y0;
        y0 = y1;
        y1 = tmpy;
    }
    if (color[0] > 255 || color[0] < 0 || color[1] > 255 || color[1] < 0
    || color[2] > 255 || color[2] < 0 ) {
        printf("Введены некорретные данные: цвета должны лежать от 0 до 255\n");
        exit(45);
    }
    if ((fill_color[0] > 255 || fill_color[0] < 0 || fill_color[1] > 255 || fill_color[1] < 0 
        || fill_color[2] > 255 || fill_color[2] < 0 ) && (fill)){
        printf("Введены некорретные данные: цвета должны лежать от 0 до 255\n");
        exit(45);
    }
    
    int x2 = x1, y2 = y0, x3 = x0, y3 = y1;

    for (int i = y0; i <= y1; i++){
		for (int j = x0; j <= x1; j++){
            if (fill && (j >= x0 + thickness/2 && j <= x1 - thickness/2) && (i >= y0 + thickness/2 && i <= y1 - thickness/2)) {
                set_pixel(image, j, i, fill_color);
            }
		}
	}
    for ( int x = x0; x <= x2; x++){
        for (int y = y0 - thickness/2; y <= y0 + thickness/2; y++){
            set_pixel(image, x, y, color);
        }
    }
    for (int x = x3; x <= x1; x++){
        for (int y = y3 - thickness/2; y <= y3 + thickness/2; y++){
            set_pixel(image, x, y, color);
        }
    }
    for ( int x = x0 - thickness/2; x <= x0 + thickness/2; x++){
        for (int y = y0; y <= y3 ; y++){
            set_pixel(image, x, y, color);
        }
    }
    for (int x = x1 - thickness/2; x <= x1 + thickness/2; x++){
        for (int y = y2; y <= y1 ; y++){
            set_pixel(image, x, y, color);
        }
    }

    plot_circle(image, x0, y0, thickness, color);
    plot_circle(image, x1, y1, thickness, color);
    plot_circle(image, x2, y2, thickness, color);
    plot_circle(image, x3, y3, thickness, color);

}
void draw_hexagon(struct Png* image, int x0, int y0, float r, float thickness, int* color, bool fill, int* fill_color){

    if (x0 < 0 || y0 < 0 || r < 0 || thickness < 0 )  {
        printf("Введены некорретные данные: "
               "координаты, радиус и ширина линий "
               "не могут иметь отрицательные значения\n");
        exit(45);
    }
    if (x0 >= image->width || y0 >= image->height ) {
        printf("Введены некорретные данные: координаты должны "
               "находиться в пределах изображения\n");
        exit(45);
    }
    if (color[0] > 255 || color[0] < 0 || color[1] > 255 || color[1] < 0
    || color[2] > 255 || color[2] < 0 ) {
        printf("Введены некорретные данные: цвета должны лежать от 0 до 255\n");
        exit(45);
    }
    if ((fill_color[0] > 255 || fill_color[0] < 0 || fill_color[1] > 255 || fill_color[1] < 0 
        || fill_color[2] > 255 || fill_color[2] < 0 ) && (fill)){
        printf("Введены некорретные данные: цвета должны лежать от 0 до 255\n");
        exit(45);
    }

    int x1 = x0 + r, y1 = y0;
    int x2 = x0 + (r/2), y2 = y0 - (r * (sqrt(3))/2);
    int x3 = x0 - (r/2), y3 = y0 - (r * (sqrt(3))/2);
    int x4 = x0 - r, y4 = y0;
    int x5 = x0 - (r/2), y5 = y0 + (r * (sqrt(3))/2);
    int x6 = x0 + (r/2), y6 = y0 + (r * (sqrt(3))/2);

    fill_rect(image, x3, y3, x6, y6, fill, fill_color);

    draw_line2(image, x3, y3, x2, y2, thickness, color) ; 
    draw_line3(image, x4, y4, x3, y3, r, thickness, color, fill, fill_color) ; 
    draw_line1(image, x4, y4, x5, y5, r, thickness, color, fill, fill_color) ; 
    draw_line2(image, x5, y5, x6, y6, thickness, color) ; 
    draw_line3(image, x6, y6, x1, y1, r, thickness, color, false, fill_color) ; 
    draw_line1(image, x2, y2, x1, y1, r, thickness, color, false, fill_color) ;
    
    plot_circle(image, x1, y1, thickness, color); 
    plot_circle(image, x2, y2, thickness, color); 
    plot_circle(image, x3, y3, thickness, color); 
    plot_circle(image, x4, y4, thickness, color); 
    plot_circle(image, x5, y5, thickness, color); 
    plot_circle(image, x6, y6, thickness, color); 
}

void get_color(struct Png* image, int x, int y, int x0, int y0, int* color_pixel){
    
    png_byte *row = image->row_pointers[y];
    png_byte *ptr = &(row[x * 3]);
    color_pixel[0] = ptr[0];
    color_pixel[1] = ptr[1];
    color_pixel[2] = ptr[2];
    set_pixel(image, x0, y0, color_pixel);
}

void copy(struct Png* image, int x0, int y0, int x1, int y1, int x2, int y2){

    if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)  {
        printf("Введены некорретные данные: "
               "координаты, радиус и ширина линий "
               "не могут иметь отрицательные значения\n");
        exit(45);
    }
    if (x0 >= image->width || x1 >= image->width || y0 >= image->height || y1 >= image->height
    || x2 >= image->width || y2 >= image->height) {
        printf("Введены некорретные данные: координаты должны "
               "находиться в пределах изображения\n");
        exit(45);
    }
    if (x1 < x0 || y1 < y0 ) {
        printf("Введены некорретные данные: координаты верхнего левого угла "
               "должны быть меньше координат нижнего правого угла\n");
        exit(45);
    }

    int dx = x2 - x0, dy = y2 - y0;
    int color_pixel[3];
    
    if ((x2 <= x1) && (x2 >= x0) && (y2 <= y1) && (y2 >= y0)){
        for (int i = y1; i >= y0; i--){
            for (int j = x1; j >= x0; j--){
                get_color(image, j, i, j + dx, i + dy, color_pixel);
            }
        }
    }
    else {
        for (int i = y0; i <= y1; i++){
            for (int j = x0; j <= x1; j++){
                get_color(image, j, i, j + dx, i + dy, color_pixel);
            }
        }
    }

}

void bin(struct Png *image, int threshold){

    
    int sum_color = 0;
    for (int y = 0; y < image->height; y++){
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++){
            png_byte *ptr = &(row[x * 3]);
            sum_color = ptr[0] + ptr[1] + ptr[2];
            if (sum_color >= threshold){
                ptr[0] = (255, 255, 255);
                ptr[1] = (255, 255, 255);
                ptr[2] = (255, 255, 255);
            } 
            else{
                ptr[0] = (0, 0, 0);
                ptr[1] = (0, 0, 0);
                ptr[2] = (0, 0, 0);
            }
        }
    }
}


void print_png_info(struct Png *image){
    printf("Ширина изображения: %d\n", image->width);
    printf("Высота изображения: %d\n", image->height);
    printf("Тип цвета: %u\n", image->color_type);
    printf("Глубина цвета: %u\n", image->bit_depth);
}

void print_help(){
    printf("Course work for option 4.21, created by Smirnova Elizaveta.\n\n");
    printf("Флаги:\n\n");
    printf("--help : вызов функции помощи\n\n");
    printf("--info : вывод на экран информации о файле\n\n");
    printf("--input : ввод имени входного файла\n\n");
    printf("--output : ввод имени выходного файла\n\n");
    printf("--rect (--left_up --right_down --thickness --color --fill --fill_color) : рисование прямоугольника\n\n");
    printf("--hexagon (--center --radius --thickness --color --fill --fill_color) : рисование правильного шестиугольника\n\n");
    printf("--copy (--left_up --right_down --dest_left_up) : копирование заданной области\n\n");
}

int main(int argc, char* argv[]) {

    char* input_file = argv[argc - 1];
    char* output_file = "res.png";
    
    struct Png image;

    const char* short_opts = "hI:rs:f:t:q:Ff:HC:R:cS:o:i:bT:";
    const struct option long_opts[] ={
            {"help", no_argument, NULL, 'h'},
            {"info", required_argument,NULL, 'I'},
            {"rect", no_argument,NULL, 'r'},
            {"left_up", required_argument,NULL, 's'},
            {"right_down", required_argument,NULL, 'e'},
            {"thickness", required_argument, NULL, 't'},
            {"color", required_argument, NULL, 'q'},
            {"fill", no_argument, NULL, 'F'},
            {"fill_color", required_argument, NULL, 'f'},
            {"hexagon", no_argument, NULL, 'H'},
            {"center", required_argument, NULL, 'C'},
            {"radius", required_argument, NULL, 'R'},
            {"copy", no_argument, NULL, 'c'},
            {"dest_left_up", required_argument, NULL, 'S'},
            {"output", required_argument, NULL, 'o' },
            {"input", required_argument, NULL, 'i' },
            {"binarization", no_argument, NULL, 'b'},
            {"threshold", required_argument, NULL, 'T'},
    };

    int x0 = 0, y0 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, opt = -1, opt_number = -1, threshold = 0;
    float thickness = -1, radius = 0;
    int fill_color[3] = {0,0,0};
    int color[3] = {0,0,0};
    bool fill = false;
    

    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1){

        switch(opt){
            case 'h':
            {
                print_help();
                exit(0);
                break;
            }
            case 'I':
            {
                read_png_file(input_file, &image);
                print_png_info(&image);
                break;
            }
            case 'r':
            {
                opt_number = 1;
                break;
            }
            case 's':
            {
                sscanf(optarg, "%d.%d", &x0, &y0);
                break;
            }
            case 'e':
            {
                sscanf(optarg, "%d.%d", &x1, &y1);
                break;
            }
            case 't':
            {
                sscanf(optarg, "%f", &thickness);
                break;
            }
            case 'q':
            {
                sscanf(optarg, "%d.%d.%d", &color[0], &color[1], &color[2]);
                break;
            }
            case 'F':
            {
                fill = true;
                break;
            }
            case 'f':
            {
                sscanf(optarg, "%d.%d.%d", &fill_color[0], &fill_color[1], &fill_color[2]);
                break;
            }
            case 'H':
            {
                opt_number = 2;
                break;
            }
            case 'C':
            {
                sscanf(optarg, "%d.%d", &x0, &y0);
                break;
            }
            case 'R':
            {
                sscanf(optarg, "%f", &radius);
                break;
            }
            case 'c':
            {
                opt_number = 3;
                break;
            }
            case 'S':
            {
                sscanf(optarg, "%d.%d", &x2, &y2);
                break;
            }
            case 'o':
            {
                output_file = optarg;
                break;
            }
            case 'i':
            {
                input_file = optarg;
                break;
            }
            case 'T':
            {
                sscanf(optarg, "%d", &threshold);
                break;
            }
            case 'b':
            {
                opt_number = 4;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    read_png_file(input_file, &image);
    
    switch (opt_number)
    {
        case 1:
        {
            draw_rectangle(&image, x0, y0, x1, y1, thickness, color, fill, fill_color);
            break;
        }
        case 2:
        {
            draw_hexagon(&image, x0, y0, radius, thickness, color, fill, fill_color); 
            break;
        }
        case 3:
        {
            copy(&image, x0, y0, x1, y1, x2, y2);
            break;
        }
        case 4:
        {
            bin(&image, threshold);
            break;
        }
        default:
        {
            break;
        }
    }

    write_png_file(output_file, &image);
    return 0;
}
