#include "../input_output.h"
#include "../toolkit.h"
#include "../image.h"
#include <getopt.h>

void check_and_exit(int condition) {
    if (!condition) {
        print_error_and_exit(ERROR_REQUIRED_PARAMETER);
    }
}

void process_command(Image *image, Config config, int command, int flag_old_color, int flag_new_color, int flag_component_name, int flag_component_value, int flag_number_x, int flag_number_y, int flag_color, int flag_thickness, int flag_size, int flag_circle_color) {
    switch (command) {
        case 1:
            check_and_exit(flag_old_color == 1 && flag_new_color == 1);
            change_color(image, config.old_color, config.new_color);
            break;
        case 2:
            check_and_exit(flag_component_name == 1);
            apply_rgb_filter(image, config.component_name, config.component_value);
            break;
        case 3:
            check_and_exit(flag_number_x == 1 && flag_number_y == 1 && flag_color == 1 && flag_thickness == 1);
            draw_split(image, config.number_x, config.number_y, config.thickness, config.color);
            break;
        case 4:
            check_and_exit(flag_color == 1 && flag_circle_color == 1 && flag_size == 1);
            draw_circle_pixels(image, config.size, config.color, config.circle_color);
            break;
    }
}
void help_case(int argc){
    if (argc == 3)
        {
        print_help();
        }
        else
        {
            puts("Некорректный вызов подсказки.");
            puts("Примеры корректного вызова подсказки:");
            puts("./a.out (вызов программы без аргументов)");
            puts("./a.out sample.bmp");
            puts("./a.out sample.bmp -h");
        }
}

void print_info_case(int argc){
    BitmapInfoHeader *bmif = malloc(sizeof(BitmapInfoHeader));
    BitmapFileHeader *bmfh = malloc(sizeof(BitmapFileHeader));
    if (argc == 3)
        {
        print_file_header(*bmfh);
        print_info_header(*bmif);
        }
    else
    {
        puts("Слишком много аргументов для получения информации об изображении");
        puts("Пример корректного вызова: ./a.out sample.bmp -d");
        }
}

void choose_component_case(Config config,char* opt){
    if (strcmp(opt, "red") == 0)
        {
        config.component_name = 0;
        }
    else if (strcmp(opt, "green") == 0)
        {
        config.component_name = 1;
        }
    else if (strcmp(opt, "blue") == 0)
        {
        config.component_name = 2;
        }
    else
    {
    fprintf(stderr, "error: wrong argument!");
    exit(ERROR_CODE);
    }
}

void work_with_opt(int argc, char *argv[]){
    BitmapInfoHeader *bmif = malloc(sizeof(BitmapInfoHeader));
    BitmapFileHeader *bmfh = malloc(sizeof(BitmapFileHeader));
    char *file_input = "sample.bmp";
    char *file_output = "out.bmp";
    Config config;
    int command = 0;
    int opt;
    const char *short_options = "hdcrfWi:o:L:N:B:C:X:T:O:Y:s:q:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'd'},
        {"color_replace", no_argument, NULL, 'c'},
        {"rgbfilter", no_argument, NULL, 'r'},
        {"split", no_argument, NULL, 'f'},
        {"circle_pixel", no_argument, NULL, 'W'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"old_color", required_argument, 0, 'L'},
        {"new_color", required_argument, 0, 'N'},
        {"component_name", required_argument, 0, 'B'},
        {"component_value", required_argument, 0, 'C'},
        {"number_x", required_argument, 0, 'X'},
        {"thickness", required_argument, 0, 'T'},
        {"color", required_argument, 0, 'O'},
        {"number_y", required_argument, 0, 'Y'},
        {"size", required_argument, NULL, 's'},
        {"circle_color", required_argument, NULL, 'q'},
        {NULL, 0, NULL, 0}
    };
    int flag_old_color = 0;
    int flag_new_color = 0;
    int flag_component_name = 0;
    int flag_component_value = 0;
    int flag_number_x = 0;
    int flag_number_y = 0;
    int flag_color = 0;
    int flag_thickness = 0;
    int flag_size = 0;
    int flag_circle_color = 0;

    opt = getopt_long(argc, argv, short_options, long_options, NULL);
    while (opt != -1)
    {
        switch (opt)
        {
        case 'h':
            help_case(argc);
            exit;
            break;
        case 'd':
            print_info_case(argc);
            exit;
            break;
        case 'c':
            command = 1;
            break;
        case 'r':
            command = 2;
            break;
        case 'f':
            command = 3;
            break;
        case 'W':
            command = 4;
            break;
        case 'i':
            file_input = optarg;
            break;
        case 'o':
            file_output = optarg;
            break;
        case 'L':
            flag_old_color = 1;
            config.old_color = get_color_arg(optarg);
            break;
        case 'N':
            flag_new_color = 1;
            config.new_color = get_color_arg(optarg);
            break;
        case 'B':
            flag_component_name = 1;
            choose_component_case(config ,optarg);
            break;
        case 'C':
            flag_component_value = 1;
            config.component_value = get_number(optarg);
            break;
        case 'T':
            flag_thickness = 1;
            config.thickness = get_number(optarg);
            break;
        case 'X':
            flag_number_x = 1;
            config.number_x = get_number(optarg);
            break;
        case 'O':
            flag_color = 1;
            config.color = get_color_arg(optarg);
            break;
        case 'Y':
            flag_number_y = 1;
            config.number_y = get_number(optarg);
            break;
        case 's':
            flag_size = 1;
            config.size = get_number(optarg);
            break;
        case 'q':
            flag_circle_color = 1;
            config.circle_color = get_color_arg(optarg);
            break;
        case '?':
            exit;
        default:
            break;
        }

        opt = getopt_long(argc, argv, short_options, long_options, &optind);
    }

    Image image = read_bmp(file_input, bmfh, bmif);
    process_command(&image, config, command, flag_old_color, flag_new_color, flag_component_name, flag_component_value, flag_number_x, flag_number_y, flag_color, flag_thickness, flag_size, flag_circle_color);
    write_bmp(file_output, &image, *bmfh, *bmif);

}

int main(int argc, char *argv[]) {
    work_with_opt(argc,argv);
    return 0;
}
