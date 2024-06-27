#include "image_processing.h"

void get_points(char* string, int* x1, int* y1, int* x2, int* y2, int* x3, int* y3, regmatch_t groupArray[]){
    char* number;
    int group_number = 1;
    int buffer[3][2];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++){
            number = calloc(MAX_STRING, sizeof(char));
            for(int k = groupArray[group_number].rm_so; k < groupArray[group_number].rm_eo; k++)
                number[k - groupArray[group_number].rm_so] = string[k];
            buffer[i][j] = atoi(number);
            group_number++;
        }
    *x1 = buffer[0][0];
    *y1 = buffer[0][1];
    *x2 = buffer[1][0];
    *y2 = buffer[1][1];
    *x3 = buffer[2][0];
    *y3 = buffer[2][1];
}

int get_color(char* string, int buffer[3], regmatch_t groupArray[]){
    char* number;
    int index;
    for(int i = 0; i < 3; i++){
        number = calloc(MAX_STRING, sizeof(char));
        index = 0;
        for(int k = groupArray[i+1].rm_so; k < groupArray[i+1].rm_eo; k++)
            number[index++] = string[k];
        buffer[i] = atoi(number);
        if(buffer[i] < 0 || buffer[i] > 255){
            return 1;
        }
    }
    return 0;
}

int point_is_in(Png* image, int x, int y){
    if(x >= 0 && x < image->width && y >= 0 && y < image->height)
        return 1;
    return 0;
}

void set_pixel(Png* image, int x, int y, int color[3]){
    if(point_is_in(image, x, y)){
        image->row_pointers[y][x * image->channels + 0] = color[0];
        image->row_pointers[y][x * image->channels + 1] = color[1];
        image->row_pointers[y][x * image->channels + 2] = color[2];
        if(image->channels == 4)
            image->row_pointers[y][x * image->channels + 3] = 255;
    }
}

void draw_thin_line(Png* image, int x0, int y0, int x1, int y1, int color[3]){
  int dy = y1 - y0;
  int dx = x0 - x1;

  int signa = dy < 0 ? -1 : 1;
  int signb = dx < 0 ? -1 : 1;
  int f = 0;
  set_pixel(image, x0, y0, color);
  
  if (abs(dy) <= abs(dx)){
    do {
      f += dy * signa;
      if (f > 0){
        f -= dx * signb;
        y0 += signa;
      }
      x0 -= signb;
      set_pixel(image, x0, y0, color);
    } while (x0 != x1 || y0 != y1);
  } else {
    do {
      f += dx * signb;
      if (f > 0){
        f -= dy * signa;
        x0 -= signb;
      }
      y0 += signa;
      set_pixel(image, x0, y0, color);
    } while (x0 != x1 || y0 != y1);
  }
}

void draw_line(Png* image, int x1, int y1, int x2, int y2, int color[3], int thickness){
    draw_thin_line(image, x1, y1, x2, y2, color);
    for(int i = 1; i <= (thickness - 1) / 2; i++){
        if(abs(x1-x2) >= abs(y1-y2)){
            draw_thin_line(image, x1, y1 + i, x2, y2 + i, color);
            draw_thin_line(image, x1, y1 - i, x2, y2 - i, color);
        } else{
            draw_thin_line(image, x1 + i, y1, x2 + i, y2, color);
            draw_thin_line(image, x1 - i, y1, x2 - i, y2, color);
        }
    }
    if(thickness % 2 == 0){
        if(abs(x1-x2) >= abs(y1-y2)){
            draw_thin_line(image, x1, y1 + 1, x2, y2 + 1, color);
        } else{
            draw_thin_line(image, x1 + 1, y1, x2 + 1, y2, color);
        }
    }
}

Png* create_new_image(Png* image, int width, int height){
    Png* new_image = malloc(sizeof(Png));

    new_image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!new_image->png_ptr) {
        printf("Error in make_empty_image function: png_create_read_struct failed.\n");
        exit(20);
    }
    new_image->info_ptr = png_create_info_struct(new_image->png_ptr);

    new_image->width = width;
    new_image->height = height;
    new_image->color_type = image->color_type;
    new_image->bit_depth = image->bit_depth;
    new_image->channels = image->channels;

    png_read_update_info(new_image->png_ptr, new_image->info_ptr);

    new_image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * new_image->height);
    for (int y = 0; y < new_image->height; y++)
        new_image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr) / image->width * new_image->width);
    
    return new_image;
}

