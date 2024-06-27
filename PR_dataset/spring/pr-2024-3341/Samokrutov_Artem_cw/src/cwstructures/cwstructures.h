#ifndef CWSTRUCTURES_H
#define CWSTRUCTURES_H


#pragma pack(push, 1)
typedef struct {
    unsigned short signature;
    unsigned int file_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int data_offset;

    unsigned int header_size;
    signed int width;
    signed int height;
    unsigned short color_planes_num;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int image_size;
    unsigned int horizontal_resolution_pxpm;
    unsigned int vertical_resolution_pxpm;
    unsigned int number_of_colors;
    unsigned int number_of_important_colors;
} Bitmap_header_t;
#pragma pack(pop)

typedef struct {
    unsigned char b, g, r;
} RGB_t;

typedef struct {
    Bitmap_header_t hdr;
    unsigned char *data;
    unsigned int data_size;
} Bitmap_image_t;

typedef struct {
    int x, y;
} Coord_t;


#endif