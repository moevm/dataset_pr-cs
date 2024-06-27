#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
void rotate(BitmapFileHeader * bmfh, BitmapInfoHeader *bmih, Rgb **arr, int *xy0, int *xy1, int deg, char *out){
int h = bmih->height;
int w = bmih->width;
if(*xy0<0){*xy0=0;}if(*xy1<0){*xy1=0;}if(*xy1>w){*xy1=w;}if(*xy0>w){*xy0=w;}   
if(*(xy0+1)<0){*(xy0+1)=0;}if(*(xy0+1)>h){*(xy0+1)=h;}if(*(xy1+1)<0){*(xy1+1)=0;}if(*(xy1+1)>h){*(xy1+1)=h;}
int a = *(xy1+1)-*(xy0+1);
int c=0;int d=0;
int b = *xy1 -*xy0;
if(a>b){c=(a-b)/2;}else{c=-((b-a)/2);}
d=c;
if(a>0 && b>0){
        Rgb **new_arr=malloc(a*sizeof(Rgb*));
        if(new_arr==NULL){printf("Memory error\n"); exit(49);}
        for(int i =0; i<a;i++){
                new_arr[i]=malloc(b*sizeof(Rgb)+(b*3)%4);
                if(new_arr[i]==NULL){printf("Memory error\n"); exit(49);}
        }
        for(int i=0; i<a; i++){
                for(int j =0; j<b; j++){
                        if(*(xy1+1)-i>0 && *(xy1+1)-i<=h && *xy0+j>=0 && *xy0+j<w){
                                new_arr[i][j]=arr[h-*(xy1+1)+i][*xy0+j];
                        }
                }

        }
        if(deg==90){
                for(int i=0; i<a;i++){
                        for(int j = 0; j<b; j++){
                                if(*(xy1+1)-j-c>0 && *(xy1+1)-j-c<=h && *xy1-i+d>=0 && *xy1-i+d<w){
                                        arr[h-*(xy1+1)+j+c][*(xy1)-i+d-1]=new_arr[i][j];
                                }
                        }
                }
        }
        if(deg==180){
                for(int i =0;i<a; i++){
                        for(int j=0; j<b; j++){
                                if(*(xy0+1)+i>0 && *(xy0+1)+i<=h && *xy1-j>=0 && *xy1-j<w){
                                        arr[h-*(xy0+1)-i-1][*(xy1)-j-1]=new_arr[i][j];
                                }
                        }
                }
        }
        if(deg==270){
                for(int i=0; i<a; i++){
                        for(int j=0; j<b; j++){
                                if(*(xy0+1)+j+c+1>0 && *(xy0+1)+j+c+1<=h && *xy0+i-d>=0 && *xy0+i-d<w){
                                        arr[h-*(xy0+1)-j-c-1][*(xy0)+i-d]=new_arr[i][j];
                                }
                        }
                }
        }
for(int i=0; i<a; i++){free(new_arr[i]);}free(new_arr);
}
write_bmp(arr, bmih->height, bmih->width, *bmfh, *bmih, out);
}

