#include <stdlib.h>

#include "structs.h"
#include "read_write_png.h"
#include "png_draw.h"
#include "png_edit.h"
#include "params.h"


void print_info(png_t* image){
    printf("Image info:\nHeight: %d; Width: %d; Color type: %d; Bit depth: %d\n", image->height, image->width, image->color_type, image->bit_depth);
}

int main(int argc, char** argv){
    params_t params;
    init_params(&params);
    parse_params(&params, argc, argv);
    png_t image;
    if (strcmp(params.input,params.output)==0){
        puts("Input and output can't be the same file!");
        exit(49);
    }
    read_png(params.input, &image);
    int cnt = 0;
    if (params.rect) cnt++;
    if (params.hexagon) cnt++;
    if (params.copy) cnt++;
    if (cnt > 1){
        raise_arg_error();
    }
    if (params.rect){
        if (params.left_up_x != -1 && params.left_up_y != -1 && 
        params.right_down_x != -1 && params.right_down_y != -1 &&
        params.color_input &&
        params.thickness != -1)
            if (params.fill && (!params.fcolor_input))
                raise_arg_error();
            else
                draw_rectangle(&image, params.left_up_x, params.left_up_y, params.right_down_x, params.right_down_y, params.color, params.thickness, params.fill, params.fill_color);
        else
            raise_arg_error();
    }
    if (params.hexagon){
        if (params.center_x != -1 && params.center_y != -1 && params.radius != -1 &&
        params.color_input &&
        params.thickness != -1)
            if (params.fill && (!params.fcolor_input))
                raise_arg_error();
            else
                draw_hexagon(&image, params.center_x, params.center_y, params.color, params.radius, params.thickness, params.fill, params.fill_color);
        else
            raise_arg_error();
    }
    if (params.copy){
        if (params.left_up_x!= -1 && params.left_up_y != -1 && params.right_down_x != -1 &&
        params.right_down_y != -1 && params.dest_left_up_x != -1 && params.dest_left_up_y != -1)
            copy_area_to(&image, params.left_up_x, params.left_up_y, params.right_down_x, params.right_down_y, params.dest_left_up_x, params.dest_left_up_y);
        else
            raise_arg_error();
    }
    if (params.blur)
        if (params.size != -1) blur(&image, params.size);
        else (raise_arg_error());

    if (params.info) print_info(&image);
    write_png(params.output, &image);
}
