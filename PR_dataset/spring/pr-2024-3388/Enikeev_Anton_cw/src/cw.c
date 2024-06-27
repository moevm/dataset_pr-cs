#include <stdio.h>
#include <png.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define PNG_SIG_SIZE 8
#define ERROR_CODE 40
#define MAX_RGB 255
#define MAX_FILENAME_LEN 255
#define FILE_OPEN_ERROR "Error: cannot open file %s\n"
#define PNG_SIG_ERROR "Error: the image format is not PNG\n"
#define PNG_STRUCT_INIT_ERROR "Error: failed to initialize the PNG read/write structure\n"
#define PNG_INFO_INIT_ERROR "Error: failed to initialize the PNG information structure\n"
#define PNG_READ_ERROR "Error: failed to read PNG file %s\n"
#define PNG_COLOR_TYPE_ERROR "Error: the program supports only RGB color type\n"
#define PNG_BIT_DEPTH_ERROR "Error: only 8-bit color depth is supported\n"
#define PNG_WRITE_IMAGE_ERROR "Error: failed to write PNG image data to file %s\n"
#define NEGATIVE_NUMBER_ERROR "Error: the %s must be a positive integer\n"
#define INVALID_COLOR_ERROR "Error: invalid color value - %s\n"
#define TOO_LONG_FILE_NAME "Error, the %s-file name is too long\n"
#define PNG_PATTERN_ERROR "Error: invalid pattern format - %s\n"
#define FRAMES_COUNT_EXCEEDED "Error: the number of square frames of the specified thickness exceeds the size of the image\n"
#define MEMORY_ALLOCATION_ERROR "Error: Unable to allocate memory\n"
#define NOT_ENOUGH_ARGS "Error: the required flag %s is missing to execute the main command.\n"
#define MAIN_COMM_MISSED "Please specify the main command. For reference, use the '--help' or '-h' flag.\n"
#define SAME_NAME_ERROR "Error: the name of the input and output file are the same, change the name of the output file\n"

