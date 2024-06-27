#include "input_hell.h"


char *find_value(Element *dict, int len, char *key) {
    for (int i = 0; i < len; i++) {
        if (strcmp(key, dict[i].key) == 0) {
            return dict[i].value;
        }
    }
}
void check_output_and_input_match(char* input, char* output){
    if (strcmp(input,output)==0){
        fprintf(stderr,"Input and output files are the same\n");
        exit(41);
    }
}
int check_extra_option(Element *dict, int len_dict) {
    int len_main_options = 7;
    char *main_options[] = {"squared_lines", "rgbfilter", "rotate", "info", "input", "output", "contrast"};
    int count_main_options = 0;
    for (int i = 0; i < len_dict; i++) {
        for (int j = 0; j < len_main_options; j++) {
            if (strcmp(dict[i].key, main_options[j]) == 0) {
                count_main_options++;
            }
            if (strcmp(dict[i].key, main_options[3]) == 0) {
                count_main_options = -1;
                return count_main_options;
            }
        }
    }
    return count_main_options;
}

void check_flags(Element *dict, int len_dict, int *input_flag, int *output_flag, int *info_flag, int *help_flag, int *squared_lines_flag, int *side_size_flag, int *left_up_flag, int *right_down_flag, int *rgbfilter_flag, int *component_name_flag, int *component_value_flag, int *thickness_flag, int *color_flag, int *fill_flag, int *fill_color_flag, int *rotate_flag, int *angle_flag, int *contr_f, int *alpha_f, int *betha_f) {
    

    for (int i = 0; i < len_dict; i++) {
        if (strcmp("input", dict[i].key) == 0) {
            *input_flag = 1;
        } else if (strcmp("info", dict[i].key) == 0) {
            *info_flag = 1;
        } else if (strcmp("help", dict[i].key) == 0) {
            *help_flag = 1;
        } else if (strcmp("squared_lines", dict[i].key) == 0) {
            *squared_lines_flag = 1;
        } else if (strcmp("side_size", dict[i].key) == 0) {
            *side_size_flag = 1;
        } else if (strcmp("left_up", dict[i].key) == 0) {
            *left_up_flag = 1;
        } else if (strcmp("right_down", dict[i].key) == 0) {
            *right_down_flag = 1;
        } else if (strcmp("rgbfilter", dict[i].key) == 0) {
            *rgbfilter_flag = 1;
        } else if (strcmp("component_name", dict[i].key) == 0) {
            *component_name_flag = 1;
        } else if (strcmp("component_value", dict[i].key) == 0) {
            *component_value_flag = 1;
        } else if (strcmp("thickness", dict[i].key) == 0) {
            *thickness_flag = 1;
        } else if (strcmp("color", dict[i].key) == 0) {
            *color_flag = 1;
        } else if (strcmp("fill", dict[i].key) == 0) {
            *fill_flag = 1;
        } else if (strcmp("fill_color", dict[i].key) == 0) {
            *fill_color_flag = 1;
        } else if (strcmp("rotate", dict[i].key) == 0) {
            *rotate_flag = 1;
        } else if (strcmp("angle", dict[i].key) == 0) {
            *angle_flag = 1;
        }else if (strcmp("contrast", dict[i].key) == 0) {
            *contr_f = 1;
        }else if (strcmp("alpha", dict[i].key) == 0) {
            *alpha_f = 1;
        }else if (strcmp("beta", dict[i].key) == 0) {
            *betha_f = 1;
        }
        
        else if (strcmp("output", dict[i].key) == 0) {
            *output_flag = 1;
        }
    }
}


