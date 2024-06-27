#include "command.h"
#include "struct_png.h"

int main(int argc, char* argv[]){
    struct Png image;
    return process_args(argc, argv, &image);
}