typedef struct{
    unsigned int width, height;
    png_byte color_type; 
    png_byte bit_depth;
    png_structp png_ptr; 
    png_infop info_ptr; 
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

typedef struct{
    int key;
    int old_color[3];
    int new_color[3];
    char pattern[20];
    char *input;
    char *second_input;
    char *output;
    int color[3];
    double alpha;
    int beta;
    int thickness;
    int border_color[3];
    int count;
} Args;

void print_help(){
    printf("Course work for option 4.22, created by Enikeev Anton.\n");
    FILE *file = fopen("help", "rb");
    char ch;
    if (!file){
        fprintf(stderr, FILE_OPEN_ERROR, "help");
        exit(ERROR_CODE);
    }
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
}

void print_info(Png *img){
    printf("Image Width: %d\n", img->width);
    printf("Image Height: %d\n", img->height);
    printf("Image Bit Depth: %d\n", img->bit_depth);
    printf("Image Color Type: %d\n", img->color_type);
}

void initialize_args(Args *args) {
    for (int i = 0; i < 3; ++i) {
        args->old_color[i] = -1;
        args->new_color[i] = -1;
        args->color[i] = -1;
        args->border_color[i] = -1;
    }
    args->key = -1;
    args->thickness = -1;
    args->count = -1;
    args->alpha = -1.0;
    args->beta = -1;
    args->input = (char *)malloc(MAX_FILENAME_LEN * sizeof(char));
    args->second_input = (char *)malloc(MAX_FILENAME_LEN * sizeof(char));
    args->output = (char *)malloc(MAX_FILENAME_LEN * sizeof(char));
    strcpy(args->pattern, "default");
    strcpy(args->input, "default");
    strcpy(args->second_input, "default");
    strcpy(args->output, "out.png");
}

void free_image(Png *image){
    for (int y = 0; y < image->height; y++)
         free(image->row_pointers[y]);
    free(image->row_pointers);
}

void check_png_structs(Png *image, FILE *fp, int param) {
    if ((param == 1 && !image->png_ptr) || (param == 2 && !image->info_ptr)){
        fclose(fp);
        fprintf(stderr, PNG_STRUCT_INIT_ERROR);
        exit(ERROR_CODE);
    }
}

void read_png_file(const char *filename, Png *image) {
    png_byte png_sig[PNG_SIG_SIZE];
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, FILE_OPEN_ERROR, filename);
        exit(ERROR_CODE);
    }
    fread(png_sig, 1, PNG_SIG_SIZE, fp);
    if (png_sig_cmp(png_sig, 0, PNG_SIG_SIZE)) {
        fprintf(stderr, PNG_SIG_ERROR);
        exit(ERROR_CODE);
    }
    image -> png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    check_png_structs(image, fp, 1);
    image -> info_ptr = png_create_info_struct(image -> png_ptr);
    if (!image -> info_ptr) {
        png_destroy_read_struct(&(image -> png_ptr), NULL, NULL);
        fclose(fp);
        fprintf(stderr, PNG_INFO_INIT_ERROR);
        exit(ERROR_CODE);
    }

    if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_READ_ERROR, filename);
        exit(ERROR_CODE);
    }

    png_init_io(image -> png_ptr, fp);
    png_set_sig_bytes(image -> png_ptr, PNG_SIG_SIZE);
    png_read_info(image -> png_ptr, image -> info_ptr);

    image->width = png_get_image_width(image -> png_ptr, image ->info_ptr);
    image->height = png_get_image_height(image -> png_ptr, image -> info_ptr);
    image->color_type = png_get_color_type(image -> png_ptr, image -> info_ptr);
    image->bit_depth = png_get_bit_depth(image -> png_ptr, image -> info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);

    if (image -> color_type != PNG_COLOR_TYPE_RGB){
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_COLOR_TYPE_ERROR);
        exit(ERROR_CODE);
    }
    if (image -> bit_depth != 8){
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_BIT_DEPTH_ERROR);
        exit(ERROR_CODE);
    }

    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_READ_ERROR, filename);
        exit(ERROR_CODE);
    }

    image->row_pointers = (png_bytep *)malloc(sizeof(png_bytep)* image->height);

    for (int y = 0; y < image->height; y++){
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
}

void write_png_file(char *file_name, Png *image){
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        fprintf(stderr, FILE_OPEN_ERROR, file_name);
        exit(ERROR_CODE);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    check_png_structs(image, fp, 1);
    image->info_ptr = png_create_info_struct(image->png_ptr);
    check_png_structs(image, fp, 2);

    if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_READ_ERROR, file_name);
        exit(ERROR_CODE);
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_WRITE_IMAGE_ERROR, file_name);
        exit(ERROR_CODE);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
    image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_WRITE_IMAGE_ERROR, file_name);
        exit(ERROR_CODE);
    }

     png_write_image(image->png_ptr, image->row_pointers);

     if (setjmp(png_jmpbuf(image -> png_ptr))) {
        png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
        fclose(fp);
        fprintf(stderr, PNG_WRITE_IMAGE_ERROR, file_name);
        exit(ERROR_CODE);
    }

     png_write_end(image->png_ptr, NULL);
     png_destroy_read_struct(&(image -> png_ptr), &(image -> info_ptr), NULL);
     free_image(image);
     fclose(fp);
}

int is_num(char *word){
    for (int j = 0; word[j] != '\0'; j++){
        if (!isdigit(word[j]))
            return 0;
    }
    return 1;
}

void replace_colors(Png *image, int *old_color, int *new_color) {
    unsigned int height = image->height;
    unsigned int width = image->width;

    for (unsigned int y = 0; y < height; y++) {
        png_bytep row = image->row_pointers[y];
        for (unsigned int x = 0; x < width; x++) {
            png_bytep pixel = &row[x * 3];

            if (pixel[0] == old_color[0] && pixel[1] == old_color[1] && pixel[2] == old_color[2]) {
                pixel[0] = new_color[0];
                pixel[1] = new_color[1];
                pixel[2] = new_color[2];
            }
        }
    }
}

