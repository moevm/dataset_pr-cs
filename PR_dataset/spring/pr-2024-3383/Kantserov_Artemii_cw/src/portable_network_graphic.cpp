#include "portable_network_graphic.h"
#include <png.h>
//#include "/opt/homebrew/include/png.h"
#include <iostream>
#include "struct_png.h"
using namespace std;

void info(struct Png* image) {
    cout << "Информация об изображении:" << endl;
    cout << "  Ширина: " << image->width << " пикселей" << endl;
    cout << "  Высота: " << image->height << " пикселей" << endl;
    cout << "  Глубина цвета: " << (int)image->bit_depth << " бит" << endl;
    cout << "  Тип цвета: " << (int)image->color_type << endl;
}

int write_png_file(const char* file_name, struct Png* image) {
    FILE* fp = fopen(file_name, "wb");
    if (!fp) {
        cerr << "No file." << endl;
        return 45;
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,NULL);
    if (!image->png_ptr) {
        cerr << "Error in png sructure." << endl;
        return 45;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        cerr << "Error in png info-structure." << endl;
        return 45;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        cerr << "Error" << endl;
        return 45;
    }
    png_init_io(image->png_ptr, fp);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        cerr << "Error" << endl;
        return 45;
    }
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        cerr << "Error" << endl;
        return 45;
    }
    png_write_image(image->png_ptr, image->row_pointers);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        cerr << "Error" << endl;
        return 45;
    }
    png_write_end(image->png_ptr, NULL);
    fclose(fp);
    return 0;
}

int read_png_file(const char* file_name, struct Png* image) {
    int y;
    unsigned char header[8];
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        cerr << "No file." << endl;
        return 45;
    }
    fread(header, 1, 8 , fp);
    if (png_sig_cmp(header, 0, 8)){
        cerr << "No read." << endl;
        return 45;
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        cerr << "Error in png sructure." << endl;
        return 45;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        cerr << "Error in png info-structure." << endl;
        return 45;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        cerr << "Error" << endl;
        return 45;
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr,image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++){
        image->row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
    return 0;
}