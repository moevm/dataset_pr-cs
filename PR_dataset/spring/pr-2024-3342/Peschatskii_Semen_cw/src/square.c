#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
void swap(int  *a, int *b){
	int t = *a;
	*a=*b;
	*b=t;
}
void vert_line(Rgb **arr, int h, int w, int x0, int y0,int y1, int thickness, int* color){
	for(int y = y0; y < y1; y++){
		for (int j = -thickness/2; j < thickness/2+1; j++){
				if(y>0 && y<=h && x0-j>=0 && x0-j<w){
				arr[h-y][x0-j].r=*(color);
				arr[h-y][x0-j].g=*(color + 1);
				arr[h-y][x0-j].b=*(color + 2);
			}
		}
	}
}
void hor_line(Rgb **arr, int h, int w, int x0, int y0, int x1, int thickness, int* color){
	for (int x = x0; x < x1; x++){
		for (int j = -thickness/2; j <thickness/2+ 1; j++){
			if(y0-j<=h && y0-j>0 && x<w && x>=0){
				arr[h-y0+j][x].r=*(color);
				arr[h-y0+j][x].g=*(color + 1);
				arr[h-y0+j][x].b=*(color + 2);
			}
		}
	}

}
void filler(Rgb **arr, int h, int w, int x0, int y0, int x1, int y1, int thickness, int *color){
	for(int y = y0; y < y1; y++){
		for(int x = x0; x <x1; x++){
			if(y>0 && y<=h && x>=0 && x<w){
			arr[h-y][x].r=*(color);
			arr[h-y][x].g=*(color+1);
			arr[h-y][x].b=*(color+2);
			}
		}
	}
}
void diagonal(Rgb **arr, int h, int w, int x0,int y0, int x1, int side, int thickness, int *color){
	for(int x=x0; x<x1; x++){
		for(int j=0-thickness/2;j<thickness; j++){
			if(y0-j-(x0-x)<=h && y0-j-(x0-x)>0 && x>=0 && x<w){
			arr[h-y0+j+(x0-x)][x].r=*(color);
			arr[h-y0+j+(x0-x)][x].g=*(color+1);
			arr[h-y0+j+(x0-x)][x].b=*(color+2);
			}
		}
	}
	for(int x=x0; x<x1; x++){
		for(int j=0-thickness/2; j<thickness; j++){
			if(y0-(x-x0)-j+side-thickness/2<=h && y0-(x-x0)-j+side-thickness/2>0 && x>=0 && x<w){
			arr[h-y0+(x-x0)+j-side+thickness/2][x].r=*(color);
			arr[h-y0+(x-x0)+j-side+thickness/2][x].g=*(color+1);
			arr[h-y0+(x-x0)+j-side+thickness/2][x].b=*(color+2);
			}
		}
	}
}
void cicle(int h, int w, Rgb**arr, int *xy, int rad, int thick, int *filcol, int *color){
        for(int i =0; i<w; i++){
                for(int j=0; j<h; j++){
                        if((j-*xy)*(j-*xy)+(i-xy[1])*(i-xy[1])<=rad*rad && (j-*xy)*(j-*xy)+(i-xy[1])*(i-xy[1])>=(rad-thick)*(rad-thick) && i>=0 && i<h && j>=0 && j<w){
                                arr[i][j].r=*(color);
                                arr[i][j].g=*(color+1);
                                arr[i][j].b=*(color+2);
                        }
                }
        }
}

void square(int cordx, int cordy, int side, int thick, int* fill,FILE * fptr, BitmapFileHeader * bmfh, BitmapInfoHeader  *bmih, Rgb **arr, int *color, char *output){
	hor_line(arr, bmih->height, bmih->width, cordx, cordy, cordx+side,thick, color);
	hor_line(arr, bmih->height, bmih->width, cordx, cordy+side, cordx+side,thick, color);
	vert_line(arr, bmih->height, bmih->width, cordx, cordy, cordy+side, thick, color);
	vert_line(arr, bmih->height, bmih->width, cordx+side, cordy, cordy+side,thick,  color);
	int cords[2];cords[0]=cordx;cords[1]=bmih->height-cordy;cicle(bmih->height, bmih->width, arr, cords, thick/2, thick/2, color, color);
	cords[0]=cordx;cords[1]=bmih->height-cordy-side;cicle(bmih->height, bmih->width, arr, cords, thick/2, thick/2, color, color);
	cords[0]=cordx+side;cords[1]=bmih->height-cordy;cicle(bmih->height, bmih->width, arr, cords, thick/2, thick/2, color, color);
	cords[0]=cordx+side;cords[1]=bmih->height-cordy-side;cicle(bmih->height, bmih->width, arr, cords, thick/2, thick/2, color, color);
	if(fill[0]!=-1){filler(arr, bmih->height, bmih->width, cordx+thick/2, cordy+thick/2, cordx+side-thick/2, cordy+side-thick/2,thick, fill);}
	diagonal(arr, bmih->height, bmih->width, cordx+thick/4, cordy+thick/2, cordx+side-thick/4,side,thick, color);
	write_bmp(arr, bmih->height, bmih->width, *bmfh, *bmih, output);
};
