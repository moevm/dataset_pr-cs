#include "../include/pngfile.h"
#include <png.h>

// This function reads png file by given path into PngFile object
//
// Arguments:
// path - input file path
// info_only - should be PNGFILE_READ_INFO_ONLY or PNGFILE_READ_NORMAL,
//             function will read only file header if set to info only
//
// Return:
// output_ptr - ptr to PngFile* to store result into
// status_code - ptr to variable to put status_code into
//
// Status codes should be handled with handle_error() from "errors.h"
void pngfile_read(char* path, uint8_t read_mode, PngFile** output_ptr,
                  int* status_code)
{
    // Open file, check for access errors
    FILE *fp = fopen(path, "rb");
    if(!fp)
    {
        *status_code = RETCODE_IO_ERROR;
        return;
    }
    // Read first 8 bytes into header_buf, check file signature
    uint8_t header_buf[8];
    fread(header_buf, 1, 8, fp);
    if(png_sig_cmp(header_buf, 0, 8))
    {
        *status_code = RETCODE_FILE_ERROR;
        fclose(fp);
        return;
    }

    // Memory allocation required by libpng, check for alloc errors
    PngFile* output = (PngFile*)malloc(sizeof(PngFile));
    output->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL);
    if(output->png_ptr == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        free(output);
        fclose(fp);
        return;
    }
    output->info_ptr = png_create_info_struct(output->png_ptr);
    if(output->info_ptr == NULL)
    {
        png_destroy_read_struct(&(output->png_ptr),
            (png_infopp)NULL, (png_infopp)NULL);
        *status_code = RETCODE_MEMORY_ERROR;
        free(output);
        fclose(fp);
        return;
    }

    // Error handling during init_io, read_info and read_image
    if (setjmp(png_jmpbuf(output->png_ptr)))
    {
        png_destroy_read_struct(&(output->png_ptr),
            &(output->info_ptr), (png_infopp)NULL);
        *status_code = RETCODE_FILE_ERROR;
        free(output);
        fclose(fp);
        return;
    }

    // Initializationi required by libpng
    png_init_io(output->png_ptr, fp);
    png_set_sig_bytes(output->png_ptr, 8);

    png_read_info(output->png_ptr, output->info_ptr);

    // Write some info into structure
    output->info.width      = png_get_image_width (output->png_ptr,
        output->info_ptr);
    output->info.height     = png_get_image_height(output->png_ptr,
        output->info_ptr);
    output->info.channels   = png_get_channels(output->png_ptr,
        output->info_ptr);
    output->info.bit_depth  = png_get_bit_depth(output->png_ptr,
        output->info_ptr);
    output->info.color_type = png_get_color_type(output->png_ptr,
        output->info_ptr);

    if(read_mode == PNGFILE_READ_INFO_ONLY)
    {    
        fclose(fp);
        output->row_pointers = NULL;
        *output_ptr = output;
        *status_code = RETCODE_OK;
        return;
    }

    // This section converts all supported types of input into RGBA 16-bit
    // Convert palette image to RGB
    if (output->info.color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(output->png_ptr);
    // Expand bit depth to 8 for grayscale images
    // with less than 8 bit depth
    if (output->info.color_type == PNG_COLOR_TYPE_GRAY &&
        output->info.bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(output->png_ptr);
    // Convert palette alpha to normal alpha channel
    if (png_get_valid(output->png_ptr, output->info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(output->png_ptr);
    // Set packing to prevent offset errors
    if (output->info.bit_depth < 8)
        png_set_packing(output->png_ptr);

    // Add alpha channel with full opacity if
    // image doesn't already have one
    if (output->info.color_type == PNG_COLOR_TYPE_RGB ||
        output->info.color_type == PNG_COLOR_TYPE_GRAY ||
        output->info.color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_filler(output->png_ptr, 0xFFFF, PNG_FILLER_AFTER);
    }

    // Convert grayscale img to RGB
    if (output->info.color_type == PNG_COLOR_TYPE_GRAY ||
        output->info.color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(output->png_ptr);
    }

    // Expand channels to full 16 bit resolution
    if (output->info.bit_depth != 16) {
        png_set_expand_16(output->png_ptr);
    }

    // Update read info according to selected filters
    png_read_update_info(output->png_ptr, output->info_ptr);


    // Allocate memory for raw image data and check for errors
    output->row_pointers = (png_byte **) malloc(sizeof(png_bytep) *
        output->info.height);
    if(output->row_pointers == NULL)
    {
        png_destroy_read_struct(&(output->png_ptr),
            &(output->info_ptr), (png_infopp)NULL);
        *status_code = RETCODE_MEMORY_ERROR;
        free(output);
        fclose(fp);
        return;
    }
    for (uint32_t i = 0; i < output->info.height; i++)
    {
        output->row_pointers[i] =
            (png_byte *) malloc(png_get_rowbytes(output->png_ptr,
                output->info_ptr));
        if(output->row_pointers[i] == NULL)
        {
            png_destroy_read_struct(&(output->png_ptr),
                &(output->info_ptr), (png_infopp)NULL);
            *status_code = RETCODE_MEMORY_ERROR;
            for(uint32_t j = 0; j < i; j++)
            {
                    free(output->row_pointers[j]);
            }
            free(output);
            fclose(fp);
            return;
        }
    }

    // Read raw image data
    png_read_image(output->png_ptr, output->row_pointers);
    fclose(fp);
    *output_ptr = output;
    *status_code = RETCODE_OK;
}


// This function reads PngFile raw image data into Image object
//
// Arguments:
// png_ptr - ptr PngFile to read from
//
// Return:
// img - ptr to Image to store result into
// status_code - ptr to variable to put status_code into
//
// Status codes should be handled with handle_error() from "errors.h"
void pngfile_export_image(PngFile* png_ptr, Image **img, int *status_code)
{
    // Allocate memory for image object
    Image *new_img = (Image *) malloc(sizeof(Image));
    if(new_img == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    // Allocate memory for image, check for errors
    Pixel** arr = (Pixel**) malloc(sizeof(Pixel*) *
        png_ptr->info.height);
    if(arr == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    for(uint32_t row = 0; row < png_ptr->info.height; row++) {
        arr[row] = (Pixel*) malloc(sizeof(Pixel) *
            png_ptr->info.width);
        if(arr[row] == NULL)
        {
            *status_code = RETCODE_MEMORY_ERROR;
            for(uint32_t i = 0; i < row; i++)
            {
                free(arr[row]);
            }
            free(arr);
            return;
        }
        // Every pixel is stored in format like RRGGBBAA, big-endian;
        // so first byte in pixel is pos * 8
        for(uint32_t pos = 0; pos < png_ptr->info.width; pos++) {
            arr[row][pos].r = png_ptr->row_pointers[row][pos*8] << 8;
            arr[row][pos].r |= png_ptr->row_pointers[row][pos*8+1];
            arr[row][pos].g = png_ptr->row_pointers[row][pos*8+2] << 8;
            arr[row][pos].g |= png_ptr->row_pointers[row][pos*8+3];
            arr[row][pos].b = png_ptr->row_pointers[row][pos*8+4] << 8;
            arr[row][pos].b |= png_ptr->row_pointers[row][pos*8+5];
            arr[row][pos].a = png_ptr->row_pointers[row][pos*8+6] << 8;
            arr[row][pos].a |= png_ptr->row_pointers[row][pos*8+7];
        }
    }
    new_img->arr = arr;
    new_img->width = png_ptr->info.width;
    new_img->height = png_ptr->info.height;
    *img = new_img;
    *status_code = RETCODE_OK;
}


// Convert RGB color into grayscale with NTSC formula
// No nonlinear gamma correction is used
uint16_t rgb_to_grayscale(uint16_t r, uint16_t g, uint16_t b)
{
    return (6969 * r + 23434 * g + 2365 * b)/32768;
}


// This function transforms PngPixel 2D array back to row_pointers array,
// that's suitable for writing into PNG with pngfile_write()
//
// Arguments:
// img - Image to convert
// output_format - ptr to PngInfo that describes target output format
// 
// Return:
// output_rows - ptr to 2D png_byte array to store raw image data in
// status_code - ptr to variable to put status_code into
//
// Status codes should be handled with handle_error() from "errors.h"
void pngfile_import_image(Image img, PngInfo *output_format,
                          png_byte ***output_rows, int *status_code)
{
    Pixel** pixels = img.arr;
    // Copy output size from image
    output_format->height = img.height;
    output_format->width = img.width;
    // Allocate memory for raw data, check for errors
    *output_rows = (png_byte **) malloc(sizeof(png_bytep) *
        output_format->height);
    if(*output_rows == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    for (uint32_t i = 0; i < output_format->height; i++)
    {
        (*output_rows)[i] = (png_byte *) malloc(sizeof(png_byte) *
            output_format->channels *
            (output_format->bit_depth / 8) *
            output_format->width);
        if((*output_rows)[i] == NULL)
        {
            for(uint32_t j = 0; j < i; j++)
            {
                free((*output_rows)[j]);
            }
            free(*output_rows);
            *status_code = RETCODE_MEMORY_ERROR;
            return;
        }
    }

    // Converting from PngPixels into target format array
    if(output_format->bit_depth == 16)
    {
        switch(output_format->color_type)
        {
        // Converting colors into grayscale, writing GG, big-endian
        case PNGFILE_TYPE_G: 
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    uint16_t gray = rgb_to_grayscale(pixels[row][pos].r,
                                                     pixels[row][pos].g,
                                                     pixels[row][pos].b);
                    (*output_rows)[row][pos*2]   = (uint8_t)(gray>>8);
                    (*output_rows)[row][pos*2+1] = (uint8_t)(gray);
                }
            }
            break;
        // Converting colors into grayscale, writing GGAA, big-endian
        case PNGFILE_TYPE_GA:
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    uint16_t gray = rgb_to_grayscale(pixels[row][pos].r,
                                                     pixels[row][pos].g,
                                                     pixels[row][pos].b);
                    (*output_rows)[row][pos*4]   = (uint8_t)(gray>>8);
                    
                    (*output_rows)[row][pos*4+1] = (uint8_t)(gray);
                    
                    (*output_rows)[row][pos*4+2] =
                        (uint8_t)(pixels[row][pos].a>>8);
                    
                    (*output_rows)[row][pos*4+3] =
                        (uint8_t)(pixels[row][pos].a);
                }
            }
            break;
        // Rejecting opacity, writing RRGGBB, big-endian
        case PNGFILE_TYPE_RGB:
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    (*output_rows)[row][pos*6]   =
                        (uint8_t)(pixels[row][pos].r>>8);

                    (*output_rows)[row][pos*6+1] = 
                        (uint8_t)(pixels[row][pos].r);

                    (*output_rows)[row][pos*6+2] = 
                        (uint8_t)(pixels[row][pos].g>>8);

                    (*output_rows)[row][pos*6+3] = 
                        (uint8_t)(pixels[row][pos].g);

                    (*output_rows)[row][pos*6+4] = 
                        (uint8_t)(pixels[row][pos].b>>8);

                    (*output_rows)[row][pos*6+5] = 
                        (uint8_t)(pixels[row][pos].b);
                }
            }
            break;
        // Writing RRGGBBAA, big-endian
        case PNGFILE_TYPE_RGBA: 
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    (*output_rows)[row][pos*8]   = 
                        (uint8_t)(pixels[row][pos].r>>8);
                    
                    (*output_rows)[row][pos*8+1] = 
                        (uint8_t)(pixels[row][pos].r);
                    
                    (*output_rows)[row][pos*8+2] = 
                        (uint8_t)(pixels[row][pos].g>>8);
                    
                    (*output_rows)[row][pos*8+3] = 
                        (uint8_t)(pixels[row][pos].g);
                    
                    (*output_rows)[row][pos*8+4] = 
                        (uint8_t)(pixels[row][pos].b>>8);
                    
                    (*output_rows)[row][pos*8+5] = 
                        (uint8_t)(pixels[row][pos].b);
                    
                    (*output_rows)[row][pos*8+6] = 
                        (uint8_t)(pixels[row][pos].a>>8);
                    
                    (*output_rows)[row][pos*8+7] = 
                        (uint8_t)(pixels[row][pos].a);
                    
                }
            }
            break;
        }
    }
    else if(output_format->bit_depth == 8)
    {
        // 65535 / 255 - scale 16-bit to 8-bit
        const uint16_t scale_k = 257;
        switch(output_format->color_type)
        {
        case PNGFILE_TYPE_G: // Converting colors into grayscale, writing G
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    uint16_t gray = rgb_to_grayscale(pixels[row][pos].r,
                                                     pixels[row][pos].g,
                                                     pixels[row][pos].b);
                    gray /= scale_k;
                    (*output_rows)[row][pos] = (uint8_t)(gray);
                }
            }
            break;
        case PNGFILE_TYPE_GA: // Converting colors into grayscale, writing GA
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    uint16_t gray = rgb_to_grayscale(pixels[row][pos].r,
                                                     pixels[row][pos].g,
                                                     pixels[row][pos].b);
                    gray /= scale_k;
                    (*output_rows)[row][pos*2]   = (uint8_t)(gray);
                    
                    (*output_rows)[row][pos*2+1] =
                        (uint8_t)(pixels[row][pos].a / scale_k);
                }
            }
            break;
        case PNGFILE_TYPE_RGB: // Rejecting opacity, writing RGB
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    (*output_rows)[row][pos*3]   = 
                        (uint8_t)(pixels[row][pos].r / scale_k);
                    
                    (*output_rows)[row][pos*3+1] = 
                        (uint8_t)(pixels[row][pos].g / scale_k);
                    
                    (*output_rows)[row][pos*3+2] = 
                        (uint8_t)(pixels[row][pos].b / scale_k);
                    
                }
            }
            break;
        case PNGFILE_TYPE_RGBA: // Writing RGBA
            for(uint32_t row = 0; row < output_format->height; row++)
            {
                for(uint32_t pos = 0; pos < output_format->width; pos++)
                {
                    (*output_rows)[row][pos*4]   =
                        (uint8_t)(pixels[row][pos].r / scale_k);
                    
                    (*output_rows)[row][pos*4+1] =
                        (uint8_t)(pixels[row][pos].g / scale_k);
                    
                    (*output_rows)[row][pos*4+2] =
                        (uint8_t)(pixels[row][pos].b / scale_k);
                    
                    (*output_rows)[row][pos*4+3] =
                        (uint8_t)(pixels[row][pos].a / scale_k);
                    
                }
            }
            break;
        }
    }
    *status_code = RETCODE_OK;
}


