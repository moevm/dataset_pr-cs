#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

typedef struct {
    int value;
    char* message;
} Error;

typedef struct {
    int rgb_filter_flag;
    int squared_lines_flag;
    int fill_flag;
    int circle_pixel_flag;

    char* output_name;
    char* input_name;

    int rotate_flag;
    int info_flag;

    char* component_name;
    char* component_value;

    char* left_up;
    char* right_down;

    char* side_size;
    char* thickness;
    char* angle;
    
    char* color;
    char* fill_color;
    char* size;
    char* circle_color;
} Options;

#pragma pack (push, 1)
typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int coloursIncolourTable;
    unsigned int importantcolourCount;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;

#pragma pack(pop)

char* strdup (const char* s) {
    size_t slen = strlen(s);
    char* result = malloc(slen + 1);

    if(result == NULL) return NULL;
    memcpy(result, s, slen + 1);
    return result;
}

void print_help() {
    printf("Флаги, используемые в программе:\n"
        "--help: Выводит справочную информацию.\n"
        "--input: Задаёт имя входного изображения.\n"
        "--output: Задаёт имя выходного изображения.\n"
        "--info: Вывод информации об изображении.\n"
        "--squared_lines: Рисование квадрата с диагоналями.\n"
        "--side_size: Размер стороны. Принимает число больше 0.\n"
        "--thickness: Толщина линии. Принимает число больше 0.\n"
        "--color: Цвет линии, задаётся строкой \'rrr.ggg.bbb\', где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n"
        "--fill: Может быть залит или нет. Флаг работает как бинарное значение: флага нет – false , флаг есть – true.\n"
        "--fill_color: Цветом которым он залит, если пользователем выбран залитый. работает аналогично флагу \'--color\'.\n"        
        "--rgbfilter: Фильтр rgb-компонент.\n"
        "--component_name: Какую компоненту требуется изменить. Возможные значения \'red\', \'green\' и \'blue\'\n"
        "--component_value: В какое значение ее требуется изменить. Принимает значение в виде числа от 0 до 255.\n"
        "--rotate: Поворот изображения (части) на 90/180/270 градусов.\n"
        "--left_up: Координаты левого верхнего угла области. Значение задаётся в формате \'left.up\', где left – координата по x, up – координата по y.\n"
        "--right_down: Координаты правого нижнего угла области. Значение задаётся в формате \'right.down\', где right – координата по x, down – координата по y.\n"
        "--angle: Угол поворота. Возможные значения: \'90\', \'180\', \'270\'.\n");
}

void print_file_header(BitmapFileHeader* header) {
    printf("signature:\t%x (%hu)\n", header->signature, header->signature);
    printf("filesize:\t%x (%u)\n", header->filesize, header->filesize);
    printf("reserved1:\t%x (%hu)\n", header->reserved1, header->reserved1);
    printf("reserved2:\t%x (%hu)\n", header->reserved2, header->reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header->pixelArrOffset, header->pixelArrOffset);
}

void print_info_header(BitmapInfoHeader* header) {
    printf("headerSize:\t%x (%u)\n", header->headerSize, header->headerSize);
    printf("width: \t%x (%u)\n", header->width, header->width);
    printf("height: \t%x (%u)\n", header->height, header->height);
    printf("planes: \t%x (%hu)\n", header->planes, header->planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header->bitsPerPixel, header->bitsPerPixel);
    printf("compression:\t%x (%u)\n", header->compression, header->compression);
    printf("imageSize:\t%x (%u)\n", header->imageSize, header->imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header->xPixelsPerMeter, header->xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header->yPixelsPerMeter, header->yPixelsPerMeter);
    printf("coloursIncolourTable:\t%x (%u)\n", header->coloursIncolourTable, header->coloursIncolourTable);
    printf("importantcolourCount:\t%x (%u)\n", header->importantcolourCount, header->importantcolourCount);
}

void initialize_opts(Options* opts) {
    opts->rgb_filter_flag = 0;
    opts->squared_lines_flag = 0;
    opts->circle_pixel_flag = 0;
    
    opts->fill_flag = 0;
    opts->rotate_flag = 0;
    opts->info_flag = 0;
    
    opts->input_name = "";
    opts->output_name = "out.bmp";
    opts->fill_color = NULL;

    opts->component_name = "";
    opts->component_value = NULL;
    opts->left_up = NULL;

    opts->right_down = NULL;
    opts->side_size = NULL;
    opts->thickness = NULL;
    
    opts->angle = NULL;
    opts->color = NULL;
    opts->fill_color = NULL;
}

