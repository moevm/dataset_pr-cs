#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <png.h>
#include <getopt.h>
#include <math.h>
#include <string.h>

//structs, read/write png, data func
typedef struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
}png;

int read_png_file(char *file_name, struct Png *image) {
    int x,y;
    char header[8];
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        printf("File %s can't be readen\n", file_name);
        exit(41);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        printf("File %s isn't a png\n", file_name);
        exit(41);
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
    if (!image->png_ptr){
        printf("Png structure error\n"); 
        exit(41); 
    } 
    image->info_ptr = png_create_info_struct(image->png_ptr); 
    if (!image->info_ptr){ 
        printf("Png info error\n"); 
        exit(41);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error with reading\n");
        exit(41);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr,image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep)*image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
    return 0;
}

int write_png_file(char *file_name, png *image) {
    int x,y;
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf("File %s can't be opened\n", file_name);
        exit(42);
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
       printf("Png structure error\n");
       exit(42);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
       printf("Png info error\n");
       exit(42);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
       printf("Error with writing\n");
       exit(42);
    }
    png_init_io(image->png_ptr, fp);
    if (setjmp(png_jmpbuf(image->png_ptr))){
       printf("Error with writing\n");
       exit(42);
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width,  image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))){
       printf("Error with writing\n");
       exit(42);
    }
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr))){
       printf("Error with writing\n");
       exit(42);
    }
    png_write_end(image->png_ptr, NULL);
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);
}

typedef struct user_input_data {
    char func;

    int left_up_x;
    int left_up_y;
    int up_flag;
    int side_size;
    int thickness;
    int color_r;
    int color_g;
    int color_b;
    int fill;
    int fill_color_r;
    int fill_color_g;
    int fill_color_b;
    char* component_name;
    int component_value;
    int right_down_x;
    int right_down_y;
    int down_flag;
    int angle;
    int upper_vertex_x;
    int upper_vertex_y;
    int flag;
    int size;

    char* input;
    char* output;
}user_input_data;

user_input_data* init_input_data() {
    user_input_data* basic_data = malloc(sizeof(user_input_data));
    basic_data->func = ' ';

    basic_data->left_up_x = 0;
    basic_data->left_up_y = 0;
    basic_data->up_flag = 1;
    basic_data->side_size = -1;
    basic_data->thickness = -1;
    basic_data->color_r = -1;
    basic_data->color_g = -1;
    basic_data->color_b = -1;
    basic_data->fill = 0; 
    basic_data->fill_color_r = -1;
    basic_data->fill_color_g = -1;
    basic_data->fill_color_b = -1;
    basic_data->component_name = calloc(sizeof(char), strlen("None") + 1);
    strcpy(basic_data->component_name, "None");
    basic_data->component_value = -1;
    basic_data->right_down_x = 0;
    basic_data->right_down_y = 0;
    basic_data->down_flag = 1;
    basic_data->angle = -1;
    basic_data->upper_vertex_x = 0;
    basic_data->upper_vertex_y = 0;
    basic_data->flag = 1;
    basic_data->size = -1;

    basic_data->input = calloc(sizeof(char), strlen("None") + 1);
    strcpy(basic_data->input, "None");
    basic_data->output = calloc(sizeof(char), strlen("out.png") + 1);
    strcpy(basic_data->output, "out.png");
    return basic_data;
}

//easy funcs
void print_info(struct Png *image){
    printf("Width %d\n", image->width);
    printf("Height %d\n", image->height);
    printf("Color type %u\n", image->color_type);
    printf("Bit depth %u\n", image->bit_depth);
}

void print_help(){
    printf("Help. Description of the functions that the program performs.\n");
    printf("-s --squared_lines, drawing a square with diagonals. Parameters:\n"
            "1) -l --left_up, coordinates of the upper left corner\n"
            "2) -z --side_size, the size of the side of the square\n"
            "3) -t --thickness, the thickness of the lines\n"
            "4) -c --color, the color of the lines\n"
            "5) -b --fill, to fill or not\n"
            "6) -f --fill_color, if a fill is selected, specify its color\n");
    printf("-r --rgbfilter, set the value of the specified rgb component to 0 or 255 for the entire image. Parameters:\n"
            "1) -n --component_name, rgb component\n"
            "2) -v --component_value, the value of the component \n");
    printf("-e --rotate, rotate the image (part) by 90/180/270 degrees. Parameters:\n"
            "1) -l --left_up, coordinates of the upper left corner\n"
            "2) -d --right_down, coordinates of the lower right corner\n"
            "3) -a --angle, angle of rotation\n");
    printf("-7 --square_rhombus, drawing a square rhombus. Parameters:\n"
            "1) -8 --upper_vertex, coordinates of the upper vertex\n"
            "2) -9 --size, the size of the side of the square rhombus\n"
            "3) -f --fill_color, the color of the square rhombus\n");
    printf("-1 --info, file information\n");
    printf("-h --help, program instructions\n");
}

