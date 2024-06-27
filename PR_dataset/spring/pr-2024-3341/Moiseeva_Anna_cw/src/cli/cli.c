#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "../file_handling/file_handling.h"
#include "../image_processing/image_processing.h"
#include "cli.h"

void display_help() {
    FILE *file = fopen("help", "r");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void cli(int argc, char *argv[]) {
    int opt;
    char *input_file_name = NULL;
    char *output_file_name = "out.bmp";
    int output_flag = 0, input_flag = 0, info_flag = 0, triangle_flag = 0, color_flag = 0, points_flag = 0, thickness_flag = 0, fill_flag = 0, fill_color_flag = 0;
    int rect_flag = 0, old_color_flag = 0, new_color_flag = 0, collage_flag = 0, x_flag = 0, y_flag = 0;
    int x1, y1, x2, y2, x3, y3, thickness, x, y, r, g, b;
    int bin_flag = 0, threshold_flag = 0, step_flag = 0, axis_flag = 0, shift_flag = 0;
    int porog, step;
    char* axis = NULL;
    Rgb color_triangle, fill_color, old_color, new_color;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"output", required_argument, 0, 'o'},
        {"input", required_argument, 0, 'i'},
        {"info", no_argument, 0, 'I'},
        {"triangle", no_argument, 0, 'T'},
        {"color", required_argument, 0, 'c'},
        {"points", required_argument, 0, 'p'},
        {"thickness", required_argument, 0, 't'},
        {"fill", no_argument, 0, 'f'},
        {"fill_color", required_argument, 0, 'F'},
        {"biggest_rect", no_argument, 0, 'b'},
        {"old_color", required_argument, 0, 'O'},
        {"new_color", required_argument, 0, 'n'},
        {"collage", no_argument, 0, 'C'},
        {"number_x", required_argument, 0, 'x'},
        {"number_y", required_argument, 0, 'y'},
        {"binarization", no_argument, 0, 'z'},
        {"threshold", required_argument, 0, 'Z'},
        {"shift", no_argument, 0, 'S'},
        {"step", required_argument, 0, 's'},
        {"axis", required_argument, 0, 'a'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ho:i:ITc:p:t:fF:bO:n:Cx:y:zZ:s:a:S", long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                display_help();
                return;
            case 'o':
                output_flag++;
                output_file_name = optarg;
                break;
            case 'i':
                input_flag++;
                input_file_name = optarg;
                break;
            case 'I':
                info_flag++;
                break;
            case 'T':
                triangle_flag++;
                break;
            case 'c':
                color_flag++;
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3) {
                    fprintf(stdout, "Неверный формат цвета. Используйте формат rrr.ggg.bbb.\n");
                    exit(45);
                }
                color_triangle = check_color(r, g, b);
                break;
            case 'p':
                points_flag++;
                sscanf(optarg, "%d.%d.%d.%d.%d.%d", &x1, &y1, &x2, &y2, &x3, &y3);
                break;
            case 't':
                thickness_flag++;
                thickness = atoi(optarg);
                if (thickness <= 0) {
                    fprintf(stdout, "Неверная толщина линии\n");
                    exit(45);
                }
                break;
            case 'f':
                fill_flag++;
                break;
            case 'F':
                fill_color_flag++;
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3) {
                    fprintf(stdout, "Неверный формат цвета. Используйте формат rrr.ggg.bbb.\n");
                    exit(45);
                }
                fill_color = check_color(r, g, b);
                break;
            case 'b':
                rect_flag++;
                break;
            case 'O':
                old_color_flag++;
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3) {
                    fprintf(stdout, "Неверный формат цвета. Используйте формат rrr.ggg.bbb.\n");
                    exit(45);
                }
                old_color = check_color(r, g, b);
                break;
            case 'n':
                new_color_flag++;
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3) {
                    fprintf(stdout, "Неверный формат цвета. Используйте формат rrr.ggg.bbb.\n");
                    exit(45);
                }
                new_color = check_color(r, g, b);
                break;
            case 'C':
                collage_flag++;
                break;
            case 'x':
                x_flag++;
                x = atoi(optarg);
                if (x <= 0) {
                    fprintf(stdout, "Неверное количество повторений\n");
                    exit(45);
                }
                break;
            case 'y':
                y_flag++;
                y = atoi(optarg);
                if (y <= 0) {
                    fprintf(stdout, "Неверное количество повторений\n");
                    exit(45);
                }
                break;
            case 'z':
                bin_flag++;
                break;
            case 'Z':
                threshold_flag++;
                porog = atoi(optarg);
                if (porog <= 0) {
                    fprintf(stdout, "Неверное пороговое значение\n");
                    exit(45);
                }
                break;
            case 's':
                step_flag++;
                step = atoi(optarg);
                if (step <= 0) {
                    fprintf(stdout, "Неверное значение\n");
                    exit(45);
                }
                break;
            case 'a':
                axis_flag++;
                axis = optarg;
                break;
            case 'S':
                shift_flag++;
                break;
            default:
                fprintf(stdout, "Неверный флаг.\n");
                exit(45);
        }
    }

    if (optind < argc && input_file_name == NULL) {
        if (strcmp(argv[optind], output_file_name) == 0) {
            fprintf(stdout, "Имя входного файла и имя выходного файла не должны совпадать.\n");
            exit(45);
        }
        input_file_name = argv[optind];
    }

    if (input_file_name == NULL) {
        fprintf(stdout, "Входной файл не указан.\n");
        exit(45);
    }

    BitmapFileHeader *bmfh = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *bmif = malloc(sizeof(BitmapInfoHeader));

    if (info_flag) {
        show_info(bmfh, bmif);
        free(bmfh);
        free(bmif);
        return;
    }

    if (check_bmp(input_file_name, bmfh, bmif)) {
        Rgb **arr = read_bmp(input_file_name, bmfh, bmif);
        unsigned int H = bmif->height;
        unsigned int W = bmif->width;

        if (triangle_flag) {
            if (!(color_flag && thickness_flag && points_flag)) {
                fprintf(stdout, "Необходимо указать все параметры для флага --triangle.\n");
                exit(45);
            }
            if (fill_flag && fill_color_flag) {
                fill_tr(arr, fill_color, x1, y1, x2, y2, x3, y3, H, W);
            }
            triangle(x1, y1, x2, y2, x3, y3, thickness, H, W, arr, color_triangle);
        }

        if (rect_flag) {
            if (!(old_color_flag && new_color_flag)) {
                fprintf(stdout, "Необходимо указать все параметры для флага --biggest_rect.\n");
                exit(45);
            }
            find_color_max_rect(H, W, arr, old_color, new_color);
        }
        if (collage_flag) {
            if (!(x_flag && y_flag)) {
                fprintf(stdout, "Необходимо указать все параметры для флага --collage.\n");
                exit(45);
            }
            arr = collage(x, y, H, W, bmfh, bmif, arr);
        }

        if (bin_flag && threshold_flag) {
            do_bin(arr, H, W, porog);
        }

        if (shift_flag && axis_flag && step_flag) {
            if (strcmp(axis, "x") == 0) {
                shift(arr, H, W, step, 0);
            } else if (strcmp(axis, "y") == 0) {
                shift(arr, H, W, 0, step);
            } else if (strcmp(axis, "xy") == 0) {
                shift(arr, H, W, step, step);
            } else {
                fprintf(stdout, "Неверное значение оси.\n");
                exit(45);
            }
        }

        write_bmp(output_file_name, bmfh, bmif, arr);

        for (unsigned int i = 0; i < H; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    free(bmfh);
    free(bmif);
}