void set_pixel_color(Png *img, int x, int y, int *color) {
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        png_bytep row = img->row_pointers[y];
        png_bytep pixel = &(row[x * 3]);
        pixel[0] = color[0];
        pixel[1] = color[1];
        pixel[2] = color[2];
    }
}

void write_pixel_color(Png *img, int x, int y, int *color_RGB){
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        png_bytep row = img->row_pointers[y];
        png_bytep pixel = &(row[x * 3]);
        color_RGB[0] = pixel[0];
        color_RGB[1] = pixel[1];
        color_RGB[2] = pixel[2];
    }
}
void fill_circle(int center_x, int center_y, int radius, int *color, Png *img) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                if (center_x + x >= 0 && center_y + y >= 0) {
                    set_pixel_color(img, center_x + x, center_y + y, color);
                }
            }
        }
    }
}

void fill_circle_external(int center_x, int center_y, int radius, int *color, Png *img) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) > radius * radius) {
                set_pixel_color(img, x, y, color);
            }
        }
    }
}

void draw_thick_circle(int center_x, int center_y, int radius, int thickness, int *color, Png *img) {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while (y >= 0) {
        if (center_x + x  >= 0 && center_y + y >= 0) {
                set_pixel_color(img, center_x + x, center_y + y, color);
                fill_circle(center_x + x, center_y + y, (thickness + 1) / 2, color, img);
                set_pixel_color(img, center_x - x, center_y + y, color); 
                fill_circle(center_x - x, center_y + y, (thickness + 1) / 2, color, img);
                set_pixel_color(img, center_x + x, center_y - y, color);
                fill_circle(center_x + x, center_y - y, (thickness + 1) / 2, color, img);
                set_pixel_color(img, center_x - x, center_y - y, color);
                fill_circle(center_x - x, center_y - y, (thickness + 1) / 2, color, img);
        }
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }
}

void draw_line(int *color, int thickness, int beg_x, int beg_y, int end_x, int end_y, Png *img) {
    const int delta_x = abs(end_x - beg_x);
    const int delta_y = abs(end_y - beg_y);
    const int sign_x = beg_x < end_x ? 1 : -1;
    const int sign_y = beg_y < end_y ? 1 : -1;
    int error = delta_x - delta_y;
    set_pixel_color(img, end_x, end_y, color);
    fill_circle(end_x, end_y, (thickness + 1) / 2, color, img);
    while(beg_x != end_x || beg_y != end_y) 
   {
        set_pixel_color(img, beg_x, beg_y, color);
        fill_circle(beg_x, beg_y, (thickness + 1) / 2, color, img);
        int error2 = error * 2;
        if(error2 > -delta_y) 
        {
            error -= delta_y;
            beg_x += sign_x;
        }
        if(error2 < delta_x) 
        {
            error += delta_x;
            beg_y += sign_y;
        }
    }

}
int color_matching(int x, int y, int *color, Png *img){
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        png_bytep row = img->row_pointers[y];
        png_bytep pixel = &(row[x * 3]);
        if (
            pixel[0] == color[0] &&
            pixel[1] == color[1] &&
            pixel[2] == color[2]
        )
            return 1;
    }
    return 0;
}

void draw_rectangle_border(int *color, int thickness, int left_x, int left_y, int right_x, int right_y, Png *img) {
    draw_line(color, thickness, left_x - 1, left_y - 1, right_x + 1 , left_y - 1, img);
    draw_line(color, thickness, left_x - 1, right_y + 1, right_x + 1, right_y + 1, img);
    draw_line(color, thickness, left_x - 1, left_y - 1, left_x - 1, right_y + 1, img);
    draw_line(color, thickness, right_x + 1, left_y - 1, right_x + 1, right_y + 1, img);
}

