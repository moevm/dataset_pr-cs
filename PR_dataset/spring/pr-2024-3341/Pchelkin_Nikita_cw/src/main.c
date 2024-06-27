#include <stdio.h>
#include <getopt.h>

#include "image_processing.h"
#include "file_manager.h"


int main(int argc, char* argv[]){
    printf("Course work for option 4.19, created by Nikita Pchelkin.\n");

    opterr = 0;
    Png image;
    char* input_file = strdup(find_input_file(argc, argv));
    char* output_file = calloc(MAX_STRING, sizeof(char));

    read_png_file(input_file, &image);
    image_processing(argc, argv, &image, &output_file, input_file);
    write_png_file(output_file, &image);

    return 0;
}