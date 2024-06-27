#include "option.h"

check_option do_check(){
    check_option check;
    check.above = 0;
    check.below = 0;
    check.color = 0;
    check.end = 0;
    check.gray = 0;
    check.input = 0;
    check.inverse = 0;
    check.left = 0;
    check.left_up = 0;
    check.line = 0;
    check.output = 0;
    check.resize = 0;
    check.right = 0;
    check.right_down = 0;
    check.start = 0;
    check.thickness = 0;
    check.info = 0;
    check.compress = 0;
    check.num = 0;
    return check;
}

value do_value(){
    value val;
    val.down = 0;
    val.left = 0;
    val.right = 0;
    val.up = 0;
    val.input_file = (char*) calloc(sizeof(char), 128);
    val.output_file = (char*) calloc(sizeof(char), 128);
    return val;
}

void check_flags(check_option check){
    int sum_check = check.inverse + check.gray + check.resize + check.line + check.info + check.compress;
    if (sum_check > 1){
        fprintf(stderr, "Input Error: impossible use several functions at once\n");
        exit(41); 
    }
    if (sum_check == 0){
        fprintf(stderr, "Input Error: none of the action functions were called\n");
        exit(41);
    }
    if (check.above>1 || check.below>1 || check.compress>1 || check.num>1 || check.color>1 || check.end>1 || check.gray>1 || check.input>1 || check.inverse>1 || check.left>1 || check.left_up>1 || check.line>1 || check.output>1 || check.resize>1 || check.right>1 || check.right_down>1 || check.start>1 || check.thickness>1){
        fprintf(stderr, "Input Error: forbidden use the same flag multiple times\n");
        exit(41);
    }
    if (check.info==0 && check.num==0 && (check.left_up + check.right_down)!=2 && ((check.left+check.right+check.above+check.below)== 0 || check.color == 0 ) && (check.start+check.end+check.color+check.thickness)!=4){
        fprintf(stderr, "Input Error: not enough arguments for the function\n");
        exit(41);
    }
}