char *find_main_option(Element *dict, int len_dict, int *input_flag, int *output_flag, int *info_flag, int *help_flag, int *
squared_lines_flag,int *side_size_flag, int *left_up_flag, int *right_down_flag, int *rgbfilter_flag, int
                       *component_name_flag, int *component_value_flag, int *thickness_flag, int *color_flag, int *fill_flag, int
                       *fill_color_flag, int *rotate_flag, int *angle_flag, int *contr_f, int *alpha_f, int *betha_f) {
    check_flags(dict, len_dict, input_flag, output_flag, info_flag, help_flag, squared_lines_flag, side_size_flag,
                left_up_flag, right_down_flag, rgbfilter_flag, component_name_flag, component_value_flag,
                thickness_flag, color_flag, fill_flag, fill_color_flag, rotate_flag, angle_flag, contr_f, alpha_f, betha_f);
    int count_main_options = check_extra_option(dict, len_dict);
    // printf("%d", *output_flag);
    if (count_main_options == 3) {
        // переделать проверки
        if ((*squared_lines_flag)==1) {
            if ((*left_up_flag)==1 && (*side_size_flag==1) && (*thickness_flag)==1 && (*color_flag)==1 && (*output_flag)==1 && (*input_flag) ==1){
                check_one_coords(find_value(dict, len_dict, "left_up"));
                check_size(find_value(dict, len_dict, "side_size")); //maybe i need to check >0
                check_color(find_value(dict, len_dict, "color"));
                if ((*fill_flag) == 1 && (*fill_color_flag) == 1){
                    check_color(find_value(dict, len_dict, "fill_color"));
                }
                if ((*fill_flag) == 1 && (*fill_color_flag) == 0){
                    fprintf(stderr, "Не задан цвет заливки\n");
                    exit(41);
                }
                check_output_and_input_match(find_value(dict, len_dict, "input"), find_value(dict, len_dict, "output"));
                return "squared_lines";
            } else {
                fprintf(stderr, "Недостаточное количество флагов для функции squared_lines\n");
                exit(41);
            }
        } else if ((*rgbfilter_flag)==1) {
            if ((*component_name_flag)==1 && (*component_value_flag)==1 && (*output_flag)==1 && (*input_flag)==1){

                check_component_name(find_value(dict, len_dict, "component_name"));
                check_size(find_value(dict, len_dict, "component_value"));
                check_output_and_input_match(find_value(dict, len_dict, "input"), find_value(dict, len_dict, "output"));
                return "rgbfilter";
            } else {
                fprintf(stderr, "Недостаточное количество флагов для функции rgbfilter_flag\n");
                exit(41);
            }
        }else if ((*contr_f)==1) {
            if((*alpha_f) == 1 && (*betha_f) == 1){
                check_thickness(find_value(dict, len_dict, "beta"));
                check_flo(find_value(dict, len_dict, "alpha"));
                return "contr";
            }else{
                //printf("%d %d", alpha_f, betha_f);
                fprintf(stderr, "OOOOPS");
                exit(41);
            }



        }else if ((*rotate_flag)==1) {
            if ((*left_up_flag)==1 && (*right_down_flag)==1 && (*angle_flag)==1 && (*output_flag)==1 && (*input_flag)==1){
                check_one_coords(find_value(dict, len_dict, "left_up"));
                check_one_coords(find_value(dict, len_dict, "right_down"));
                check_angle(find_value(dict, len_dict, "angle"));
                check_output_and_input_match(find_value(dict, len_dict, "input"), find_value(dict, len_dict, "output"));
                return "rotate";
            } else {
                fprintf(stderr, "Недостаточное количество флагов для функции rotate\n");
                exit(41);
            }
        } else if ((*info_flag)==1) {
            return "info";
        }
    } else if (count_main_options > 3) {
        fprintf(stderr, "Можно выполнить только 1 основную функцию, а не несколько\n");
        exit(41);
    } else if(count_main_options == -1 && (*input_flag)==1){return "info";} else {
        return "Not main option";
    }
}



