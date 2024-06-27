#include "../include/main.h"

int main(int argc, char** argv) {
    Parametrs* par = CLI(argc, argv);
    checkExtraArguments(par);
    Png image;
    read_png_file(par->input, &image);
    if (par->info)
        Info(&image);
    if (par->square) {
        checkSquare(&image, par);
        Square(&image, par);
    }
    if (par->exchange) {
        checkExchange(&image, par);
        Exchange(&image, par);
    }
    if (par->freq_color) {
        checkFreq(&image, par);
        FreqColor(&image, par);
    }
    if(par->contrast) {
        checkContrast(&image, par);
        Contrast(&image, par);
    }
    write_png_file(par->output, &image);
    free(par);
    return 0;
}