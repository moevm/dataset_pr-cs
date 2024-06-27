#include "utils.h"

void free_args(func_param_args_t* args){
    free(args->axis);
    free(args->left_up);
    free(args->right_down);
    free(args->center);
    free(args->radius);
    free(args->thickness);
    free(args->color);
    free(args->fill_color);
    free(args->input);
    free(args->output);
}

void free_all(func_param_args_t* args, func_params_t* params, png_t* img){
    free_args(args);
    free(params);
    free(img);
}

void panic(char* message){
	printf(PANIC_TEMPLATE, message, EXIT_CODE);
	exit(EXIT_CODE);
}

void print_params(func_params_t* params){
    printf(PARAMS_INFO_TEMPLATE,
            params->mirror, params->pentagram, params->rect, params->hexagon, params->fill, params->info,
            params->axis, params->left_up_x, params->left_up_y, params->right_down_x, params->right_down_y,
            params->center_x, params->center_y, params->radius, params->thickness,
            params->color_r, params->color_g, params->color_b,
            params->fill_color_r, params->fill_color_g, params->fill_color_b,
            params->input, params->output);
}