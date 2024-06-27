#include "call_func.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "split.h"
#include "print_usage.h"
#include "rotate.h"
#include "rect.h"
#include "ornament.h"
#include "edge.h"
#include "edge_alina.h"
#include "outside_ornament.h"
#include "tiles.h"
#include "rhombus.h"

struct option long_opt[] = {
        {"split", no_argument, 0, 's'},
        {"rect", no_argument, 0, 'e'},
        {"rotate", no_argument, 0, 'r'},
        {"ornament", no_argument, 0, 'n'},
        {"info", no_argument, 0, 'i'},
        {"help", no_argument, 0, 'h'},
        {"left_up", required_argument, 0, 'u'},
        {"right_down", required_argument, 0, 'd'},
        {"angle", required_argument, 0, 'z'},
        {"fill", no_argument, 0, 'f'},

        {"number_x", required_argument, 0, 'x'},
        {"number_y", required_argument, 0, 'y'},

        {"thickness", required_argument, 0, 't'},
        {"color", required_argument, 0, 'c'},
        {"fill_color", required_argument, 0, 'j'},
        {"pattern", required_argument, 0, 'p'},
        {"count", required_argument, 0, 'w'},

        {"input", required_argument, 0, 'a'},
        {"output", required_argument, 0, 'o'},
        {"edge", no_argument, 0, 'k'},
        {"outside_ornament", no_argument, 0, 'g'},
        {"tiles", no_argument, 0, 'j'},
        {"rhombus", no_argument, 0, 'l'},
        {0, no_argument, 0, 0}
};

