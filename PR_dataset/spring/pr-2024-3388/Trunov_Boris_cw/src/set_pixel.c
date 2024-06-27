#include "set_pixel.h"

void set_pixel(image_bmp * image, int x, int y, rgb color){
		if (y >= 0 && y < image->dheader.height && x >= 0 && x < image->dheader.width){
			image->data[y][x].r = color.r;
	 		image->data[y][x].g = color.g;
	 		image->data[y][x].b = color.b;
 		}
}