void draw_octagon(Png* image, int x, int y, int xc, int yc, int color[3]){
    set_pixel(image, xc+x, yc+y, color);
    set_pixel(image, xc-x, yc+y, color);
    set_pixel(image, xc+x, yc-y, color);
    set_pixel(image, xc-x, yc-y, color);
    set_pixel(image, xc+y, yc+x, color);
    set_pixel(image, xc-y, yc+x, color);
    set_pixel(image, xc+y, yc-x, color);
    set_pixel(image, xc-y, yc-x, color);
}

void draw_circle(Png* image, int xc, int yc, int radius, int thickness, int color[3]) {
    for(int i = 0; i < thickness; i++){	
        int x = 0;
        int y = abs(radius - i);
        int delta = 1 - 2 * radius;
        int error = 0;
        while(y >= 0) {
            draw_octagon(image, x, y, xc, yc, color);
            error = 2 * (delta + y) - 1;
            if(delta < 0 && error <= 0) {
                x++;
                delta += 2 * x + 1;
                continue;
            }
            if(delta > 0 && error > 0) {
                y--;
                delta += 1 - 2 * y;
                continue;
            }
            x++;
            delta += 2 * (x - y);
            y--;
        }
    }
}

Png* copy(Png* image, int x1, int y1, int x2, int y2){
    int height = y2-y1+1;
    int width = x2-x1+1;
    Png* new_image = create_new_image(image, width, height);
    for(int y = 0; y < height;  y++)
        for(int x = 0; x < width; x++){
            png_byte* ptr = &(image->row_pointers[y+y1][(x + x1)*image->channels]);
            png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
            for(int k = 0; k < image->channels; k++)
                new_ptr[k] = ptr[k];
        }
    return new_image;
}

void rotate_90(Png* image){
    Png* new_image = create_new_image(image, image->height, image->width);
    for(int y = 0; y < image->height; y++)
        for(int x = 0; x < image->width; x++){
            png_byte* ptr = &(image->row_pointers[y][x*image->channels]);
            png_byte* new_ptr = &(new_image->row_pointers[x][(new_image->width - y - 1)*image->channels]);
            for(int k = 0; k < image->channels; k++)
                new_ptr[k] = ptr[k];
        }
    *image =  *new_image;
}

void rotate_180(Png* image){
    Png* new_image = create_new_image(image, image->height, image->width);
    for(int y = 0; y < image->height; y++)
        for(int x = 0; x < image->width; x++){
            png_byte* ptr = &(image->row_pointers[y][(new_image->height - x - 1)*image->channels]);
            png_byte* new_ptr = &(new_image->row_pointers[x][(new_image->width - y - 1)*image->channels]);
            for(int k = 0; k < image->channels; k++)
                new_ptr[k] = ptr[k];
        }
    *image =  *new_image;
}

void rotate_270(Png* image){
    Png* new_image = create_new_image(image, image->height, image->width);
    for(int y = 0; y < image->height; y++)
        for(int x = 0; x < image->width; x++){
            png_byte* ptr = &(image->row_pointers[y][(new_image->height - x - 1)*image->channels]);
            png_byte* new_ptr = &(new_image->row_pointers[x][y*image->channels]);
            for(int k = 0; k < image->channels; k++)
                new_ptr[k] = ptr[k];
        }
    *image =  *new_image;
}

void mirror(Png* image){
    for(int y = 0; y < image->height; y++)
        for(int x = 0; x < image->width / 2; x++){
            png_byte* ptr_left = &(image->row_pointers[y][x*image->channels]);
            png_byte* ptr_right = &(image->row_pointers[y][(image->width - x - 1)*image->channels]);
            for(int k = 0; k < image->channels; k++){
                png_byte tmp = ptr_right[k];
                ptr_right[k] = ptr_left[k];
                ptr_left[k] = tmp;
            }
        }
}

int paste(Png* image, Png* piece, int x1, int y1){
    if(piece->width + x1 > image->width || piece->height + y1 > image->height)
        return 0;
    for(int y = 0; y < piece->height; y++)
        for(int x = 0; x < piece->width; x++){
            png_byte* ptr = &(image->row_pointers[y+y1][(x+x1)*image->channels]);
            png_byte* piece_ptr = &(piece->row_pointers[y][x*image->channels]);
            for(int k = 0; k < image->channels; k++)
                ptr[k] = piece_ptr[k];
        }
    return 1;
}

