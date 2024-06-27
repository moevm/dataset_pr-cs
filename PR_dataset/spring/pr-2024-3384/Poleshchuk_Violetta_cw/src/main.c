#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#pragma pack (push, 1)
typedef struct
{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
} BitmapFileHeader;
typedef struct
{
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
} BitmapInfoHeader;
typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;
#pragma pack(pop)
void printFileHeader(BitmapFileHeader header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}
void printInfoHeader(BitmapInfoHeader header){
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
void printHelp(){
	printf("-help, -h: get info, how to use programm\n");
	printf("--info, -I: print info about file\n");
	printf("--input, -i: name of input file\n");
	printf("--output, -o: name of output file\n");
	printf("--rect, -t: function of drawing rectangle\n");
	printf("--left_up, -l: left_up coords\n");
	printf("--right_down, -r: right_down coords\n");
	printf("--start, -s: coords(x0, yo), where function start draw line\n");
	printf("--end, -e: coords(x1, y1)< where function end draw line\n");
	printf("--color, -c: color of line or petagram in circle'\n");
	printf("--radius, -R: radius\n");
	printf("--hexagon: function of drawing hexagon\n");
	printf("--copy: -p: function of copy");
}
void readBitmap(const char *filename, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif, Rgb ***arr){
    FILE *f = fopen(filename, "rb");
    if (f == NULL){
        perror("Error opening file");
        exit(1);
    }
    fread(bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(bmif, sizeof(BitmapInfoHeader), 1, f);
    if(bmfh->signature != 0x4D42 || bmif->headerSize != 40 || bmif->bitsPerPixel != 24 || bmif->compression != 0){
        printf("Error: file has not BMP format\n");
        exit(1);
    }
    unsigned int H = bmif->height;
    unsigned int W = bmif->width;
    *arr = malloc(H * sizeof(Rgb *));
    for (int i = H-1; i >= 0; i--){
        (*arr)[i] = malloc(W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4 ) % 4);
        fread((*arr)[i], 1, W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4)% 4, f);
    }
    fclose(f);
}
void drawCircle(Rgb **arr, int centerX, int centerY, int radius, Rgb color, int H, int W);
int checkNumber(char* str);

void fill_circle(Rgb **arr, int x0, int y0, int radius, Rgb color, int H, int W){
    int xmin = x0 - radius;
    int xmax = x0 + radius;
    int ymin = y0 - radius;
    int ymax = y0 + radius;

    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= W) xmax = W - 1;
    if (ymax >= H) ymax = H - 1;

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            if ((x - x0)*(x - x0) + (y - y0)*(y - y0) <= radius*radius){
                if(x >= 0 && y >= 0 && x < W && y < H){
                    arr[y][x] = color;
                }
            }
        }
    }
}

void drawLine(Rgb** arr, int x0, int y0, int x1, int y1, int thickness, Rgb color, int H, int W){
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x0 >= 0 && x0 < W && y0 >= 0 && y0 < H) {
            if (thickness == 1) arr[y0][x0] = color;
		}
        if(thickness > 1 && x0 - (thickness/2) < W && y0 - (thickness/2) < H && x0 + (thickness/2) >= 0 && y0 + (thickness/2) >= 0){
            fill_circle(arr, x0, y0, thickness / 2, color, H, W);
        }

        if (x0 == x1 && y0 == y1){
			break;
		}
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
void fillTriangle(Rgb** arr, int x0, int y0, int x1, int y1, int centerX, Rgb color, int H, int W){
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x0 >= 0 && x0 < W && y0 >= 0 && y0 < H) {
            drawLine(arr, x0, y0, centerX, y0, 1, color, H, W);
        }
        if (x0 == x1 && y0 == y1) {
            break;
        }
		if (x0 >= W) drawLine(arr, W, y0, centerX, y0, 1, color, H, W);
		else if (x0 <= 0) drawLine(arr, 0, y0, centerX, y0, 1, color, H, W);
		else if (y0 >= H) drawLine(arr, x0, H, centerX, H, 1, color, H, W);
		else if (y0 <= 0) drawLine(arr, x0, 0, centerX, 0, 1, color, H, W);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