RGB** create_RGB(int height, int width) {
    RGB** rgb = malloc(height * sizeof(RGB *));

    for(int i = 0; i < height; i++)
        rgb[i] = malloc(width * sizeof(RGB) + ((4 - (width * sizeof(RGB)) % 4) % 4));

    return rgb;
}

void delete_RGB(RGB** rgb, int height) {
    for(int i = 0; i < height; i++) 
        free(rgb[i]);

    free(rgb);
}

void check_bmp(BitmapFileHeader* file, Error* err) {
    if (file->signature != 0x4d42 && file->signature != 0x424d) {
        err->value = 1;
        err->message = "Given file is not a BMP.";
    }
}

RGB** read_bmp(char* file_name, BitmapFileHeader* file, BitmapInfoHeader* info, Error* err) {
    FILE *f = fopen(file_name, "rb");
    if (!f) {
        err->value = 1;
        err->message = "Couldn't open given file.";
        return create_RGB(0, 0);
    } 
    
    fread(file, 1, sizeof(BitmapFileHeader), f);
    fread(info, 1, sizeof(BitmapInfoHeader), f);

    check_bmp(file, err);
    if (err->value) {
        fclose(f);
        return create_RGB(0, 0);
    }

    fseek(f, file->pixelArrOffset, SEEK_SET);

    int height = info->height;
    int width = info->width;

    RGB** rgb = create_RGB(height, width);
    for(int i = 0; i < height; i++)
        fread(rgb[i], 1, width * sizeof(RGB) + ((4 - (info->width * sizeof(RGB)) % 4) % 4), f);

    fclose(f);
    return rgb;
}

void write_bmp(char* file_name, RGB** rgb, BitmapFileHeader* file, BitmapInfoHeader* info) {
    FILE* f = fopen(file_name, "wb");

    fwrite(file, 1, sizeof(BitmapFileHeader), f);
    fwrite(info, 1, sizeof(BitmapInfoHeader), f);

    fseek(f, file->pixelArrOffset, SEEK_SET);

    for(int i = 0; i < info->height; i++)
        fwrite(rgb[i], 1, info->width * sizeof(RGB) + ((4 - (info->width * sizeof(RGB)) % 4) % 4), f);

    fclose(f);
}

void paint_pixel(RGB* pixel, int b, int g, int r) {
    pixel->b = b;
    pixel->g = g;
    pixel->r = r;
}

int check_coordinates(int x, int y, int height, int width) {
    if (x >= 0 && y >= 0 && x < width && y < height) return 1;
    return 0;
}

void circle(RGB** rgb, BitmapInfoHeader* info, int radius, int x1, int y1, RGB pixel) {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x) {
        for (int i = x1 - x; i <= x1 + x; i++) {
            if (check_coordinates(i, y1+y, info->height, info->width)) rgb[y1 + y][i] = pixel;
            if (check_coordinates(i, y1-y, info->height, info->width))rgb[y1 - y][i] = pixel;
        }
        
        for (int i = x1 - y; i <= x1 + y; i++) {
            if (check_coordinates(i, y1+x, info->height, info->width))rgb[y1 + x][i] = pixel;
            if (check_coordinates(i, y1-x, info->height, info->width))rgb[y1 - x][i] = pixel;
        }

        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }
}

void line(RGB** rgb, BitmapInfoHeader* info, int x0, int y0, int x1, int y1, int thickness, RGB pixel) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1; 

    int err = (dx > dy ? dx : -dy) / 2;

    while(1) {
        circle(rgb, info, (thickness + 1)/2, x0, y0, pixel);
        
        if (x0 == x1 && y0 == y1) 
            break;

        if (err > -dx) { 
            err -= dy; 
            x0 += sx; 
        }

        if (err < dy) { 
            err += dx; 
            y0 += sy; 
        }
    }
}

int check_color(char* color) {
    int dot_count = 0;
    int num = 0;

    for (int i = 0; i < strlen(color); i++) {
        if (!isdigit(color[i]) && color[i] != '.') return 0;
        if (color[i] == '.') dot_count++;
    }

    if (dot_count != 2)
        return 0;

    if (color[0] == '.' || color[strlen(color) - 1] == '.')
        return 0;

    char* token = strtok(strdup(color), ".");
    for (int i = 0; i < 3; i++) {
        if (token == NULL || !isdigit(token[0])) return 0;
        num = atoi(token);
        
        if (num < 0 || num > 255) return 0;
        token = strtok(NULL, ".");
    }

    return 1;
}

