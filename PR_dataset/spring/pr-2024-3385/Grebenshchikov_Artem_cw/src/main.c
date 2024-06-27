#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <getopt.h>
#include "cw.h"



int main(int argc, char **argv) {
    if (argc <= 1) {
        print_help();
        return 0;
    }
    Png img, new_img;
    args params;
    flags storing_flags = {0,0,0,0,0,0,0,0,0,0};
    int opt, key = 'h', long_opt_index = 0;
    char *optstring = "hi:o:ftp:T:C:FK:bcy:x:ls:e:Pn:";
    struct option long_options[] = {
            {"help", no_argument, NULL, 'h'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},
            {"info", no_argument, NULL, 'f'},
            {"triangle", no_argument, NULL, 't'},
            {"points", required_argument, NULL, 'p'},
            {"thickness", required_argument, NULL, 'T'},
            {"color", required_argument, NULL, 'C'},
            {"fill", no_argument, NULL, 'F'},
            {"fill_color", required_argument, NULL, 'K'},
            {"biggest_rect", no_argument, NULL, 'b'},
            {"old_color", required_argument, NULL, 'C'},
            {"new_color", required_argument, NULL, 'K'},
            {"collage", no_argument, NULL, 'c'},
            {"number_y", required_argument, NULL, 'y'},
            {"number_x", required_argument, NULL, 'x'},
            {"line", no_argument, NULL, 'l'},
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},
            {"compress", no_argument, NULL, 'P'},
            {"num", required_argument, NULL, 'n'},
            {0, 0, 0, 0}
    };
    opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);
    char input_file[256], output_file[256];
    strcpy(output_file, "out.png");
    opterr = 0;
    while (opt != -1) {
        switch (opt) {
            case 'h':
                check_extra_arg(argv[optind], "-help", 0, optind, argc, storing_flags.input_file);
                if (storing_flags.main_flag) {
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'h';
                break;
            case 'i':
                check_extra_arg(argv[optind], "-input", 1, optind, argc, storing_flags.input_file);
                storing_flags.input_file++;
                strcpy(input_file, optarg);
                break;
            case 'o':
                check_extra_arg(argv[optind], "-output", 1, optind, argc, storing_flags.input_file);
                strcpy(output_file, optarg);
                break;
            case 'f':
                check_extra_arg(argv[optind], "-info", 0, optind, argc, storing_flags.input_file);
                if (storing_flags.main_flag) {
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'f';
                break;
            case 't':
                check_extra_arg(argv[optind], "-triangle", 0, optind, argc, storing_flags.input_file);
                if(storing_flags.main_flag){
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 't';
                break;
            case 'P':
                check_extra_arg(argv[optind], "-", 0, optind, argc, storing_flags.input_file);
                if(storing_flags.main_flag){
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'P';
                break;
            case 'n':
                check_extra_arg(argv[optind], "-", 1, optind, argc, storing_flags.input_file);
                if (is_digit(optarg)) {
                    printf("Thickness is not a number.\n");
                    exit(40);
                }
                params.thickness = atoi(optarg);
                if (params.thickness <= 1) {
                    printf("The must be a natural number.\n");
                    exit(40);
                }
                storing_flags.num++;
                break;
            case 'p':
                check_extra_arg(argv[optind], "-points", 1, optind, argc, storing_flags.input_file);
                int* arr_coord = string_tok(optarg, 6);
                params.xy1[0] = arr_coord[0];
                params.xy1[1] = arr_coord[1];
                params.xy2[0] = arr_coord[2];
                params.xy2[1] = arr_coord[3];
                params.xy3[0] = arr_coord[4];
                params.xy3[1] = arr_coord[5];
                storing_flags.points++;
                free(arr_coord);
                break;
            case 'T':
                check_extra_arg(argv[optind], "-thickness", 1, optind, argc, storing_flags.input_file);
                if (is_digit(optarg)) {
                    printf("Thickness is not a number.\n");
                    exit(40);
                }
                params.thickness = atoi(optarg);
                if (params.thickness <= 0) {
                    printf("The thickness must be a natural number.\n");
                    exit(40);
                }
                storing_flags.tickness++;
                break;
            case 'C':
                check_extra_arg(argv[optind], "-color/-old_color", 1, optind, argc, storing_flags.input_file);
                int* arr_color = string_tok(optarg, 3);
                params.base_color[0] = arr_color[0];
                params.base_color[1] = arr_color[1];
                params.base_color[2] = arr_color[2];
                if (params.base_color[0] < 0 || params.base_color[0] > 255 || params.base_color[1] < 0 ||
                    params.base_color[1] > 255 || params.base_color[2] < 0 || params.base_color[2] > 255) {
                    printf("The entered color is incorrect.\n");
                    exit(40);
                }
                storing_flags.color++;
                free(arr_color);
                break;
            case 'F':
                check_extra_arg(argv[optind], "-fill", 0, optind, argc, storing_flags.input_file);
                storing_flags.fill = 1;
                break;
            case 'K':
                check_extra_arg(argv[optind], "-fill_color/-new_color", 1, optind, argc, storing_flags.input_file);
                int* arr_color_fill = string_tok(optarg, 3);
                params.fill_color[0] = arr_color_fill[0];
                params.fill_color[1] = arr_color_fill[1];
                params.fill_color[2] = arr_color_fill[2];
                if (params.fill_color[0] < 0 || params.fill_color[0] > 255 || params.fill_color[1] < 0 || 
                    params.fill_color[1] > 255 || params.fill_color[2] < 0 || params.fill_color[2] > 255) {
                    printf("The entered color is incorrect.\n");
                    exit(40);
                }
                storing_flags.fill_or_new_color++;
                free(arr_color_fill);
                break;
            case 'b':
                check_extra_arg(argv[optind], "-biggest_rect", 0, optind, argc, storing_flags.input_file);
                if(storing_flags.main_flag){
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'b';
                break;
            case 'c':
                check_extra_arg(argv[optind], "-collage", 0, optind, argc, storing_flags.input_file);
                if(storing_flags.main_flag){
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'c';
                break;
            case 'y':
                check_extra_arg(argv[optind], "-number_y", 1, optind, argc, storing_flags.input_file);
                if (is_digit(optarg)) {
                    printf("Height is not a number.\n");
                    exit(40);
                }
                params.number_y = atoi(optarg);
                if (params.number_y <= 0) {
                    printf("The number_y of the collage cannot be negative or 0.\n");
                    exit(40);
                }
                storing_flags.end_or_number_y++;
                break;
            case 'x':
                check_extra_arg(argv[optind], "-number_x", 1, optind, argc, storing_flags.input_file);
                if (is_digit(optarg)) {
                    printf("Width is not a number.\n");
                    exit(40);
                }
                params.number_x = atoi(optarg);
                if (params.number_x <= 0) {
                    printf("The number_x of the collage cannot be negative or 0.\n");
                    exit(40);
                }
                storing_flags.start_or_number_x++;
                break;
            case 'l':
                check_extra_arg(argv[optind], "-line", 0, optind, argc, storing_flags.input_file);
                if(storing_flags.main_flag){
                    printf("Choose one command\n");
                    exit(40);
                }
                storing_flags.main_flag++;
                key = 'l';
                break;
            case 's':
                check_extra_arg(argv[optind], "-start", 1, optind, argc, storing_flags.input_file);
                int* arr_xy1 = string_tok(optarg, 2);
                params.xy1[0] = arr_xy1[0];
                params.xy1[1] = arr_xy1[1];
                storing_flags.start_or_number_x++;
                free(arr_xy1);
                break;
            case 'e':
                check_extra_arg(argv[optind], "-end", 1, optind, argc, storing_flags.input_file);
                int* arr_xy2 = string_tok(optarg, 2);
                params.xy2[0] = arr_xy2[0];
                params.xy2[1] = arr_xy2[1];
                storing_flags.end_or_number_y++;
                free(arr_xy2);
                break;
            case '?':
                fprintf(stderr, "Arguments entered incorrectly.\n");
                return 0;
            default:
                break;
        }
        opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);
    }
    if(!strcmp(input_file, output_file)){
        printf("input file ‘%s’ is the same as output file\n", input_file);
        exit(40);
    }
    if (storing_flags.input_file == 0){
        strcat(input_file, argv[argc-1]);
    }
    switch (key) {
        case 't':
            if ((storing_flags.points + storing_flags.color + storing_flags.tickness) != 3) {
                printf("Not enough arguments have been entered to draw a triangle.\n");
                exit(40);
            }
            if (!is_triangle(params.xy1[0], params.xy1[1], params.xy2[0], params.xy2[1], params.xy3[0], params.xy3[1])) {
                printf("The entered coordinates of the tops do not form a triangle.\n");
                exit(40);
            }
            if ((storing_flags.fill + storing_flags.fill_or_new_color) == 1){
                printf("Оnly the 'fill' or 'fill_color' flag is applied\n");
                exit(40);   
            }
            read_png_file(input_file, &img);
            draw_triangle(&img, params.xy1[0], params.xy1[1], params.xy2[0], params.xy2[1], params.xy3[0], params.xy3[1], 
            params.thickness, params.base_color, storing_flags.fill, params.fill_color);
            write_png_file(output_file, &img);
            break;
        case 'b':
            if ((storing_flags.color + storing_flags.fill_or_new_color) != 2) {
                printf("Not enough arguments have been entered to recolor the largest rectangle.\n");
                exit(40);
            }
            read_png_file(input_file, &img);
            recolor_max_rectangle(&img, params.base_color, params.fill_color);
            write_png_file(output_file, &img);
            break;
        case 'c':
            if ((storing_flags.start_or_number_x + storing_flags.end_or_number_y) != 2) {
                printf("Not enough arguments have been entered to create a collage.\n");
                exit(40);
            }
            read_png_file(input_file, &img);
            make_collage(&img, &new_img, params.number_y, params.number_x);
            write_png_file(output_file, &new_img);
            free_image_data(&new_img);
            break;
        case 'l':
            if ((storing_flags.start_or_number_x + storing_flags.end_or_number_y + storing_flags.color + storing_flags.tickness) != 4) {
                printf("Not enough arguments have been entered to draw the line.\n");
                exit(40);
            }
            read_png_file(input_file, &img);
            draw_thick_line(&img, params.xy1[0], params.xy1[1], params.xy2[0], params.xy2[1], params.thickness, params.base_color);
            write_png_file(output_file, &img);
            break;
        case 'f':
            read_png_file(input_file, &img);
            print_png_info(&img);
            break;
        case 'h':
            print_help();
            return 0;
        case 'P':
            read_png_file(input_file, &img);
            if(storing_flags.num != 1){
                printf("Not enough arguments have been entered.\n");
                exit(40);
            }
            comr(&img,&new_img, params.thickness);
            write_png_file(output_file, &new_img);
            free_image_data(&new_img);
            return 0;
        default:
            fprintf(stderr, "Arguments entered incorrectly.\n");
            return 0;
    }
    free_image_data(&img);
    return 0;
}