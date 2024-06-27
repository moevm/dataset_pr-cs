#include "image.hpp"

Image::~Image(){
	if(bitmap){
		for(int i = 0; i < height; ++i)
			delete[] bitmap[i];
		delete[] bitmap;
	}
}

void
Image::setpixel(int x, int y, rgb &color){
	if(checkCoordinats(x, y)){
		*getpixel(x, y) = color;
	}
}

rgb*
Image::getpixel(int x, int y){
	if(checkCoordinats(x, y))
		return (rgb*)&bitmap[y][x * pixelsize];
	return NULL;
}

bool
Image::checkCoordinats(int x, int y){
	return (x >= 0 && x < width && y >= 0 && y < height);
}

int
rgb::toint(){
	return ((int(r) << 16) + (int(g) << 8) + int(b));

}

rgb::rgb(int x, int y, int z){
	r = x;
	g = y;
	b = z;
}

rgb::rgb(){
	r = 0;
	g = 0;
	b = 0;
}