int check_coordinate_format(char* coord) {
    int dot_count = 0;

    for (int i = 0; i < strlen(coord); i++) {
        if (!isdigit(coord[i]) && coord[i] != '.') return 0;
        if (coord[i] == '.') dot_count++;
    }

    if (dot_count != 1)
        return 0;

    if (coord[0] == '.' || coord[strlen(coord) - 1] == '.')
        return 0;
    
    return 1;
}

RGB get_colour(char* colour) {
    RGB pixel;
    char* str = strdup(colour);
    char* end;

    int red = strtol(str, &end, 10);
    int green = strtol(end + 1, &end, 10);
    int blue = strtol(end + 1, NULL, 10);

    paint_pixel(&pixel, blue, green, red);
    return pixel;
}

void get_coordinates(char* left_up, int* x, int* y) {
    char* str = strdup(left_up);
    char* end;

    *x = strtol(str, &end, 10);
    *y = strtol(end + 1, NULL, 10);
}

void draw_square(RGB** rgb, BitmapInfoHeader* info, int x, int y, int side_size, int thickness, char* colour, int fill, char* fill_colour) {
    RGB pixel = get_colour(colour);

    if (fill) {
        RGB pixel_filled = get_colour(fill_colour);
        
        for (int i = y+thickness/2; i < y+side_size-thickness/2; i++) {
            for (int j = x+thickness/2; j < x+side_size-thickness/2; j++) {
                if (check_coordinates(j, i, info->height, info->width)) rgb[i][j] = pixel_filled;
            }
        }
        
    }

    line(rgb, info, x, y, x + side_size, y, thickness, pixel);
    line(rgb, info, x, y, x, y + side_size, thickness, pixel);
    line(rgb, info, x, y + side_size, x + side_size, y + side_size, thickness, pixel);
    line(rgb, info, x + side_size, y, x + side_size, y + side_size, thickness, pixel);

    line(rgb, info, x, y, x + side_size, y + side_size, thickness, pixel);
    line(rgb, info, x + side_size, y, x, y + side_size, thickness, pixel);
}

void swap_channels(RGB** rgb, int height, int width, char* component_name, unsigned int component_value) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if (!strcmp(component_name, "green"))
                rgb[i][j].g = component_value;
            else if (!strcmp(component_name, "blue"))
                rgb[i][j].b = component_value;
            else 
                rgb[i][j].r = component_value;
        }
    }
}

void rotate(RGB** rgb, int height, int width, int x0, int y0, int x1, int y1, int angle) {
    RGB** rgb_rotated = create_RGB(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rgb_rotated[i][j] = rgb[i][j];
        }
    }

    int xc = (x1 + x0) / 2; int yc = (y1 + y0) / 2;

    int x; int y;
    int xr; int yr;
    
    for (int i = y0; i < y1; i++) {
        for (int j = x0; j < x1; j++) {
            switch(angle) {
                case 90:
                    xr = j - xc; yr = i - yc;
                    x = xc - yr; y = yc + xr;
                    
                    if (!((y1 + y0) % 2 == 0 && (x1 + x0) % 2 == 0)) {
                        if ((y1 + y0) % 2 == 0) y -= 1;
                        if ((y1 + y0) % 2 != 0) y += 1;
                    }

                    if ((x1 + x0) % 2 != 0) x -= 1;
                    
                    if (check_coordinates(j, i, height, width) && check_coordinates(x, y, height, width))
                        rgb[y][x] = rgb_rotated[i][j];
                    break;
                case 180:
                    x = x1 - j - 1 + x0; y = y1 - i - 1 + y0;

                    if (check_coordinates(j, i, height, width) && check_coordinates(x, y, height, width))
                        rgb[i][j] = rgb_rotated[y][x];
                    break;
                case 270:
                    xr = j - xc; yr = i - yc;
                    x = xc + yr; y = yc - xr;

                    if ((y1 + y0) % 2 == 0) y -= 1;

                    if (check_coordinates(j, i, height, width) && check_coordinates(x, y, height, width))
                        rgb[y][x] = rgb_rotated[i][j];
                    break;
            }
        }  
    }

    delete_RGB(rgb_rotated, height);
}

int check_int(char* str) {
    if (!str) return 0;

    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }

    return 1;
}