void run(Element *dict, int len_dict) {
    int input_flag = 0;
    int output_flag = 0;
    int info_flag = 0;
    int help_flag = 0;
    int squared_lines_flag = 0;
    int side_size_flag = 0;
    int left_up_flag = 0;
    int right_down_flag = 0;
    int rgbfilter_flag = 0;
    int component_name_flag = 0;
    int component_value_flag = 0;
    int thickness_flag = 0;
    int color_flag = 0;
    int fill_flag = 0;
    int fill_color_flag = 0;
    int rotate_flag = 0;
    int angle_flag = 0;

    int cont_f = 0;
    int alpha_f = 0;
    int betha_f = 0;

    char *main_option = find_main_option(dict, len_dict, &input_flag, &output_flag, &info_flag, &help_flag, &squared_lines_flag, &side_size_flag,
                                         &left_up_flag, &right_down_flag, &rgbfilter_flag, &component_name_flag, &component_value_flag, &thickness_flag, &color_flag,
                                         &fill_flag, &fill_color_flag, &rotate_flag, &angle_flag, &cont_f, &alpha_f, &betha_f);

    //printf("%s", main_option);
    if (strcmp(main_option, "squared_lines") == 0) {
        //printf("SQUARED\n");

        BitmapFileHeader bmfh;
        BitmapInfoHeader bmif;
        Rgb **arr;
        arr = read_bmp(find_value(dict, len_dict, "input"), &bmfh, &bmif);
        //print_info_header(bmif);
        int H = bmif.height;
        int W = bmif.width;

        int *coords_all = parse_coords(find_value(dict, len_dict, "left_up"));
        int start_x = coords_all[0];
        int start_y = coords_all[1];
        int len_s = atoi(find_value(dict, len_dict, "side_size"));
        int th = atoi(find_value(dict, len_dict, "thickness"));
        int *col = parse_color(find_value(dict, len_dict, "color"));
        // if(start_x+len_s > W){
        //     fprintf(stderr, "wrong size\n");
        //     exit(41);
        // }
        // if(start_y + len_s > H){
        //     fprintf(stderr, "wrong size\n");
        //     exit(41);
        // }
        if(fill_flag){
            int *col_f = parse_color(find_value(dict, len_dict, "fill_color"));
            draw_sq(arr, start_x, start_y, len_s, H, W, th, col, 1, col_f, th-1); // check coords 0
        }else{
            // printf("%d-x\n %d-y\n %d-len\n %d-th\n", start_x, start_y,len_s, th);
            int col_f[3] = {0, 0, 0};
            draw_sq(arr, start_x, start_y, len_s, H, W, th, col, 0, col_f, th-1);
        }
        write_bmp(find_value(dict, len_dict, "output"), arr, H, W, bmfh, bmif);

        for (int i = 0; i < H; i++){
            free(arr[i]);
        }
        free(arr);

    }
    else if(strcmp(main_option,"rgbfilter")==0){
        //printf("FILTERS");
        BitmapFileHeader bmfh;
        BitmapInfoHeader bmif;
        Rgb **arr;
        arr = read_bmp(find_value(dict, len_dict, "input"), &bmfh, &bmif);
        //print_info_header(bmif);
        int H = bmif.height;
        int W = bmif.width;
        char* color = find_value(dict, len_dict, "component_name");
        int val = atoi(find_value(dict, len_dict, "component_value"));
        //printf("_%c_", color[0]);
        if(color[0] == 'r'){
            change_red_chanel(arr, H, W, val);
        }else if(color[0] == 'g'){
            change_green_chanel(arr, H, W, val);
        }else if (color[0] == 'b'){
            change_blue_chanel(arr, H, W, val);
        }

        write_bmp(find_value(dict, len_dict, "output"), arr, H, W, bmfh, bmif);

        for (int i = 0; i < H; i++){
            free(arr[i]);
        }
        free(arr);
        
    }
    else if(strcmp(main_option,"rotate")==0){
        //printf("ROTATOS\n");

        BitmapFileHeader bmfh;
        BitmapInfoHeader bmif;
        Rgb **arr;
        arr = read_bmp(find_value(dict, len_dict, "input"), &bmfh, &bmif);
        //print_info_header(bmif);
        int H = bmif.height;
        int W = bmif.width;
        //int col[3] = {255, 255, 255};
        int col_f[3] = {255, 0, 0};

        int *coords_all = parse_coords(find_value(dict, len_dict, "left_up"));
        int *coords_all_down = parse_coords(find_value(dict, len_dict, "right_down"));
        int start_x = coords_all[0];
        int start_y = coords_all[1];
        int end_x = coords_all_down[0];
        int end_y = coords_all_down[1];
        int a = atoi(find_value(dict, len_dict, "angle"));
        
        turn(arr, H, W, start_x, start_y, end_x, end_y, a);
        //turn(arr, H, W, start_x, start_y, end_x, end_y, a);
        //turn(arr, H, W, start_x, start_y, end_x, end_y, a);
        //turn(arr, H, W, start_x, start_y, end_x, end_y, a);
        

        write_bmp(find_value(dict, len_dict, "output"), arr, H, W, bmfh, bmif);

        for (int i = 0; i < H; i++){
            free(arr[i]);
        }
        free(arr);

    }else if(strcmp(main_option,"contr")==0){
        BitmapFileHeader bmfh;
        BitmapInfoHeader bmif;
        Rgb **arr;
        arr = read_bmp(find_value(dict, len_dict, "input"), &bmfh, &bmif);
        //print_info_header(bmif);
        int H = bmif.height;
        int W = bmif.width;
        float alpha = atof(find_value(dict, len_dict, "alpha"));
        int beta = atoi(find_value(dict, len_dict, "beta"));

        def_task(arr, alpha, beta, H, W);

        write_bmp(find_value(dict, len_dict, "output"), arr, H, W, bmfh, bmif);

        for (int i = 0; i < H; i++){
            free(arr[i]);
        }
        free(arr);

    }

    

    else if(strcmp(main_option,"info")==0){
        //printf("INFOS");
        BitmapFileHeader bmfh;
        BitmapInfoHeader bmif;
        Rgb **arr;
        arr = read_bmp(find_value(dict, len_dict, "input"), &bmfh, &bmif);
        int H = bmif.height;
        int W = bmif.width;
        print_file_header(bmfh);
        print_info_header(bmif);
        for (int i = 0; i < H; i++){
            free(arr[i]);
        }
        free(arr);

    }
    else{
        if (help_flag){
            printf("Course work for option 4.12, created by Aleksandr Klyukin.\n");
        }
    }
}
