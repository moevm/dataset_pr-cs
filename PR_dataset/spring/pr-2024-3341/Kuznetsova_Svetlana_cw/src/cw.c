#include <stdio.h>
#include <getopt.h>

#include "image_processing.h"
#include "args_parsing.h"
#include "png_io.h"

int main(int argc, char** argv){
    
    printf("Course work for option 4.13, created by Svetlana Kuznetsova\n");

    opterr = 0;
    Png image;
    char* path_i = (char *)calloc(128, sizeof(char));
    char* path_o = (char *)calloc(128, sizeof(char));
    int flag;
    OPTS options = init_options();
    path_o = strdup("out.png");

    args_parsing(argc, argv, path_i, path_o, &options, &flag);
    printf("%s\n", path_i);

    read_png_file(path_i, &image);
    choose_func(image, flag, &options);
    write_png_file(path_o, &image);

    return 0;
}