void circle_pixel(RGB** rgb, int height, int width, RGB color, RGB circle, int s) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(rgb[i][j].b == color.b && rgb[i][j].g == color.g && rgb[i][j].r == color.r) {
                for (int a = i - s; a < i + s; a++) {
                    for (int b = j - s; b < j + s; b++) {
                        if (check_coordinates(b, a, height, width)) {
                            if (a != i || b != j) {
                                if (rgb[a][b].b != color.b || rgb[a][b].g != color.g || rgb[a][b].r != color.r) {
                                    rgb[a][b] = circle;
                                }
                            }
                        } 
                    }
                }
            }
        }
    }
}

int check_options(Options* opts, Error* err) {
    if (opts->rgb_filter_flag) {
        if (!opts->component_name || !opts->component_value) {
            err->value = 1;
            err->message = "Some required flags are missing.";
            return 1;
        }

        if (!opts->component_name || (strcmp(opts->component_name, "green") && strcmp(opts->component_name, "blue") && strcmp(opts->component_name, "red"))) {
            err->value = 1;
            err->message = "Incorrect component name, must be blue, red or green.";
            return 1;
        }
        
        if (!check_int(opts->component_value)) {
            err->value = 1;
            err->message = "Incorrect component value, must be an integer.";
            return 1;
        }
        
        if (atoi(opts->component_value) < 0 || atoi(opts->component_value) > 255) {
            err->value = 1;
            err->message = "Incorrect component value, must be between 0 and 255.";
            return 1;
        }
    }

    if (opts->squared_lines_flag) {
        if (!opts->left_up || !opts->side_size || !opts->thickness || !opts->color || ((opts->fill_flag && !opts->fill_color))) {
            err->value = 1;
            err->message = "Some required flags are missing.";
            return 1;
        }

        if(!check_coordinate_format(opts->left_up)) {
            err->value = 1;
            err->message = "Given coordinates must be in format \"x.y\".";
            return 1;
        }

        if (!check_int(opts->side_size) || !check_int(opts->thickness)) {
            err->value = 1;
            err->message = "Incorrect side_size or thickness values, must be integers.";
            return 1;
        }

        if (atoi(opts->side_size) < 0 || atoi(opts->thickness) < 0) {
            err->value = 1;
            err->message = "Numeric values must be positive.";
            return 1;
        }

        if (!check_color(opts->color) || (opts->fill_flag && !check_color(opts->fill_color))) {
            err->value = 1;
            err->message = "Color must be given in format \"0.0.0\".";
            return 1;
        }
    }

    if (opts->rotate_flag) {
        if(!opts->left_up || !opts->right_down || !opts->angle) {
            err->value = 1;
            err->message = "Some required flags are missing.";
            return 1;
        }

        if(!check_coordinate_format(opts->left_up) || !check_coordinate_format(opts->right_down)) {
            err->value = 1;
            err->message = "Given coordinates must be in format \"x.y\".";
            return 1;
        }

        if (!check_int(opts->angle)) {
            err->value = 1;
            err->message = "Incorrect angle value, must be an integer.";
            return 1;
        }

        if (atoi(opts->angle) % 90 != 0 || atoi(opts->angle) < 0 || atoi(opts->angle) > 270) {
            err->value = 1;
            err->message = "Rotation angle must be 90, 180 or 270 degrees.";
            return 1;
        }
    }

    return 0;
}

Error process_image(char* filename, Options opts) {
    BitmapFileHeader file;
	BitmapInfoHeader info;
    
    Error err;
    err.value = 0;

    RGB** rgb = read_bmp(filename, &file, &info, &err);
    if (err.value == 1) return err;

    if (opts.info_flag) {
        print_file_header(&file);
        print_info_header(&info);
    }

    if (opts.rgb_filter_flag) {
        if(!check_options(&opts, &err)) swap_channels(rgb, info.height, info.width, opts.component_name, atoi(opts.component_value));
    }

    if (opts.squared_lines_flag) {
        if (!check_options(&opts, &err)) {
            int x; int y;
            get_coordinates(opts.left_up, &x, &y);

            if (opts.fill_flag)
                draw_square(rgb, &info, x, info.height - y - atoi(opts.side_size), atoi(opts.side_size), atoi(opts.thickness), opts.color, 1, opts.fill_color);
            else
                draw_square(rgb, &info, x, info.height - y - atoi(opts.side_size), atoi(opts.side_size), atoi(opts.thickness), opts.color, 0, NULL);
        } 
    }

    if (opts.rotate_flag) {
        if(!check_options(&opts, &err)) {
            int x0, y0, x1, y1;

            get_coordinates(opts.left_up, &x0, &y0);
            get_coordinates(opts.right_down, &x1, &y1);

            int side_size = abs(y1 - y0);

            if (y1 < y0 || x1 < x0) {
                int temp_x = x0; int temp_y = y0;
                x0 = x1; y0 = y1;
                x1 = temp_x; y1 = temp_y;
            }
            
            rotate(rgb, info.height, info.width, x0, info.height - y0 - side_size, x1, info.height - y1 + side_size, atoi(opts.angle));
        }
    }

    if (opts.circle_pixel_flag) {
        circle_pixel(rgb, info.height, info.width, get_colour(opts.color), get_colour(opts.circle_color), atoi(opts.size));
    }

    write_bmp(opts.output_name, rgb, &file, &info);

    delete_RGB(rgb, info.height);
    return err;
}

