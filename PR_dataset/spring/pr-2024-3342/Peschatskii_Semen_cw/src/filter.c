#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
void filter(BitmapFileHeader * bmfh, BitmapInfoHeader *bmih, Rgb **arr, char * name, int val, char *out){
	if(strcmp(name, "red")==0){
		for(int i=0; i<bmih->height; i++){
			for(int j=0; j<bmih->width; j++){
				arr[i][j].r=val;
			}
		}
	}
	if(strcmp(name, "blue")==0){
                for(int i=0; i<bmih->height; i++){
                        for(int j=0; j<bmih->width; j++){
				arr[i][j].b=val;
			}
		}
	}
	if(strcmp(name,"green")==0){
                for(int i=0; i<bmih->height; i++){
                        for(int j=0; j<bmih->width; j++){
                                arr[i][j].g=val;
			}
		}
	}
	write_bmp(arr, bmih->height, bmih->width, *bmfh, *bmih, out);
}
