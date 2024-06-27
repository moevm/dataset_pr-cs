#include "input_output.h"

Image read_bmp(char file_name[], BitmapFileHeader*
bmfh, BitmapInfoHeader* bmif){
	Image image;
    FILE *f = fopen(file_name, "rb");
    if (f == NULL) {
        print_error_and_exit("Error opening the file.\n");
    }
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    if (bmfh->signature != 0x4D42){
        print_error_and_exit("Error opening\n");
    }
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    image.height = bmif->height;
    image.width = bmif->width;

	if (image.height > 50000 || image.width > 50000) {
	    fprintf(stderr, "error: not enough memory");
        fclose(f);
        exit(40);
	}
	if  (bmif->bitsPerPixel != 24 || bmif->compression != 0) {
        fprintf(stderr, "error: unsupported bmp format\n");
        fclose(f);
        exit(40);
    }
    Rgb **arr = malloc(image.height * sizeof(Rgb*));
    
    int padd = 4 - (image.width*sizeof(Rgb))%4;
    for(unsigned int i = 0; i < image.height; i++){ 
        arr[i] = malloc(image.width * sizeof(Rgb) + padd%4); 
        fread(arr[i], 1, image.width * sizeof(Rgb) + padd%4, f); 
    } 
    fclose(f);
    Rgb **pix = malloc(image.width * sizeof(Rgb*));
    for(int i = 0; i < image.width; i++){
        pix[i] = malloc(image.height * sizeof(Rgb));
    }
    for(int i=0; i < image.width; i++)
        for(int j=0; j<image.height; j++){
            pix[i][j] = arr[image.height-j-1][i];
        }
    image.pix = pix;
    return image;
}

void print_file_header(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:     \t%x (%u)\n", header.width, header.width);
    printf("height:    \t%x (%u)\n", header.height, header.height);
    printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void write_bmp(char file_name[], Image* image, BitmapFileHeader bmfh, BitmapInfoHeader bmif){	
	Rgb **arr = malloc(image->height * sizeof(Rgb*));
    for(int i = 0; i < image->height; i++){
        arr[i] = malloc(image->width * sizeof(Rgb) );
    }
	for(int i=0; i < image->width; i++)
        for(int j=0; j < image->height; j++){
            arr[image->height-j-1][i] = image->pix[i][j];
        }
    FILE *ff = fopen(file_name, "wb");
    if (ff == NULL) {
        print_error_and_exit("Error opening the file.\n");
    }
    int padd = 4 - (image->width*sizeof(Rgb))%4;
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    for(int i = 0; i < image->height; i++){
    	fwrite(arr[i], 1, image->width * sizeof(Rgb) + padd%4, ff); 
    }
    fclose(ff);
}
