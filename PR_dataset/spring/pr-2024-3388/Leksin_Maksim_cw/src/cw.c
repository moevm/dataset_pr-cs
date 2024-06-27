#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#define PI  3.1415926535
#define MAX_COLOR_COMPONENT 4
#define ERROR_CODE 40
#define PNG_SIGNATURE_BYTES 8
#define MAX_COMPONENT_VALUE 255
#define COMPONENT_COUNT 3
#define HELP "Course work for option 4.21, created by Maksim Leksin.\n\nЭто программа с CLI для редактирования изображений в формате PNG!\nПоддерживаются файлы с глубиной цвета 8 бит, RGB, RGBa.\nФормат ввода:\033[1;35m [./pngedit] [command] [input.png] -[o]/--[option] [argument] [output.png]\033[0m\n\n[имя файла] \033[1;35m--rect/-r \033[0m - рисование прямоугольника\n    --left_up/-L [x.y] - координаты левого верхнего угла\n    --right_down/-R [x.y] - координаты правого нижнего угла\n    --thickness/-t [n] - толщина линии в пикселях (больше 0)\n    --color/-c [rrr.ggg.bbb] - числа от 0 до 255, цвет линии\n    --fill/-f - опция для заливки. Есть флаг - есть заливка, нет флага - нет заливки\n    --fill_color/-F [rrr.ggg.bbb] - цвет заливки, если она есть\n\n[имя файла] \033[1;35m--hexagon/-H\033[0m - рисование правильного шестиугольника\n    --center/-s [x.y] - координаты центра шестиугольника\n    --radius/-d [n] - радиус шестиугольника (больше 0)\n    --thickness/-t [n] - толщина линии в пикселях (больше 0)\n    --color/-c [rrr.ggg.bbb] - числа от 0 до 255, цвет линии\n    --fill/-f - опция для заливки. Есть флаг - есть заливка, нет флага - нет заливки\n    --fill_color/-F [rrr.ggg.bbb] - цвет заливки, если она есть\n\n[имя файла] \033[1;35m--copy/-C\033[0m - копирование заданной области\n    --left_up/-L [x.y] - координаты левого верхнего угла области-источника\n    --right_down/-R [x.y] - координаты правого нижнего угла области-источника\n    --dest_left_up/-D [x.y] - координаты левого верхнего угла области-назначения\n\n[имя файла] \033[1;35m-i/--info\033[0m - получить информацию об изображении\n[имя файла] \033[1;35m-h/--help\033[0m - вызвать справку\n"
#define COLOR_FLAG 0
#define FILL_FLAG 1
#define FILL_COLOR_FLAG 2
#define BINARIZATION_FLAG 3
#define INFO_FLAG 4
#define RECT_FLAG 5
#define HEX_FLAG 6
#define COPY_FLAG 7
#define LEFT_UP_FLAG 8
#define RIGHT_DOWN_FLAG 9
#define THICKNESS_FLAG 10
#define CENTER_FLAG 11
#define RADIUS_FLAG 12
#define THRESHOLD_FLAG 13
#define DEST_LEFT_UP_FLAG 14
#define OUTPUT_FLAG 15
#define INPUT_FLAG 16
#define FLAGS_COUNT 17

typedef struct
{
    int width;
    int height;
    png_byte bit_depth;
    png_byte color_type;
    png_byte channels;
    png_infop info_ptr;
    png_structp png_ptr;
    png_bytep *row_pointers;    
} Image;

typedef struct {
    int first_x, first_y, second_x, second_y, third_x, third_y;
    int thickness, radius, isFill;
    int border_color[COMPONENT_COUNT];
    int fill_color[COMPONENT_COUNT];
} Data;

typedef struct {
    int first_x, first_y, second_x, second_y, thickness, isFill;
    int border_color[COMPONENT_COUNT];
    int fill_color[COMPONENT_COUNT];
} Rectangle;

typedef struct {
    int first_x, first_y, radius, thickness, isFill;
    int border_color[COMPONENT_COUNT];
    int fill_color[COMPONENT_COUNT];
} Hexagon;