png_bytepp call_split(int argc, char **argv, image_data image) {
    int c, option_index;
    char *x, *y, *thickness, *color;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "x:y:t:c:", long_opt, &option_index);
        switch(c) {
            case 'x':
                x = optarg;
                break;
            case 'y':
                y = optarg;
                break;
            case 't':
                thickness = optarg;
                break;
            case 'c':
                color = optarg;
                break;
            case '?':
                printf("[call_split()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    long int_x, int_y, int_thickness;
    pixel RGB;

    if(x && y && color && thickness) {
        RGB = parse_color(color);
        char *endptr;
        int_x = strtol(x, &endptr, 10);
        int_y = strtol(y, &endptr, 10);
        int_thickness = strtol(thickness, &endptr, 10);

        if(int_x <= 1) {
            return (png_bytepp)image.rows;
        }

        if(int_y <= 1) {
            return (png_bytepp)image.rows;
        }

        if(int_thickness <= 0) {
            return (png_bytepp)image.rows;
        }

        return split(int_x, int_y, RGB, int_thickness, image);
    }
    else {
        printf("[call_split()]: некоторые аргументы отсутствуют.\n");
        print_usage();
        exit(40);
    }
}

png_bytepp call_ornament(int argc, char **argv, image_data image) {
    int c, option_index;
    optind = 1;
    char *pattern = NULL, *color = NULL, *thickness = NULL, *count = NULL;
    do {
        c = getopt_long(argc, argv, "p:c:t:w:", long_opt, &option_index);
        switch(c) {
            case 'p':
                pattern = optarg;
                break;
            case 'c':
                color = optarg;
                break;
            case 't':
                thickness = optarg;
                break;
            case 'w':
                count = optarg;
                break;
            case '?':
                printf("[call_ornament()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    long int_count, int_thickness;
    pixel RGB;

    if(pattern && color && thickness && count) {
        char *endptr;

        int_count = strtol(count, &endptr, 10);
        int_thickness = strtol(thickness, &endptr, 10);

        if (int_count < 1 || int_thickness < 1) {
            return (png_bytepp)image.rows;
        }
        RGB = parse_color(color);
        return ornament(pattern, int_count, RGB, int_thickness, image);

    }
    else {
        printf("[call_ornament()] некоторые аргументы отсутствуют.\n");
        print_usage();
        exit(40);
    }
}

png_bytepp call_rect(int argc, char **argv, image_data image) {
    int c, option_index;
    optind = 1;
    char *left_up = NULL, *right_down = NULL, *thickness = NULL, *color = NULL, *fill = NULL, *fill_color = NULL;
    pixel RGB, RGB_f;

    do {
        c = getopt_long(argc, argv, "u:d:t:c:fh:", long_opt, &option_index);
        switch(c) {
            case 'u':
                left_up = optarg;
                break;
            case 'd':
                right_down = optarg;
                break;
            case 't':
                thickness = optarg;
                break;
            case 'c':
                color = optarg;
                RGB = parse_color(color);
                break;
            case 'f':
                fill = "True";
                break;
            case 'j':
                fill_color = optarg;
                RGB_f = parse_color(fill_color);
                break;
            case '?':
                printf("[call_rect()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    if(left_up && right_down && thickness && color) {
        char *endptr;
        long left_up_x, left_up_y, right_down_x, right_down_y;

        left_up_x = strtol(left_up, &endptr, 10);

        if (endptr + 1)
            left_up_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет left_up_y координаты\n");
            print_usage();
            exit(40);
        }

        right_down_x = strtol(right_down, &endptr, 10);
        if (endptr + 1)
            right_down_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет right_down_y координаты\n");
            print_usage();
            exit(40);
        }

        long int_thickness = strtol(thickness, &endptr, 10);

        if (int_thickness < 1) {
            return (png_bytepp)image.rows;
        }

        if(right_down_x > left_up_x) {
            long temp;
            temp = right_down_x;
            right_down_x = left_up_x;
            left_up_x = temp;
        }
        if(right_down_y > left_up_y) {
            long temp;
            temp = right_down_y;
            right_down_y = left_up_y;
            left_up_y = temp;
        }

        return rect(right_down_x, right_down_y, left_up_x, left_up_y, int_thickness, RGB, fill, RGB_f, image, 0);
    }
    else {
        printf("[call_rect()] некоторые аргументы отсутствуют.\n");
        print_usage();
        exit(40);
    }
}

png_bytepp call_rotate(int argc, char **argv, image_data image) {
    int c, option_index;
    char *left_up = NULL, *right_down = NULL, *angle = NULL;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "u:d:z:", long_opt, &option_index);
        switch(c) {
            case 'u':
                left_up = optarg;
                break;
            case 'd':
                right_down = optarg;
                break;
            case 'z':
                angle = optarg;
                break;
            case '?':
                printf("[call_rotate()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);
    if(left_up && right_down && angle) {
        char *endptr;
        long left_up_x, left_up_y, right_down_x, right_down_y, int_angle;

        left_up_x = strtol(left_up, &endptr, 10);

        if (endptr + 1)
            left_up_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет left_up_y координаты\n");
            print_usage();
            exit(40);
        }

        right_down_x = strtol(right_down, &endptr, 10);
        if (endptr + 1)
            right_down_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет right_down_y координаты\n");
            print_usage();
            exit(40);
        }

        int_angle = strtol(angle, &endptr, 10);

        if (int_angle != 90 && int_angle != 180 && int_angle != 270) {
            printf("[call_rotate()] неверное значение angle, должно быть 90, 180 или 270.\n");
            exit(40);
        }

        if(right_down_x < left_up_x || right_down_y < left_up_y || left_up_x >= image.width || left_up_y >= image.height) {
            return (png_bytepp)image.rows;
        }

        return rotate(left_up_x, left_up_y, right_down_x, right_down_y, int_angle, image);
    }
    else {
        printf("[call_rotate()] некоторые аргументы отсутствуют.\n");
        print_usage();
        exit(40);
    }
}

png_bytepp call_edge(int argc, char **argv, image_data image) {
    int c, option_index;
    char *color, *fill_color;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "x:y:t:c:", long_opt, &option_index);
        switch(c) {
            case 'c':
                color = optarg;
                break;
            case 'j':
                fill_color = optarg;
                break;
            case '?':
                printf("[call_edge()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    pixel color_RGB = parse_color(color),
          fill_RGB = parse_color(fill_color);

    return edge_alina(image, color_RGB, fill_RGB);
}

png_bytepp call_outside_ornament(int argc, char **argv, image_data image) {
    int c, option_index;
    char *color = NULL, *thickness = NULL;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "c:t:", long_opt, &option_index);
        switch(c) {
            case 'c':
                color = optarg;
                break;
            case 't':
                thickness = optarg;
                break;
            case '?':
                printf("[call_edge()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);
    if(thickness && color) {
        pixel color_RGB = parse_color(color);
        char *endptr;
        long int_thickness = strtol(thickness, &endptr, 10);
        return outside_ornament(image, color_RGB, int_thickness);
    }
    else {
        exit(40);
    }
}

png_bytepp call_tiles(int argc, char **argv, image_data image) {
    int c, option_index;
    char *left_up = NULL, *right_down = NULL;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "u:d:z:", long_opt, &option_index);
        switch(c) {
            case 'u':
                left_up = optarg;
                break;
            case 'd':
                right_down = optarg;
                break;
            case '?':
                printf("[call_rotate()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);
    if(left_up && right_down) {
        char *endptr;
        long left_up_x, left_up_y, right_down_x, right_down_y;

        left_up_x = strtol(left_up, &endptr, 10);

        if (endptr + 1)
            left_up_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет left_up_y координаты\n");
            print_usage();
            exit(40);
        }

        right_down_x = strtol(right_down, &endptr, 10);
        if (endptr + 1)
            right_down_y = strtol(endptr + 1, &endptr, 10);
        else {
            printf("[call_rotate()] нет right_down_y координаты\n");
            print_usage();
            exit(40);
        }


        if(right_down_x < left_up_x || right_down_y < left_up_y || left_up_x >= image.width || left_up_y >= image.height) {
            return (png_bytepp)image.rows;
        }

        return tiles(image, left_up_x, left_up_y, right_down_x, right_down_y);
    }
    else {
        printf("[call_rotate()] некоторые аргументы отсутствуют.\n");
        print_usage();
        exit(40);
    }
}

png_bytepp call_rhombus(int argc, char **argv, image_data image) {
    int c, option_index;
    char *color, *fill_color;
    optind = 1;
    do {
        c = getopt_long(argc, argv, "c:", long_opt, &option_index);
        switch(c) {
            case 'c':
                color = optarg;
                break;
            case '?':
                printf("[call_rhombus()] была введена неподдерживаемая опция\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);

    pixel color_RGB = parse_color(color);
    return rhombus(image, color_RGB);
}

png_bytepp call_func(int argc, char **argv, image_data image) {
    int c, option_index;
    optind = 1; /* необходимо для того, чтобы заново пройтись по аргументам */

    do {
        c = getopt_long(argc, argv, "sernikg", long_opt, &option_index);
        switch (c) {
            case 's':
                return call_split(argc, argv, image);
            case 'e':
                return call_rect(argc, argv, image);
            case 'r':
                return call_rotate(argc, argv, image);
            case 'n':
                return call_ornament(argc, argv, image);
//            case 'k':
//                return call_edge(argc, argv, image);
//            case 'g':
//                return call_outside_ornament(argc, argv, image);
//            case 'j':
//                return call_tiles(argc, argv, image);
            case 'l':
                return call_rhombus(argc, argv, image);
            case 'i':
                return NULL;
            case '?':
                printf("[call_func()] не удалось распознать опцию.\n");
                print_usage();
                exit(40);
            case -1:
                printf("Введите опцию.\n\n");
                print_usage();
                exit(40);
            default:
                break;
        }
    } while(c != -1);
}
