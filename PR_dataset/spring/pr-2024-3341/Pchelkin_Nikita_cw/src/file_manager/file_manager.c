#include "file_manager.h"

char* find_input_file(int argc, char* argv[]){
    optind = 0;
    int opt;
    int option_index = 0;
    struct option long_option[] = {
        {"input", 1, NULL, 'i'},
        {"help", 0, NULL, 'h'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, "-hi:", long_option, &option_index)) != -1){
        if(opt == 'i')
            return optarg;
        if(opt == 'h'){
            print_help();
            exit(0);
        }    
    }
    
    return argv[argc-1];
}

void read_png_file(char* file_name, Png* image) {

    int y;
    char header[8]; 

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
       raise_reading_error("file could not be opened");
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
       raise_reading_error("file is not recognized as a PNG"); 
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
       raise_reading_error("png_create_read_struct failed");  
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        raise_reading_error("png_create_info_struct failed");
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        raise_reading_error("error during init_io");  
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))){
       raise_reading_error("error during read_image");   
    }
    if (png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGB && png_get_color_type(image->png_ptr, image->info_ptr) != PNG_COLOR_TYPE_RGBA){
        raise_reading_error("Can't support this color type");
    }
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}

void write_png_file(char *file_name, Png* image) {
    int y;
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        raise_reading_error("file could not be opened");
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        raise_reading_error("png_create_write_struct failed"); 
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
       raise_reading_error("png_create_info_struct failed"); 
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        raise_reading_error("error during init_io");
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        raise_reading_error("error during writing header");
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    if (setjmp(png_jmpbuf(image->png_ptr))){
       raise_reading_error("error during writing bytes"); 
    }

    png_write_image(image->png_ptr, image->row_pointers);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        raise_reading_error("error during end of write"); 
    }

    png_write_end(image->png_ptr, NULL);

    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}