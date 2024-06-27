#include "main.h"

struct option long_opts[] = {
    {"help", no_argument, NULL, 'e'},
    {"mirror", no_argument, NULL, 'm'},
    {"rect", no_argument, NULL, 'r'},
    {"pentagram", no_argument, NULL, 'p'},
    {"hexagon", no_argument, NULL, 'h'},
    {"paving", no_argument, NULL, 'a'},
    {"outside_rect", no_argument, NULL, 'u'},
    {"axis", required_argument, NULL, 'A'},
    {"left_up", required_argument, NULL, 'L'},
    {"right_down", required_argument, NULL, 'R'},
    {"center", required_argument, NULL, 'E'},
    {"radius", required_argument, NULL, 'D'},
    {"thickness", required_argument, NULL, 'T'},
    {"color", required_argument, NULL, 'C'},
    {"fill", no_argument, NULL, 'F'},
    {"fill_color", required_argument, NULL, 'I'},
    {"output", required_argument, NULL, 'o'},
    {"input", required_argument, NULL, 'n'},
    {NULL, 0, NULL, 0}
};

void print_help()
{
    puts(
        "Getting command and flags via the console\n"
        "pattern:\n"
        "(object file) (option) (flags for option) (input file)\n"
        "List of option:\n"
        "  --mirror - reflection is a part of the image along one of the axes. Flags: --axis, --left_up, --right_down\n"
        "  --pentagram - draws a five-pointed star in a circle. Flags: --center, --radius, --thickness, --color\n"
        "  --rect - drawing a square (filled in or not). Flags: --left_up, --right_down, --thickness, --color, --fill, --fill_color\n"
        "  --hexagon - drawing a hexagon (filled in or not). Flags: --center, --radius, --thickness, --color, --fill, --fill_color\n"
        "  --help - print help message.\n"
        "\n"
        "The picture must be in PNG format. Each command has its own flags and arguments for flags");

}

int process_option(char opt, char* optarg, char** parts, args *argum, int *flag, char** output_file, char** input_file) {
    switch(opt) {
            case 'L':
                if(parts && is_num(parts[0]) && is_num(parts[1])) {
                    argum->start[0] = atoi(parts[0]);
                    argum->start[1] = atoi(parts[1]);
                } else {
                    fprintf(stderr, coordinates_error);
                    exit(40);
                }
                break;
            case 'R':
                if(parts && is_num(parts[0]) && is_num(parts[1])) {
                    argum->end[0] = atoi(parts[0]);
                    argum->end[1] = atoi(parts[1]);
                } else {
                    fprintf(stderr, coordinates_error);
                    exit(41);
                }
                break;
            case 'A':
                if (*(optarg) == 'x' || *(optarg) == 'y') {
                    strcpy(argum->axis, optarg);
                } else {
                    fprintf(stderr, axis_error);
                    exit(42);
                }
                break;
            case 'E':
                if(parts && is_num(parts[0]) && is_num(parts[1])) {
                    argum->center[0] = atoi(parts[0]);
                    argum->center[1] = atoi(parts[1]);
                } else {
                    fprintf(stderr, coordinates_center_error);
                    exit(43);
                }
                break;
            case 'D':
                if(is_num(optarg) && atoi(optarg) >= 1 && atoi(optarg) < 800) {
                    argum->radius = atoi(optarg);
                } else {
                    fprintf(stderr, radius_error);
                    exit(44);
                }
                break;
            case 'T':
                if(is_num(optarg) && atoi(optarg) >= 1 && atoi(optarg) < 800) {
                    argum->width = atoi(optarg);
                } else {
                    fprintf(stderr, width_error);
                    exit(45);
                }
                break;
            case 'C':
                if(parts[2] && is_num(parts[0]) && is_num(parts[1]) && is_num(parts[2]) && check_colors(parts)) {
                    argum->color[0] = atoi(parts[0]);
                    argum->color[1] = atoi(parts[1]);
                    argum->color[2] = atoi(parts[2]);
                    parts[0] = "a";
                } else {
                    fprintf(stderr, color_error);
                    exit(46);
                }
                break;
            case 'I':
                if(parts[2] && is_num(parts[0]) && is_num(parts[1]) && is_num(parts[2]) && check_colors(parts)) {
                    argum->color_for_fill[0] = atoi(parts[0]);
                    argum->color_for_fill[1] = atoi(parts[1]);
                    argum->color_for_fill[2] = atoi(parts[2]);
                } else {
                    fprintf(stderr, color_error);
                    exit(47);
                }
                break;
            case 'F':
                argum->fill = true;
                break;
            case 'm':
                *(flag) = 'm';
                break;
            case 'r':
                *(flag) = 'r';
                break;
            case 'p':
                *(flag) = 'p';
                break;
            case 'h':
                *(flag) = 'h';
                break;
            case 'a':
                *(flag) = 'a';
                break;
            case 'u':
                *(flag) = 'u';
            case 'o':
                *output_file = optarg;
                break;
            case 'n':
                *input_file = optarg;
                break;
                
    }
}

int trigger_option(image *img, args argum, int flag) {
    switch (flag)
    {
        case 'm': 
            if(mirror(img, argum.axis, argum.start[0], argum.start[1], argum.end[0], argum.end[1])) {
                return 0;
            }   
            break;
        case 'r':
            if(rect(img, argum.start[0], argum.start[1], argum.end[0], argum.end[1], argum.width, argum.color, argum.fill, argum.color_for_fill)) {
                return 0;
            }
            break;
        case 'p':
            if(pentagram(img,  argum.center[1], argum.center[0], argum.radius, argum.width, argum.color)) {
                return 0;
            }
            break;
        case 'h':
            if(hexagon(img, argum.center[0], argum.center[1], argum.radius, argum.width, argum.color, argum.fill, argum.color_for_fill)) {
                return 0;
            }
            break;
        case 'a':
            if(paving(img, argum.start[0], argum.start[1], argum.end[0], argum.end[1])) {
                return 0;
            }
            break;
        case 'u':
            if(outside_rect(img, argum.start[0], argum.start[1], argum.end[0], argum.end[1], argum.color)) {
                return 0;
            }
        default:
            break;
    }
}

int main(int argc, char **argv) {
    puts("Course work for option 5.15, created by Oleg Kashechkin.");
    int flag = 1;
    char* short_opts_string = "emrphauA:L:R:E:D:T:C:FI:o:n:";
    int long_index = 0;
    char* output_file = "out.png";
    char* input_file = "f.png";
    args argum; 
    image *img;
    argum.fill = false;

    int opt = getopt_long(argc, argv, short_opts_string, long_opts, &long_index);
    
   if(opt == 'e' || argc <= 1) {
        print_help();
        return 0;
    }

    while(opt != -1) {
        char** parts;
        if (optarg && has_dot(optarg) && opt != 'o' && opt != 'n') {
            parts = split_string(optarg);
        }
        process_option(opt, optarg, parts, &argum, &flag, &output_file, &input_file);
       
        opt = getopt_long(argc, argv, short_opts_string, long_opts, &long_index);
    }
    // if(strcmp(input_file + strlen(input_file) - 4, ".png") != 0) {
    //     printf("Ошибка: Входной файл должен быть формата .png\n");
    //      exit(41);
    // }
    if(!(img = open_image(input_file))) {
        exit(40);
    }

    trigger_option(img, argum, flag);

    save_image(img, output_file);
    // free_image(img);
    return 0;
}
