#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <png.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define M_PI 3.14159265358979323846

typedef struct{
    int red;
    int green;
    int blue;
}Color;

typedef struct {
    int x;
    int y;
} Point;

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

void process_file(struct Png *png) {
    int x,y;
    if (png_get_color_type(png->png_ptr, png->info_ptr) !=PNG_COLOR_TYPE_RGBA){
        return;
    }
    for (y = 0; y < png->height; y++) {
        png_byte *row = png->row_pointers[y];
        for (x = 0; x < png->width; x++) {
            png_byte *ptr = &(row[x * 4]); 
            if (ptr[3] == 0){
                ptr[3] = 255;
            }
        }
    }
 // Изменение альфа канала

}

struct Png *read_png(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Не удалось открыть файл %s для чтения\n", filename);
        exit(41);
    }

    struct Png *png = malloc(sizeof(struct Png));
    if (!png) {
        fclose(fp);
        printf("Ошибка выделения памяти\n");
        exit(41);
    }

    png_byte header[8];

// Считываем первые 8 байт файла
    fread(header, 1, 8, fp);

// Проверяем, является ли файл PNG
    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        free(png);
        printf("Файл %s не является PNG изображением\n", filename);
        exit(41);
    }

// Создаем структуру png_struct для работы с PNG изображением
    png->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png->png_ptr) {
        fclose(fp);
        free(png);
        printf("Ошибка создания структуры png_struct\n");
        exit(41);
    }

    png->info_ptr = png_create_info_struct(png->png_ptr);
    if (!png->info_ptr) {
        fclose(fp);
        free(png);
        printf("Ошибка создания структуры png_info\n");
        exit(49);
    }

// Устанавливаем начало чтения файла
    png_init_io(png->png_ptr, fp);
    png_set_sig_bytes(png->png_ptr, 8); 

    png_read_info(png->png_ptr, png->info_ptr);
    png->width = png_get_image_width(png->png_ptr, png->info_ptr);
    png->height = png_get_image_height(png->png_ptr, png->info_ptr);
    png->color_type = png_get_color_type(png->png_ptr, png->info_ptr);
    png->bit_depth = png_get_bit_depth(png->png_ptr, png->info_ptr);


    png->number_of_passes = png_set_interlace_handling(png->png_ptr);
    png_read_update_info(png->png_ptr, png->info_ptr);


// Считываем строки изображения и сохраняем их
    png->row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * png->height);
    for (int y = 0; y < png->height; y++) {
        png->row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png->png_ptr, png->info_ptr));
    }

    png_read_image(png->png_ptr, png->row_pointers);

    fclose(fp);
    process_file(png);
    return png;
} 
void save_png(const char *filename, struct Png *png) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Ошибка открытия файла %s для записи\n", filename);
        exit(48);
    }
    

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        printf("Ошибка создания структуры png_struct для записи\n");
        exit(47);
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, NULL);
        printf("Ошибка создания структуры png_info для записи\n");
        exit(46);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        printf("Ошибка записи PNG изображения\n");
        exit(45);
    }

    png_init_io(png_ptr, fp);
    int color_type = PNG_COLOR_TYPE_RGB;
    if (png->color_type == PNG_COLOR_TYPE_RGBA) {
        color_type = PNG_COLOR_TYPE_RGBA;
    }

    png_set_IHDR(png_ptr, info_ptr, png->width, png->height, png->bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);
    

    png_write_image(png_ptr, png->row_pointers);

    png_write_end(png_ptr, NULL);

    fclose(fp);
}

