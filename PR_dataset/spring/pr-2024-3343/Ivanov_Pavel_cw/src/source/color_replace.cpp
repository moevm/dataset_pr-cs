#include "../include/functions.h"

void color_replace(PICInfo& info, int* old_colors, int* new_colors) {
    int old_red = old_colors[0];
    int old_green = old_colors[1];
    int old_blue = old_colors[2];
    int new_red = new_colors[0];
    int new_green = new_colors[1];
    int new_blue = new_colors[2];


    for (unsigned int i = 0; i < size_image - 2; i+=3) {
        if((info.pixels[i] == old_blue) && (info.pixels[i+1] == old_green) && (info.pixels[i+2] == old_red)){
            info.pixels[i] = new_blue;
            info.pixels[i+1] = new_green;
            info.pixels[i+2] = new_red;
        }
    }
}