// This function writes raw data image in row_pointers format
// to PNG file, using output format described by PngInfo object
//
// Arguments:
// path - output file path
// png_info - PngInfo object that describes output format
// row_pointers - raw image data, generated by pngfile_import_image()
// compression_level - output file comparession level (0...9)
// status_code - ptr to variable to put status_code into
//
// Return:
// Status codes should be handled with handle_error() from "errors.h"
void pngfile_write(char* path, PngInfo png_info, png_byte **row_pointers,
                   uint8_t compression_level, int* status_code)
{
    FILE *fp = fopen(path, "wb");
    if(!fp)
    {
        *status_code = RETCODE_IO_ERROR;
        return;
    }

    // Memory allocation
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL);
    if(png == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    png_infop info = png_create_info_struct(png);
    if(info == NULL)
    {
        png_destroy_write_struct(&png, (png_infopp)NULL);
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }

    // Error handling durint io init and writing
    if (setjmp(png_jmpbuf(png)))
    {
        png_destroy_write_struct(&png, &info);
        *status_code = RETCODE_IO_ERROR;
        return;
    }
    
    // Initialization
    png_init_io(png, fp);
    png_set_compression_level(png, compression_level);

    // Setting up header
    png_set_IHDR(png, info, png_info.width, png_info.height,
        png_info.bit_depth, png_info.color_type, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    fclose(fp);
    png_destroy_write_struct(&png, &info);
    *status_code = RETCODE_OK;
}


// This function destroys PngFile object created by pngfile_read()
//
// Arguments:
// file - ptr to PngFile to destroy
void pngfile_destroy_file(PngFile* file)
{
    if(file->row_pointers != NULL)
    {
        for (int i = 0; i < file->info.height; i++)
        {
            free(file->row_pointers[i]);
        }
        free(file->row_pointers);
    }
    png_destroy_read_struct(&(file->png_ptr), &(file->info_ptr),
        (png_infopp)NULL);
    free(file);
}

// This function destroys row_pointers 2D array
// created by pngfile_import_image()
//
// Arguments:
// row_pointers - ptr to 2D row_pointers array
// img_height - height of image from which row_pointers array was created
void pngfile_destroy_rows(png_byte ***row_pointers, uint32_t img_height)
{
    for(uint32_t i = 0; i < img_height; i++)
    {
        free((*row_pointers)[i]);
    }
    free(*row_pointers);
}
