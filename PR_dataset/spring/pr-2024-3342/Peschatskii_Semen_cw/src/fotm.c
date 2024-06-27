#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "fotm.h"
#include "structures.h"
#include "square.h"
#include "filter.h"
#include "rotate.h"
#include "circle.h"
#include "check.h"
#include "romb.h"
#include "smalcheck.h"
void fotm(int argc, char * const args[]){
	FILE* fptr;
	int sqropt=0;
	int fopt=0;
	int ropt=0;
	int copt=0;
	int Ropt=0;
	char buffer[1000];
	char * opts = "crgsoih";
	int opt_index = 0;
	char input[1000];
	char output[1000];
	strcpy(output, "out.bmp");
	int cordf[2];
	int cords[2];
	int side_size;
	int thickness;
	int fill[4];
	fill[3]=-1;
	fill[0]=-1;
	int color[4];
	char name[7];
	int whyDoINeedSoManyVars=0;
	int val;
	int key=0;
	struct option long_options[]={
		{"help", 0, 0,'h'},
		{"squared_lines", 0, 0,'s'},
		{"rgbfilter", 0, 0, 'g'},
		{"rotate", 0, 0, 'r'},
		{"circle", 0, 0, 'c'},
		{"left_up", 1, 0, 'l'},
		{"right_down", 1, 0, 'd'},
		{"angle", 1, 0, 'a'},
		{"side_size", 1, 0, 'z'},
		{"thickness", 1, 0, 't'},
		{"fill_color", 1, 0, 'j'},
		{"fill", 0, 0, 'f'},
		{"rhombus", 0, 0, 'R'},
		{"color", 1, 0, 'q'},
		{"center", 1, 0, 'e'},
		{"radius", 1, 0, 'u'},
		{"component_name", 1, 0, 'n'},
		{"component_value", 1, 0, 'v'},
		{"info", 0, 0, 'i'},
		{"output", 1, 0, 'o'},
		{"input", 1, 0, 'p'},
		{0, 0, 0, 0}
		};
	int opt = getopt_long(argc, args, opts, long_options, &opt_index);
	while(1){
	if(argc==0){opt='h';}
	if(opt!='?'){
	if(opt==-1){break;}
	switch(opt){
		case 'h':
		printf("Each execution of programm requires file name of bmp format that will be change. Default name of output file is out.bmp(can be changed with --output). (req) mean option is required for correct work of program.\n--squared_lines draws a square with set cordinates, side length, side thickness, color and optionaly fillament. Next options are available:\n --left_up (req) sets cordinates of upper left corner(argument format: (num))\n --side_size (req) sets length of sides in pixels(argument format:(num))\n --thickness (req) sets thickness of all lines in pixels(argument format: (num))\n --color (req) sets color of lines(argument format: (num).(num).(num) each number must be in 0-255 interval)\n --fill determines if square is filled or not, requires --fill_color after(argument format: no argument))\n --fill_color (req if --fill is present) sets color of filler pixels(argument format: (num).(num).(num) each number must be in 0-255 interval)\n\n--rgbfilter changes changes red, green, or blue of each pixel to set value. Next options available:\n --component_name (req) gets name of component that will be changed(argument format:red or green or blue))\n --component_val (req) value that each pixel's set component will be changed to(argument format:(num) must be in 0-255 interval)\n\n--rotate rotates certain part of picture(segment of picture is always a square). Next options are available:\n --left_up (req) sets cordinates of upper left corner(argument format:(num))\n --right_down (req) sets cordinates of lower right corner(argument format:(num))\n --angle (req) sets angle that segemnt will be rotate for(argument format:90 or 180 or 270)\n\n--circle draws a circle. Next options are available:\n --center (req) sets cords of center of the circle(argument format:(num).(num))\n --radius sets raduis in pixels(argument format:(num))\n --thickness determines thickness of lines(argument format:(num))\n --color (req) sets color of circle(argument format:(num).(num).(num) each num is 0-255 interval)\n --fill if present circle will be filled withc certain color, requires --fill_color after(argument format:no argument)\n --fill_color (req if --fill is present) sets filler color(argument format:(num).(num).(num) each num is in 0-255 interval)\n");return;
		break;
		case 'i':
			whyDoINeedSoManyVars=1;
			break;
		case 's':
                        if(key==0){key=1;}
                        else{exit(41);}
                        break;
		case 'l':
			cordf[0]=atoi(strtok(optarg, "."));
			cordf[1]=atoi(strtok(NULL, "."));
			sqropt++;
			ropt++;
			break;
		case 'z':
			side_size =atoi(optarg);
			sqropt++;
			break;
		case 't':
			thickness =atoi(optarg);
			sqropt++;
			copt++;
			break;
		case 'j':
			strcpy(buffer, optarg);
			if(check(buffer)){
				fill[0]=atoi(strtok(optarg, "."));
				fill[1]=atoi(strtok(NULL, "."));
				fill[2]=atoi(strtok(NULL, "."));
			}
			else{exit(42);}
			break;
		case 'q':
			strcpy(buffer, optarg);
			if(check(buffer)){
    		        	color[0]=atoi(strtok(optarg, "."));
				color[1]=atoi(strtok(NULL, "."));
				color[2]=atoi(strtok(NULL, "."));
				sqropt++;
				copt++;
				Ropt++;
				}
			else{exit(42);}
			break;
		case 'R':
			if(key==0){key=5;}
			else{exit(41);}
			break;
		case 'g':
                        if(key==0){key=2;}
                        else{exit(41);}
                        break;
                case 'n':
			strcpy(name, optarg);
			if(strcmp(name, "red")!=0 && strcmp(name, "green")!=0 && strcmp(name, "blue")!=0){exit(43);}
			fopt++;
                        break;
                case 'v':
			if(smalcheck(optarg)){val = atoi(optarg);}
			else{exit(42);}
			fopt++;
                        break;
		case 'r':
			if(key==0){key=3;}
			else{exit(41);}
			break;
                case 'd':
			cords[0]=atoi(strtok(optarg, "."));
                        cords[1]=atoi(strtok(NULL, "."));
			ropt++;
                       	break;
                case 'a':
			val = atoi(optarg);
			if(val!=90 && val!=180 && val!=270){exit(45);}
			ropt++;
                        break;
		case 'c':
                        if(key==0){key=4;}
                        else{exit(41);}
			break;
                case 'e':
        	        cordf[0]=atoi(strtok(optarg, "."));
			cordf[1]=atoi(strtok(NULL, "."));
			copt++;
                        break;
       	        case 'u':
			val = atoi(optarg);
			copt++;
                        break;
		case 'p':
			strcpy(input, optarg);
			break;
		case 'o':
			strcpy(output, optarg);
			break;
		case 'f':
			fill[3]=0;
			break;
		default:
			break;
		}
	}
	else{exit(48);}
	opt = getopt_long(argc, args, opts, long_options, &opt_index);
	}
	if(key==1 || key==4){if(fill[3]!=-1 && fill[0]==-1){exit(44);}}
	if(strcmp(output, input)==0){exit(47);}
       	BitmapFileHeader * bmfh = (BitmapFileHeader*) malloc(sizeof(BitmapFileHeader));
       	if(bmfh==NULL){printf("Memory error\n"); exit(49);}
       	BitmapInfoHeader * bmih = (BitmapInfoHeader*) malloc(sizeof(BitmapInfoHeader));
       	if(bmih==NULL){printf("Memory error\n"); exit(49);}
	fptr=fopen(input, "rb");
	if(!fptr){exit(40);}
       	fread(bmfh, 1, sizeof(BitmapFileHeader), fptr);
       	if(bmfh->signa==0x4d42){
       		fread(bmih, 1, sizeof(BitmapInfoHeader), fptr);
			if(whyDoINeedSoManyVars){
			printf("---info---\n");
			printf("Width: %d\n Height: %d\n bitsPerPixel: %d\n", bmih->width, bmih->height, bmih->bitsPerPixel);}
      		if(bmih->bitsPerPixel==24 && bmih->compression==0 && bmih->headerSize==40){
        		Rgb **arr = read_bmp(fptr, bmfh, bmih);
			switch(key){
				case 1:
					if(sqropt==4){
					square(cordf[0], cordf[1], side_size, thickness, fill, fptr, bmfh, bmih, arr, color, output);}
					else{exit(46);}
					break;
				case 2:
					if(fopt==2){
					filter(bmfh, bmih, arr, name, val, output);}
					else{exit(46);}
					break;
				case 3:
					if(ropt==3){
					rotate(bmfh, bmih, arr, cordf, cords, val,output);}
					else{exit(46);}
					break;
				case 4:
					if(copt==4){
					circle(bmfh, bmih, arr, cordf, val, thickness, fill, color, output);}
					else{exit(46);}
					break;
				case 5:
					if(Ropt==1){
					romb(bmfh, bmih, arr, color, output);}
					else{exit(46);}
					break;
				default:
					break;
			}
		}
	}
	free(bmih);
	free(bmfh);
}
