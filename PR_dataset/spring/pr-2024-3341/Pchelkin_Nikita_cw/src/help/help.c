#include "help.h"

void print_help(){
    printf("Flags -o, --output are used to set name of output file (out.png by default).\n");
    printf("Flags -i, --input are used to set name of input file (last argument by default).\n");
    printf("Flag --info is used to get the info about recieved png image.\n");
    printf("\nThere are some functions to edit the image:\n");

    printf("Flag --triangle is used to draw a triangle. For initializing it you need to set some values:\n");
    printf("\t-P, --points <x1.y1.x2.y2.x3.y3>:\n\t\tCoordinates of points of the triangle.\n");
    printf("\t-T, --thickness <number>:\n\t\tThickness of the lines. Requires positive number.\n");
    printf("\t-C, --color <rrr.ggg.bbb>:\n\t\tColor of the lines. rrr/ggg/bbb - numbers specifying red/green/blue color component.\n");
    printf("\t-F, --fill:\n\t\tIf there is a flag, the triangle will be filled.\n");
    printf("\t--fill_color <rrr.ggg.bbb>:\n\t\tFill color. Take values similar to --color.\n");

    printf("\nFlag --biggest_rect is used to find the largest rectangle of a given color and recolor it with a different color. For initializing it you need to set some values:\n");
    printf("\t--old_color <rrr.ggg.bbb>:\n\t\tThe color of the rectangle to find. rrr/ggg/bbb - numbers specifying red/green/blue color component.\n");
    printf("\t--new_color <rrr.ggg.bbb>:\n\t\tThe color to recolor the rectangle. Take values similar to --old_color.\n");

    printf("\nFlag --collage is used to create collage. For initializing it you need to set some values:\n");
    printf("\t-X, --number_x <number>:\n\t\tNumber of images vertically. Requires positive number.\n");
    printf("\t-Y, --number_y <number>:\n\t\tNumber of images horizontally. Requires positive number.\n");
}

void raise_error(char* reason){
    fprintf(stderr, "Error: %s\nSee '--help' or '-h' for a complete list of options.\n", reason);
    exit(41);
}

void raise_reading_error(char* reason){
    fprintf(stderr, "Error: %s.\n", reason);
    exit(42);
}

void info(Png* image){
    printf("Image Width: %d\n", image->width);
    printf("Image Height: %d\n", image->height);
    printf("Image Bit Depth: %d\n", image->bit_depth);
    printf("Image Channels: %d\n", image->channels);
    if (image->color_type == PNG_COLOR_TYPE_RGB) {
        printf("Image Colour Type: RGB\n");
    } else {
        printf("Image Colour Type: RGB_A\n");
    }
}