void outline_rectangles_filled_color(int *color, int *border_color, int thickness, Png *img){
    int **checked = (int **)calloc(img->width, sizeof(int *));
    if (checked == NULL) {
        fprintf(stderr, MEMORY_ALLOCATION_ERROR);
        exit(ERROR_CODE);
    }

    for (int i = 0; i < img->width; i++) {
        checked[i] = (int *)calloc(img->height, sizeof(int));
        if (checked[i] == NULL) {
            fprintf(stderr, MEMORY_ALLOCATION_ERROR);
            exit(ERROR_CODE);
        }
    }

    for (int curr_x = 0; curr_x < img->width; curr_x++){
        for (int curr_y = 0; curr_y < img->height; curr_y++){
            if (!checked[curr_x][curr_y] && color_matching(curr_x, curr_y, color, img)){
                int new_x = curr_x;
                int new_y = curr_y;
                while (new_x < img->width && color_matching(new_x, curr_y, color, img)){
                    new_x++;
                }
                if (new_x != curr_x) {new_x--;}
                while (new_y < img->height && color_matching(curr_x, new_y, color, img)){
                    new_y++;
                }
                if (new_y != curr_y) {new_y--;}

                if ((new_x - curr_x + 1) * (new_y - curr_y + 1) >= 2){
                    int valid_rectangle = 1;
                    for (int i = curr_x; i <= new_x; i++) {
                        for (int j = curr_y; j <= new_y; j++) {
                            checked[i][j] = 1;
                            if (!color_matching(i, j, color, img)) {
                                valid_rectangle = 0;
                                break;
                            }
                        }

                        if (!valid_rectangle) {
                            break;
                        }   
                    }
                    if (valid_rectangle){
                        draw_rectangle_border(border_color, thickness, curr_x, curr_y, new_x, new_y, img);
                    }
                }
            }
        }
    }
    for (int i = 0; i < img->width; i++) {
        free(checked[i]);
    }
    free(checked);
}

void fill_rectangle(int *color, int left_x, int left_y, int right_x, int right_y, Png *img) {
    if (left_x > right_x) {
        int temp = left_x;
        left_x = right_x;
        right_x = temp;
    }
    if (left_y > right_y) {
        int temp = left_y;
        left_y = right_y;
        right_y = temp;
    }

    for (int y = left_y; y <= right_y; y++) {
        for (int x = left_x; x <= right_x; x++) {
            set_pixel_color(img, x, y, color);
        }
    }
}

void frame_rectangle(Png *img, int *color, int thickness, int count){
    for (int i = 0; i < count; i++){
        int x = 2*i * thickness;
        int y = 2*i * thickness;
        int x_new = img->width - 1 - 2*i * thickness;
        int y_new = (2*i + 1) * thickness - 1;
        int y_new_left = img->height - 1 - 2*i * thickness;
        int rigth_x = img->width - (2*i + 1) * thickness;
        int y_down = img->height - (2*i + 1) * thickness;
        if (x >= x_new || y >= y_new || y >= y_new_left || y_down >= y_new_left)
            return;
        fill_rectangle(color, x, y, x_new, y_new, img); //up
        fill_rectangle(color, x, y, y_new, y_new_left, img); //left
        fill_rectangle(color, rigth_x, y, x_new, y_new_left, img); //right
        fill_rectangle(color, x, y_down, x_new, y_new_left, img); //down
    }
}

void frame_circle(Png *img, int *color){
    int center_x = ceil(img->width / 2.0);
    int center_y = ceil(img->height / 2.0);
    int radius = fmin(center_x, center_y);
    fill_circle_external(center_x, center_y, radius, color, img);
}

