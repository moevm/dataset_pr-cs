#include "utils.h"

void panic(char* message){
	fprintf(stderr, ERROR_TEMPLATE, message, EXIT_CODE);
	exit(EXIT_CODE);
}

void free_args(args_t* args){
	free(args->input_file);
	free(args->output_file);
	free(args->number_x);
	free(args->number_y);
	free(args->points);
	free(args->thickness);
	free(args->color);
	free(args->fill_color);
	free(args->old_color);
	free(args->new_color);
}

void free_image(img_t* image){
	for (size_t i = 0; i < image->info_header->height; i++)
		free(image->pixels[i]);
	free(image->pixels);
	
	free(image->file_header);
	free(image->info_header);
}

void print_file_header(bmp_file_header_t header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.file_size, header.file_size);
	printf("reserved1:\t%x (%hu)\n", header.first_reserved, header.first_reserved);
	printf("reserved2:\t%x (%hu)\n", header.second_reserved, header.second_reserved);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixel_arr_offset, header.pixel_arr_offset);
}

void print_info_header(bmp_info_header_t header){
	printf("headerSize:\t%x (%u)\n", header.header_size, header.header_size);
	printf("width:     \t%x (%u)\n", header.width, header.width);
	printf("height:    \t%x (%u)\n", header.height, header.height);
	printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bits_per_pixel, header.bits_per_pixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.image_size, header.image_size);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.x_pixels_per_meter, header.x_pixels_per_meter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.y_pixels_per_meter, header.y_pixels_per_meter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colors_in_color_table, header.colors_in_color_table);
	printf("importantColorCount:\t%x (%u)\n", header.important_color_count, header.important_color_count);
}