int is_in_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3){
    if(((x1-x0)*(y2-y1)-(x2-x1)*(y1-y0))*((x2-x0)*(y3-y2)-(x3-x2)*(y2-y0))*((x3-x0)*(y1-y3)-(x1-x3)*(y3-y0)) == 0)
        return 0;
    int sign_1 = (x1-x0)*(y2-y1)-(x2-x1)*(y1-y0) > 0 ? 1 : -1;
    int sign_2 = (x2-x0)*(y3-y2)-(x3-x2)*(y2-y0) > 0 ? 1 : -1;
    int sign_3 = (x3-x0)*(y1-y3)-(x1-x3)*(y3-y0) > 0 ? 1 : -1;
    if(sign_1 == sign_2 && sign_2 == sign_3)
        return 1;
    else
        return -1;
}

void draw_triangle(Png* image, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int color[3], int fill, int fill_color[3]){
    if(fill)
        for(int i = 0; i < image->height; i++)
            for(int j = 0; j < image->width; j++)
                if(is_in_triangle(j, i, x1, y1, x2, y2, x3, y3) == 1)
                    set_pixel(image, j, i, fill_color);

    draw_line(image, x1, y1, x3, y3, color, thickness);
    draw_line(image, x1, y1, x2, y2, color, thickness);
    draw_line(image, x3, y3, x2, y2, color, thickness);
}

int check_color(Png* image, int x, int y, int color[3]){
    if(!point_is_in(image, x, y))
        return 0;
    for(int i = 0; i < 3; i++)
        if(image->row_pointers[y][x*image->channels + i] != color[i])
            return 0;
    return 1;
}

int* find_biggest_rect(Png* image, int color[3]){
    int max_area = 0;
    int current_area, max_current_area;
    int a, b;
    int x1, y1, x2, y2;
    int a_max, b_max;

    for(int x = 0; x < image->width; x++)
        for(int y = 0; y < image->height; y++)
            if(check_color(image, x, y, color) && (!check_color(image, x-1, y, color) || !check_color(image, x, y-1, color))){
                int b_current_max = image->height;
                max_current_area = 0;
                a = 0, b = 0;
                while(point_is_in(image, x + a, y) && check_color(image, x + a, y, color)){
                    while(point_is_in(image, x + a, y + b) && check_color(image, x + a, y + b, color)){
                        b++;
                        if(b > b_current_max)
                            break;
                        current_area = (a+1)*b;
                    }

                    if(current_area > max_current_area){
                        max_current_area = current_area;
                        a_max = a;
                        b_max = b - 1;
                        b_current_max = b - 1;
                    }
                    current_area = 0;
                    b = 0;
                    a++;
                }

                if(max_current_area > max_area){
                        max_area = max_current_area;
                        x1 = x, y1 = y;
                        x2 = x + a_max, y2 = y + b_max;                 
                }
            }
    
    if(max_area == 0){
        int* result = malloc(4 * sizeof(int));
        result[0] = -1, result[1] = -1, result[2] = -1, result[3] = -1;
        return result;
    }

    int* result = malloc(4 * sizeof(int));
    result[0] = x1, result[1] = y1, result[2] = x2, result[3] = y2;
    return result;
}

void recolor_biggest_rect(Png* image, int old_color[3], int new_color[3]){
    int* coordinates = find_biggest_rect(image, old_color);
    for(int x = coordinates[0]; x <= coordinates[2]; x++)
        for(int y = coordinates[1]; y <= coordinates[3]; y++)
            set_pixel(image, x, y, new_color);
}

void make_collage(Png* image, int number_x, int number_y){
    Png* new_image = create_new_image(image, image->width*number_x, image->height*number_y);
    
    png_byte* new_ptr;
    png_byte* ptr;
    
    for(int i = 0; i < number_x; i++)
        for(int j = 0; j < number_y; j++)
            for(int y = 0; y < image->height; y++)
                for(int x = 0; x < image->width; x++){
                    new_ptr = &(new_image->row_pointers[y+j*image->height][(x + i*image->width)*image->channels]);
                    ptr = &(image->row_pointers[y][x*image->channels]);
                    for(int k = 0; k < image->channels; k++)
                        new_ptr[k] = ptr[k];
                }

    *image = *new_image;
}

