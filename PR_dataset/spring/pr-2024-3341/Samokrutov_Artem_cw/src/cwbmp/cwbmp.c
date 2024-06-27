#ifndef CWBMP_C
#define CWBMP_C

#include "../cwbmp/cwbmp.h"


void info(const char *filename)
{
    Bitmap_image_t *bmp = load_bmp(filename);

    Bitmap_header_t *header = &bmp->hdr;

    printf("Signature -- %hu\n", header->signature);
    printf("File size -- %u\n", header->file_size);
    printf("Data start at byte №%u\n", header->data_offset);
    printf("Header size -- %u\n", header->header_size);
    printf("Size -- %i by %i\n", header->width, header->height);
    printf("Number of color planes -- %hu\n", header->color_planes_num);
    printf("Bits per pixel -- %hu\n", header->bits_per_pixel);
    printf("Compression -- %u\n", header->compression);
    printf("Resolution -- %u by %u\n", header->horizontal_resolution_pxpm, header->vertical_resolution_pxpm);
    printf("Number of colors -- %u\n", header->number_of_colors);
    printf("Number of important colors -- %u\n", header->number_of_important_colors);

    free(bmp);
}

Bitmap_image_t *load_bmp(const char *filename) 
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        throw_error(FILE_ERROR_MSG, FILE_ERROR_RET_VAL);
    }

    Bitmap_image_t *bmp = (Bitmap_image_t *)malloc(sizeof(Bitmap_image_t));

    if (bmp == NULL) 
    {
        throw_error(MEMORY_ERROR_MSG, MEMORY_ERROR_RET_VAL);
    }
    
    int read_hdr = fread(&bmp->hdr, sizeof(Bitmap_header_t), 1, file);

    if (read_hdr != 1)
    {
        throw_error(BMP_DATA_ERROR_MSG, BMP_DATA_ERROR_RET_VAL);
    }

    if (!valid_header(bmp))
    {
        throw_error(NOT_A_BMP_ERROR_MESSAGE, NOT_A_BMP_ERROR_RET_VAL);
    }

    bmp->data_size = bmp->hdr.file_size - sizeof(Bitmap_header_t);
    bmp->data = (unsigned char *)malloc(bmp->data_size * sizeof(unsigned char));

    if (bmp->data == NULL) {
        throw_error(MEMORY_ERROR_MSG, MEMORY_ERROR_RET_VAL);
    }

    fseek(file, bmp->hdr.data_offset, SEEK_SET);
    int read_data = fread(bmp->data, bmp->data_size, 1, file);

    if (read_data != 1) {
        throw_error(BMP_DATA_ERROR_MSG, BMP_DATA_ERROR_RET_VAL);
    }

    fclose(file);
    return bmp;
}

void save_bmp(const Bitmap_image_t *bmp, const char *filename) 
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL) 
    {
        throw_error(FILE_ERROR_MSG, FILE_ERROR_RET_VAL);
    }

    rewind(file);
    int written_hdr = fwrite(&bmp->hdr, sizeof(Bitmap_header_t), 1, file);

    if (written_hdr != 1)
    {
        throw_error(BMP_DATA_ERROR_MSG, BMP_DATA_ERROR_RET_VAL);
    }

    fseek(file, bmp->hdr.data_offset, SEEK_SET);
    int written_data = fwrite(bmp->data, bmp->data_size * sizeof(unsigned char), 1, file);

    if (written_data != 1)
    {
        throw_error(BMP_DATA_ERROR_MSG, BMP_DATA_ERROR_RET_VAL);
    }

    fclose(file);
}

void free_bmp(Bitmap_image_t *bmp) 
{
    if (bmp != NULL) 
    {
        if (bmp->data != NULL) 
        {
            free(bmp->data);
        }
        free(bmp);
    }
}

bool valid_rgb(RGB_t color)
{
    if (color.r < 0x00 || color.r > 0xFF)
    {
        return false;
    }

    if (color.g < 0x00 || color.g > 0xFF)
    {
        return false;
    }

    if (color.b < 0x00 || color.b > 0xFF) 
    {
        return false;
    }

    return true;
}

bool valid_coordinate(Coord_t coordinate, int width, int height)
{
    if (coordinate.x < 0 || coordinate.x >= width)
    {
        return false;
    }

    if (coordinate.y < 0 || coordinate.y >= height)
    {
        return false;
    }

    return true;
}

bool valid_header(const Bitmap_image_t *image)
{
    if (image->hdr.signature != BMP_SIGNATURE)
    {
        return false;
    }

    if (image->hdr.bits_per_pixel != BITS_PER_PIXEL)
    {
        return false;
    }

    if (image->hdr.compression != COMPRESSION)
    {
        return false;
    }

    return true;
}

int get_padding(int width)
{
    return (4 - (width * sizeof(RGB_t)) % 4) % 4;
}

int get_row_size(int width)
{
    return (width * sizeof(RGB_t)) + get_padding(width);
}

int get_position(Coord_t coordinate, int width, int height) 
{
    if (!valid_coordinate(coordinate, width, height)) 
    {
        throw_error(INVALID_COORDINATE_ERROR_MSG, INVALID_COORDINATE_ERROR_RET_VAL);
    }

    int col = coordinate.x * sizeof(RGB_t);
    int row = (height - coordinate.y - 1) * get_row_size(width);

    return col + row;
}

RGB_t get_pixel(const Bitmap_image_t *bmp, Coord_t coordinate)
{
    int width = bmp->hdr.width;
    int height = bmp->hdr.height;
    int pos = get_position(coordinate, width, height);

    RGB_t color = {
        bmp->data[pos + RED],
        bmp->data[pos + GREEN],
        bmp->data[pos + BLUE]
    };

    return color;
}

void set_pixel(Bitmap_image_t *bmp, Coord_t coordinate, RGB_t color)
{
    if (!valid_rgb(color)) 
    {
        throw_error(INVALID_RGB_ERROR_MSG, INVALID_RGB_ERROR_RET_VAL);
    }

    int width = bmp->hdr.width;
    int height = bmp->hdr.height;
    int pos = get_position(coordinate, width, height);

    bmp->data[pos + RED] = color.r;
    bmp->data[pos + GREEN] = color.g;
    bmp->data[pos + BLUE] = color.b;
}


#endif