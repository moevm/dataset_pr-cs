#include "option.h"
#include "bmp.h"

int main(int argc, char* argv[]) {
    printf("Course work for option 5.4, created by Margarita Chinaeva\n");
    check_option check = do_check();
    value values = do_value();
    get_options(argc, argv, &check, &values);
    BitmapFileHeader* bmfh = (BitmapFileHeader*)malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader* bmif = (BitmapInfoHeader*)malloc(sizeof(BitmapInfoHeader));
    check_bmp(values.input_file, bmfh, bmif);
    Rgb **arr = read_bmp(values.input_file, bmfh, bmif);
    Rgb **new_arr = do_option(&check, arr, &values, bmfh, bmif);
    write_bmp(values.output_file, bmfh, bmif, new_arr);
    for (int i = 0; i < bmif->height; i++){
        free(new_arr[i]);
    }
    free(new_arr);
    free(bmif);
    free(bmfh);
    return 0;
}
