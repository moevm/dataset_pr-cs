#include "inverse.hpp"


void
inverserect(Image *image, int x1, int y1, int x2, int y2){
	for(int i = x1; i < x2; ++i)
		for(int j = y1; j < y2; ++j)
			inversepixel(image->getpixel(i, j));
}

void
inversepixel(rgb *pixel){
	if(pixel){
		pixel->r = ~pixel->r;
		pixel->g = ~pixel->g;
		pixel->b = ~pixel->b;
	}
}
