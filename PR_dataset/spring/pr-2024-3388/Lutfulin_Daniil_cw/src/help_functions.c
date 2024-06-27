#include "help_functions.h"


void leave(char* error_string, int error_code){
    fprintf(stderr,"%sExit code: %d\n", error_string, error_code);
    exit(error_code);
}

void swap_int(int* first, int* second){
    int tmp = *first;
    *first = *second;
    *second = tmp; 
}

void swap_rgb(rgb_t* first_pixel, rgb_t* second_pixel){
    rgb_t tmp = {first_pixel->b, first_pixel->g, first_pixel->r};

    first_pixel->b = second_pixel->b;
    first_pixel->g = second_pixel->g;
    first_pixel->r = second_pixel->r;
    
    second_pixel->b = tmp.b;
    second_pixel->g = tmp.g;
    second_pixel->r = tmp.r;
}

void set_pixel(pixels_t* pixels, int y, int x, rgb_t color){
    if(x >= 0 && y >= 0 && x < pixels->width && y < pixels->height){
        pixels->arr[y][x].r = color.r;
        pixels->arr[y][x].g = color.g;
        pixels->arr[y][x].b = color.b;
    }
}

void print_args(args_t args){
    printf("help: %d\n", args.help);
    printf("info: %d\n", args.info);
    printf("input: %s\n", args.input_file);
    printf("output: %s\n", args.output_file);
    printf("mirror: %d\n", args.mirror);
    printf("axis: %s\n", args.mirror_axis);
    printf("left_up: %s\n", args.left_up);
    printf("right_down: %s\n", args.right_down);
    printf("copy: %d\n", args.copy);
    printf("dest_left_up: %s\n", args.dest_left_up);
    printf("color replace: %d\n", args.color_replace);
    printf("old_color: %s\n", args.old_color);
    printf("new_color: %s\n", args.new_color);
    printf("split: %d\n", args.split);
    printf("number_x: %s\n", args.number_x);
    printf("number_y: %s\n", args.number_y);
    printf("thickness: %s\n", args.thickness);
    printf("color: %s\n", args.color);
}

void print_pargs(pargs_t args){
    printf("info: %d\n", args.info);
    printf("input: %s\n", args.input_file);
    printf("output: %s\n", args.output_file);
    printf("mirror: %d\n", args.mirror);
    printf("axis: %c\n", args.mirror_axis);
    printf("left_up: %d %d \n", args.left_up.x, args.left_up.y);
    printf("right_down: %d %d\n", args.right_down.x, args.right_down.y);
    printf("copy: %d\n", args.copy);
    printf("dest_left_up: %d %d\n", args.dest_left_up.x, args.dest_left_up.y);
    printf("color replace: %d\n", args.color_replace);
    printf("old_color: %d!%d!%d\n", args.old_color.r,args.old_color.g,args.old_color.b);
    printf("new_color: %d!%d!%d\n", args.new_color.r,args.new_color.g,args.new_color.b);
    printf("split: %d\n", args.split);
    printf("number_x: %lu\n", args.number_x);
    printf("number_y: %lu\n", args.number_y);
    printf("thickness: %lu\n", args.thickness);
    printf("color: %d!%d!%d\n", args.color.r,args.color.g,args.color.b);
}

void print_info_header(bmp_info_header_t info_header){
    printf("header size: %u\n", info_header.headerSize);
    printf("width: %u\n", info_header.width);
    printf("height: %u\n", info_header.height);
    printf("planes: %hu\n", info_header.planes);
    printf("bits per pixel: %hu\n", info_header.bitsPerPixel);
    printf("compression: %u\n", info_header.compression);
    printf("imageSize: %u\n", info_header.imageSize);
    printf("xPixelsPerMeter: %u\n", info_header.xPixelsPerMeter);
    printf("yPixelsPerMeter: %u\n", info_header.yPixelsPerMeter);
    printf("colorsInColorTable: %u\n", info_header.colorsInColorTable);
    printf("importantColorCount: %u\n", info_header.importantColorCount);
}

void print_file_header(bmp_file_header_t header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_help(){
    printf("%s", HELP_TEXT);
}

void free_picture(pixels_t *pixels){
    for(int i = pixels->height-1; i >= 0; i--){
        free(pixels->arr[i]);
    }
    free(pixels->arr);
    free(pixels);
}
