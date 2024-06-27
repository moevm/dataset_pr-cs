#include "help.h"

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

void print_help(){
	printf("Flags -o, --output are used to set name of output file (out.bmp by default).\n");
	printf("Flags -i, --input are used to set name of input file (last argument by default).\n");
	printf("Flag --info is used to get the info about bmp image.\n");
	printf("Functions to edit the image:\n");
	
	printf("\nFlag --inverse is used to invert a given area. For initializing it you need to set some values:\n");
	printf("\t--left_up <left.up>: \n\t left is the x coordinate, up is the y coordinate\n");
	printf("\t--right_down <right.down>: \n\t right is the x coordinate, down is the y coordinate\n");
	
	printf("\nFlag --gray is used to gray a given area. For initializing it you need to set some values:\n");
	printf("\t--left_up <left.up>: \n\t left is the x coordinate, up is the y coordinate\n");
	printf("\t--right_down <right.down>: \n\t right is the x coordinate, down is the y coordinate\n");
	
	printf("\nFlag --resize is used to resize the image. For initializing it you need to set some values:\n");
	printf("\t--left <left>\n");
	printf("\t--right <right>\n");
	printf("\t--above <above>\n ");
	printf("\t--below <below>\n ");
	printf("\t You must enter at least one side value. A positive number means expansion, a negative number means pruning\n");
	printf("\t--color <rrr.ggg.bbb>: \n\t Background color\n");
	
	printf("\n--line is used to draw line. For initializing it you need to set some values:\n");
	printf("\t--start <x.y>\n ");
	printf("\t--end <x.y>\n ");
	printf("\t--color <rrr.ggg.bbb>: \n\t Background color\n");
	printf("\t-- thickness <value>: \n\t Value must be positive\n");
}

