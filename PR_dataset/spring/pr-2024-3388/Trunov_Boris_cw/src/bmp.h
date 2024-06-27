#ifndef BMP_HEADER
#define BMP_HEADER

#pragma pack(push, 1)
typedef struct {
    unsigned short signature; // unsigned char signature[2]
    unsigned int filesize;
    unsigned char unused[4];
    unsigned int pixel_arr_offset;
} bitmap_file_header;

typedef struct {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bit_per_pixel;
    unsigned int compression;
    unsigned int image_size;
    unsigned int x_pixels_per_meter;
    unsigned int y_pixels_per_meter;
    unsigned int colors_in_color_table;
    unsigned int important_color_count;
} bitmap_info_header;
#pragma pack(pop)

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} rgb;

typedef struct {
    bitmap_file_header bheader;
    bitmap_info_header dheader;
    rgb ** data;
} image_bmp;

#endif