void frame_semicircles(Png *img, int *color, int thickness, int count){
    int radius_x = fmax(1, ceil(img->width / (count * 2.0)));
    int radius_y = fmax(1, ceil(img->height / (count * 2.0)));
    for (int i = 0; i < count; i++){
        draw_thick_circle((2*i + 1) * radius_x, 0, radius_x, thickness, color, img);
        draw_thick_circle((2*i + 1) * radius_x, img->height - 1, radius_x, thickness, color, img);
        draw_thick_circle(0, (2*i + 1) * radius_y, radius_y, thickness, color, img);
        draw_thick_circle(img->width - 1, (2*i + 1) * radius_y, radius_y, thickness, color, img);
    }
}

void transfer_pixels(Png *new_image, Png *image, int start_x, int start_y) {
    int *color_RGB = (int *)malloc(3 *sizeof(int));
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            write_pixel_color(image, x, y, color_RGB);
            set_pixel_color(new_image, start_x + x, start_y + y, color_RGB);
        }
    }
    free(color_RGB);
}

void parse_color(char *color_str, int *color_array) {
    char *token;
    int i = 0;
    token = strtok(color_str, ".");

    while (token != NULL) {
        if (i > 3)
            break;
        
        if (!is_num(token)) {
            fprintf(stderr, INVALID_COLOR_ERROR, token);
            exit(ERROR_CODE);
        }

        int color_value = atoi(token);

        if (color_value < 0 || color_value > MAX_RGB) {
            fprintf(stderr, INVALID_COLOR_ERROR, token);
            exit(ERROR_CODE);
        }
        color_array[i++] = color_value;
        token = strtok(NULL, ".");
    }
    
    if (i != 3) {
        fprintf(stderr, INVALID_COLOR_ERROR, "incorrect number of color components");
        exit(ERROR_CODE);
    }
}
void make_conrt(Png *image, double alpha, int beta){
    int *color = (int *)malloc(3*sizeof(int));
    for (int x = 0; x < image->width; x++){
        for (int y = 0; y < image->height; y++){
            write_pixel_color(image, x, y, color);
            int first = (int)(alpha * (double)color[0]);
            int second = (int)(alpha *(double)color[1]);
            int third = (int)(alpha * (double)color[2]);
            int res_f = first + beta;
            int res_s = second + beta;
            int res_th = third + beta;
            if (res_f - MAX_RGB >0){
                res_f = res_f - (res_f - MAX_RGB);
            }
            if (res_s - MAX_RGB > 0){
                res_s = res_s - (res_s - MAX_RGB);
            }
            if (res_th - MAX_RGB > 0){
                res_th = res_th - (res_th - MAX_RGB);
            }
            color[0] = res_f;
            color[1] = res_s;
            color[2] = res_th;
            set_pixel_color(image, x, y, color);
        }
    }
    free(color);
}
void create_empty_image(Png *img, Png *new_img, int height, int width, int *color) {
    new_img->width = width;
    new_img->height = height;
    new_img->color_type = img->color_type;
    new_img->bit_depth = img->bit_depth;
    new_img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!new_img->png_ptr) {
        fprintf(stderr, PNG_STRUCT_INIT_ERROR);
        exit(ERROR_CODE);
    }
    new_img->info_ptr = png_create_info_struct(new_img->png_ptr);
    if (!new_img->info_ptr) {
        png_destroy_read_struct(&(new_img -> png_ptr), NULL, NULL);
        fprintf(stderr, PNG_INFO_INIT_ERROR);
        exit(ERROR_CODE);
    }
    png_read_update_info(new_img->png_ptr, new_img->info_ptr);
    new_img->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * new_img->height);
    for (int y = 0; y < new_img->height; y++) {
        new_img->row_pointers[y] = (png_byte *) malloc((png_get_rowbytes(img->png_ptr, img->info_ptr) / img->width) * new_img->width);

    }
    if (color[0] != -1) {
        for (int y = 0; y < new_img->height; y++) {
            for (int x = 0; x < new_img->width; x++) {
                set_pixel_color(new_img, x, y, color);
            }
        }
    }
}