int check_file(char* filename) {
    BitmapFileHeader file;
    BitmapInfoHeader info;

    Error err;
    err.value = 0;
    
    RGB** rgb = read_bmp(filename, &file, &info, &err);

    if (err.value == 0) {
        delete_RGB(rgb, info.height);
        return 1;
    }

    delete_RGB(rgb, info.height);
    return 0;
}

void process_args(int argc, char* argv[]) {
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"output", required_argument, 0, 'o'},
        {"info", no_argument, 0, 5},
        {"input", required_argument, 0, 'i'},
        {"rgbfilter", no_argument, 0, 1},
        {"component_name", required_argument, 0, 'n'},
        {"component_value", required_argument, 0, 'v'},
        {"squared_lines", no_argument, 0, 2},
        {"left_up", required_argument, 0, 'l'},
        {"side_size", required_argument, 0, 's'},
        {"thickness", required_argument, 0, 't'},
        {"color", required_argument, 0, 'c'},
        {"fill", no_argument, 0, 3},
        {"fill_color", required_argument, 0, 'f'},
        {"rotate", no_argument, 0, 4},
        {"right_down", required_argument, 0, 'r'},
        {"angle", required_argument, 0, 'a'},
        {"circle_pixel", no_argument, 0, 6},
        {"size", required_argument, 0, 'p'},
        {"circle_color", required_argument, 0, 'z'},
        {0, 0, 0, 0}
    };

    char* extra_args[argc];
    int extra_args_count = 0;

    Options opts;
    initialize_opts(&opts);

    int opt;
    opterr = 0;

    while ((opt = getopt_long(argc, argv, "hi:o:n:v:l:s:t:c:f:r:a:z:p:", long_options, NULL)) != -1) {
        switch (opt) {
            case 1:
                opts.rgb_filter_flag = 1;
                break;
            case 2:
                opts.squared_lines_flag = 1;
                break;
            case 3:
                opts.fill_flag = 1;
                break;
            case 4:
                opts.rotate_flag = 1;
                break;
            case 5:
                opts.info_flag = 1;
                break;
            case 6:
                opts.circle_pixel_flag = 1;
                break;
            case 'p':
                opts.size = optarg;
                break;
            case 'z':
                opts.circle_color = optarg;
                break;
            case 'n':
                opts.component_name = optarg;
                break;
            case 'v':
                opts.component_value = optarg;
                break;
            case 'l':
                opts.left_up = optarg;
                break;
            case 's':
                opts.side_size = optarg;
                break;
            case 't':
                opts.thickness = optarg;
                break;
            case 'c':
                opts.color = optarg;
                break;
            case 'f':
                opts.fill_color = optarg;
                break;
            case 'r':
                opts.right_down = optarg;
                break;
            case 'a':
                opts.angle = optarg;
                break;
            case 'h':
                print_help();
                break;
            case 'o':
                opts.output_name = optarg;
                break;
            case 'i':
                opts.input_name = optarg;
                break;
            case '?':
                extra_args[extra_args_count++] = argv[optind - 1];
                break;
        }
    }

    while (optind < argc) {
        extra_args[extra_args_count++] = argv[optind++];
    }

    Error err;
    err.value = 0;

    if (optind == 1) print_help();

    if (extra_args_count > 0) {
        for (int i = 0; i < extra_args_count; i++) {
            if (check_file(extra_args[i])) {
                opts.input_name = extra_args[i];
            }

            else printf("Extra argument \'%s\' will be ignored.\n", extra_args[i]);
        }
    }

    if (strstr(opts.input_name, opts.output_name)) {
        err.value = 1;
        err.message = "Can't use the same input and output file names.";
    }

    if (!err.value) err = process_image(opts.input_name, opts);
    if (err.value) printf("%s\n", err.message);
}

int main(int argc, char* argv[]) {
    printf("Course work for option 4.12, created by Vera Ermolaeva.\n");
    process_args(argc, argv);
    return 0;
}