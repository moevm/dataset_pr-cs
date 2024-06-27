#include "main.h"

void make_all(int argc, char* argv[]){
    args_t args;
    params_t params;
    img_t* img;

    args = get_args(argc, argv);
    check_args(args);
    params = get_params(args);

    img = read_img(&params);

    edit_image(img, &params);
    write_img(img, &params);
    
    free_args(&args);
    free_image(img);
}

int main(int argc, char* argv[]){
    make_all(argc, argv);
    return 0;
}