void process_option_r(Args *args, Png *image){
    if (args->old_color[0] == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--old_color/-s");
        exit(ERROR_CODE);
    }
    if (args->new_color[0] == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--new_color/-n");
        exit(ERROR_CODE);
    }
    replace_colors(image, args->old_color, args->new_color);
    write_png_file(args->output, image);
}

void process_option_d(Args *args, Png *image, Png *new_image){
    if (strcmp(args->pattern, "default") == 0){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--pattern/-p");
        exit(ERROR_CODE);
    }else if (args->color[0] == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--color/-c");
        exit(ERROR_CODE);
    }
    if (strcmp(args->pattern, "circle")){
        if (args->thickness == -1){
            fprintf(stderr, NOT_ENOUGH_ARGS, "--thickness/-t");
            exit(ERROR_CODE);
        }else if (args->count == -1 && strcmp(args->pattern, "square")){
            fprintf(stderr, NOT_ENOUGH_ARGS, "--count/-u");
            exit(ERROR_CODE);
        }
    }

    if (strcmp(args->pattern, "rectangle") == 0){
        frame_rectangle(image, args->color, args->thickness, args->count);
        write_png_file(args->output, image);
    }else if (strcmp(args->pattern, "circle") == 0){
        frame_circle(image, args->color);
        write_png_file(args->output, image);
    }else if (strcmp(args->pattern, "semicircles") == 0){
        frame_semicircles(image, args->color, args->thickness, args->count);
        write_png_file(args->output, image);
    }else if(strcmp(args->pattern, "square") == 0){
        create_empty_image(image, new_image, image->height + 2*args->thickness, image->width + 2*args->thickness, args->color);
        transfer_pixels(new_image, image, args->thickness + 1, args->thickness + 1);
        write_png_file(args->output, new_image);
    }
    else{
        fprintf(stderr, PNG_PATTERN_ERROR, args->pattern);
        exit(ERROR_CODE);
    }
}

void process_option_k(Args *args, Png *image){
    if (args->color[0] == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--color/-c");
        exit(ERROR_CODE);
    }else if (args->thickness == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--thickness/-t");
        exit(ERROR_CODE);
    }else if (args->border_color[0] == -1){
        fprintf(stderr, NOT_ENOUGH_ARGS, "--border_color/-b");
        exit(ERROR_CODE);
    }
    outline_rectangles_filled_color(args->color, args->border_color, args->thickness, image);
    write_png_file(args->output, image);
}

