#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"
void romb(BitmapFileHeader *bmfh, BitmapInfoHeader *bmih, Rgb **arr ,int * color, char* out){
int h = bmih->height;
int w = bmih->width;
int y1;
int y2;
float buff=(h/2)/(w/2);
for(int i=0; i<w/2; i++){
	y1=((((h/2)*1000)/(w/2))*(w/2-i))/1000+1+h/2;
	y2=((((-h/2)*1000)/(w/2))*(w/2-i))/1000+1+h/2;
	for(int j = y2; j<y1; j++){
		if(j>0 && j<=h){
			arr[h-j][i+w/2].r=color[0];
			arr[h-j][i+w/2].g=color[1];
			arr[h-j][i+w/2].b=color[2];
		}
	}
}
for(int i=0; i<w/2; i++){
        y1=((((-h/2)*1000)/(w/2))*(i))/1000+1+h/2;
	y2=((((h/2)*1000)/(w/2))*(i))/1000+1+h/2;
	for(int j = y1; j<y2; j++){
		if(j>0 && j<=h){
	        	arr[h-j][i].r=color[0];
        		arr[h-j][i].g=color[1];
       			arr[h-j][i].b=color[2];
	        }
	}
}

write_bmp(arr, h, w, *bmfh, *bmih, out);
}