void get_options( int argc, char* argv[], check_option* check, value* values){
    if (argc == 1) {
        fprintf(stderr, "Input Error: no arguments were entered\n");
        exit(41);
    }
    struct option long_options[] = {
        {"inverse", no_argument, NULL, 'n'},
        {"gray", no_argument, NULL, 'g'},
        {"resize", no_argument, NULL, 'r'},
        {"line", no_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"left_up", required_argument, NULL, 'u'},
        {"right_down", required_argument, NULL, 'd'},
        {"left", required_argument, NULL, 'L'},
        {"right", required_argument, NULL, 'R'},
        {"above", required_argument, NULL, 'A'},
        {"below", required_argument, NULL, 'B'},
        {"color", required_argument, NULL, 'C'},
        {"start", required_argument, NULL, 's'},
        {"end", required_argument, NULL, 'e'},
        {"thickness", required_argument, NULL, 't'},
        {"compress", no_argument, NULL, 'c'},
        {"num", required_argument, NULL, 'N'},
        {NULL, 0, NULL, 0}
    };
    int option;
    while ((option = getopt_long(argc, argv, "ngrlhIi:o:u:d:L:R:A:B:C:s:e:t:cN:", long_options, NULL)) != -1) {
        switch (option) {
            case 'n':
                check->inverse++;
                break;
            case 'g':
                check->gray++;
                break;
            case 'r':
                check->resize++;
                break;
            case 'l':
                check->line++;
                break;
            case 'h':
                print_help();
                exit(0);
                break;
            case 'I':
                check->info++;
                break;
            case 'i':
                check->input++;
                strncpy(values->input_file, optarg, 127); 
                break;
            case 'o':
                check->output++;
                strncpy(values->output_file, optarg, 127); 
                break;
            case 'u':
                check->left_up++;
                if (sscanf(optarg, "%d.%d", &values->left, &values->up) != 2) {
                    fprintf(stderr, "Type Error: coordinates must be of the int type\n");
                    exit(40);
                }
                break;
            case 'd':
                check->right_down++;
                if (sscanf(optarg, "%d.%d", &values->right, &values->down) != 2) {
                    fprintf(stderr, "Type Error: coordinates must be of the int type\n");
                    exit(40);
                }
                break;
            case 'L':
                check->left++;
                if (sscanf(optarg, "%d", &values->left) != 1) {
                    fprintf(stderr, "Type Error: value of resize must be of the int type\n");
                    exit(40);
                }
                break;
            case 'R':
                check->right++;
                if (sscanf(optarg, "%d", &values->right) != 1) {
                    fprintf(stderr, "Type Error: value of resize must be of the int type\n");
                    exit(40);
                }
                break;
            case 'A':
                check->above++;
                if (sscanf(optarg, "%d", &values->up) != 1) {
                    fprintf(stderr, "Type Error: value of resize must be of the int type\n");
                    exit(40);
                }
                break;
            case 'B':
                check->below++;
                if (sscanf(optarg, "%d", &values->down) != 1) {
                    fprintf(stderr, "Type Error: value of resize must be of the int type\n");
                    exit(40);
                }
                break;
            case 'C':
                check->color++;
                int r, g, b;
                if (sscanf(optarg, "%d.%d.%d", &r, &g, &b) != 3) {
                    fprintf(stderr, "Type Error: color must be in the format rrr.ggg.bbb\n");
                    exit(40);
                }
                values->color = check_color(r,g,b);
                break;
            case 's':
                check->start++;
                if (sscanf(optarg, "%d.%d", &values->start_x, &values->start_y) != 2) {
                    fprintf(stderr, "Type Error: coordinates must be of the int type\n");
                    exit(40);
                }
                break;
            case 'e':
                check->end++;
                if (sscanf(optarg, "%d.%d", &values->end_x, &values->end_y) != 2) {
                    fprintf(stderr, "Type Error: coordinates must be of the int type\n");
                    exit(40);
                }
                break;
            case 't':
                check->thickness++;
                if (sscanf(optarg, "%d", &values->thickness) != 1) {
                    fprintf(stderr, "Type Error: value of thinckness must be of the int type\n");
                    exit(40);
                }
                if (values->thickness<0){
                    fprintf(stderr, "Value Error: value of thinckness must be unsigned\n");
                    exit(42);
                }
                break;
            case 'c':
                check->compress++;
                break;
            case 'N':
                check->num++;
                if (sscanf(optarg, "%d", &values->num) != 1) {
                    fprintf(stderr, "Type Error: value of num must be of the int type\n");
                    exit(40);
                }
                if (values->num<1){
                    fprintf(stderr, "Value Error: value of num must be unsigned\n");
                    exit(42);
                }
                break;
            case '?':
                fprintf(stderr, "Input Error: wrong option\n");
                exit(41);
                break;
        }
    }
    if (check->output == 0) {
        strncpy(values->output_file, "out.bmp", 127);
    }
    if (check->input == 0){
        strncpy(values->input_file, argv[argc-1], 127); 
    }
    if (strcmp(values->output_file, values->input_file)==0){
        fprintf(stderr, "Input Error: names of the input and output files should not match\n");
        exit(41);
    }
    check_flags(*check);
}

Rgb** do_option(check_option* check, Rgb** arr, value* values, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif){
    if(check->info){
        print_info_header(*bmif);
        print_file_header(*bmfh);
    }
    if (check->inverse){
        check_coord(bmif, &values->left, &values->up, &values->right, &values->down);
        inverse(arr, *bmif, values->left, values->up, values->right, values->down); 
        return arr;
    }
    if (check->gray){
        check_coord(bmif, &values->left, &values->up, &values->right, &values->down);
        gray(arr, *bmif, values->left, values->up, values->right, values->down); 
        return arr;
    }
    if (check->resize){
        int arr_height = bmif->height;
        Rgb** new_arr = resize(arr, bmif, values->left, values->right, values->down, values->up, values->color);
        for (int i = 0; i < arr_height; i++){
            free(arr[i]);
        }
        return new_arr;
    }
    if (check->line){
        draw_line(arr, bmif, values->start_x, values->start_y, values->end_x, values->end_y, values->thickness, values->color);
        return arr;
    }
    if (check->compress){
        int arr_height = bmif->height;
        Rgb** new_arr = compress(arr, values->num, bmif);
        for (int i = 0; i < arr_height; i++){
            free(arr[i]);
        }
        return new_arr;
    }
}