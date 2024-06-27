#include "io_img.h"

img_t* read_img(params_t* params){
    FILE* f = fopen(params->input_file, "rb");;
    img_t* img = malloc(sizeof(img_t));
    img->file_header = malloc(sizeof(bmp_file_header_t));
    img->info_header = malloc(sizeof(bmp_info_header_t));

    if (!f)
        panic(NO_FILE_ERROR);

    fread(img->file_header, 1, sizeof(bmp_file_header_t), f);
    fread(img->info_header, 1, sizeof(bmp_info_header_t), f);
    
    if (img->file_header->signature != SIGNATRUE || img->info_header->bits_per_pixel != BMP_PIX_SIZE)
        panic(INVALID_FILE_ERROR);

    img->pixels = malloc(img->info_header->height*sizeof(rgb_t*));
    int align = (4 - (img->info_header->width*sizeof(rgb_t))%4)%4;
    for (size_t i = 0; i < img->info_header->height; i++){
        img->pixels[img->info_header->height - i - 1] = malloc(img->info_header->width * sizeof(rgb_t) + align);
        fread(img->pixels[img->info_header->height - i - 1], 1, img->info_header->width * sizeof(rgb_t) + align, f);
    }

    fclose(f);
    return img;  
}

void write_img(img_t* img, params_t* params){
    FILE* f = fopen(params->output_file, "wb");
    fwrite(img->file_header, 1, sizeof(bmp_file_header_t), f);
	fwrite(img->info_header, 1, sizeof(bmp_info_header_t), f);
    if (!f)
        panic(OUTPUT_FILE_ERROR);

    int align = (4 - (img->info_header->width*sizeof(rgb_t))%4)%4;
    for (size_t i = 0; i < img->info_header->height; i++)
        fwrite(img->pixels[img->info_header->height - i - 1], 1, img->info_header->width * sizeof(rgb_t) + align, f);

    fclose(f);
}