void fillRecrangle(Rgb** arr, int x1, int y1, int x2, int y2, Rgb color, int H, int W){
	if (x1 > x2){
		int b = x1;
		x1 = x2;
		x2 = b;
	} if (y2 < y1){
		int b = y1;
		y1 = y2;
		y2 = b;
	}
	for (int i = 1; i < y2-y1; i++){
		drawLine(arr, x1+1, y1+i, x2-1, y1+i, 1, color, H, W);
	}
}
void drawCircle(Rgb** arr, int centerX, int centerY, int radius, Rgb color, int H, int W) {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while (y >= 0) {
		if (centerY + y < H && centerY + y >= 0 && centerX + x < W && centerX + x >= 0) {
			arr[centerY + y][centerX + x] = color;
		}
		if (centerY - y < H && centerY - y >= 0 && centerX + x < W && centerX + x >= 0) {
			arr[centerY - y][centerX + x] = color;
		}
		if (centerY + y < H && centerY + y >= 0 && centerX - x < W && centerX - x >= 0) {
			arr[centerY + y][centerX - x] = color;
		}
		if (centerY - y < H && centerY - y >= 0 && centerX - x < W && centerX - x >= 0) {
			arr[centerY - y][centerX - x] = color;
		}
		drawLine(arr, centerX - x, centerY - y, centerX - x, centerY + y, 1, color, H, W);
		drawLine(arr, centerX + x, centerY - y, centerX + x, centerY + y, 1, color, H, W);
    	
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }
}

void drawRectangle(Rgb** arr, int x1, int y1, int x2, int y2, int thickness, Rgb color, int H, int W){
	//if (fill) fillRecrangle(arr, x1, y1, x2, y2, fillColor, H, W);
	drawLine(arr, x1, y1, x2, y1, thickness, color, H, W);
	drawLine(arr, x2, y1, x2, y2, thickness, color, H, W);
	drawLine(arr, x1, y1, x1, y2, thickness, color, H, W);
	drawLine(arr, x1, y2, x2, y2, thickness, color, H, W);
}

void fillHexagon(Rgb** arr, int x, int y, int radius, Rgb fillColor, int H, int W){
	/* Rgb color1 = {0, 0, 0}; */
	fillRecrangle(arr, x-(radius/2), y - radius*(sqrt(3)/2), x+(radius/2), y + radius*(sqrt(3)/2), fillColor, H, W);
	fillTriangle(arr, x-radius,  y, x-(radius/2), y - radius*(sqrt(3)/2),  x-(radius/2), fillColor, H, W);
	fillTriangle(arr, x-(radius/2), y + radius*(sqrt(3)/2), x-radius, y, x-(radius/2), fillColor, H, W);
	fillTriangle(arr, x+(radius/2), y - radius*(sqrt(3)/2), x+radius, y, x+(radius/2), fillColor, H, W);
	fillTriangle(arr, x+radius, y, x+(radius/2), y + radius*(sqrt(3)/2), x+(radius/2), fillColor, H, W);
}

void drawHexagon(Rgb** arr, int x, int y, int radius, int thickness, Rgb color, int H, int W){
	drawLine(arr, x-radius, y, x-(radius/2), y - radius*(sqrt(3)/2), thickness, color, H, W);
	drawLine(arr, x-(radius/2),  y - radius*(sqrt(3)/2), x+(radius/2), y - radius*(sqrt(3)/2), thickness, color, H, W);
	drawLine(arr, x+(radius/2), y - radius*(sqrt(3)/2), x+radius, y, thickness, color, H, W);
	drawLine(arr, x+radius, y, x+(radius/2), y + radius*(sqrt(3)/2), thickness, color, H, W);
	drawLine(arr,x+(radius/2), y + radius*(sqrt(3)/2), x-(radius/2), y + radius*(sqrt(3)/2), thickness, color, H, W);
	drawLine(arr, x-(radius/2), y + radius*(sqrt(3)/2), x-radius, y, thickness, color, H, W);
	
}
void copy(Rgb** arr, int xLeft, int yLeft, int xRight, int yRight, int xDest, int yDest, int H, int W){
	if (xLeft >= xRight){
		int b = xLeft;
		xLeft = xRight;
		xRight = b;
	}
	if (yLeft >= yRight){
		int p = yLeft;
		yLeft = yRight;
		yRight = p;
	}
	if (xLeft < 0) xLeft = 0;
	if (yLeft < 0) yLeft = 0;
	if (xRight >= W) xRight = W-1;
	if (yRight >= H) yRight = H-1;
	int differenceX = xDest - xLeft;
	int differenceY = yDest - yLeft;
	Rgb** copyArr =  malloc((H+1) * sizeof(Rgb*));
	for (int i = 0; i < H; i++) {
    	copyArr[i] = malloc((W+1) * sizeof(Rgb));
	}
	if (xLeft >= 0 || xLeft < W || xRight >= 0 || xRight < W || yLeft >= 0 || yLeft < H || yRight >= 0 || yRight < H){
		for (int i = xRight; i >= xLeft; i--){
			for (int j = yRight; j >= yLeft; j--){
				if (differenceY + j < H && differenceX + i < W) copyArr[j+differenceY][i+differenceX] =  arr[j][i];
			}
		}
		for (int i = xRight + differenceX; i >= xLeft + differenceX; i--){
			for (int j = yRight + differenceY ; j >= yLeft + differenceY ; j--){
				if (j < H && i < W) arr[j][i] = copyArr[j][i];
			}
		}
	}
}