void draw_line(struct Png *png, float start_x, float start_y, float end_x, float end_y, Color color, int thickness) { 
    // Вычисляем разницу между координатами начала и конца отрезка 
    float dx = end_x - start_x; 
    float dy = end_y - start_y; 
     
    // Вычисляем длину отрезка 
    float length = sqrt(dx * dx + dy * dy); 
     
    // Нормализуем вектор отрезка 
    float norm_dx = dx / length; 
    float norm_dy = dy / length; 
     
    // Половина толщины 
    float half_thickness = thickness / 2.0f; 
     
    // Цикл по длине отрезка 
    for (float i = 0; i < length; i += 0.5f) { 
        // Текущая точка на линии 
        float current_x = start_x + norm_dx * i; 
        float current_y = start_y + norm_dy * i; 
         
        // Вычисляем нормаль к линии 
        float normal_x = -norm_dy; 
        float normal_y = norm_dx; 
         
        png_byte red = color.red;
        png_byte green = color.green;
        png_byte blue = color.blue;


        // Цикл по толщине линии 
        for (float j = -half_thickness; j <= half_thickness; j += 0.5f) { 
            // Точка на границе линии 
            float border_x = current_x + normal_x * j; 
            float border_y = current_y + normal_y * j; 
             
            // Округляем координаты до целых 
            int px = (int)round(border_x); 
            int py = (int)round(border_y); 
             
            // Проверяем, находится ли точка в пределах изображения 
            if (px >= 0 && px < png->width && py >= 0 && py < png->height) { 
                // Устанавливаем цвет пикселя 
                if (png_get_color_type(png->png_ptr, png->info_ptr) !=PNG_COLOR_TYPE_RGBA){
                    png_byte *ptr = &(png->row_pointers[py][px * 3]); 

                    ptr[0] = red; 
                    ptr[1] = green; 
                    ptr[2] = blue; 

                }
                if (png_get_color_type(png->png_ptr, png->info_ptr) ==PNG_COLOR_TYPE_RGBA){
                    png_byte *ptr = &(png->row_pointers[py][px * 4]); 

                    ptr[0] = red; 
                    ptr[1] = green; 
                    ptr[2] = blue; 
                    ptr[3] = 255; 
                }

            } 
        } 
    } 
}

void mirror_region(struct Png *png, char axis, int left, int up, int right, int down) {
    int x, y;


    if (png_get_color_type(png->png_ptr, png->info_ptr) ==PNG_COLOR_TYPE_RGBA){
        png_byte temp[4];
                    

        if (left >= right || up >= down) {
            printf("Некорректно задана область для отражения\n");
            return;
        }
    
    // Отражение относительно горизонтальной оси
        if (axis == 'y') {
            for (y = up; y < (up + down) / 2; y++) {
                for (x = left; x < right; x++) {

                    memcpy(temp, &(png->row_pointers[y][x * 4]), 4);
                    memcpy(&(png->row_pointers[y][x * 4]), &(png->row_pointers[down - (y - up)][x * 4]), 4);
                    memcpy(&(png->row_pointers[down - (y - up)][x * 4]), temp, 4);
                }
            }
        }
    // Отражение относительно вертикальной оси
        else if (axis == 'x') {
            for (x = left; x < (left + right) / 2; x++) {
                for (y = up; y < down; y++) {
                    memcpy(temp, &(png->row_pointers[y][x * 4]), 4);
                    memcpy(&(png->row_pointers[y][x * 4]), &(png->row_pointers[y][(right - (x - left)) * 4]), 4);
                    memcpy(&(png->row_pointers[y][(right - (x - left)) * 4]), temp, 4);
                }
            }
        }
        else {
            printf("Некорректно указана ось для отражения\n");
            return;
        }
    }

    //for RGB

    if (png_get_color_type(png->png_ptr, png->info_ptr) !=PNG_COLOR_TYPE_RGBA){
        png_byte temp[3];
    
        if (left >= right || up >= down) {
            printf("Некорректно задана область для отражения\n");
            return;
        }
    
    // Отражение относительно горизонтальной оси
        if (axis == 'y') {
            for (y = up; y < (up + down) / 2; y++) {
                for (x = left; x < right; x++) {

                    memcpy(temp, &(png->row_pointers[y][x * 3]), 3);
                    memcpy(&(png->row_pointers[y][x * 3]), &(png->row_pointers[down - (y - up)][x * 3]), 3);
                    memcpy(&(png->row_pointers[down - (y - up)][x * 3]), temp, 3);
                }
            }
        }
    // Отражение относительно вертикальной оси
        else if (axis == 'x') {
            for (x = left; x < (left + right) / 2; x++) {
                for (y = up; y < down; y++) {
                    memcpy(temp, &(png->row_pointers[y][x * 3]), 3);
                    memcpy(&(png->row_pointers[y][x * 3]), &(png->row_pointers[y][(right - (x - left)) * 3]), 3);
                    memcpy(&(png->row_pointers[y][(right - (x - left)) * 3]), temp, 3);
                }
            }
        }
        else {
            printf("Некорректно указана ось для отражения\n");
            return;
        }
    }
}

