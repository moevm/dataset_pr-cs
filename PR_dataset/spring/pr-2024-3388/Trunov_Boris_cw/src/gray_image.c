#include "gray_image.h"

void gray_image(image_bmp * img, int x_start, int y_start, int x_end, int y_end){
	x_start = (x_start < 0) ? 0 : (x_start >= (int)img->dheader.width) ? img->dheader.width : x_start;
	x_end = (x_end < 0) ? 0 : (x_end >= (int)img->dheader.width) ? img->dheader.width : x_end;
	y_start = (y_start < 0) ? 0 : (y_start >= (int)img->dheader.height) ? img->dheader.height : y_start;
	y_end = (y_end < 0) ? 0 : (y_end >= (int)img->dheader.height) ? img->dheader.height : y_end;
	int start_x = x_start < x_end ? x_start : x_end;
	int end_x = x_end > x_start ? x_end : x_start;
	int start_y = y_end < y_start ? y_end : y_start;
	int end_y = y_start > y_end ? y_start : y_end;
	for (int x = start_x; x < end_x; x++){
		for (int y = start_y; y < end_y; y++){
			int brightness = round((int)img->data[y][x].r*COEFF_RED + (int)img->data[y][x].g*COEFF_GREEN + (int)img->data[y][x].b*COEFF_BLUE);
			brightness = (brightness > 255) ? 255 : (brightness < 0) ? 0 : brightness;
			rgb color_p;
			color_p.r = brightness;
			color_p.g = brightness;
			color_p.b = brightness;			
			set_pixel(img, x, y, color_p);
		}
	}
}

