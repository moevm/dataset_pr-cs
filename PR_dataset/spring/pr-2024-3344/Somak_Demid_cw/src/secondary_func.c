#include "secondary_func.h"

void swap_int(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

unsigned int padding(unsigned int w){
    unsigned int padding = (w*sizeof(Rgb))%4;
    if(padding) padding = 4 - padding;
    return padding;
}

unsigned int row_len(unsigned int w){
    return w*sizeof(Rgb) + padding(w);
}