float distance(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

void draw_point(struct Png *png, int x, int y, Color color){
    if (x >= 0 && x < png->width && y >= 0 && y < png->height) {
        if (png_get_color_type(png->png_ptr, png->info_ptr) == PNG_COLOR_TYPE_RGBA) {
            png_byte *ptr = &(png->row_pointers[y][x * 4]);
            ptr[0] = color.red;
            ptr[1] = color.green;
            ptr[2] = color.blue;
            ptr[3] = 255;
        } else if (png_get_color_type(png->png_ptr, png->info_ptr) != PNG_COLOR_TYPE_RGBA) {
            png_byte *ptr = &(png->row_pointers[y][x * 3]);
            ptr[0] = color.red;
            ptr[1] = color.green;
            ptr[2] = color.blue;
        }  
    }
}


void draw_pentagram(struct Png *png, Point center, int radius, int thickness, Color color) {
    radius=radius+(thickness/2);
    for(int i = center.x-radius; i<center.x+radius; i++){
        for(int j=center.y - radius; j<center.y+radius; j++){
            if(((center.x - i)*(center.x-i)+(center.y-j)*(center.y-j)>(radius*radius)-2*thickness*radius)&&((center.x-i)*(center.x-i)+(center.y-j)*(center.y-j)<(radius*radius))){
                draw_point(png, i, j, color);
            }
        }
    }

    Point points[5];
    for (int i = 0; i < 5; i++) {
        float phi = (M_PI / 5.0) * (2.0 * i + (3.0 / 2.0));
        points[i].x = center.x + round((radius-thickness/2) * cos(phi));
        points[i].y = center.y + round((radius-thickness/2) * sin(phi));
    }
    
    // Рисуем линии пентаграммы
    for (int i = 0; i < 5; i++) {
        draw_line(png, points[i].x, points[i].y, points[(i + 2) % 5].x, points[(i + 2) % 5].y, color, thickness);
    }
}
void to_hsv(struct Png *png){
    for (int i=0; i<png->height; i++){
        png_byte *row = png->row_pointers[i];
        for (int j = 0; j < png->width; j++) {
            png_byte *ptr = &(row[j * 3]); 
            float r1=ptr[0]/255.0;
            float g1=ptr[1]/255.0;
            float b1=ptr[2]/255.0;
            // printf("%lf%lf%lf", r1, g1, b1);
            float c_max = fmaxf(r1, fmaxf(g1, b1));
            float c_min = fminf(r1, fminf(g1, b1));
            float delta = c_max-c_min;
            float H = 0.0f;
            if (delta!=0){
                if (c_max==r1){
                H=(60*fmodf(((g1-b1)/delta), 6));
            }else if (c_max==g1){
                H=(60*(((b1-r1)/delta)+2));
            }else if (c_max==b1){
                H=(60*(((r1-g1)/delta)+4));
            }
            if (H<0){
                H+=360;
            }
            float S = (c_max==0)? 0: (delta/c_max);
            float V = c_max;

            // printf("%f %f %f", H, S, V);
            ptr[1]=(unsigned char)(H/360.0f*255.0f);
            ptr[0]=(unsigned char)(S*255.0f);
            ptr[2]=(unsigned char)(V*255.0f);
            }
        }

    }
}

int main(int argc, char *argv[]){
    int opt;
    int option_index=0;
    int will_draw_line=0;
    int will_mirror=0;
    int will_draw_pentagram=0;
    int start_x, start_y;
    Color color = {0, 0, 0};
    int end_x, end_y;
    int thickness_of_line=0;
    char wich_mirror;
    int up_x, up_y;
    int right_x, right_y;
    int hsv=0;
    Point center = {0.0, 0.0};
    int radius;
    int print_info=0;
    char* png_name_of_file=NULL;
    char* png_out_name=NULL;
    static struct option long_option[]={
        {"line", no_argument, 0, 'l'},
        {"start", required_argument, 0, 's'}, 
        {"end", required_argument, 0, 'e'}, 
        {"color", required_argument, 0, 'k'},
        {"thickness", required_argument, 0, 't'},
        {"mirror",no_argument, 0, 'm'},
        {"axis", required_argument, 0, 'a'},
        {"left_up", required_argument, 0, 'u'},
        {"right_down", required_argument, 0, 'd'},
        {"pentagram", no_argument, 0, 'p'},
        {"center", required_argument, 0, 'c'},
        {"radius", required_argument, 0, 'r'},
        {"help", no_argument, 0, 'h'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"info", no_argument, 0, 'z'},
        {"hsv", no_argument, 0, 'b'}
    };
    while ((opt=getopt_long(argc, argv, "ls:e:k:t:ma:u:d:pc:r:hi:o:z", long_option, &option_index))!=-1){
        switch(opt){
            case 'h':
                printf("Course work for option 4.20, created by Yana Konasova. Вызов флага --line рисует линию. Используйте флаг --start для задачи координат для начала линии и флаг --end для задачи координат конца линии, а также флаг --color для задачи цвета и флаг --thickness для задачи толщины линии. Вызов флага --mirror отображает заданную область. Используйте флаг --axis для выбора оси относительно которой отображать, а также флаг --left_up для задачи левого верхнего угла области и флаг --right_down для задачи правого нижнего угла области. Вызов флага --pentagram рисует пентаграмму в круге. Используйте флаг --center для задачи координат центра круга и флаг -radius для задачи радиуса круга, а также флаг --thickness для задачи толщины линий и флаг --color для задачи цвета.\n ");
                return 0;
                break;
            case 'l':
                will_draw_line=1;
                break;
            case 'm':
                will_mirror=1;
                break;
            case 'p':
                will_draw_pentagram=1;
                break;
            case 's':
                if(sscanf(optarg, "%d.%d", &start_x, &start_y)!=2){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                break;
            case 'e':
                if(sscanf(optarg, "%d.%d", &end_x, &end_y)!=2){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                break;
            case 'k':
                if(sscanf(optarg, "%d.%d.%d", &color.red, &color.green, &color.blue)!=3){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                if (!(color.red>=0&&color.red<=255&&color.blue>=0&&color.blue<=255&&color.green>=0&&color.green<=255)){
                    printf("Задан некорректный цвет.\n"); 
                    exit(40); 
                }

                break;
            case 't':
                if(sscanf(optarg, "%d", &thickness_of_line)!=1){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                if (thickness_of_line<=0){
                    printf("Задана некорректная толщина линии.\n"); 
                    exit(41); 
                }
                break;
            case 'a':
                if(sscanf(optarg, "%c", &wich_mirror)!=1){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                if (!((wich_mirror=='x')||(wich_mirror=='y'))){
                    printf("Задана некорректная ось отображения.\n"); 
                    exit(42); 
                }
                break;
            case 'u':
                if(sscanf(optarg, "%d.%d", &up_x, &up_y)!=2){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                break;
            case 'd':
                if(sscanf(optarg, "%d.%d", &right_x, &right_y)!=2){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                break;
            case 'c':
                if(sscanf(optarg, "%d.%d", &center.x, &center.y)!=2){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                break;
            case 'r':
                if(sscanf(optarg, "%d", &radius)!=1){
                    printf("Задан некорректный аргумент\n");
                    exit(43);
                }
                if (radius<=0){
                    printf("Задан некорректный радиус.\n"); 
                    exit(43); 
                }
                break;
            case 'b':
                hsv=1;
                break;
            case 'i':
                png_name_of_file=optarg;
                break;
            case 'o':
                png_out_name=optarg;
                break;
            case 'z':
                print_info=1;
                break;



        }
    }
    if (optind < argc) {
        png_name_of_file = argv[optind];
    } 
    if (png_out_name!=NULL&& png_name_of_file!=NULL&& strcmp(png_name_of_file, png_out_name) == 0) { 

        printf("Ошибка: Имена входного и выходного файлов не могут совпадать.\n"); 
        exit(44); 
    }
    struct Png *png;
    png = read_png(png_name_of_file);

    if (print_info==1){
        printf("Высота изображения: %d\nШирина изображения: %d\nГлубина цвета изображения: %d\n", png->height, png->width, png->bit_depth);
        switch (png->color_type){
            case PNG_COLOR_TYPE_RGB:
                printf("Тип цвета: RGB\n");
                break;
            case PNG_COLOR_TYPE_RGBA:
                printf("Тип цвета: RGBA\n");
                break;
        }
        return 0;
    }

    if (will_draw_line==1){
        draw_line(png, start_x, start_y, end_x, end_y, color, thickness_of_line);
    }
 
    if (will_mirror==1){
        mirror_region(png, wich_mirror, up_x, up_y, right_x, right_y);
    }
    
    if (will_draw_pentagram==1){
        draw_pentagram(png, center, radius, thickness_of_line, color);
    }
    if (hsv==1){
        to_hsv(png);
    }




    save_png(png_out_name, png);
    for (int y = 0; y < png->height; y++) {
        free(png->row_pointers[y]);
    }
    free(png->row_pointers);


    return 0;
}