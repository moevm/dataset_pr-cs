#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifndef bfh
#define bfh
typedef struct {
        unsigned short signa;
        unsigned int filesize;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int pixelArrOffset;
}__attribute__ ((packed)) BitmapFileHeader;
#endif
#ifndef bih
#define bih
typedef struct {
	unsigned int headerSize;
	unsigned int width;
 	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable;
	unsigned int importantColorCount;
}__attribute__ ((packed)) BitmapInfoHeader;
#endif
#ifndef rog
#define rog
typedef struct{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}__attribute__((packed))Rgb;
#endif
Rgb **read_bmp(FILE *fptr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif){
	int w=bmif->width;
	int h=bmif->height;
	Rgb **arr = malloc(h * sizeof(Rgb*));
	if(arr==NULL){printf("Memory error\n"); exit(49);}
	for(int i = 0; i<h; i++){
		arr[i] = malloc(w*sizeof(Rgb) + (4-(w*sizeof(Rgb))%4)%4);
		if(arr[i]==NULL){printf("Memory error\n"); exit(49);}
		fread(arr[i], 1, w*sizeof(Rgb) + (4-(w*sizeof(Rgb))%4)%4, fptr);
	}
	fclose(fptr);
	return arr;
}
void write_bmp(Rgb **arr, int h, int w, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char* out){
	FILE *output = fopen(out, "wb");
	fwrite(&bmfh, 1, sizeof(BitmapFileHeader), output);
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader), output);
	int padding = (4-(w*3)%4)%4;
	uint8_t paddingBytes[3] = { 0 };
	for(int i = 0; i<h; i++){
		fwrite(arr[i], sizeof(Rgb), w, output);
		fwrite(paddingBytes, sizeof(uint8_t), padding, output);
	}
	for(int i = 0; i<h; i++){for(int j=0; j<w; j++){free(arr[i][j]);}free(arr[i]);}free(arr);
	fclose(output);
}