void parse_arguments(int argc, char *argv[], Args *args){
    struct option long_options[] = {
        {"info", no_argument, NULL, 'f'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"help", no_argument, NULL, 'h'},
        {"color_replace", no_argument, NULL, 'r'},
        {"old_color", required_argument, NULL, 's'},
        {"new_color", required_argument, NULL, 'n'},
        {"ornament", no_argument, NULL, 'd'},
        {"pattern", required_argument, NULL, 'p'},
        {"color", required_argument, NULL, 'c'},
        {"thickness", required_argument, NULL, 't'},
        {"count", required_argument, NULL, 'u'},
        {"filled_rects", no_argument, NULL, 'k'},
        {"border_color", required_argument, NULL, 'b'},
        {"contrast", no_argument, NULL, 'v'},
        {"alpha", required_argument, NULL, 'X'},
        {"beta", required_argument, NULL, 'Y'},
        {NULL, 0, NULL, 0}
    };
    char *short_opts = "fhrvdks:n:X:Y:p:c:b:t:u:i:o:";
    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1){
        switch (opt)
        {
        case 'f':
            args->key = 'f';
            break;
        case 'h':
            args->key = 'h';
            break;
        case 'r':
            args->key = 'r';
            break;
        case 'd':
            args->key = 'd';
            break;
        case 'k':
            args->key = 'k';
            break;
        case 'v':
            args->key = 'v';
            break;
        case 'X':
            args->alpha = atof(optarg);
            break;
        case 'Y':
            args->beta = atoi(optarg);
            break;
        case 'i':
            if (strlen(optarg) > MAX_FILENAME_LEN){
                fprintf(stderr, TOO_LONG_FILE_NAME, "input");
                break;
            }
            strncpy(args->input, optarg, MAX_FILENAME_LEN);
            if (optind < argc && argv[optind][0] != '-'){
                if (strlen(argv[optind]) > MAX_FILENAME_LEN){
                    fprintf(stderr, TOO_LONG_FILE_NAME, "second_input");
                    break;
                }
                strncpy(args->second_input, argv[optind], MAX_FILENAME_LEN);
            }
            break;
        case 'o':
            if (strlen(optarg) > MAX_FILENAME_LEN){
                fprintf(stderr, TOO_LONG_FILE_NAME, "output");
                exit(ERROR_CODE);
            }
            strncpy(args->output, optarg, MAX_FILENAME_LEN);
            break;
        case 's':
            parse_color(optarg, args->old_color);
            break;
        case 'n':
            parse_color(optarg, args->new_color);
            break;
        case 'p':
            if (strlen(optarg) > sizeof(args->pattern) - 1){
                fprintf(stderr, PNG_PATTERN_ERROR, optarg);
                exit(ERROR_CODE);
            }
            strncpy(args->pattern, optarg, sizeof(args->pattern));
            break;
        case 'c':
            parse_color(optarg, args->color);
            break;
        case 'b':
            parse_color(optarg, args->border_color);
            break;
        case 't':
            if (!is_num(optarg)){
                fprintf(stderr, NEGATIVE_NUMBER_ERROR, "thickness");
                exit(ERROR_CODE);
            }
            int th = atoi(optarg);
            if (th <= 0){
                fprintf(stderr, NEGATIVE_NUMBER_ERROR, "thickness");
                exit(ERROR_CODE);
            }
            args->thickness = th;
            break;
        case 'u':
            if (!is_num(optarg)){
                fprintf(stderr, NEGATIVE_NUMBER_ERROR, "count");
                exit(ERROR_CODE);
            }
            int cnt = atoi(optarg);
            if (cnt <= 0){
                fprintf(stderr, NEGATIVE_NUMBER_ERROR, "count");
                exit(ERROR_CODE);
            }
            args->count = cnt;
            break;
        default:
            break;
        }
    }
}

void image_processing(int argc, char **argv, Args *args, Png *image, Png *new_image){
    if (args->key == -1){
        fprintf(stderr, MAIN_COMM_MISSED);
        exit(ERROR_CODE);
    }

    if (strcmp(args->input, "default") == 0 && strcmp(argv[argc - 1], args->output) != 0){
        read_png_file(argv[argc - 1], image);
    }else if (strcmp(args->input, args->output) != 0){
        read_png_file(args->input, image);
    }else{
        fprintf(stderr, SAME_NAME_ERROR);
        exit(ERROR_CODE);
    }

    switch (args->key){
        case 'h':
            print_help();
            break;
        case 'f':
            print_info(image);
            return;
        case 'v':
            make_conrt(image, args->alpha, args->beta);
            write_png_file(args->output, image);
            break;
        case 'r':
            process_option_r(args, image);
            break;
        case 'd':
            process_option_d(args, image, new_image);
            break;
        case 'k':
            process_option_k(args, image);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv){
    if (argc <= 1 || argc == 2){
        print_help();
        return 0;
    }
    Args args;
    Png image, new_image;
    initialize_args(&args);
    parse_arguments(argc, argv, &args);
    image_processing(argc, argv, &args, &image, &new_image);
    free(args.input);
    free(args.output);
    free(args.second_input);
    return 0;
}
