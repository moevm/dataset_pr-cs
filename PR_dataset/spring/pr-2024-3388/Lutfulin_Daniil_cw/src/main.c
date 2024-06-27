#include "get_args.h"
#include "structs.h"
#include "read_picture.h"
#include "change_picture.h"
#include <stdio.h>

int main(int argc, char **argv){
    args_t args = get_args(argc, argv);
    pargs_t pargs = process_arguments(args);
    bmp_file_header_t file_header;
    bmp_info_header_t info_header;
    pixels_t *pixels = read_bmp_file(pargs.input_file, &file_header, &info_header);
    change_picture(pixels, &pargs, &info_header, &file_header);
    if(!pargs.info)
        write_bmp_file(pargs.output_file, pixels->arr, &file_header, &info_header);
    free_picture(pixels);
}