void shift(Png* image, int step, int axis){
    Png* new_image = create_new_image(image, image->width, image->height);
    Png* super_new_image = create_new_image(image, image->width, image->height);
    switch(axis){
    case 0:
        for(int y = 0; y < image->height; y++){
            for(int x = step; x < image->width; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][(x)*image->channels]);
                png_byte* ptr = &(image->row_pointers[y][(x-step)*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
            for(int x = 0; x < step; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(image->row_pointers[y][(image->width - step + x)*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}}
        break;
    case 1:
        for(int y = step; y < image->height; y++)
            for(int x = 0; x < image->width; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(image->row_pointers[y-step][x*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
        for(int y = 0; y < step; y++)
            for(int x = 0; x < image->width; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(image->row_pointers[image->height - step + y][x*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
        break;
    case 2:
        for(int y = step; y < image->height; y++)
            for(int x = 0; x < image->width; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(image->row_pointers[y-step][x*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
        for(int y = 0; y < step; y++)
            for(int x = 0; x < image->width; x++){
                png_byte* new_ptr = &(new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(image->row_pointers[image->height - step + y][x*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
        for(int y = 0; y < image->height; y++){
            for(int x = step; x < image->width; x++){
                png_byte* new_ptr = &(super_new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(new_image->row_pointers[y][(x-step)*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}
            for(int x = 0; x < step; x++){
                png_byte* new_ptr = &(super_new_image->row_pointers[y][x*image->channels]);
                png_byte* ptr = &(new_image->row_pointers[y][(image->width - step + x)*image->channels]);
                for(int k = 0; k < image->channels; k++)
                    new_ptr[k] = ptr[k];}}
        break;
    }
    if(axis == 2)
        *image = *super_new_image;
    else
        *image = *new_image;
    
}

void binarization(Png* image, int threshold){
    for(int y = 0; y < image->height; y++)
        for(int x = 0; x < image->width; x++){
            int color[3];
            png_byte* ptr = &(image->row_pointers[y][x*image->channels]);
            int sum = 0;
            for(int k = 0; k < image->channels; k++)
                sum += ptr[k];
            if(sum >= threshold)
                color[0] = 255, color[1] = 255, color[2] = 255;
            else
                color[0] = 0, color[1] = 0, color[2] = 0;
            set_pixel(image, x, y, color);
        }
}

void image_processing(int argc, char* argv[], Png* image, char** output_file, char* input_file){

    int opt;
    char* options = "-sztbcfhFP:T:C:L:O:o:i:N:X:Y:S:A:H:?";
    int option_index = 0;
    optind = 0;
    int input_is_set = 0;
    struct option long_options[] = {
        {"triangle", 0, NULL, 't'},
        {"biggest_rect", 0, NULL, 'b'},
        {"collage", 0, NULL, 'c'},
        {"info", 0, NULL, 'f'},
        {"help", 0, NULL, 'h'},
        {"input", 1, NULL, 'i'},
        {"output", 1, NULL, 'o'},
        {"points", 1, NULL, 'P'},
        {"thickness", 1, NULL, 'T'},
        {"color", 1, NULL, 'C'},
        {"fill", 0, NULL, 'F'},
        {"fill_color", 1, NULL, 'L'},
        {"old_color", 1, NULL, 'O'},
        {"new_color", 1, NULL, 'N'},
        {"number_y", 1, NULL, 'Y'},
        {"number_x", 1, NULL, 'X'},
        {"shift", 0, NULL, 's'},
        {"step", 1, NULL, 'S'},
        {"axis", 1, NULL, 'A'},
        {"binarization", 0, NULL, 'z'},
        {"threshold", 1, NULL, 'H'},
        {0, 0, 0, 0}
    };

    char* regexColor = "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$";
    regex_t regexColorCompiled;
    size_t maxColorGroups = 4;
    regcomp(&regexColorCompiled, regexColor, REG_EXTENDED);
    regmatch_t groupArrayColor[maxColorGroups];

    char* regexPoints = "([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)";
    regex_t regexPointsCompiled;
    size_t maxPointsGroups = 7;
    regcomp(&regexPointsCompiled, regexPoints, REG_EXTENDED);
    regmatch_t groupArrayPoints[maxPointsGroups];
    
    char key = 0;

    int x1, x2, x3, y1, y2, y3;
    int thickness;
    int color[3];
    int fill_color[3];
    int p_is_set = 0;
    int t_is_set = 0;
    int c_is_set = 0;
    int f_is_set = 0;
    int fc_is_set = 0;

    int old_color[3];
    int new_color[3];
    int O_is_set = 0;
    int N_is_set = 0;

    int x, y;
    int x_is_set = 0;
    int y_is_set = 0;

    int step;
    int axis;
    int s_is_set = 0;
    int a_is_set = 0;    

    int threshold;
    int h_is_set = 0;

    while((opt = getopt_long(argc, argv, options, long_options, &option_index)) != -1){
        switch(opt){
        case 't':
        case 'b':
        case 'c':
        case 's':
        case 'z':
            key = opt;
            break;

        case 'P':
            if(regexec(&regexPointsCompiled, optarg, maxPointsGroups, groupArrayPoints, 0) == REG_NOMATCH)
                raise_error("Wrong argument for --points.");
            get_points(optarg, &x1, &y1, &x2, &y2, &x3, &y3, groupArrayPoints);           
            p_is_set = 1;
            break;
        case 'T':
            if(atoi(optarg) <= 0)
                raise_error("Wrong argument for --thickness.");
            thickness = atoi(optarg);
            t_is_set = 1;
            break;
        case 'C':
            if(regexec(&regexColorCompiled, optarg, maxColorGroups, groupArrayColor, 0) == REG_NOMATCH || get_color(optarg, color, groupArrayColor))
                raise_error("Wrong argument for --color.");
            get_color(optarg, color, groupArrayColor);
            c_is_set = 1;
            break;
        case 'F':
            f_is_set = 1;
            break;
        case 'L':
            if(regexec(&regexColorCompiled, optarg, maxColorGroups, groupArrayColor, 0) == REG_NOMATCH || get_color(optarg, fill_color, groupArrayColor))
                raise_error("Wrong argument for --color.");
            get_color(optarg, fill_color, groupArrayColor);
            fc_is_set = 1;
            break;


        case 'O':
            if(regexec(&regexColorCompiled, optarg, maxColorGroups, groupArrayColor, 0) == REG_NOMATCH || get_color(optarg, old_color, groupArrayColor))
                raise_error("Wrong argument for --old_color.");               
            O_is_set = 1;
            break;
        case 'N':
            if(regexec(&regexColorCompiled, optarg, maxColorGroups, groupArrayColor, 0) == REG_NOMATCH || get_color(optarg, new_color, groupArrayColor))
                raise_error("Wrong argument for --new_color.");               
            N_is_set = 1;
            break;


        case 'X':
            if(atoi(optarg) <= 0)
                raise_error("Wrong argument for --number_x.");                     
            x = atoi(optarg);
            x_is_set = 1;
            break;
        case 'Y':
            if(atoi(optarg) <= 0)
                raise_error("Wrong argument for --number_y.");               
            y = atoi(optarg);
            y_is_set = 1;
            break;


        case 'A':
            if(!strcmp(optarg, "x"))
                axis = 0;
            else if(!strcmp(optarg, "y"))
                axis = 1;
            else if(!strcmp(optarg, "xy"))
                axis = 2;
            else
                raise_error("Wrong argument for --axis.");
            a_is_set = 1;
            break;
        case 'S':               
            step = atoi(optarg);
            s_is_set = 1;
            break;

        case 'H':
            if(atoi(optarg) <= 0)
                raise_error("Wrong argument for --threshold.");        
            threshold = atoi(optarg);
            h_is_set = 1;
            break;

        case 'o':
            if(!strcmp(optarg, input_file))
                raise_error("Names of the input and output files are the same.");
            *output_file = strdup(optarg);
            break;
        case 'f':
            info(image);
            exit(0);
        case 'i':
            input_is_set = 1;
            break;
        case 'h':
            print_help();
            exit(0);
        case '?':
            raise_error("Wrong option.");
        case 1:;
            char* message = malloc(MAX_STRING*sizeof(char));
            sprintf(message, "Argument \"%s\" was unidentified and ignored.", optarg);
            opt = getopt_long(argc, argv, options, long_options, &option_index);
            if(opt != -1 || input_is_set == 1)
                raise_error(message);
            break;
        }
    }



    switch(key){
        case 't':
            if(p_is_set + t_is_set + c_is_set - f_is_set + fc_is_set < 3)
                raise_error("Not all options were set for --triangle.");
            draw_triangle(image, x1, y1, x2, y2, x3, y3, thickness, color, f_is_set, fill_color);
            break;
        case 'b':
            if(N_is_set + O_is_set < 2)
                raise_error("Not all options were set for --biggest_rect.");
            recolor_biggest_rect(image, old_color, new_color);
            break;
        case 'c':
            if(x_is_set + y_is_set < 2)
                raise_error("Not all options were set for --collage.");
            make_collage(image, x, y);
            break;
        case 's':
            if(a_is_set + s_is_set < 2)
                raise_error("Not all options were set for --shift.");
            shift(image, step, axis);
            break;
        case 'z':
            if(h_is_set == 0)
                raise_error("Not all options were set for --binarization.");
            binarization(image, threshold);
            break;
        case 0:
            printf("No command was entered.\n");
            print_help();
            exit(0);
            break;
    }

    if(!strcmp(*output_file, BLANK_STRING))
        *output_file = strdup("out.png");
}