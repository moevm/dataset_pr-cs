#pragma once

#pragma pack (push, 1)

typedef struct BitmapFileHeader{
	unsigned short signature;
	unsigned int file_size;
	unsigned short first_reserved;
	unsigned short second_reserved;
	unsigned int pixel_arr_offset;
} bmp_file_header_t;

typedef struct BitmapInfoHeader{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bits_per_pixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int x_pixels_per_meter;
	unsigned int y_pixels_per_meter;
	unsigned int colors_in_color_table;
	unsigned int important_color_count;
} bmp_info_header_t;

typedef struct Rgb{
    unsigned char b;
	unsigned char g;
	unsigned char r;
} rgb_t;

#pragma pack(pop)


typedef struct Arguments{
    int info_flag;
    char* input_file;
    char* output_file;

    int triangle;
	int biggest_rect;
	int collage;
	int fill;
	char* number_x;
	char* number_y;
    char* points;
	char* thickness;
    char* color;
	char* fill_color;
	char* old_color;
	char* new_color;

	int gamma;
	char* value;
} args_t;

typedef struct Coordinates{
    int x;
    int y;
} coords_t;

typedef struct FunctionParameters{
    char* input_file;
    char* output_file;
    int info_flag;

    int triangle;
	int biggest_rect;
	int collage;
	int fill;

	int number_x;
	int number_y;
	int thickness;

    coords_t points[3];
	
    rgb_t color;
	rgb_t fill_color;
	rgb_t new_color;
	rgb_t old_color;

	int gamma;
	float value;
} params_t;

typedef struct Image{
	bmp_file_header_t* file_header;
    bmp_info_header_t* info_header;
    rgb_t** pixels;
} img_t;