#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "error_handler.h"

void freeMemory(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb **arr){
    int H = 0;
    if (bmif != NULL)
        H = abs((int)bmif->height);
    if (arr) {
        for (int i = 0; i < H; i++)
            free(arr[i]);
    }
    free(arr);
    free(bmfh);
    free(bmif);
}

void print_error(char* message, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb **arr) {
    fprintf(stderr, "====ERROR====\n%sCommand for help: --help -h\n", message);
    freeMemory(bmfh, bmif, arr);
    exit(42);
}