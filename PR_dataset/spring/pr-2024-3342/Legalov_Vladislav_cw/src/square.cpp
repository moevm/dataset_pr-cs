#include "square.hpp"


void drawSquare(Image *image, int x, int y, int l, int thickness, rgb color){
	for(int k = 0; k < thickness; ++k){
		for(int i = x + k; i < x + l - k; ++i){
			image->setpixel(i, y + k, color);
			image->setpixel(i, y + l - k - 1, color);
		}
		for(int j = y + k; j < y + l - k; ++j){
			image->setpixel(x + k, j, color);
			image->setpixel(x + l - k - 1, j, color);
		}
	}
}

void drawSquare(Image *image, int x, int y, int l, int thickness, rgb color, rgb fill){
	x -= thickness / 2;
	y -= thickness / 2;
	l += thickness / 2;
	drawSquare(image, x, y, l, thickness, color);
	x += thickness;
	y += thickness;
	l = (l >= thickness)? l - 2 * thickness: 0;
	for(int i = x; i < x + l; ++i)
		for(int j = y; j < y + l; ++j)
			image->setpixel(i, j, fill);
}


