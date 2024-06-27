#include "../include/png_objects.h" /* объекты и структуры для PNG */
#include "../include/read_write.h" /* функции чтения и записи файла */
#include "../include/print_help_info.h" /* функции вывода информации о программе и изображении*/
#include "../include/draw_line.h" /* функции рисования линии */
#include "../include/draw_pentagram.h" /* функции рисования пентаграммы */
#include "../include/draw_mirror.h" /* функции отражения области */
#include "../include/draw_contrast.h"

int main(int argc, char *argv[]) {
    /* вывод информации о курсовой работе и авторе */
    puts("Course work for option 4.20, created by Alexander Korshkov.");

    /* проверка, переданы ли аргументы */
    if (argc == 1) {
        print_help();
        return 0;
    }
    opterr = 0;
    /* структура, содержащая длинная флаги */
    struct option long_opt[] = {
            {"help",       no_argument,       NULL, 'h'}, /* справка */
            {"info",       no_argument,       NULL, '!'}, /* информация о файле */

            {"input",      required_argument, NULL, 'i'}, /* входной файл */
            {"output",     required_argument, NULL, 'o'}, /* выходной файл */

            {"line",       no_argument,       NULL, 300}, /* рисование линии */
            {"start",      required_argument, NULL, 301}, /* начальная точка */
            {"end",        required_argument, NULL, 302}, /* конечная точка */
            {"color",      required_argument, NULL, 303}, /* цвет линии */
            {"thickness",  required_argument, NULL, 304}, /* толщина линии */

            {"mirror",     no_argument,       NULL, 400}, /* отражение */
            {"axis",       required_argument, NULL, 401}, /* ось отражения */
            {"left_up",    required_argument, NULL, 402}, /* верхний левый угол области */
            {"right_down", required_argument, NULL, 403}, /* нижний правый угол области */

            {"pentagram",  no_argument,       NULL, 404}, /* рисование пентаграммы в круге*/
            {"center",     required_argument, NULL, 405}, /* центр круга */
            {"radius",     required_argument, NULL, 406}, /* радиус круга */
            /* color */ /* цвет линии пентаграмма */
            /* thickness */ /* толщина линии пентаграмма */

            {"contrast",   no_argument,       NULL, 500},
            {"alpha",      required_argument, NULL, 501},
            {"beta",       required_argument, NULL, 502},
            {0,            0,                 0,    0}
    };

    /* информация о фото */
    Png input_image;

    /* информация о входном и выходном файле */
    info_file information = {.output_file = "out.png", .info = 0};

    /* информация о линии, области для отражения и рисования пентаграммы */
    info_line line = {.p = 0, .p0 = {.x = -1, .y = -1}, .p1 = {.x = -1, .y = -1},
            .thickness = -1, .color = {.r = -1, .g = -1, .b = -1}};
    info_mirror mirror = {.p = 0, .p0 = {.x = -1, .y = -1}, .p1 = {.x = -1, .y = -1}, .axis = 'n'};
    info_pentagram pentagram = {.p = 0, .center = {.x = -1, .y = -1}, .radius = -1};

    info_contrast contrast = {.p=0, .alpha=-1.0, .beta=-1};
    /* цикл, обрабатывающий флаги и аргументы */
    int opt;
    while ((opt = getopt_long(argc, argv, "hi:o:", long_opt, NULL)) != -1) {
        switch (opt) {
            /* справка */
            case 'h': {
                print_help();
                return 0;
            }
                /* информация о файле */
            case '!': {
                information.info = 1;
                break;
            }
                /* входной файл */
            case 'i': {
                information.input_file = optarg;
                break;
            }
                /* выходной файл */
            case 'o': {
                information.output_file = optarg;
                break;
            }
                /* рисование линии */
            case 300: {
                line.p = 1;
                break;
            }
                /* начальная координата линии */
            case 301: {
                set_start_cords(optarg, &line);
                break;
            }
                /* конечная координата линии */
            case 302: {
                set_end_cords(optarg, &line);
                break;
            }
                /* цвет линии (для пентаграммы тоже)*/
            case 303: {
                char *color = strdup(optarg);
                set_color_line(optarg, &line);
                set_color_pentagram(color, &pentagram);
                break;
            }
                /* толщина линии (для пентаграммы тоже) */
            case 304: {
                char *thickness = strdup(optarg);
                set_thickness_line(optarg, &line);
                set_thickness_pentagram(thickness, &pentagram);
                break;
            }
                /* отражение области */
            case 400: {
                mirror.p = 1;
                break;
            }
                /* ось отражённой области */
            case 401: {
                set_axis(optarg, &mirror);
                break;
            }
                /* верхний левый угол области */
            case 402: {
                set_left_up(optarg, &mirror);
                break;
            }
                /* нижний правый угол области */
            case 403: {
                set_right_down(optarg, &mirror);
                break;
            }
                /* рисование пентаграммы в круге */
            case 404: {
                pentagram.p = 1;
                break;
            }
                /* центр круга */
            case 405: {
                set_center(optarg, &pentagram);
                break;
            }
                /* радиус круга */
            case 406: {
                set_radius(optarg, &pentagram);
                break;
            }
            case 500: {
                contrast.p += 1;
                break;
            }
            case 501: {
                set_alpha(optarg, &contrast);
                break;
            }
            case 502: {
                set_beta(optarg, &contrast);
                break;
            }
            default: {
                puts("Unknown option!");
                exit(47);
            }
        }
    }
    if (line.p + mirror.p + pentagram.p + contrast.p == 0) {
        printf("You don't specify any function!\n");
        exit(40);
    }
    if (line.p + mirror.p + pentagram.p + contrast.p != 1) {
        printf("You specify more than one function!\n");
        exit(40);
    }
    /* проверка, что имя файла было как-то передано (через опцию или в конце отдельным аргументом) */
    if (!information.input_file) {
        if (optind < argc) {
            information.input_file = argv[argc - 1];
        } else {
            printf("You don't specify input file!\n");
            exit(40);
        }
    }
    /* чтение и получение информации об изображении */
    read_png_file(information.input_file, &input_image);

    /* проверка, ввёл ли пользователь флаг --info */
    if (information.info == 1) {
        print_info(information.input_file, &input_image);
        return 0;
    }
    /* проверка на корректность и количество введённых параметров линии */
    if (line.p) {
        if (check_line(&line))
            draw_line(line.p0.x, line.p0.y, line.p1.x, line.p1.y, line.thickness, line.color, &input_image);
        else {
            printf("You don't specify all parameters for line!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    /* проверка на корректность и количество введённых параметров отражённой области */
    if (mirror.p) {
        if (check_mirror(&mirror))
            draw_mirror(mirror.p0.x, mirror.p0.y, mirror.p1.x, mirror.p1.y, mirror.axis, &input_image);
        else {
            printf("You don't specify all parameters for mirror!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    /* проверка на корректность и количество введённых параметров пентаграммы в круге */
    if (pentagram.p) {
        if (check_pentagram(&pentagram))
            draw_pentagram(pentagram.center.x, pentagram.center.y, pentagram.radius, pentagram.thickness,
                           pentagram.color, &input_image);
        else {
            printf("You don't specify all parameters for pentagram!\n");
            free_png(&input_image);
            exit(40);
        }
    }
    if (contrast.p) {
        set_contrast(&contrast, &input_image);
    }
    /* запись файла */
    write_png_file(information.output_file, &input_image);
    return 0;
}
