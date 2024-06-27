#include "input.h"
#include "functions.h"
#include "checker.h"

int main(int argc, char **argv) {
    printf("Course work for option 5.17, created by Marina Konyaeva.\n");
    if (argc <= 1) {
        print_help();
        return 0;
    }

    struct Png img;
    struct Configs conf;
    struct Flags flag;

    create_default(&conf);
    create_defaut_for_flags(&flag);
    
    int opt;
    int long_opt_index = 0;
    int key = -1;
    int write_fl = 0;
    char *optstring = "i:o:h";
    struct option long_options[] = {
            {"circle", no_argument, NULL, 'c'},
            {"rgbfilter", no_argument, NULL, 'r'},
            {"split", no_argument, NULL, 's'},
            {"squared_lines", no_argument, NULL, 'l'},

            {"help", no_argument, NULL, 'h'},
            {"info", required_argument, NULL, 'f'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},

            {"center", required_argument, NULL, 'A'},
            {"radius", required_argument, NULL, 'B'},
            {"thickness", required_argument, NULL, 'Z'},
            {"color", required_argument, NULL, 'D'},
            {"fill", no_argument, NULL, 'E'},
            {"fill_color", required_argument, NULL, 'Q'},

            {"component_name", required_argument, NULL, 'W'},
            {"component_value", required_argument, NULL, 'Y'},

            {"number_x", required_argument, NULL, 'R'},
            {"number_y", required_argument, NULL, 'T'},

            {"left_up", required_argument, NULL, 'A'},
            {"side_size", required_argument, NULL, 'P'},

            {"rhombus,", no_argument, NULL, 'x'},
            {NULL, 0, NULL, 0}
    };
    opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);

    char *pch;
    int input_flag = 0;
    int output_flag = 0;
    char input_file[255];
    char output_file[255];

    int circle_param_c = 0;
    int filter_param_c = 0;
    int split_param_c = 0;
    int square_param_c = 0;

    while (opt != -1) {
        switch (opt) {
            case 'h':
                no_argschecker(argv[optind],"--help");
                print_help();
                return 0;
            case 'c':
                no_argschecker(argv[optind],"--circle");
                key = 'c';
                break;
            case 'r':
                no_argschecker(argv[optind],"--rgbfilter");
                key = 'r';
                break;
            case 's':
                no_argschecker(argv[optind],"--split");
                key = 's';
                break;
            case 'l':
                no_argschecker(argv[optind],"--squared_lines");
                key = 'l';
                break;
            case 'x':
                key = 'x';
                break;
            case 'i':
                input_flag = 1;
                strcpy(input_file, optarg);
                break;
            case 'o':
                output_flag = 1;
                strcpy(output_file, optarg);
                break;
            case 'f':
                read_png_file(optarg, &img);
                print_png_info(&img);
                free_image_data(&img);
                return 0;
                break;
            case 'A':
                coords_checker(optarg);

                pch = strtok (optarg,".");
                conf.x_y[0] = atoi(pch);
                pch = strtok (NULL, " ");
                conf.x_y[1] = atoi(pch);
                
                flag.x_y = 1;
                break;
            case 'B':
                distance_checker(optarg);
                conf.radius = atoi(optarg);
                flag.radius = 1;
                break;
            case 'Z':
                distance_checker(optarg);
                conf.thickness = atoi(optarg);
                flag.thickness = 1;
                break;
            case 'D': 
                color_checker(optarg);
                conf.color = parse_color(optarg);  
                flag.color = 1;
                break;
            case 'E':
                conf.fill = 1;
                break;
            case 'Q':       
                color_checker(optarg);
                conf.fill_color = parse_color(optarg);
                break;    
            case 'W':
                conf.component_name = optarg;
                flag.component_name = 1;
                break;
            case 'Y':
                conf.component_value = atoi(optarg);
                flag.component_value = 1;
                break;
            case 'R':
                distance_checker(optarg);
                conf.number_x = atoi(optarg);
                flag.number_x = 1;
                break;
            case 'T':
                distance_checker(optarg);
                conf.number_y = atoi(optarg);
                flag.number_y = 1;
                break;
            case 'P':
                distance_checker(optarg);
                conf.side_size = atoi(optarg);
                flag.side_size = 1;
                break;
            case '?':
                printf("Arguments entered incorrectly.\n");
                return 0;
            default:
                break;
        };
        opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);
    }

    if (!input_flag){
        input_flag = 1;
        strcpy(input_file, argv[argc - 1]);
    }
    if (!output_flag){
        output_flag = 1;
        strcpy(output_file, "out.png");
    }

    names_checker(input_file, output_file);
    read_png_file(input_file, &img);

    switch (key) {
        case 'c':
            if (!flag.x_y || !flag.radius || !flag.thickness || !flag.color) {
                printf("Not enough arguments have been entered to draw a circle.\n");
                return 0;
            }
            draw_circle(&img, conf.x_y, conf.radius, conf.thickness, conf.color, conf.fill, conf.fill_color);
            write_png_file(output_file, &img);
            break;
        case 'r':
            if (!flag.component_name || !flag.component_value){
                printf("Not enough arguments have been entered to switch filter.\n");
                return 0;
            }
            switch_filter(&img, conf.component_name, conf.component_value);
            write_png_file(output_file, &img);
            break;
        case 's':
            if (!flag.number_x || !flag.number_y || !flag.thickness || !flag.color){
                printf("Not enough arguments have been entered to split image.\n");
                return 0;
            }
            divide_image(&img, conf.number_x, conf.number_y, conf.thickness, conf.color);
            write_png_file(output_file, &img);
            break;
        case 'l':
            if (!flag.x_y || !flag.side_size || !flag.thickness || !flag.color){
                printf("Not enough arguments have been entered to draw a square.\n");
                return 0;
            }
            draw_square(&img, conf.x_y, conf.side_size, conf.thickness, conf.color, conf.fill, conf.fill_color);
            write_png_file(output_file, &img);
            break;
        case 'x':
            test(&img, img.width/2 , 0, 0, img.height/2, img.width/2, img.height, conf.color);
            test(&img, img.width/2, 0, img.width, img.height/2, img.width/2, img.height, conf.color);
            write_png_file(output_file, &img);
            break;
        default:
            printf("Arguments entered incorrectly.\n");
            return 0;
    };

    free_conf(&conf);
    return 0;
}