typedef struct {
    int old_first_x, old_first_y, old_second_x, old_second_y;
    int new_x, new_y;
} Copy;

void panic(const char* error){
    fprintf(stderr, "%s", error);
    exit(ERROR_CODE);
}

void panic_with_variable(const char* error, const char* var){
    fprintf(stderr, error, var);
    exit(ERROR_CODE);
}

void panic_with_close_file(const char* error, const char* var, FILE* fp){
    fprintf(stderr, error, var);
    fclose(fp);
    exit(ERROR_CODE);
}

void print_PNG_info(Image * image)
{
    printf("Информация об изображении:\n");
    printf("    Ширина изображения: %d\n", image->width);
    printf("    Высота изображения: %d\n", image->height);
    printf("    Тип цвета: %u\n", image->color_type);
    printf("    Глубина цвета: %u\n", image->bit_depth);
    printf("    Каналы: %u\n", image->channels);
}

void print_help()
{
    printf(HELP);
}

void check_png_pointers(Image * image, FILE * fp){
    if (!image->png_ptr) {
        panic_with_close_file("Ошибка: не удалось создать структуру для чтения формата PNG\n", "", fp);
    }
    if (!image->info_ptr) {
        panic_with_close_file("Ошибка: не удалось создать информационную структуру PNG\n", "", fp);
    }
}

void read_image(const char * filename, Image * image)
{
    FILE * fp = fopen(filename, "rb");

    if (!fp) {
        panic_with_variable("Ошибка: Не удалось открыть файл  '%s'\n", filename);
    }

    unsigned char header[PNG_SIGNATURE_BYTES];
    if (fread(header, 1, PNG_SIGNATURE_BYTES, fp) != PNG_SIGNATURE_BYTES) {
        panic_with_close_file("Ошибка: не удалось прочитать файл '%s'\n", filename, fp);
    }

    int is_png = !png_sig_cmp(header, 0, PNG_SIGNATURE_BYTES);
    if (!is_png) {
        panic_with_close_file("Ошибка: файл '%s' не является PNG\n", filename, fp);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    image->info_ptr = png_create_info_struct(image->png_ptr);
    check_png_pointers(image, fp);

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, PNG_SIGNATURE_BYTES);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *)malloc(image->height * sizeof(png_bytep));

    for (int i = 0; i < image->height; i++) {
        image->row_pointers[i] = (png_byte *)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }

    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}

