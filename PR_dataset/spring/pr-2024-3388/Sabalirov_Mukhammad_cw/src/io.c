#include "io.h"

png_t* read_png_file(func_params_t* params){
    png_t* img = malloc(sizeof(png_t));   
    char header[HEADER_LEN];
    FILE *fp = fopen(params->input, "rb");

    if (!fp){
        panic(READ_FILE_ERROR);
    }

    fread(header, 1, HEADER_LEN, fp);
    if (png_sig_cmp(header, 0, HEADER_LEN)){
        panic(NOT_PNG_ERROR);
    }

    img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!img->png_ptr){
        panic(PNG_STRUCT_ERROR);
    }

    img->info_ptr = png_create_info_struct(img->png_ptr); 
    if (!img->info_ptr){
        panic(PNG_INFO_STRUCT_ERROR);
    }

    if (setjmp(png_jmpbuf(img->png_ptr))){
        panic(SETJMP_ERROR);
    }

    png_init_io(img->png_ptr, fp);
    png_set_sig_bytes(img->png_ptr, 8);
    png_read_info(img->png_ptr, img->info_ptr);
    img->width = png_get_image_width(img->png_ptr, img->info_ptr);
    img->height = png_get_image_height(img->png_ptr, img->info_ptr);
    img->color_type = png_get_color_type(img->png_ptr,img->info_ptr);
    img->bit_depth = png_get_bit_depth(img->png_ptr, img->info_ptr);
    img->number_of_passes = png_set_interlace_handling(img->png_ptr);
    png_read_update_info(img->png_ptr, img->info_ptr);

    img->row_pointers = malloc(sizeof(png_bytep)*img->height);
    for (size_t y = 0; y < img->height; ++y){
        img->row_pointers[y] = malloc(png_get_rowbytes(img->png_ptr,img->info_ptr));
    }
    png_read_image(img->png_ptr, img->row_pointers);
    fclose(fp);

    return img;
}

void write_png_file(png_t* img, func_params_t* params){
    FILE *fp = fopen(params->output, "wb");
    if (!fp) {
        panic(READ_FILE_ERROR);
    }
    
    img->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!img->png_ptr) {
        panic(PNG_STRUCT_ERROR);
    }
    
    img->info_ptr = png_create_info_struct(img->png_ptr);
    if (!img->info_ptr) {
        panic(PNG_INFO_STRUCT_ERROR);
    }
    
    if (setjmp(png_jmpbuf(img->png_ptr))) {
        panic(SETJMP_ERROR);
    }
    
    png_init_io(img->png_ptr, fp);
    
    if (setjmp(png_jmpbuf(img->png_ptr))) {
        panic(PROCESS_IMG_ERROR);
    }
    
    png_set_IHDR(img->png_ptr, img->info_ptr, img->width, img->height, img->bit_depth, img->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(img->png_ptr, img->info_ptr);
    
    if (setjmp(png_jmpbuf(img->png_ptr))) {
        panic(WRITE_IMG_ERROR);
    }
    
    png_write_image(img->png_ptr, img->row_pointers);
    
    if (setjmp(png_jmpbuf(img->png_ptr))) {
        panic(WRITE_END_IMG_ERROR);
    }
    
    png_write_end(img->png_ptr, NULL);
    
    for (size_t y = 0; y < img->height; ++y) {
        free(img->row_pointers[y]);
    }
    
    free(img->row_pointers);
    fclose(fp);
}