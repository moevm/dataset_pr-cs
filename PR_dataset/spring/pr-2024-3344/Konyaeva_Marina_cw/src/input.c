#include "input.h"

void read_png_file(char *file_name, struct Png *img) {

    char header[8];    // 8 is the maximum size that can be checked
    /* open file and test for it being a png */

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        printf("Error in read_png_file function: file could not be opened.\n");
        exit(40);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        printf("Error in read_png_file function: file is not recognized as a PNG.\n");
        exit(41);
    }

    /* initialize stuff */
    img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!img->png_ptr){
        printf("Error in read_png_file function: png_create_read_struct failed.\n");
        exit(42);
    }

    img->info_ptr = png_create_info_struct(img->png_ptr);
    if (!img->info_ptr){
        printf("Error in read_png_file function: png_create_info_struct failed.\n");
        exit(40);
    }

    if (setjmp(png_jmpbuf(img->png_ptr))){
        fclose(fp);
        printf("Error in read_png_file function: error during init_io.\n");
        exit(43);
    }

    png_init_io(img->png_ptr, fp);
    png_set_sig_bytes(img->png_ptr, 8);

    png_read_info(img->png_ptr, img->info_ptr);

    img->width = png_get_image_width(img->png_ptr, img->info_ptr);
    img->height = png_get_image_height(img->png_ptr, img->info_ptr);
    img->color_type = png_get_color_type(img->png_ptr, img->info_ptr);
    img->bit_depth = png_get_bit_depth(img->png_ptr, img->info_ptr);
    //есть channels а есть numofpasses
    img->number_of_passes = png_set_interlace_handling(img->png_ptr);
    img->channels = png_get_channels(img->png_ptr, img->info_ptr);
    
    if (img->color_type == PNG_COLOR_TYPE_GRAY) {
        printf("The program does not support working with the PNG_COLOR_TYPE_GRAY color type.\n");
        exit(44);
    } else if (img->color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        printf("The program does not support working with the PNG_COLOR_TYPE_GRAY_ALPHA color type.\n");
        exit(45);
    } else if (img->color_type == PNG_COLOR_TYPE_PALETTE) {
        printf("The program does not support working with the PNG_COLOR_TYPE_PALETTE color type.\n");
        exit(46);
    }

    png_read_update_info(img->png_ptr, img->info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(img->png_ptr))){
        printf("Error in read_png_file function: error during read_img.\n");
        exit(47);
    }

    img->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * img->height);
    for (int y = 0; y < img->height; y++)
        img->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(img->png_ptr, img->info_ptr));

    png_read_image(img->png_ptr, img->row_pointers);

    fclose(fp);
}


void write_png_file(char *file_name, struct Png *img) {

    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf("Error in write_png_file function: file could not be opened.\n");
        exit(40);
    }

    /* initialize stuff */
    img->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!img->png_ptr){
        printf("Error in write_png_file function: png_create_write_struct failed.\n");
        exit(41);
    }

    img->info_ptr = png_create_info_struct(img->png_ptr);
    if (!img->info_ptr){
        printf("Error in write_png_file function: png_create_info_struct failed.\n");
        exit(42);
    }

    if (setjmp(png_jmpbuf(img->png_ptr))){
        printf("Error in write_png_file function: error during init_io.\n");
        exit(43);    
    }

    png_init_io(img->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(img->png_ptr))){
        fclose(fp);
        printf("Error in write_png_file function: error during writing header.\n");
        exit(44);
    }

    png_set_IHDR(img->png_ptr, img->info_ptr, img->width, img->height,
                 img->bit_depth, img->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(img->png_ptr, img->info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(img->png_ptr))){
        fclose(fp);
        printf("Error in write_png_file function: error during writing bytes.\n");
        exit(45);
    }

    png_write_image(img->png_ptr, img->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(img->png_ptr))){
        fclose(fp);
        printf("Error in write_png_file function: error during writing end of file.\n");
        exit(46);
    }

    png_write_end(img->png_ptr, NULL);

    /* cleanup heap allocation */
    for (int y = 0; y < img->height; y++) //можно вынести в отдельную функцию
        free(img->row_pointers[y]);
    free(img->row_pointers);

    fclose(fp);
}

void print_png_info(struct Png *img) {
    printf("img Width: %d\n", img->width);
    printf("img Height: %d\n", img->height);
    printf("img Bit Depth: %d\n", img->bit_depth);
    printf("img Number of passes: %d\n", img->number_of_passes);
    printf("img Channels: %d\n", img->channels);
    if (img->color_type == PNG_COLOR_TYPE_RGB) {
        printf("img Colour Type: RGB\n");
    } else {
        printf("img Colour Type: RGB_A\n");
    }
}

void print_help(){
    printf("Course work for option 5.17, created by Marina Konyaeva.\n");
    printf("\nВспомогательные функции:\n\n\
            -h, -help - справка, которую вы видите сейчас\n\n\
            -info - подробная информация об изображении\n\n\
            -i, -input - задаёт имя входного изображения\n\n\
            -o, -output - задаёт имя выходного изображения\n\n");
    printf("Функции по обработке изображений:\n\n\
            --circle - рисование окружности\n\
                --center - координаты центра\n\
                ---radius - радиус окружности\n\
                --thickness - толщина обводки\n\
                --color - цвет обводки\n\
                --fill - флаг заливки\n\
                --fill_color - цвет заливки\n\
            --rgbfilter - фильтр rgb-компонент\n\
                --component_name - имя изменяемоей компоненты\n\
                --component_value - новое значение изменяемой компоненты\n\
            --split - разделяет изображение на N*M частей\n\
                --number_x - количество частей по оси Y\n\
                --number_y - количество частей по оси X\n\
                --thickness - толщина линии\n\
                --color - цвет линий\n\
            --squared_lines - рисование квадрата с диагоналями\n\
                --left_up - координаты левого верхнего угла\n\
                --side_size - размер стороны\n\
                --thickness - толщина линий\n\
                --color - цвет линий\n\
                --fill - флаг заливки\n\
                --fill_color - цвет заливки\n");
}

void free_image_data(struct Png *img) {
    for (int y = 0; y < img->height; y++) {
        free(img->row_pointers[y]);
    }
    free(img->row_pointers);
}

void create_default(struct Configs* conf){
    conf->x_y[0] = -1;
    conf->x_y[1] = -1;
    conf->radius = -1;
    conf->thickness = -1;
    conf->fill = 0;
    conf->color = malloc(sizeof(int) * 3);
    conf->fill_color = malloc(sizeof(int) * 3);
    for (int i = 0; i < 3; i++){
        conf->color[i] = 0;
        conf->fill_color[i] = 0;
    }
    conf->component_value = -1;
    conf->number_x = -1;
    conf->number_y = -1;
    conf->side_size = -1;
}

void create_defaut_for_flags(struct Flags* flag){
    flag->x_y = 0;
    flag->radius = 0;
    flag->thickness = 0;
    flag->color = 0;

    flag->component_name= 0;
    flag->component_value = 0;

    flag->number_x = 0;
    flag->number_y = 0;

    flag->side_size = 0;
}
void free_conf(struct Configs* conf){
    free(conf->color);
    free(conf->fill_color);
}