void write_image(const char * filename, Image * image)
{
    FILE * fp = fopen(filename, "wb");

    if (!fp) {
        panic_with_variable("Ошибка: не удалось открыть файл '%s' для записи\n", filename);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    image->info_ptr = png_create_info_struct(image->png_ptr);
    check_png_pointers(image, fp);

    png_init_io(image->png_ptr, fp);
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    png_write_image(image->png_ptr, image->row_pointers);
    png_write_end(image->png_ptr, NULL);
    fclose(fp);
}

void set_pixel(Image * image, int x, int y, int * color)
{
    if (x < 0 || y < 0 || x >= image->width || y >= image->height) {
        return;
    }

    png_bytep row = image->row_pointers[y];
    png_bytep pixel = &row[x * image->channels];

    switch (image->color_type) {
        case PNG_COLOR_TYPE_RGB:
            pixel[0] = color[0];
            pixel[1] = color[1];
            pixel[2] = color[2];
            break;
        default:
            panic("Ошибка: Неподдерживаемый тип цвета\n");
            return;
    }
}

void draw_circle (Image * image, int first_x, int first_y, int radius, int * color) 
{
    if (radius == 0){
        set_pixel(image, first_x, first_y, color);
        return;
    }

    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        set_pixel(image, first_x + x, first_y + y, color);
        set_pixel(image, first_x + x, first_y - y, color);
        set_pixel(image, first_x - x, first_y + y, color);
        set_pixel(image, first_x - x, first_y - y, color);
        set_pixel(image, first_x + y, first_y + x, color);
        set_pixel(image, first_x + y, first_y - x, color);
        set_pixel(image, first_x - y, first_y + x, color);
        set_pixel(image, first_x - y, first_y - x, color);

        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 * (++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 *(--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }

    draw_circle(image, first_x, first_y, radius / 2, color);
}

void draw_line(Image * image, int first_x, int first_y, int second_x, int second_y, int thickness, int * color)
{
    int delta_x = abs(second_x - first_x);
    int sign_x = first_x < second_x ? 1 : -1;
    int delta_y = abs(second_y - first_y);
    int sign_y = first_y < second_y ? 1 : -1;
    int first_error = delta_x - delta_y;
    int second_error;
    draw_circle(image, second_x, second_y, thickness / 2, color);
    while(first_x != second_x || first_y != second_y) {
        draw_circle(image, first_x, first_y, thickness / 2, color);
        second_error = 2 * first_error;
        if (second_error > -delta_y) {
            first_error -= delta_y;
            first_x += sign_x;
        }
        if (second_error < delta_x) {
            first_error += delta_x;
            first_y += sign_y;
        }
    }
}

void draw_rectangle(Image * image, Rectangle rect)
{
    if (rect.first_x > rect.second_x) {
        int temp = rect.first_x;
        rect.first_x = rect.second_x;
        rect.second_x = temp;
    }
    if (rect.first_y > rect.second_y) {
        int temp = rect.first_y;
        rect.first_y = rect.second_y;
        rect.second_y = temp;
    }
    if(rect.isFill) {
        for (int y = rect.first_y + 1; y < rect.second_y; y++) {
            for (int x = rect.first_x + 1; x < rect.second_x; x++) {
                set_pixel(image, x, y, rect.fill_color);
            }
        }
    }
    draw_line(image, rect.first_x, rect.first_y, rect.second_x, rect.first_y, rect.thickness, rect.border_color);
    draw_line(image, rect.second_x, rect.first_y, rect.second_x, rect.second_y, rect.thickness, rect.border_color);
    draw_line(image, rect.second_x, rect.second_y, rect.first_x, rect.second_y, rect.thickness, rect.border_color);
    draw_line(image, rect.first_x, rect.second_y, rect.first_x, rect.first_y, rect.thickness, rect.border_color);
}

int is_inside_treangle(int x, int y, int second_x, int second_y, int third_x, int third_y, int fourth_x, int fourth_y) 
{
    int a = (second_x - x) * (third_y - second_y) - (third_x - second_x) * (second_y - y);
    int b = (third_x - x) * (fourth_y - third_y) - (fourth_x - third_x) * (third_y - y);
    int c = (fourth_x - x) * (second_y - fourth_y) - (second_x - fourth_x) * (fourth_y - y);
    if (a >= 0 && b >= 0 && c >= 0 || (a < 0 && b < 0 && c < 0)) return 1;
    else return 0;
}

void draw_hexagon(Image * image, Hexagon hex) 
{
    int first_x, first_y, second_x, second_y;
    if(hex.isFill) {
        for (int i = 0; i < 6; i++) {
            first_x = hex.first_x + hex.radius * cos(i * PI / 3);
            first_y = hex.first_y + hex.radius * sin(i * PI / 3);
            second_x = hex.first_x + hex.radius * cos((i + 1) * PI / 3);
            second_y = hex.first_y + hex.radius * sin((i + 1) * PI / 3);

            for (int h = 0; h <= image->height; h++) {
                for (int w = 0; w <= image->width; w++) {
                    if (is_inside_treangle(w, h, hex.first_x, hex.first_y, first_x, first_y, second_x, second_y) == 1) {
                        set_pixel(image, w, h, hex.fill_color);
                    }
                }
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        first_x = hex.first_x + hex.radius * cos(i * PI / 3);
        first_y = hex.first_y + hex.radius * sin(i * PI / 3);
        second_x = hex.first_x + hex.radius * cos((i + 1) * PI / 3);
        second_y = hex.first_y + hex.radius * sin((i + 1) * PI / 3);
        draw_line(image, first_x, first_y, second_x, second_y, hex.thickness, hex.border_color);
    }
}

void copyPaste(Image *image, Copy copy) 
{
    int width = copy.old_second_x - copy.old_first_x + 1;
    int height = copy.old_second_y - copy.old_first_y + 1;
    int row_bytes = width * image->channels;

    int first_x = copy.old_first_x < 0 ? 0 : copy.old_first_x;
    int first_y = copy.old_first_y < 0 ? 0 : copy.old_first_y;
    int second_x = copy.old_second_x >= image->width ? image->width - 1 : copy.old_second_x;
    int second_y = copy.old_second_y >= image->height ? image->height - 1 : copy.old_second_y;
    int third_x = copy.new_x < 0 ? 0 : copy.new_x;
    int third_y = copy.new_y < 0 ? 0 : copy.new_y;

    int paste_width = width;
    int paste_height = height;

    if (third_x + width > image->width) {
        paste_width = image->width - third_x;
    }
    if (third_y + height > image->height) {
        paste_height = image->height - third_y;
    }

    row_bytes = paste_width * image->channels;

    png_bytep buffer = (png_bytep)malloc(paste_height * row_bytes);
    if (!buffer) {
        panic("Ошибка: Не удалось выделить память для буфера копирования\n");
    }

    for (int y = 0; y < paste_height; y++) {
        png_bytep src_row = image->row_pointers[first_y + y];
        png_bytep dest_row = &buffer[y * row_bytes];
        memcpy(dest_row, &src_row[first_x * image->channels], row_bytes);
    }

    for (int y = 0; y < paste_height; y++) {
        png_bytep dest_row = image->row_pointers[third_y + y];
        memcpy(&dest_row[third_x * image->channels], &buffer[y * row_bytes], row_bytes);
    }

    free(buffer);
}

void binarization_image(Image * image, int threshold)
{
    for (int y = 0; y < image->height; y++) {
        png_bytep row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_bytep pixel = &row[x * COMPONENT_COUNT];
            int sum = 0;
            for (int i = 0; i < COMPONENT_COUNT; i++) {
                sum += pixel[i];
            }
            if (sum >= threshold) {
                for (int i = 0; i < COMPONENT_COUNT; i++) {
                    pixel[i] = MAX_COMPONENT_VALUE;
                }
            }
            else {
                for (int i = 0; i < COMPONENT_COUNT; i++) {
                    pixel[i] = 0;
                }
            }
        }
    }
}

void initialize(char **output_file, char **input_file, int *flags, int *threshold, Data *data) {
    *output_file = "out.png";
    *input_file = NULL;
    memset(flags, 0, 17 * sizeof(int));
    *threshold = 0;

    data->isFill = 0;
    for (int i = 0; i < COMPONENT_COUNT; i++) {
        data->border_color[i] = 0;
        data->fill_color[i] = 0;
    }
}

void parse_arguments(int argc, char *argv[], Data *data, char **input_file, char **output_file, int *flags, int *threshold) {
    int opt;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"output", required_argument, 0, 'o'},
        {"input", required_argument, 0, 'i'},
        {"info", no_argument, 0, 'I'},
        {"rect", no_argument, 0, 'r'},
        {"left_up", required_argument, 0, 'L'},
        {"right_down", required_argument, 0, 'R'},
        {"thickness", required_argument, 0, 't'},
        {"color", required_argument, 0, 'c'},
        {"fill", no_argument, 0, 'f'},
        {"fill_color", required_argument, 0, 'F'},
        {"center", required_argument, 0, 's'},
        {"radius", required_argument, 0, 'd'},
        {"hexagon", no_argument, 0, 'H'},
        {"dest_left_up", required_argument, 0, 'D'},
        {"copy", no_argument, 0, 'C'},
        {"binarization", no_argument, 0, 'B'},
        {"threshold", required_argument, 0, 'T'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "BIrfhHCo:L:R:t:c:F:s:d:D:i:T:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                exit(0);
            case 'o':
                flags[OUTPUT_FLAG]++;
                *output_file = optarg;
                break;
            case 'i':
                flags[INPUT_FLAG]++;
                *input_file = optarg;
                break;
            case 'I':
                flags[INFO_FLAG]++;
                break;
            case 'r':
                flags[RECT_FLAG]++;
                break;
            case 'H':
                flags[HEX_FLAG]++;
                break;
            case 'C':
                flags[COPY_FLAG]++;
                break;
            case 'D':
                flags[DEST_LEFT_UP_FLAG]++;
                sscanf(optarg, "%d.%d", &data->third_x, &data->third_y);
                break;
            case 'd':
                flags[RADIUS_FLAG]++;
                sscanf(optarg, "%d", &data->radius);
                break;
            case 's':
                flags[CENTER_FLAG]++;
                sscanf(optarg, "%d.%d", &data->first_x, &data->first_y);
                break;
            case 'L':
                flags[LEFT_UP_FLAG]++;
                sscanf(optarg, "%d.%d", &data->first_x, &data->first_y);
                break;
            case 'R':
                flags[RIGHT_DOWN_FLAG]++;
                sscanf(optarg, "%d.%d", &data->second_x, &data->second_y);
                break;
            case 't':
                flags[THICKNESS_FLAG]++;
                data->thickness = atoi(optarg);
                break;
            case 'c':
                flags[COLOR_FLAG]++;
                if (sscanf(optarg, "%d.%d.%d", &data->border_color[0], &data->border_color[1], &data->border_color[2]) != 3) {
                    panic("Ошибка: Неверный формат цвета.\n");
                }
                for (int i = 0; i < COMPONENT_COUNT; i++) {
                    if (data->border_color[i] < 0 || data->border_color[i] > MAX_COMPONENT_VALUE) {
                        panic("Ошибка: Компонента цвета должна быть в диапазоне 0-255.\n");
                    }
                }
                break;
            case 'f':
                flags[FILL_FLAG]++;
                data->isFill = 1;
                break;
            case 'F':
                flags[FILL_COLOR_FLAG]++;
                if (data->isFill) {
                    if (sscanf(optarg, "%d.%d.%d", &data->fill_color[0], &data->fill_color[1], &data->fill_color[2]) != 3) {
                        panic("Ошибка: Неверный формат цвета.\n");
                    }
                    for (int i = 0; i < COMPONENT_COUNT; i++) {
                        if (data->fill_color[i] < 0 || data->fill_color[i] > MAX_COMPONENT_VALUE) {
                            panic("Ошибка: Компонента цвета должна быть в диапазоне 0-255.\n");
                        }
                    }
                }
                break;
            case 'B':
                flags[BINARIZATION_FLAG]++;
                break;
            case 'T':
                flags[THRESHOLD_FLAG]++;
                sscanf(optarg, "%d", threshold);
                if (*threshold <= 0) {
                    panic("Ошибка: значение threshold должно быть больше 0\n");
                }
                break;
            default:
                panic("Ошибка: Неверный флаг.\n");
        }
    }

    if (optind < argc && *input_file == NULL) {
        if (strcmp(argv[optind], *output_file) == 0) {
            panic("Ошибка: имя входного файла и имя выходного файла не должны совпадать.\n");
        }
        *input_file = argv[optind];
    }
    if (*input_file == NULL) {
        panic("Ошибка: Входной файл не указан.\n");
    }
}

void validate_flags(const int *flags, const Data *data) {
    if ((flags[RECT_FLAG] > 0 && flags[HEX_FLAG] > 0) || (flags[RECT_FLAG] > 0 && flags[COPY_FLAG] > 0) || (flags[COPY_FLAG] > 0 && flags[HEX_FLAG] > 0) || (flags[RECT_FLAG] > 0 && flags[HEX_FLAG] > 0 && flags[COPY_FLAG] > 0)) {
        panic("Нельзя использовать несколько функций вместе.\n");
    }

    for (int i = 0; i < 17; i++) {
        if (flags[i] > 1) {
            panic("Ошибка: флаги могут быть использованы только один раз\n");
        }
    }
}

void process_image(const Data *data, const int *flags, Image *image, int threshold) {
    if (flags[INFO_FLAG]) {
        print_PNG_info(image);
        exit(0);
    }

    if (flags[RECT_FLAG]) {
        if (!(flags[LEFT_UP_FLAG] && flags[RIGHT_DOWN_FLAG] && flags[THICKNESS_FLAG] && flags[COLOR_FLAG])) {
            panic("Ошибка: Необходимо указать все параметры для флага --rect.\n");
        }

        if (flags[CENTER_FLAG] || flags[RADIUS_FLAG] || flags[DEST_LEFT_UP_FLAG]) {
            panic("Ошибка: Указаны лишние параметры\n");
        }

        Rectangle rect;
        rect.first_x = data->first_x;
        rect.first_y = data->first_y;
        rect.second_x = data->second_x;
        rect.second_y = data->second_y;
        rect.thickness = data->thickness;
        rect.isFill = data->isFill;

        for (int i = 0; i < COMPONENT_COUNT; i++) {
            rect.border_color[i] = data->border_color[i];
        }

        if (flags[FILL_COLOR_FLAG] && flags[FILL_FLAG]) {
            for (int i = 0; i < COMPONENT_COUNT; i++) {
                rect.fill_color[i] = data->fill_color[i];
            }
        } else {
            rect.isFill = 0;
        }

        draw_rectangle(image, rect);
    }

    if (flags[HEX_FLAG]) {
        if (!(flags[CENTER_FLAG] && flags[RADIUS_FLAG] && flags[THICKNESS_FLAG] && flags[COLOR_FLAG])) {
            panic("Ошибка: Необходимо указать все параметры для флага --hexagon.\n");
        }

        if (flags[LEFT_UP_FLAG] || flags[RIGHT_DOWN_FLAG] || flags[DEST_LEFT_UP_FLAG]) {
            panic("Ошибка: Указаны лишние параметры\n");
        }

        Hexagon hex;
        hex.first_x = data->first_x;
        hex.first_y = data->first_y;
        hex.radius = data->radius;
        hex.thickness = data->thickness;
        hex.isFill = data->isFill;

        for (int i = 0; i < COMPONENT_COUNT; i++) {
            hex.border_color[i] = data->border_color[i];
        }

        if (flags[FILL_COLOR_FLAG] && flags[FILL_FLAG]) {
            for (int i = 0; i < COMPONENT_COUNT; i++) {
                hex.fill_color[i] = data->fill_color[i];
            }
        } else {
            hex.isFill = 0;
        }

        draw_hexagon(image, hex);
    }

    if (flags[COPY_FLAG]) {
        if (!(flags[LEFT_UP_FLAG] && flags[RIGHT_DOWN_FLAG] && flags[DEST_LEFT_UP_FLAG])) {
            panic("Ошибка: Необходимо указать все параметры для флага --copy\n");
        }

        if (flags[THICKNESS_FLAG] || flags[COLOR_FLAG] || flags[FILL_FLAG] || flags[FILL_COLOR_FLAG] || flags[CENTER_FLAG] || flags[RADIUS_FLAG]) {
            panic("Ошибка: Указаны лишние параметры\n");
        }

        Copy copy;
        copy.old_first_x = data->first_x;
        copy.old_first_y = data->first_y;
        copy.old_second_x = data->second_x;
        copy.old_second_y = data->second_y;
        copy.new_x = data->third_x;
        copy.new_y = data->third_y;

        copyPaste(image, copy);
    }

    if (flags[BINARIZATION_FLAG]) {
        if (!flags[THRESHOLD_FLAG]) {
            panic("Ошибка: Необходимо ввести флаг --threshold\n");
        }
        binarization_image(image, threshold);
    }
}

void execute_image_processing(char *input_file, char *output_file, Data *data, int *flags, int threshold) {
    Image image;
    read_image(input_file, &image);
    process_image(data, flags, &image, threshold);
    write_image(output_file, &image);
}

int main(int argc, char *argv[]) {
    char *output_file;
    char *input_file;
    int flags[17];
    int threshold;
    Data data;

    initialize(&output_file, &input_file, flags, &threshold, &data);
    parse_arguments(argc, argv, &data, &input_file, &output_file, flags, &threshold);
    validate_flags(flags, &data);
    execute_image_processing(input_file, output_file, &data, flags, threshold);

    return 0;
}