#include "exchange.hpp"


void exchange(Image *image, int x1 , int y1, int x2 , int y2, int type){
	int size = image->pixelsize;
	x1 = (x1 < 0)? 0 : x1;
	y1 = (y1 < 0)? 0 : y1;
	x2 = (x2 > image->width)? image->width : x2;
	y2 = (y2 > image->height)? image->height : y2;
	x2 -= (x2 - x1) % 2;
	y2 -= (y2 - y1) % 2;

	int x = x2 - x1;
	int y = y2 - y1;
	if (x <= 1 || y <= 1)
		return;

	uint8_t **buffer = newtable(y, x * size);
	copyrect(buffer, image->bitmap, 0, 0, x1 * size, y1, x * size, y);

	x /= 2;
	y /= 2;

	switch(type){
		case 1:
			copyrect(image->bitmap, buffer, x1 * size, y1, 0, y, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1, 0, 0, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1 + y, x * size, 0, x * size, y);
			copyrect(image->bitmap, buffer, x1 * size, y1 + y, x * size, y, x * size, y);
			break;
		case 2:
			copyrect(image->bitmap, buffer, x1 * size, y1, x * size, 0, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1, x * size, y, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1 + y, 0, y, x * size, y);
			copyrect(image->bitmap, buffer, x1 * size, y1 + y, 0, 0, x * size, y);
			break;
		case 3:
			copyrect(image->bitmap, buffer, x1 * size, y1, x * size, y, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1 + y, 0, 0, x * size, y);
			copyrect(image->bitmap, buffer, (x1 + x) * size, y1, 0, y, x * size, y);
			copyrect(image->bitmap, buffer, x1 * size, y1 + y, x * size, 0, x * size, y);
			break;
	}

	for(int i = 0; i < y * 2; ++i)
			delete[] buffer[i];
	delete[] buffer;
}

void copyrect(uint8_t **dest, uint8_t **src, int x1 , int y1, int x2 , int y2, int x, int y){
	for(int i = 0; i < y; ++i)
		memcpy(dest[y1 + i] + x1, src[y2 + i] + x2, x);
}


uint8_t **newtable(int height, int width){
	uint8_t **res = new uint8_t*[height];
	if (res == NULL){
		std::cout <<  "Error: not enough memory\n";
		exit(48);
	}
	for(int i = 0; i < height; ++i){
		res[i] = new uint8_t[width];
		if (res[i] == NULL){
			std::cout <<  "Error: not enough memory\n";
			exit(48);
		}
	}
	return res;
}
