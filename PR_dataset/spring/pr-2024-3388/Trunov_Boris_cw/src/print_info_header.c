#include <stdio.h>
#include "print_info_header.h"

void print_info_header(bitmap_info_header header){
	printf("headerSize:\t%x (%u)\n", header.header_size, header.header_size);
	printf("width:     \t%x (%u)\n", header.width, header.width);
	printf("height:    \t%x (%u)\n", header.height, header.height);
	printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bit_per_pixel, header.bit_per_pixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.image_size, header.image_size);
	printf("colorsInColorTable:\t%x (%u)\n", header.colors_in_color_table, header.colors_in_color_table);
	printf("importantColorCount:\t%x (%u)\n", header.important_color_count, header.important_color_count);
}
