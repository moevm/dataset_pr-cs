#ifndef PNGFILE_H
#define PNGFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <stdint.h>
#include "errors.h"
#include "image.h"


// Implement some color types
#define PNGFILE_TYPE_G    PNG_COLOR_TYPE_GRAY
#define PNGFILE_TYPE_GA   PNG_COLOR_TYPE_GRAY_ALPHA
#define PNGFILE_TYPE_RGB  PNG_COLOR_TYPE_RGB
#define PNGFILE_TYPE_RGBA PNG_COLOR_TYPE_RGB_ALPHA
#define PNGFILE_TYPE_P    PNG_COLOR_TYPE_PALETTE

// Compression levels
#define PNGFILE_NO_COMPRESSION      0
#define PNGFILE_OPTIMAL_COMPRESSION 6
#define PNGFILE_MAX_COMPRESSION     9

// Flags
#define PNGFILE_READ_INFO_ONLY 1
#define PNGFILE_READ_NORMAL    0

typedef struct PngInfo_struct {      
        uint32_t width, height;
        uint8_t channels, bit_depth;
        uint8_t color_type;
} PngInfo;

typedef struct PngFile_struct {
        PngInfo     info;
        png_structp png_ptr;
        png_infop   info_ptr;
        png_bytep*  row_pointers;
} PngFile;


void pngfile_read(char* path, uint8_t info_only, PngFile** output_ptr,
                  int* status_code);

void pngfile_export_image(PngFile* png_ptr, Image **img, int *status_code);

void pngfile_import_image(Image img, PngInfo *output_format,
                          png_byte ***output_rows, int *status_code);

void pngfile_write(char* path, PngInfo png_info, png_byte **row_pointers,
                   uint8_t compression_level, int* status_code);

void pngfile_destroy_file(PngFile* png_ptr);

void pngfile_destroy_rows(png_byte ***row_pointers, uint32_t img_height);

#endif