void square_rhombus(Rgb** arr, int x, int y, int size, Rgb color, int H, int W){
	
	drawLine(arr, x, y, x - (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, 1, color, H, W);
	drawLine(arr, x, y, x + (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, 1, color, H, W);
	drawLine(arr, x - (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, x , y + (size * sqrt(2)), 1, color, H, W);
	drawLine(arr, x + (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, x , y + (size * sqrt(2)), 1, color, H, W);

	fillTriangle(arr, x - (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2,  x, y, x, color, H, W);
	fillTriangle(arr, x + (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2,  x, y, x, color, H, W);
	fillTriangle(arr, x , y + (size * sqrt(2)), x - (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, x, color, H, W);
	fillTriangle(arr, x , y + (size * sqrt(2)),  x + (size * sqrt(2)) / 2, y + (size * sqrt(2)) / 2, x, color, H, W);

}

int* arg(char* str){
	int* arg = malloc(2*sizeof(int));
	char* token = strtok(str, ".");
	int index = 0;
	while(token != NULL){
		int tok = checkNumber(token);
		arg[index++] = tok;
		token = strtok(NULL, ".");
	}
	return arg;
}
Rgb colorArg(char* str){
	Rgb color;
	char* token = strtok(str, ".");
	int index = 0;
	while(token != NULL){
		if (index == 0){
			int r = atoi(token);
			if (r > 255 || r < 0){
				printf("Error, wrong color\n");
				exit(40);
			}
			color.r = r;
		}else if( index == 1){
			int g = atoi(token);
			if (g > 255 || g < 0){
				printf("Error, wrong color\n");
				exit(40);
			}
			color.g = g;
		}else{
			int b = atoi(token);
			if (b > 255 || b < 0){
				printf("Error, wrong color\n");
				exit(40);
			}
			color.b = b;
		}
		index++;
		token = strtok(NULL, ".");
	}
	return color;
}

int checkNumber(char* str){
	for (int i = 0; i < strlen(str); i++){
		if (str[i] == '-' && i == 0){
			continue;
		}else if (isdigit(str[i]) == 0){
			printf("Error, value must be digit\n");
			exit(40);
		}
	}
	int dig = atoi(str);
	return dig;
}

void write_bitmap(const char *output_filename, BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb ***arr, int H, int W){
    FILE *ff = fopen(output_filename, "wb");
    if (ff == NULL)
    {
        perror("Error opening output file");
        exit(40);
    }

    bmif.height = H;
    bmif.width = W;
    fwrite(&bmfh, sizeof(BitmapFileHeader), 1, ff);
    fwrite(&bmif, sizeof(BitmapInfoHeader), 1, ff);

    int padding = (4 - (W * 3) % 4) % 4;
    uint8_t padding_bytes[3] = { 0 };
    for (int i = H-1; i >= 0; i--)
    {        fwrite((*arr)[i], sizeof(Rgb), W, ff);
        fwrite(padding_bytes, sizeof(uint8_t), padding, ff);    }
    
    fclose(ff);
}

int main(int argc, char* argv[]){
	puts("Course work for option 4.9, created by Vioeletta Poleshchuk");
	//const char* filename = argv[argc-1];
	const char* shortOptions = "hIi:o:tl:r:T:c:f::H:C:R:pd:F::su:S:"; // rect
	const struct option longOptions[] = {
		{"help", no_argument, NULL, 'h'},
		{"info", no_argument, NULL, 'I'},
		{"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
		{"rect", no_argument, NULL, 't'},
		{"left_up", required_argument, NULL, 'l'},
		{"right_down", required_argument, NULL, 'r'},
		{"thickness", required_argument, NULL, 'T'},
		{"color", required_argument, NULL, 'c'},
		{"fill", no_argument, NULL, 'f'},
		{"hexagon", no_argument, NULL, 'H'},
		{"center", required_argument, NULL, 'C'},
		{"radius", required_argument, NULL, 'R'},
		{"copy", no_argument, NULL, 'p'},
		{"dest_left_up", required_argument, NULL, 'd'},
		{"fill_color", required_argument , NULL, 'F'},
		{"square_rhombus", no_argument, NULL,'s'},
		{"upper_vertex", required_argument, NULL, 'u'},
		{"size", required_argument, NULL,'S'}
	};
	int opt;
	int optionIndex;
	int option = -1;
	int printFileInfo = 0;
	char* color = NULL;
	char* fillColor = NULL;
	int thickness = 0;
	int fill = 0;
	char* filename = NULL;
	char* left_up = NULL;
	char* right_down = NULL;
	char* center = NULL;
	int radius = 0;
	char* dest_left_up = NULL;
	char* output_filename = NULL;
	int size = 0;
	char* upper = NULL;
	while((opt=getopt_long(argc,argv,shortOptions, longOptions,&optionIndex))!=-1){
		switch(opt){
			case 'h':
				printHelp();
				exit(0);
				break;
			case 'I':
				printFileInfo = 1;
				break;
			case 'i':
				filename = optarg;
                break;
			case 'o':
				output_filename = optarg;
                break;
			case 't':
				option = 1;
				break;
			case 'l':
				left_up = optarg;
				break;
			case 'r':
				right_down = optarg;
				break;
			case 'T':
				thickness = checkNumber(optarg);
				if (thickness <= 0){
					printf("Error, thickness");
					exit(40);
				}
                break;
			case 'c':
				color = optarg;
                break;
			case 'F':
				fillColor = optarg;
                break;
			case 'f':
				fill = 1;
				break;
			case 'H':
				option = 2;
				break;
			case 'C':
				center = optarg;
				break;
			case 'R':
				radius = checkNumber(optarg);
				if (radius <= 0){
					printf("Error, radius");
					exit(40);
				}
				break;
			case 'p':
				option = 3;
				break;
			case 'd':
				dest_left_up = optarg;
				break;
			case 's':
				option = 4;
				break;
			case 'u':
				upper = optarg;
				break;
			case 'S':
				size = checkNumber(optarg);
				break;
			case '?':
				printf("unknown option\n");
                exit(0);
                break;
		}
	}	
	BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;
	Rgb **arr;
	readBitmap(filename, &bmfh, &bmif, &arr);
	if(printFileInfo == 1){
        printFileHeader(bmfh);
        printInfoHeader(bmif);
        exit(0);
    }
	unsigned int H = bmif.height;
	unsigned int W = bmif.width;
	switch (option){
		case 1: ;
			int *leftCoord = arg(left_up);
			int *righCoord = arg(right_down);
			Rgb newColor = colorArg(color);
			Rgb fillColorOption = colorArg(fillColor);
			if (fill != 0) fillRecrangle(arr, leftCoord[0],leftCoord[1], righCoord[0], righCoord[1], fillColorOption, H, W);
			drawRectangle(arr, leftCoord[0],leftCoord[1], righCoord[0], righCoord[1], thickness, newColor, H, W);
			write_bitmap(output_filename, bmfh, bmif, &arr, H, W);
			break;
		case 2: ;
			int *centerH = arg(center);
			Rgb newColorH = colorArg(color);
			Rgb fillColorOptionH = colorArg(fillColor);
			if (fill != 0) fillHexagon(arr, centerH[0], centerH[1], radius, fillColorOptionH, H, W);
			drawHexagon(arr, centerH[0], centerH[1], radius, thickness, newColorH, H, W);
			write_bitmap(output_filename, bmfh, bmif, &arr, H, W);
			break;
		case 3: ;
			int* leftUp = arg(left_up);
			int* rightDown = arg(right_down);
			int* destLeft = arg(dest_left_up);
			copy(arr, leftUp[0], leftUp[1], rightDown[0], rightDown[1], destLeft[0], destLeft[1], H, W);
			write_bitmap(output_filename, bmfh, bmif, &arr, H, W);
			break;
		case 4:;

			Rgb newColorU = colorArg(fillColor);
			int* upperCord = arg(upper);
			square_rhombus(arr, upperCord[0], upperCord[1], size, newColorU, H, W);
			write_bitmap(output_filename, bmfh, bmif, &arr, H, W);
			break;
		default:
            break;
	}
	
return 0;
} 