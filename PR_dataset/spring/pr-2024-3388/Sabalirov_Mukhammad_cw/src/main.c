#include "main.h"

int main(int argc, char* argv[]){
    int write_flag;
    func_param_args_t args = get_args(argc, argv);
    func_params_t* params = set_and_get_func_params(args);
    png_t* img = read_png_file(params);
    process_img(img, params, &write_flag);

    if (write_flag){
        write_png_file(img, params);
    }
    
    free_all(&args, params, img);

    return 0;
}