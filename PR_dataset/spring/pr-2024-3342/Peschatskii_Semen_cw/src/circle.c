#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include <math.h>
void circle(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, Rgb**arr, int *xy, int rad, int thick, int * filcol, int *color, char *out){
int a=thick/2;
if(thick/2>=rad){a=rad;}
int h = bmif->height;
	for(int i =0; i<bmif->width; i++){
		for(int j=0; j<h; j++){
			if(filcol[3]!=-1){
				if((i-*xy)*(i-*xy)+(j-*(xy+1))*(j-*(xy+1))<=rad*rad && j>0 && j<=h){
					arr[h-j][i].r=*(filcol);
					arr[h-j][i].g=*(filcol+1);
					arr[h-j][i].b=*(filcol+2);
				}
			}
			if((i-*xy)*(i-*xy)+(j-xy[1])*(j-xy[1])<=(rad+thick/2)*(rad+thick/2) && (i-*xy)*(i-*xy)+(j-xy[1])*(j-xy[1])>=(rad-a)*(rad-a) && j>0 && j<=h){
				arr[h-j][i].r=*(color);
				arr[h-j][i].g=*(color+1);
				arr[h-j][i].b=*(color+2);
			}
		}
	}
write_bmp(arr, bmif->height, bmif->width, *bmfh, *bmif, out);
}