//input
int get_opt(user_input_data* user_data, int argc, char **argv){

    const struct option long_options[] = {
        { "input", required_argument, NULL, 'i'},
        { "output", required_argument, NULL, 'o'},
        { "help", no_argument, NULL, 'h'},
        { "info", no_argument, NULL, '1'},
        { "squared_lines", no_argument, NULL, 's'},
        { "left_up", required_argument, NULL, 'l'},
        { "side_size", required_argument, NULL, 'z'},
        { "thickness", required_argument, NULL, 't'},
        { "color", required_argument, NULL, 'c'},
        { "fill", no_argument, NULL, 'b'},
        { "fill_color", required_argument, NULL, 'f'},
        { "rgbfilter", no_argument, NULL, 'r'},
        { "component_name", required_argument, NULL, 'n'},
        { "component_value", required_argument, NULL, 'v'},
        { "rotate", no_argument, NULL, 'e'},
        { "right_down", required_argument, NULL, 'd'},
        { "angle", required_argument, NULL, 'a'},
        { "square_rhombus", no_argument, NULL, '7'},
        { "upper_vertex", required_argument, NULL, '8'},
        { "size", required_argument, NULL, '9'},
        { 0, 0, 0, 0 }
    };
    
    int opt;
    const char* short_options = "i:o:h1sl:z:t:c:bf:rn:v:ed:a:78:9:";
    opt = getopt_long(argc, argv, short_options, long_options, NULL);
    int x, y, val, r, g, b, read_check;
    png* image = malloc(sizeof(png));
    char* tmp = calloc(sizeof(char), 128);

    while(opt!=-1){
        switch (opt){
            case 'i':
                if (optarg == NULL) {
				    printf("Flag %c expects input file\n", opt);
				    exit(43);
			    }
                char* input_name = calloc(sizeof(char), strlen(optarg));
			    read_check = sscanf(optarg, "%s", input_name);
			    if (read_check != 1 || strcmp(input_name, "None") == 0) {
				    printf("Flag %c expects input file name, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->input = input_name;
                break;

            case 'o':
                if (optarg == NULL) {
				    printf("Flag %c expects output file\n", opt);
				    exit(43);
			    }
                char* output_name = calloc(sizeof(char), strlen(optarg));
			    read_check = sscanf(optarg, "%s", output_name);
			    if (read_check != 1 || strcmp(output_name, "None") == 0) {
				    printf("Flag %c expects output file name, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->output = output_name;
                break;

            case 'h':
                print_help();
                exit(0);

            case '1':
                user_data->func = 'i';
                break;
                
            case 's':
                user_data->func = 's';
                break;

            case 'l':
                if (optarg == NULL) {
				    printf("Flag %c expects arguments\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d.%d", &x, &y);
			    if (read_check != 2) {
				    printf("Flag %c expects 'number.number', but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->left_up_x = x;
                user_data->left_up_y = y;
                user_data->up_flag--;
                break;

            case 'z':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d", &val);
			    if (read_check != 1 || val <= 0) {
				    printf("Flag %c expects number over 0, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->side_size = val;
			    break;

            case 't':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d", &val);
			    if (read_check != 1 || val <= 0) {
				    printf("Flag %c expects number over 0, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->thickness = val;
			    break;
            
            case 'c':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
                read_check = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
			    if (read_check != 3 || r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255) {
				    printf("Flag %c expects number.number.number from 0 to 255, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->color_r = r;
	            user_data->color_g = g;
	            user_data->color_b = b;		
		        break;

            case 'b':
                user_data->fill++;
                break;

            case 'f':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
                read_check = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
			    if (read_check != 3 || r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255) {
				    printf("Flag %c expects number.number.number from 0 to 255, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->fill_color_r = r;
	            user_data->fill_color_g = g;
	            user_data->fill_color_b = b;		
		        break;

            case 'r':
                user_data->func = 'r';
                break;

            case 'n':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
                read_check = sscanf(optarg, "%s", tmp);
                if ((strcmp(tmp, "red") && strcmp(tmp, "green") && strcmp(tmp, "blue"))) {
				    printf("Flag %c expects one of rgb, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->component_name = tmp;
                break;

            case 'v':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
                read_check = sscanf(optarg, "%d", &val);
			    if (read_check != 1 || val < 0 || val > 255){
                    printf("Flag %c expects a number from 0 to 255, but got %s\n", opt, optarg);
                    exit(43);
                }
                user_data->component_value = val;
                break;
            
            case 'e':
                user_data->func = 'e';
                break;

            case 'd':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d.%d", &x, &y);
			    if (read_check != 2) {
				    printf("Flag %c expects 'number.number', but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->right_down_x = x;
                user_data->right_down_y = y;
                user_data->down_flag--;
                break;

            case 'a':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
                read_check = sscanf(optarg, "%d", &val);
                if (read_check != 1 || (val != 90 && val != 180 && val != 270)) {
				    printf("Flag %c expects angle 90/180/270, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->angle = val;
                break;

            case '7':
                user_data->func = 'k';
                break;
            
            case '8':
                if (optarg == NULL) {
				    printf("Flag %c expects arguments\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d.%d", &x, &y);
			    if (read_check != 2) {
				    printf("Flag %c expects 'number.number', but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->upper_vertex_x = x;
                user_data->upper_vertex_y = y;
                user_data->flag--;
                break;

            case '9':
                if (optarg == NULL) {
				    printf("Flag %c expects argument\n", opt);
				    exit(43);
			    }
			    read_check = sscanf(optarg, "%d", &val);
			    if (read_check != 1 || val <= 0) {
				    printf("Flag %c expects number over 0, but got %s\n", opt, optarg);
				    exit(43);
			    }
                user_data->size = val;
			    break;
            
        }
        opt = getopt_long(argc, argv, short_options, long_options, NULL);
    }
    return 0;
}

void non_arg_funcs(int argc, char **argv) {
    char* no_arg[] = {"--help", "-h", "--info", "-1", "--squared_lines", "-s", "--fill", "-b", "--rgbfilter", "-r", "--rotate", "-e", "--square_rhombus", "-7"};
    for (int i = 1; i < argc; i++)
        for (int k = 0; k < 14; k++)
            if ((strcmp(argv[i-1], no_arg[k]) == 0) && (strstr(argv[i], "--") == NULL && strstr(argv[i], "-") == NULL))
                if ((strstr(argv[i], ".png") == NULL) || (strstr(argv[i], ".png") != NULL && i != argc-1))
                    printf("Extra argument %s will be ignored\n", argv[i]);
}

int check_input(user_input_data* input) {
	switch (input->func) {
        case 'i':
            break;
        case 's':
            if(input->up_flag || input->side_size == -1 || input->thickness == -1 || input->color_r == -1 || input->color_g == -1 || input->color_b == -1) {
                printf("Not enough arguments for %c, check -h/--help for info\n", input->func);
                print_help();
                exit(44);
            }
            if(input->fill == 1 && (input->fill_color_r == -1 || input->fill_color_g == -1 || input->fill_color_b == -1)){
                printf("Not enough arguments for option %c, check -h/--help for info\n", input->func);
                print_help();
                exit(44);
            }
            break;

        case 'r':
            if(!(strcmp(input->component_name, "None")) || input->component_value == -1) {
                printf("Not enough arguments for %c, check -h/--help for info\n", input->func);
                print_help();
                exit(44);
            }
            break;

        case 'e':
            if(input->up_flag || input->down_flag || input->angle == -1) {
                printf("Not enough arguments for %c, check -h/--help for info\n", input->func);
                print_help();
                exit(44);
            }
            break;

        case 'k':
            if(input->flag || input->size == -1 || input->fill_color_r == -1 || input->fill_color_g == -1 || input->fill_color_b == -1) {
                printf("Not enough arguments for %c, check -h/--help for info\n", input->func);
                print_help();
                exit(44);
            }
            break;

        default:
            printf("No func for program to work with, check -h/--help for info\n");
            print_help();
            exit(44);
            break;
	}
	return 0;
}

//square func (check for coords, sides/fill color, draw sides, Bresenham's alg for diags, draw diags)
int check_x_y(png* image, int a, int b){
    if (a>=0 && b>=0 && a<image->width && b<image->height)
        return 1;
    return 0;
}

void color_square(png* image, user_input_data* square, int x, int y){
    if (check_x_y(image, x,y)){
        png_byte *ptr = &(image->row_pointers[y][x * 3]);
        ptr[0] = square->color_r;
        ptr[1] = square->color_g; 
        ptr[2] = square->color_b;
    }
}

void fill_square(png* image, user_input_data* square, int x, int y){
    if (check_x_y(image, x,y)){
        png_byte *ptr = &(image->row_pointers[y][x * 3]);
        ptr[0] = square->fill_color_r;
        ptr[1] = square->fill_color_g; 
        ptr[2] = square->fill_color_b;
    }
}

void help_square(png* image, user_input_data* square, int x0, int y0, int x1, int y1, int thick, int fill) {
    if (x0 == x1){
        for (int i = y0; i <= y1; i++)
            for (int j = 0; j < thick; j++)
                if (image->height - i >= 0 && x0 - j >= 0 && x0 - j < image->width && image->height - i < image->height)
                    if (fill)
                        fill_square(image, square, x0-j, i);
                    else
                        color_square(image, square, x0-j, i);
    }else if (y0 == y1){ 
        for(int i=x0; i <= x1; i++)
            for(int j=0; j<thick; j++)
                if (y0-j >= 0 && i>=0 && i<image->width && y0-j<image->height)
                    if (fill)
                        fill_square(image, square, i, y0-j);
                    else
                        color_square(image, square, i, y0-j);
    }
}

void draw_line(png* image, user_input_data* square, int x0, int y0, int x1, int y1) {
    int abs_x = abs(x1 - x0);
    int abs_y = abs(y1 - y0);
    int sign_x = -1;
    if (x1 > x0)
        sign_x = 1;
    int sign_y = -1;
    if (y1 > y0)
        sign_y = 1;
    int abs_x_y = abs_x - abs_y;
    color_square(image, square, x1, y1);
    while (x0 != x1 || y0 != y1) {
        color_square(image, square, x0, y0);
        int abs_x_y2 = abs_x_y * 2;
        if (abs_x_y2 > -abs_y) {
            abs_x_y -= abs_y;
            x0 += sign_x;
        }
        if (abs_x_y2 < abs_x) {
            abs_x_y += abs_x;
            y0 += sign_y;
        }
    }
}

void draw_odd_line(png* image, user_input_data* square, int x0, int y0, int x1, int y1) {
    draw_line(image, square, x0, y0, x1, y1);
    if (square->thickness == 1)
        return;
    if (abs(y1 - y0) >= abs(x1 - x0)) {
        for (int i = 1; i <= (square->thickness - 1)/2; i++) {
            draw_line(image, square, x0 + i, y0, x1 + i, y1);
            draw_line(image, square, x0 - i, y0, x1 - i, y1);
        }
    } else {
        for (int i = 1; i <= (square->thickness - 1)/2; i++) {
            draw_line(image, square, x0, y0 + i, x1, y1 + i);
            draw_line(image, square, x0, y0 - i, x1, y1 - i);
        }
    }
}

void draw_even_line(png* image, user_input_data* square, int x0, int y0, int x1, int y1) {
    square->thickness--;
    draw_odd_line(image, square, x0, y0, x1, y1);
    square->thickness++;
    if (abs(y1 - y0) >= abs(x1 - x0)) {
        draw_line(image, square, x0 + square->thickness/2, y0, x1 + square->thickness/2, y1);
    } else {
        draw_line(image, square, x0, y0 + square->thickness/2, x1, y1 + square->thickness/2);
    }
}

int squared_lines(png* image, user_input_data* square) {
    int x = square->left_up_x + square->side_size;
    int y = square->left_up_y + square->side_size;
    if (x+square->thickness/2<0 || y+square->thickness/2<0 ||
    square->left_up_x-square->thickness/2>image->width || square->left_up_y-square->thickness/2>image->height){
        printf("Square out of png, waited for %d<=x<=%d, %d<=y<=%d\n", -square->thickness/2-square->side_size, square->thickness/2+image->width, -square->thickness/2-square->side_size, square->thickness/2+image->height);
        return 0;
    }
    if(square->fill){
        int thickness_fill = x-square->left_up_x + square->thickness/2;    
        help_square(image, square, x, square->left_up_y, x, y, thickness_fill, 1);  
    }
    if (square->thickness%2==0){
        help_square(image, square, square->left_up_x+(square->thickness/2), square->left_up_y, square->left_up_x+(square->thickness/2), y, square->thickness, 0);
        help_square(image, square, square->left_up_x-(square->thickness/2)+1, y+(square->thickness/2)-1, x+(square->thickness/2)-1, y+(square->thickness/2)-1, square->thickness, 0);
        help_square(image, square, x+(square->thickness/2)-1, square->left_up_y, x+(square->thickness/2)-1, y, square->thickness, 0);
        help_square(image, square, square->left_up_x-(square->thickness/2)+1, square->left_up_y+(square->thickness/2), x+(square->thickness/2)-1, square->left_up_y+(square->thickness/2), square->thickness, 0);
    }else{
        help_square(image, square, square->left_up_x+(square->thickness/2), square->left_up_y, square->left_up_x+(square->thickness/2), y, square->thickness, 0);
        help_square(image, square, square->left_up_x-(square->thickness/2), y+(square->thickness/2), x+(square->thickness/2), y+(square->thickness/2), square->thickness, 0);
        help_square(image, square, x+(square->thickness/2), square->left_up_y, x+(square->thickness/2), y, square->thickness, 0);
        help_square(image, square, square->left_up_x-(square->thickness/2), square->left_up_y+(square->thickness/2), x+(square->thickness/2), square->left_up_y+(square->thickness/2), square->thickness, 0);
    }
    if (square->thickness % 2 == 1) {
        draw_odd_line(image, square, square->left_up_x, square->left_up_y, x, y);
        draw_odd_line(image, square, square->left_up_x, y, x, square->left_up_y);
    } else {
        draw_even_line(image, square, square->left_up_x, square->left_up_y, x, y);
        draw_even_line(image, square, square->left_up_x, y, x, square->left_up_y);
    }
}

//square rhomb (1,41421356237)
void draww(png* image, user_input_data* square, int x0, int y0, int x1, int y1) {
    int abs_x = abs(x1 - x0);
    int abs_y = abs(y1 - y0);
    int sign_x = -1;
    if (x1 > x0)
        sign_x = 1;
    int sign_y = -1;
    if (y1 > y0)
        sign_y = 1;
    int abs_x_y = abs_x - abs_y;
    fill_square(image, square, x1, y1);
    while (x0 != x1 || y0 != y1) {
        fill_square(image, square, x0, y0);
        int abs_x_y2 = abs_x_y * 2;
        if (abs_x_y2 > -abs_y) {
            abs_x_y -= abs_y;
            x0 += sign_x;
        }
        if (abs_x_y2 < abs_x) {
            abs_x_y += abs_x;
            y0 += sign_y;
        }
    }
}

void draww_odd(png* image, user_input_data* square, int x0, int y0, int x1, int y1, int check) {
    draww(image, square, x0, y0, x1, y1);
    for (int i = 1; i <= check; i++) {
        draww(image, square, x0 - i, y0 + i, x1 - i, y1 + i);
        draww(image, square, x0 - i - 1, y0 + i, x1 - i, y1 + i + 1);
        draww(image, square, x0 - i, y0 + i - 1, x1 - i + 1, y1 + i);
    }
}

int square_rhombus(png* image, user_input_data* square){
    int x_up = square->upper_vertex_x;
    int y_up = square->upper_vertex_y;;
    int check = square->size/(1.41421356237);
    int x_right = square->upper_vertex_x + square->size/(1.41421356237);
    int y_right = square->upper_vertex_y + square->size/(1.41421356237);
    
    draww_odd(image, square, x_up, y_up, x_right, y_right, check);
}

//rgb func 
int rgb_filter(png* image, user_input_data* filter) { 
    int component, x, y; 
    if (strcmp(filter->component_name, "red") == 0){
        component = 0;
    }else if (strcmp(filter->component_name, "green") == 0){
        component = 1;
    }else if (strcmp(filter->component_name, "blue") == 0){
        component = 2;
    }
    for (y = 0; y < image->height; y++) { 
        for (x = 0; x < image->width; x++) { 
            png_byte *ptr = &(image->row_pointers[y][x * 3]);
            ptr[component] = filter->component_value;
        }
    }
    return 0;
}

//rotate func (rotated pointers for angle 90/270, rotate for angles 90/270 and 180)
png_bytep* help_rotate(png* image, user_input_data* rotate, int w, int h){
    png_bytep* rot_pointers = malloc(sizeof(png_bytep) * w);
    for (int y = 0; y < w; y++)
        rot_pointers[y] = (png_byte*)malloc(sizeof(png_bytep) * 3 * h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int old_x, old_y, new_x, new_y;
            old_x = rotate->left_up_x + i;
            old_y = rotate->left_up_y + j;
            if (rotate->angle == 270){
                new_x = h - 1 - j;
                new_y = i;
            }else if(rotate->angle == 90){
                new_x = j;
                new_y = w - 1 - i;
            }
            if (check_x_y(image, old_x, old_y) && new_x < h && new_y < w){
                png_byte *ptr = &(image->row_pointers[old_y][old_x * 3]);
                png_byte *ptrn = &(rot_pointers[new_y][new_x * 3]);
                for (int r = 0; r < 3; r++)
                    ptrn[r] = ptr[r];
            }
        }
    }
    return rot_pointers;
}

void rotate_png(png* image, user_input_data* rotate){
    int h = rotate->right_down_y - rotate->left_up_y;
    int w = rotate->right_down_x - rotate->left_up_x;
    if (rotate->angle == 90 || rotate->angle == 270){
        png_bytep* rotated;
        rotated = help_rotate(image, rotate, w, h);
        int x, y;
        x = rotate->left_up_x + w/2 - h/2;
        y = rotate->left_up_y + h/2 - w/2;
        int up_x, up_y;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                up_x = x + i;
                up_y = y + j;
                if (check_x_y(image, up_x, up_y)){
                    png_byte *ptr = &(image->row_pointers[up_y][up_x * 3]);
                    png_byte *ptrr = &(rotated[j][i * 3]);
                    for (int r = 0; r < 3; r++)
                        ptr[r] = ptrr[r]; 
                }
                
            }
        }
    }

    if (rotate->angle == 180) {
        png_bytep* help_pointer = malloc(sizeof(png_bytep));
        help_pointer[0] = (png_byte*)malloc(sizeof(png_bytep) * 3);
        png_byte *ptr = &(help_pointer[0][0]);
        int x, y, up_x, up_y, down_x, down_y;
        x = rotate->right_down_x-1;
        y = rotate->right_down_y-1;
        for (int i = 0; i < h/2; i++) {
            for (int j = 0; j < w; j++) {
                up_x = rotate->left_up_x + j;
                up_y = rotate->left_up_y + i;
                down_x = x - j;
                down_y = y - i;
                png_byte *ptr_up = &(image->row_pointers[up_y][up_x * 3]);
                png_byte *ptr_down = &(image->row_pointers[down_y][down_x * 3]);
                for (int r = 0; r < 3; r++){
                    ptr[r] = ptr_up[r];
                    ptr_up[r] = ptr_down[r];
                    ptr_down[r] = ptr[r];
                }
            }
        }
        if (h % 2 != 0) {
            int mid = rotate->left_up_y + h/2;
            int left_x, right_x;
            for (int j = 0; j < w / 2; j++) {
                left_x = rotate->left_up_x + j;
                right_x = rotate->right_down_x - j - 1;
                png_byte *ptr_left = &(image->row_pointers[mid][left_x * 3]);
                png_byte *ptr_right = &(image->row_pointers[mid][right_x * 3]);
                for (int r = 0; r < 3; r++){
                    ptr[r] = ptr_left[r];
                    ptr_left[r] = ptr_right[r];
                    ptr_right[r] = ptr[r];
                }
            }
        }
    }
}

//main func (print info, init input, read file, checks, funcs, write file)
int main (int argc, char **argv) {

    printf("Course work for option 4.24, created by Anastasiya Dorogushina.\n");

	user_input_data* input = init_input_data();
    non_arg_funcs(argc, argv);
    get_opt(input, argc, argv);
    
    if (strcmp(input->input, "None") == 0) {
        if (strstr(argv[argc-1], ".png")) {
            input->input = argv[argc-1];
            
        }
        else {
            printf("No input file\n");
            exit(45);
        }
    }

    if (strcmp(input->input, input->output) == 0) {
        printf("Input name = output name\n");
        exit(45);
    }

    png* image = malloc(sizeof(png));
    if(read_png_file(input->input, image)){
        printf("Error with reading\n");
        exit(45);
    }

	check_input(input);

    switch (input->func) {
        case 'i':
            print_info(image);
            exit(0);
        case 's':
            squared_lines(image, input);
            break;
        case 'r':
            rgb_filter(image, input);
            break;
        case 'e':
            if (check_x_y(image, input->left_up_x, input->left_up_y) && check_x_y(image, input->right_down_x, input->right_down_y))
                rotate_png(image, input);
            else{
                printf("Rotate area out of image\n");
                exit(45);
            }
            break;
        case 'k':
            square_rhombus(image, input);
            break;
    }

    write_png_file(input->output, image);

    return 0;
}
