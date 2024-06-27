#include "file_interactions.h"

Png* read_png_file(std::string file_name) {
    Png* image = new Png();

    if (image == NULL)
            {
                std :: cout << "Memory error\n";
                exit(45);
            }


    unsigned char header[8];
    FILE *fp = fopen(file_name.c_str(), "rb");

    if (!fp) {
        std::cout << "File could not be opened or not found.\n";
        exit(1);
    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        std::cout << "File is not recognized as a PNG.\n";
        exit(44);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        std::cout << "png_create_read_struct failed.\n";
        exit(45);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        std::cout << "png_create_info_struct failed.\n";
        exit(46);
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    image->row_pointers = (png_byte**) new png_byte*[image->height];
    if (image->row_pointers == NULL)
            {
                std::cout << "Memory error\n";
                exit(45);
            }

    for (int i = 0; i < image->height; i++) {
        image->row_pointers[i] = new png_byte[png_get_rowbytes(image->png_ptr, image->info_ptr)];
        
        if (image->row_pointers[i] == NULL)
            {
                std::cout << "Memory error\n";
                exit(45);
            }
    }

    png_read_image(image->png_ptr, image->row_pointers);
    fclose(fp);
    return image;
}

void save_png_file(Png* image, std::string save_path) {
    FILE *fp = fopen(save_path.c_str(), "wb");
    if (!fp) {
        std::cout << "File save failed\n";
        exit(44);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        std::cout << "png_ptr failed\n";
        exit(45);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        std::cout << "info_ptr failed\n";
        exit(46);
    }

    png_init_io(image->png_ptr, fp);

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);
    png_write_image(image->png_ptr, image->row_pointers);
    png_write_end(image->png_ptr, NULL);

    fclose(fp);
}