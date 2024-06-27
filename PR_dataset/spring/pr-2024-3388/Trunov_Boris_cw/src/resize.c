#include "resize.h"

void resize(image_bmp * image, int left, int right, int up, int down, char * output_file_name, rgb color){
	image_bmp * new_image = (image_bmp*)malloc(sizeof(image_bmp));
	new_image->bheader = image->bheader;
	new_image->dheader = image->dheader;
	new_image->data = image->data;
	int old_width = image->dheader.width;
	int old_height = image->dheader.height;
	int new_width = old_width + right + left;
	int new_height = old_height + up + down;
	if (new_width <= 0 || new_height <= 0){
		failure("New size of image less then 0");
	}
	unsigned int new_file_size = new_height*(new_width * sizeof(rgb) + ((4 - (new_width * sizeof(rgb)) % 4) % 4))+ sizeof(image->bheader)+sizeof(image->dheader);
	new_image->bheader.filesize = new_file_size;
	new_image->dheader.width = new_width;
	new_image->dheader.height = new_height;
	new_image->data = (rgb**)malloc(sizeof(rgb*) * new_height);
	for (int i = 0; i < new_height; i++){
  		new_image->data[i] = (rgb*)malloc(new_width * sizeof(rgb) + ((4 - (new_width * sizeof(rgb)) % 4) % 4));
	}
	int x0 = 0;
	int y0 = 0;
	for (int x = x0; x < new_width; x++){
		for (int y = y0; y < new_height; y++){
			if (x >= left && y >= down && x < old_width + left && y < old_height + down){		
				new_image->data[y][x] = image->data[y-down][x-left];
			}else{
				new_image->data[y][x].r = color.r;
				new_image->data[y][x].g = color.g;
				new_image->data[y][x].b = color.b;
			}
		}
	}
	save_bmp(output_file_name, *new_image);
	return;
}
