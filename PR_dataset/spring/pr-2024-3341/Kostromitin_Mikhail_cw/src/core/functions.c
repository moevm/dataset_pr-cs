#include "functions.h"


void
parse_CLI(Rgb*** arr, BitmapFileHeader* file_header, BitmapInfoHeader* file_info, int argc, char* argv[]){
    int gpt;
    char shortopts[] = "ho:";
    int* indexptr = (int*)malloc(sizeof(int));
    char file_name_new[256];
    file_name_new[0] = '\0';

    char file_name_old[100];
    strncpy(file_name_old, argv[argc - 1], strlen(argv[argc - 1]));

    char colors_replace_old[15];
    char colors_replace_new[15];
    Rgb replace_old;
    Rgb replace_new;

    char component_name[6];
    int component_value;

    int x;
    int y;
    int th;
    char split_color[15];
    Rgb clr;

    float gamma_value;

    int is_read = 0;

    while ((gpt = getopt_long(argc, argv, shortopts, longopts, indexptr)) != -1){
        switch(gpt){
            case 'h':
                help();
                exit(0);
            case  'o':
                strncpy(file_name_new, optarg, strlen(optarg));
                file_name_new[strlen(optarg)] = '\0';
                break;
            case 'p':
                strncpy(file_name_old, optarg, strlen(optarg));
                file_name_old[strlen(optarg)] = '\0';
                *arr = read_bmp(file_name_old, file_header, file_info);
                is_read = 1;
                break;
            case 'i':
                info(*file_info, *file_header);
                exit(0);
            case 'a':
                strncpy(colors_replace_old, optarg, strlen(optarg));
                colors_replace_old[strlen(optarg)] = '\0';
                replace_old = parse_color(colors_replace_old);
                break;
            case 'w':
                strncpy(colors_replace_new, optarg, strlen(optarg));
                colors_replace_new[strlen(optarg)] = '\0';
                replace_new = parse_color(colors_replace_new);
                break;
            case 'n':
                strncpy(component_name, optarg, strlen(optarg));
                component_name[strlen(optarg)] = '\0';
                break;
            case 'v':
                component_value = atoi(optarg);
                break;
            case 'x':
                x = atoi(optarg);
                break;
            case 'y':
                y = atoi(optarg);
                break;
            case 't':
                th = atoi(optarg);
                break;
            case 'c':
                strncpy(split_color, optarg, strlen(optarg));
                split_color[strlen(optarg)] = '\0';
                clr = parse_color(split_color);
                break;
            case 'j':
                gamma_value = atof(optarg);
                break;
            default:
                break;
        }
    }

    if (!is_read) {
        *arr = read_bmp(file_name_old, file_header, file_info);
    }
    int H, W;
    H = (*file_info).height;
    W = (*file_info).width;

    if (is_replace != -1){
        color_replace(*arr, H, W, replace_old, replace_new);
    }
    if (is_filter != -1){
        rgb_filter(*arr, H, W, component_name, component_value);
    }
    if (is_split != -1){
        split(*arr, x, y, H, W, th, clr);
    }
    if (is_gamma != -1){
        gamma_func(*arr, H, W, gamma_value);
    }

    if (file_name_new[0] == '\0'){
        write_bmp(file_name_old, *arr, H, W, *file_header, *file_info);
    } else{
        write_bmp(file_name_new, *arr, H, W, *file_header, *file_info);
    }

    free(indexptr);
}


void
color_replace(Rgb** arr, int H, int W, Rgb old_color, Rgb new_color){
    if (!(color_validator(old_color)) || !(color_validator(new_color))){
        printf("Error 41: invalid color parameters");
        exit(41);
    }
    for (int y = 0; y < H; y++){
        for (int x = 0; x < W; x++){
            if (color_cmp(arr[y][x], old_color)){
                color_change(&arr[y][x], new_color);
            }
        }
    }
}


void
rgb_filter(Rgb** arr, int H, int W, char component[], int value){
    if (value < 0 || value > 255){
        printf("Error 42: invalid component value");
        exit(42);
    }
    if (!strcmp(component, "red")){
        for (int y = 0; y < H; y++){
            for (int x = 0; x < W; x++){
                arr[y][x].r = value;
            }
        }
    } else if (!strcmp(component, "green")){
        for (int y = 0; y < H; y++){
            for (int x = 0; x < W; x++){
                arr[y][x].g = value;
            }
        }
    } else if (!strcmp(component, "blue")){
        for (int y = 0; y < H; y++){
            for (int x = 0; x < W; x++){
                arr[y][x].b = value;
            }
        }
    } else {
        printf("Error 42: invalid component");
        exit(42);
    }
}


void
draw_line(Rgb** arr, int H, int W, int x1, int x2, int y1, int y2, Rgb color) {
    if (!coord_validator(W, x1, x2) || !coord_validator(H, y1, y2) || !(color_validator(color))){
        printf("Error 43: invalid parameters for a line");
        exit(43);
    }
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    arr[y2][x2] = color;
    while(x1 != x2 || y1 != y2){
        arr[y1][x1] = color;
        int error2 = error * 2;
        if(error2 > -deltaY){
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX){
            error += deltaX;
            y1 += signY;
        }
    }

}


void
split(Rgb** arr, int horizontal, int vertical, int H, int W, int thickness, Rgb color){
    if (horizontal < 2 || vertical < 2 || thickness <= 0){
        printf("Error 44: invalid split parameters");
        exit(44);
    }

    int y = 0;
    for (int i = 1; i < horizontal; i++){
        y += H / horizontal;
        int y_for_thick = y;

        for (int thick = 0; thick < thickness; thick++){
            if (thick % 2 == 0){
                y_for_thick -= thick;
                draw_line(arr, H, W, 0, W, y_for_thick, y_for_thick, color);
            } else {
                y_for_thick += thick;
                draw_line(arr, H, W, 0, W, y_for_thick, y_for_thick, color);
            }
        }
    }

    int x = 0;
    for (int i = 1; i < vertical; i++){
        x += W / vertical;
        int x_for_thick = x;

        for (int thick = 0; thick < thickness; thick++){
            if (thick % 2 == 0){
                x_for_thick -= thick;
                draw_line(arr, H, W, x_for_thick, x_for_thick, 0, H, color);
            } else {
                x_for_thick += thick;
                draw_line(arr, H, W, x_for_thick, x_for_thick, 0, H, color);
            }
        }
    }
}


void
gamma_func(Rgb** arr, int H, int W, float gamma_value){
    if (gamma_value < 0){
        printf("Error 47: invalid gamma value");
        exit(47);
    }
    
    for (int y = 0; y < H; y++){
        for (int x = 0; x < W; x++){
            
           arr[y][x].r = (int)(powf((double)((double)arr[y][x].r / 255.), (double)gamma_value) * 255.);
           arr[y][x].g = (int)(powf((double)((double)arr[y][x].g / 255.), (double)gamma_value) * 255.);
           arr[y][x].b = (int)(powf((double)((double)arr[y][x].b / 255.), (double)gamma_value) * 255.);
        }
        
    }
    
}
