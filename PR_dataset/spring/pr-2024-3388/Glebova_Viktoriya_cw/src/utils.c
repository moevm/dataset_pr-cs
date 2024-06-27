#include "utils.h"

void panic(char* message){
	fprintf(stderr, ERROR_TEMPLATE, message, EXIT_CODE);
	exit(EXIT_CODE);
}

void print_img_info(png_t* img){
    printf(IMG_INFO, img->width, img->height, img->color_type, img->bit_depth);
}

void free_args(args_t* args){
	free(args->input_file);
	free(args->output_file);
	free(args->center);
	free(args->radius);
	free(args->thickness);
	free(args->color);
	free(args->fill_color);
	free(args->number_x);
	free(args->number_y);
	free(args->component_name);
	free(args->component_value);
}

void free_img(png_t* img){
	//row pointers be free in write_png function
	free(img);
}