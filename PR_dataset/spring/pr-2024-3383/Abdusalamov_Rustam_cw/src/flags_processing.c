#include "flags_processing.h"

void init_param(Parameters* param){
    param->component_name = '-';
    param->component_value = -1;
    param->angle = -1;
    param->right = -1;
    param->up = -1;
    param->down = -1;
    param->left = -1;
    param->squared_lines = 0;
    param->rotate = 0;
    param->info = 0;
    param->rgb_filter = 0;
    param->input_name = NULL;
    param->output_name = "./out";
    param->fill = 0;
    param->thickness = -1;
    param->side_size = -1;
    param->color = NULL;
    param->fill_color = NULL;
    param->upper_vertex = 0;
    param->size = 0;
    param->square_rhombus = 0;
}
void check_parameters(Parameters *param) {
    if (strcmp(param->input_name, param->output_name) == 0) {
        printf("Ошибка: имена входного и выходного файлов совпадают\n");
        exit(40);
    }
    if (param->squared_lines) {
        if (param->left == -1 || param->up == -1 || param->side_size <= 0 || param->thickness < 0 || param->color == NULL || (param->fill == 1 && param->fill_color == NULL)) {
            printf("Ошибка: Не все параметры для рисования квадрата с диагоналями заданы или заданы некорректно\n");
            exit(40);
        }
    }
    if (param->rgb_filter) {
        if (param->component_name == '-' || param->component_value == -1) {
            printf("Ошибка: Не заданы все необходимые параметры для фильтра RGB-компонент\n");
            exit(40);
        }
        if (strchr("rgb", param->component_name) == NULL){
            printf("Ошибка: Задано неверное значение component_name. Допустимые значение red/green/blue\n");
            exit(40);
        }
        if (param->component_value < 0 || param->component_value > 255) {
            printf("Ошибка: Некорректное значение компоненты для фильтра RGB-компонент (должно быть от 0 до 255)\n");
            exit(40);
        }
    }
    if (param->rotate) {
        if (param->left == -1 || param->up == -1 || param->right == -1 || param->down == -1 || param->angle % 90 != 0) {
            printf("Ошибка: Не все параметры для поворота изображения заданы или заданы некорректно\n");
            exit(40);
        }
    }
    if (param->rotate == 0 && param->squared_lines == 0 && param->rgb_filter == 0 && param->info == 0 && param->square_rhombus == 0){
        printf("Ошибка: Ни одна из функций обработки изображений не была выбрана. Для вывода справки воспользуйтесь флагом -h/--help\n");
        exit(40);
    }
}
void parse_command_line(int argc, char* argv[], Parameters* param){
    if (argc == 1){
        print_help();
        exit(0);
    }
    init_param(param);
    char *opts = "hrfsi:l:R:S:t:c:FC:n:v:a:I:o:";
    static struct option longopts[] = {
            {"help",        no_argument,       NULL, 'h'},
            {"rotate", no_argument, NULL, 'r'},
            {"rgbfilter",    no_argument, NULL, 'f'},
            {"squared_lines",       no_argument, NULL, 's'},
            {"left_up", required_argument, NULL, 'l'},
            {"right_down", required_argument, NULL, 'R'},
            {"side_size", required_argument, NULL, 'S'},
            {"thickness", required_argument, NULL, 't'},
            {"color", required_argument, NULL, 'c'},
            {"fill", no_argument, NULL, 'F'},
            {"fill_color", required_argument, NULL, 'C'},
            {"component_name", required_argument, NULL, 'n'},
            {"component_value", required_argument, NULL, 'v'},
            {"angle", required_argument, NULL, 'a'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},
            {"info", no_argument, NULL, 'I'},
            {"square_rhombus", no_argument, NULL, 'u'},
            {"size", required_argument, NULL, 'q'},
            {"upper_vertex", required_argument, NULL, 'x'},
            {NULL, 0,NULL, 0},
    };
    int opt;
    int r,g,b;
    while ((opt = getopt_long(argc, argv, opts, longopts, NULL)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                exit(0);
            case 'u':
                param->square_rhombus = 1;
                break;
            case 'r':
                param->rotate = 1;
                break;
            case 'f':
                param->rgb_filter = 1;
                break;
            case 's':
                param->squared_lines = 1;
                break;
            case 'l':
                sscanf(optarg, "%d.%d", &param->left, &param->up);
                break;
            case 'R':
                if (sscanf(optarg, "%d.%d", &param->right, &param->down) != 2) {
                    printf("Ошибка: Неверный формат заданных координат. Ожидаемый формат: xx.yy\n");
                    exit(40);
                }
                break;
            case 'x':
                if (sscanf(optarg, "%d.%d", &param->left, &param->up) != 2) {
                    printf("Ошибка: Неверный формат заданных координат. Ожидаемый формат: xx.yy\n");
                    exit(40);
                }
                break;
            case 'S':
            case 'q':
                param->side_size = atoi(optarg);
                break;
            case 't':
                param->thickness = atoi(optarg);
                break;
            case 'c':
                param->color = malloc(sizeof(RGB));
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3 ||
                    r < 0 || r > 255 ||g < 0 || g > 255 ||b < 0 || b > 255) {
                    printf("Ошибка: Неверный формат цвета. Ожидается формат: rrr.ggg.bbb, где r, g, b находятся в диапазоне от 0 до 255\n");
                    exit(40);
                }
                param->color->r = (unsigned char)r, param->color->g = (unsigned char)g, param->color->b = (unsigned char)b;
                break;
            case 'F':
                param->fill = 1;
                break;
            case 'C':
                param->fill_color = malloc(sizeof(RGB));
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3 ||
                    r < 0 || r > 255 ||g < 0 || g > 255 ||b < 0 || b > 255) {
                    printf("Ошибка: Неверный формат цвета. Ожидается формат: rrr.ggg.bbb, где r, g, b находятся в диапазоне от 0 до 255\n");
                    exit(40);
                }
                param->fill_color->r = r, param->fill_color->g = g, param->fill_color->b = b;
                break;
            case 'n':
                param->component_name = optarg[0];
                break;
            case 'v':
                if (sscanf(optarg, "%d", &param->component_value) != 1) {
                    printf("Ошибка: Неверный формат значения компоненты.\n");
                    exit(40);
                }
                break;
            case 'a':
                param->angle = atoi(optarg);
                break;
            case 'i':
                if (optarg[0] == '-'){
                    printf("Ошибка: Не указано имя входного файла\n");
                    exit(40);
                }
                param->input_name = optarg;
                break;
            case 'o':
                param->output_name = optarg;
                break;
            case 'I':
                param->info = 1;
                break;
            default:
                printf("Ошибка: Неизвестная опция\n");
                exit(40);
        }
    }
    if (param->input_name == NULL) {
        if (argc > optind && argv[argc - 1] != NULL) {
            param->input_name = argv[argc - 1];
            argc -= 1;
        } else {
            printf("Ошибка: Не указано имя входного файла\n");
            exit(40);
        }
    }
    if (optind < argc) {
        printf("Ошибка: Переданы ошибочные аргументы:");
        for (int i = optind; i < argc; i++)
            printf(" %s", argv[i]);
        printf("\nПрограмма будет завершена\n");
        exit(40);
    }
    check_parameters(param);
}
