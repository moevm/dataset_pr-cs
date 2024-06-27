#include <read_write_png.h>


void read_png(char* file_name, png_t* image) {
    FILE* fp = fopen(file_name, "rb");
    if (fp == NULL){
        puts("Cannot open file!");
        exit(40);
    }
    png_byte header[8];
    fread(header, sizeof(png_byte), 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        puts("Wrong file signature! Is it a png?");
        exit(40);
    }
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (image->png_ptr == NULL){
        puts("Cannot create read struct!");
        exit(40);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (image->png_ptr == NULL){
        puts("Cannot create info struct!");
        exit(40);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error when creating read struct!");
        png_destroy_read_struct(&(image->png_ptr), &(image->info_ptr), NULL);
        exit(40);
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_passes = png_set_interlace_handling(image->png_ptr);

    if(png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGB){
        puts("Color type is not RGB!");
        exit(40);
    }

    png_read_update_info(image->png_ptr, image->info_ptr); 

    image->rows = (png_bytepp)malloc(sizeof(png_bytepp) * image->height);
    for (int i = 0; i < image->height; i++)
        image->rows[i] = (png_bytep)calloc(image->width * 3, sizeof(png_byte));
    png_read_image(image->png_ptr, image->rows);
    png_destroy_read_struct(&(image->png_ptr), &(image->info_ptr), NULL);
    fclose(fp);
}

void write_png(char* file_name, png_t* image){
    FILE *fp = fopen(file_name, "wb");
    if (fp == NULL){
      puts("Cannot open write file!");
      exit(41);
    }
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (image->png_ptr == NULL){
        puts("Cannot create write struct!");
        exit(41);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (image->png_ptr == NULL){
        puts("Cannot create info struct!");
        exit(41);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error when creating write struct!");
        png_destroy_write_struct(&(image->png_ptr), &(image->info_ptr));
        exit(41);
    }
    png_init_io(image->png_ptr, fp);
    png_set_IHDR(
    image->png_ptr,
    image->info_ptr,
    image->width, image->height,
    image->bit_depth,
    image->color_type,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE,
    PNG_FILTER_TYPE_BASE
  );
    png_write_info(image->png_ptr, image->info_ptr);
    png_write_image(image->png_ptr, image->rows);
    png_write_end(image->png_ptr, NULL);
    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error when writing PNG!");
        png_destroy_write_struct(&(image->png_ptr), &(image->info_ptr));
        exit(41);
    }
    png_destroy_write_struct(&(image->png_ptr), &(image->info_ptr));
    fclose(fp);
}
