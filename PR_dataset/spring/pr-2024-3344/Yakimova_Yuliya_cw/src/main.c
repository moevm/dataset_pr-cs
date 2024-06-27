#include "input.h"
#include "functions.h"

int main(int argc, char **argv) {
    printf("Course work for option 5.16, created by Yakimova Yuliya.\n");

    if (argc <= 1){
        print_help();
        return 0;
    }

    struct Png image;
    struct Color colors;
    struct Copy copy;
    struct Ornament ornam;
    struct Filled_Rect rect;
    struct Circle_Pix pix;

    //для getopt_long()
    int opt; 
    int long_opt_index = 0;
    char *short_opts = "i:o:h";
    struct option long_opts[] = {
            {"copy", no_argument, NULL, 'c'},
            {"color_replace", no_argument, NULL, 'r'},
            {"ornament", no_argument, NULL, 'b'},
            {"filled_rects", no_argument, NULL, 'f'},
            {"circle_pixel", no_argument, NULL, 'p'},

            {"help", no_argument, NULL, 'h'},
            {"info", required_argument, NULL, 'n'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},

            {"left_up", required_argument, NULL, 'A'},
            {"right_down", required_argument, NULL, 'B'},
            {"dest_left_up", required_argument, NULL, 'D'},

            {"old_color", required_argument, NULL, 'O'},
            {"new_color", required_argument, NULL, 'N'},

            {"pattern", required_argument, NULL, 'P'},
            {"color", required_argument, NULL, 'C'},
            {"thickness", required_argument, NULL, 'T'},
            {"count", required_argument, NULL, 'X'},

            {"border_color", required_argument, NULL, 'R'},

            {"size", required_argument, NULL, 'S'},
            {"circle_color", required_argument, NULL, 'L'},
            {NULL, 0, NULL, 0}
    };
    opt = getopt_long(argc, argv, short_opts, long_opts, &long_opt_index);

    int key = -1;
    int input_flag = 0;
    int output_flag = 0;
    char input_file[255];
    char output_file[255];
    while (opt != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'c':
                no_argschecker(argv[optind],"--copy");
                key = 'c';
                break;
            case 'r':
                no_argschecker(argv[optind],"--color_replace");
                key = 'r';
                break;
            case 'b':
                no_argschecker(argv[optind],"--ornament");
                key = 'b';
                break;
            case 'f':
                no_argschecker(argv[optind],"--filled_rects");
                key = 'f';
                break;
            case 'p':
                no_argschecker(argv[optind], "--circle_pixel");
                key = 'p';
                break;
            case 'i':
                input_flag = 1;
                strcpy(input_file, optarg);  //копирует значение следующего аргумента командной строки в input_file
                break;
            case 'o':
                output_flag = 1;
                strcpy(output_file, optarg);
                break;
            case 'n':
                read_png_file(optarg, &image);
                print_png_info(&image);
                free_image_data(&image);
                return 0;
            case 'O':
                colors.old_color = optarg;
                colors.old_color_f = 1;
                break;
            case 'N':
                colors.new_color = optarg;
                colors.new_color_f = 1;
                break;
            case 'A':
                copy.left_up = optarg;
                copy.left_up_f = 1;
                break;
            case 'B':
                copy.right_down = optarg;
                copy.right_down_f = 1;
                break;
            case 'D':
                copy.dest_left_up = optarg;
                copy.dest_left_up_f = 1;
                break;
            case 'P':
                ornam.pattern = optarg;
                ornam.pattern_f = 1;
                break;
            case 'C':
                ornam.color = optarg;
                ornam.color_f = 1;
                rect.color = optarg;
                rect.color_f = 1;
                pix.color = optarg;
                pix.color_f = 1;
                break;
            case 'T':
                ornam.thickness = optarg;
                ornam.thickness_f = 1;
                rect.thickness = optarg;
                rect.thickness_f = 1;
                break;
            case 'X':
                ornam.count = optarg;
                ornam.count_f = 1;
                break;
            case 'R':
                rect.border_color = optarg;
                rect.border_color_f = 1;
                break;
            case 'S':
                pix.size = optarg;
                pix.size_f = 1;
                break;
            case 'L':
                pix.circle_color = optarg;
                pix.circle_color_f = 1;
                break;
            case '?':
                print_help();
                return 0;
            default:
                break;
        };
        opt = getopt_long(argc, argv, short_opts, long_opts, &long_opt_index);
    }

    if (!input_flag){
        input_flag = 1;
        strcpy(input_file, argv[argc - 1]);
    }
    if (!output_flag){
        output_flag = 1;
        strcpy(output_file, "out.png");
    }
    if (strcmp(input_file, output_file)==0){
        printf("Input and output file names cannot be the same\n");
        return 0;
    }

    read_png_file(input_file, &image);

    switch (key) {
        case 'c':
            if (!copy.left_up_f || !copy.right_down_f || !copy.dest_left_up_f) {
                printf("Too few arguments have been entered to copy.\n");
                return 0;
            }
            copy_img(&image, copy.left_up, copy.right_down, copy.dest_left_up);
            write_png_file(output_file, &image);
            break;
        case 'r':
            if (!colors.new_color_f || !colors.old_color_f){
                printf("Too few arguments have been entered to replace color.\n");
                return 0;
            }
            replace_color(&image, colors.new_color, colors.old_color);
            write_png_file(output_file, &image);
            break;
        case 'b': //ornament
            if (!ornam.pattern_f) {
                printf("The pattern must be entered.\n");
                return 0;
            }
            if ((strcmp(ornam.pattern, "rectangle") != 0) && (strcmp(ornam.pattern, "circle") != 0) && (strcmp(ornam.pattern, "semicircles") != 0)) {
                printf("The pattern must be `rectangle`, `circle` or `semicircles`.\n");
                exit(41);
            }
            if (!strcmp(ornam.pattern, "rectangle")) {
                if (!ornam.color_f || !ornam.thickness_f || !ornam.count_f) {
                    printf("Too few arguments have been entered to create an ornament.\n");
                    return 0;
                }
                create_rect_ornam(&image, ornam.color, ornam.thickness, ornam.count);
            }
            if (!strcmp(ornam.pattern, "circle")) {
                if(!ornam.color_f) {
                    printf("The color has to be entered to create an ornament.\n");
                    return 0;
                }
                create_circle_ornam(&image, ornam.color);
            }
            if (!strcmp(ornam.pattern, "semicircles")) {
                if (!ornam.color_f || !ornam.thickness_f || !ornam.count_f) {
                    printf("Too few arguments have been entered to create an ornament.\n");
                    return 0;
                }
                create_semicir_ornam(&image, ornam.color, ornam.thickness, ornam.count);
            }
            write_png_file(output_file, &image);
            break;
        case 'f':
            if (!rect.color_f || !rect.border_color_f || !rect.thickness_f) {
                printf("Too few arguments have been entered to trace the rectangles.\n");
                return 0;
            }
            trace_rects(&image, rect.color, rect.border_color, rect.thickness);
            write_png_file(output_file, &image);
            break;
        case 'p':
            if(!pix.circle_color_f || !pix.color_f || !pix.size_f) {
                printf("Too few arguments have been entered to circle the pixels.\n");
                return 0;
            }
            circle_pix(&image, pix.circle_color, pix.color, pix.size);
            write_png_file(output_file, &image);
            break;
        default:
            printf("Arguments have been entered incorrectly.\n");
            return 0;
    };
}
