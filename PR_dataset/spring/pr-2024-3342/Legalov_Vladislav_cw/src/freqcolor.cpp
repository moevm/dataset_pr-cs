#include "freqcolor.hpp"


void freqcolor(Image *image, rgb color){
	std::map<int, int> colorstree;
	for(int i = 0; i < image->height; ++i)
		for(int j = 0; j < image->width; ++j){
			int key = ((rgb*)&image->bitmap[i][j * image->pixelsize])->toint();
			colorstree[key] += 1;
		}
	int maxcount = 0, col = 0;
	for(auto &val : colorstree){
		if(val.second > maxcount){
			col = val.first;
			maxcount = val.second;
		}
	}
	for(int i = 0; i < image->height; ++i)
		for(int j = 0; j < image->width; ++j)
			if(((rgb*)&image->bitmap[i][j * image->pixelsize])->toint() == col)
				*(rgb*)&image->bitmap[i][j * image->pixelsize] = color;
}
