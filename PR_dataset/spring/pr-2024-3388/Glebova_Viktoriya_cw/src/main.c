#include "main.h"

void make_all(int argc, char* argv[]){
    args_t args;
    params_t params;
    png_t* img;
    int check_answer;

    args = get_args(argc, argv);

    check_args(args);

    params = get_params(args);

    img = read_png(&params);

    change_img(img, &params);
    write_png(img, &params);

    free_args(&args);
    free_img(img);
}

int main(int argc, char* argv[]){
    make_all(argc, argv);
    return 0;
}