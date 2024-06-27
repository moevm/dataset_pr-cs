#include "../include/tasks.h"

// Prints file info to stdout
//
// Arguments:
// path - input file path
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_print_file_info(char *path)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(path, PNGFILE_READ_INFO_ONLY, &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }

    printf("File info:\n");
    printf("Path: %s\n", path);
    printf("Width: %u, height: %u\n", png_ptr->info.width,
                                      png_ptr->info.height);
    char *color_type;
    switch(png_ptr->info.color_type) {
    case PNGFILE_TYPE_G:
            color_type = "grayscale";
            break;
    case PNGFILE_TYPE_GA:
            color_type = "grayscale with transparency";
            break;
    case PNGFILE_TYPE_RGB:
            color_type = "RGB";
            break;
    case PNGFILE_TYPE_RGBA:
            color_type = "RGB with transparency";
            break;
    case PNGFILE_TYPE_P:
            color_type = "palette";
            break;
    }
    printf("Picture mode: %s\n", color_type);
    printf("Bit depth: %u\n", png_ptr->info.bit_depth);
    pngfile_destroy_file(png_ptr);
    return RETCODE_OK;
}

// Draws triangle in png file
// Output file format is equal to input file except for palette images
// All palette images are converted to 8-bit RGB
//
// Arguments:
// input - input file name
// output - output file name
// coords - [x1, y1, x2, y2, x3, y3] - vertices of the triangle to draw
// thickness - outline thickness
// color - outline color
// fill - bool flag
// fill_color - fill color, used it fill=1
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_draw_triangle(char *input, char *output, int64_t *coords,
                       uint32_t thickness, Pixel color, uint8_t fill,
                       Pixel fill_color, uint8_t compression_level)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(input, PNGFILE_READ_NORMAL, &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }
    
    Image *img;
    pngfile_export_image(png_ptr, &img, &status_code);
    if(status_code != RETCODE_OK)
    {
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    draw_polygon(img, coords, 3, thickness, color, fill, fill_color);
    
    // Saving image in same format except for palette images
    if(png_ptr->info.color_type == PNGFILE_TYPE_P) {
        png_ptr->info.color_type = PNGFILE_TYPE_RGB;
        png_ptr->info.channels = 3;
        png_ptr->info.bit_depth = 8;
    }
    png_byte **row_pointers;
    pngfile_import_image(*img, &png_ptr->info, &row_pointers, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    pngfile_write(output, png_ptr->info, row_pointers,
        compression_level, &status_code);
    pngfile_destroy_rows(&row_pointers, img->height);
    pngfile_destroy_file(png_ptr);
    image_destroy(img);
    return status_code;
}


// Creates collage from input png (repeating picture)
// Output file format is equal to input file except for palette images
// All palette images are converted to 8-bit RGB
//
// Arguments:
// input - input file name
// output - output file name
// number_x - collage "width"
// number_y - collage "height"
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_create_collage(char *input, char *output, uint32_t number_x,
                        uint32_t number_y, uint8_t compression_level)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(input, PNGFILE_READ_NORMAL,  &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }
    
    Image *img;
    pngfile_export_image(png_ptr, &img, &status_code);
    if(status_code != RETCODE_OK)
    {
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    // Check for max image size
    // libpng default image size limit is 1-million pixels along x & y
    // So, let's check that we really can create the collage
    uint32_t collage_width  = png_ptr->info.width  * number_x;
    uint32_t collage_height = png_ptr->info.height * number_y;
    if(collage_width >= 1000000 || collage_height >= 1000000)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return RETCODE_ARG_ERROR;
    }
    
    // Creating empty image with correct size for collage
    Image *collage;
    // Copy options to save with same format as in input file
    PngInfo collage_info = png_ptr->info;
    image_create(&collage, collage_width, collage_height,
        NULL, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    for(uint32_t x = 0; x < number_x; x++)
    {
        for(uint32_t y = 0; y < number_y; y++)
        {
            image_paste(&collage, img, png_ptr->info.width * x,
                png_ptr->info.height * y);
        }
    }

    // Saving image in same format except for palette images
    if(collage_info.color_type == PNGFILE_TYPE_P) {
        collage_info.color_type = PNGFILE_TYPE_RGB;
        collage_info.channels = 3;
        collage_info.bit_depth = 8;
    }
    png_byte **row_pointers;
    pngfile_import_image(*collage, &collage_info, &row_pointers, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    pngfile_write(output, collage_info, row_pointers,
        compression_level, &status_code);
    pngfile_destroy_rows(&row_pointers, collage_height);
    pngfile_destroy_file(png_ptr);
    image_destroy(img);
    image_destroy(collage);
    return status_code;
}


// Replaces biggest rectangle in picture with different color
// Output file format is equal to input file except for palette images
// All palette images are converted to 8-bit RGB
//
// Arguments:
// input - input file name
// output - output file name
// old_color - search for rectangle with this color
// new_color - replace with this color
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_rect_search(char *input, char *output, Pixel old_color,
                     Pixel new_color, uint8_t compression_level)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(input, PNGFILE_READ_NORMAL, &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }
    
    Image *img;
    pngfile_export_image(png_ptr, &img, &status_code);
    if(status_code != RETCODE_OK)
    {
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    uint32_t x0, y0, x1, y1;
    image_find_largest_rect(img, &x0, &y0, &x1, &y1,
        old_color, &status_code);
    if(status_code != RETCODE_OK)
    {
        if(status_code == RETCODE_ARG_ERROR)
            fprintf(stderr, TASK_RECT_WRONG_COLOR);
    }
    else draw_rectangle(img, x0, y0, x1, y1, new_color);
    
    // Saving image in same format except for palette images
    if(png_ptr->info.color_type == PNGFILE_TYPE_P) {
        png_ptr->info.color_type = PNGFILE_TYPE_RGB;
        png_ptr->info.channels = 3;
        png_ptr->info.bit_depth = 8;
    }
    png_byte **row_pointers;
    pngfile_import_image(*img, &png_ptr->info, &row_pointers, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    pngfile_write(output, png_ptr->info, row_pointers,
        compression_level, &status_code);
    pngfile_destroy_rows(&row_pointers, img->height);
    pngfile_destroy_file(png_ptr);
    image_destroy(img);
    return status_code;
}

// Draws line in png file
// Output file format is equal to input file except for palette images
// All palette images are converted to 8-bit RGB
//
// Arguments:
// input - input file name
// output - output file name
// coords - [x0, y0, x1, y1] - line end coordinates
// thickness - outline thickness
// color - outline color
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_draw_line(char *input, char *output, int64_t *coords,
                   uint32_t thickness, Pixel color, uint8_t compression_level)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(input, PNGFILE_READ_NORMAL, &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }
    
    Image *img;
    pngfile_export_image(png_ptr, &img, &status_code);
    if(status_code != RETCODE_OK)
    {
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    draw_line(img, coords[0], coords[2], coords[1], coords[3],
        thickness, color);

    // line ends
    if(thickness > 2)
    {
        draw_circle(img, coords[0], coords[1], (thickness-1)/2, color,
            1, 1, color);
        draw_circle(img, coords[2], coords[3], (thickness-1)/2, color,
            1, 1, color);
    }
    
    // Saving image in same format except for palette images
    if(png_ptr->info.color_type == PNGFILE_TYPE_P) {
        png_ptr->info.color_type = PNGFILE_TYPE_RGB;
        png_ptr->info.channels = 3;
        png_ptr->info.bit_depth = 8;
    }
    png_byte **row_pointers;
    pngfile_import_image(*img, &png_ptr->info, &row_pointers, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    pngfile_write(output, png_ptr->info, row_pointers,
        compression_level, &status_code);
    pngfile_destroy_rows(&row_pointers, img->height);
    pngfile_destroy_file(png_ptr);
    image_destroy(img);
    return status_code;
}


// Draws outside ornament in png file
// Output file format is equal to input file except for palette images
// All palette images are converted to 8-bit RGB
//
// Arguments:
// input - input file name
// output - output file name
// thickness - ornament thickness
// color - ornament color
//
// Return:
// Return codes should be handled with handle_error()
// from "include/errors.h"
int task_draw_outside_ornament(char *input, char *output,
                   uint32_t thickness, Pixel color,
                   uint8_t compression_level)
{
    PngFile* png_ptr;
    int status_code;
    pngfile_read(input, PNGFILE_READ_NORMAL, &png_ptr, &status_code);
    if(status_code != RETCODE_OK)
    {
        return status_code;
    }
    
    Image *img;
    pngfile_export_image(png_ptr, &img, &status_code);
    if(status_code != RETCODE_OK)
    {
        pngfile_destroy_file(png_ptr);
        return status_code;
    }
    
    // Saving image in same format except for palette images
    if(png_ptr->info.color_type == PNGFILE_TYPE_P) {
        png_ptr->info.color_type = PNGFILE_TYPE_RGB;
        png_ptr->info.channels = 3;
        png_ptr->info.bit_depth = 8;
    }

    // Check for max image size
    // libpng default image size limit is 1-million pixels along x & y
    // So, let's check that we really can create image with ornament
    uint32_t res_width  = png_ptr->info.width  + (thickness * 2);
    uint32_t res_height = png_ptr->info.height + (thickness * 2);
    if(res_width >= 1000000 || res_height >= 1000000)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return RETCODE_ARG_ERROR;
    }
    
    // Creating empty image with new size
    Image *res;
    // Copy options to save with same format as in input file
    PngInfo res_info = png_ptr->info;
    image_create(&res, res_width, res_height,
        &color, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    image_paste(&res, img, thickness, thickness);

    // Saving image in same format except for palette images
    if(res_info.color_type == PNGFILE_TYPE_P) {
        res_info.color_type = PNGFILE_TYPE_RGB;
        res_info.channels = 3;
        res_info.bit_depth = 8;
    }
    
    png_byte **row_pointers;
    pngfile_import_image(*res, &res_info, &row_pointers, &status_code);
    if(status_code != RETCODE_OK)
    {
        image_destroy(img);
        pngfile_destroy_file(png_ptr);
        return status_code;
    }

    pngfile_write(output, res_info, row_pointers,
        compression_level, &status_code);
    pngfile_destroy_rows(&row_pointers, img->height);
    pngfile_destroy_file(png_ptr);
    image_destroy(img);
    return status_code;
}
