#include<iostream>
#include<cstring>
#include<utility>
#include<math.h>

#include "image.hpp"
#include "input_arguments.hpp"
#include "pngdata.hpp"
#include "square.hpp"
#include "inverse.hpp"
#include "exchange.hpp"
#include "freqcolor.hpp"


void rhombus(Image *image, rgb color){
	int height = image->height;
	int width = image->width;

	int x_center = width / 2;
	int y_center = height / 2;
	float ta = (float)height / (float)width ;



	for(int i = 0; i <= y_center; ++i)
		for(int j = 0; j <= x_center; ++j){
			if(i >= int(ta * j)){
				image->setpixel(j + x_center, i, color);
				image->setpixel(x_center - j, i, color);
			}
			if(i <= int(ta * j)){
				image->setpixel(j, i + y_center, color);
				image->setpixel(width - j, i + y_center, color);
			}
		}
}




int main(int argc, char** argv){
	arguments *args = getarguments(argc, argv);

	FILE *file;
	if(args->ishelp){
		file = fopen("help", "rb");
		if (!file) {
			std::cout << "File \"help\" is not found.\n";
			exit(49);
		}
		char ch = (char) fgetc(file);
		while (ch != EOF) {
			printf("%c", ch);
			ch = (char) fgetc(file);
		}
		fclose(file);
		exit(0);
	}
	file = fopen(args->input_path, "rb");
	if(!file){
		std::cout << "Input file is not found\n";
		exit(49);
	}
	dataPNG source;
	source.readPNG(file);
	fclose(file);
	if(args->isinfo){
		source.printdata();
		exit(0);
	}

	Image *image = source.decodImage();


	switch(args->number){
		case 1: {
			rgb color, fill_color;
			if(args->color[0] == -1){
				std::cout << "Color is not defined\n";
				exit(42);
			}
			color = rgb(args->color[0], args->color[1], args->color[2]);

			if(args->thickness <= 0){
				std::cout << "Invalid thickness value\n";
				exit(42);
			}
			if(args->length <= 0){
				std::cout << "Invalid side size value\n";
				exit(42);
			}
			if(args->isfill){
				if(args->fill_color[0] == -1){
					std::cout << "Fill color is not defined\n";
					exit(42);
				}
				fill_color = rgb(args->fill_color[0], args->fill_color[1], args->fill_color[2]);
				drawSquare(image, args->x1, args->y1, args->length, args->thickness, color, fill_color);
			}
			else
				drawSquare(image, args->x1, args->y1, args->length, args->thickness, color);
			break;
			}
		case 2:
			if (args->x1 > args->x2)
				std::swap(args->x1, args->x2);
			if (args->y1 > args->y2)
				std::swap(args->y1, args->y2);
			if(args->type_exchange){
				exchange(image, args->x1, args->y1, args->x2, args->y2, args->type_exchange);
			} else{
				std::cout << "Invalid exchange type\n";
				exit(42);
			}
			break;
		case 3: {
			rgb color;
			if(args->color[0] == -1){
				std::cout << "Color is not defined\n";
				exit(42);
			}
			color = rgb(args->color[0], args->color[1], args->color[2]);
			freqcolor(image, color);
			break;
			}
		case 4:
			if (args->x1 > args->x2)
				std::swap(args->x1, args->x2);
			if (args->y1 > args->y2)
				std::swap(args->y1, args->y2);
			inverserect(image, args->x1, args->y1, args->x2, args->y2);
			break;
		case 5:{
			rgb color;
			if(args->color[0] == -1){
				std::cout << "Color is not defined\n";
				exit(42);
			}
			color = rgb(args->color[0], args->color[1], args->color[2]);
			rhombus(image, color);
			break;
			}
		default:
			std::cout << "Undefined operation\n";
			exit(43);
	}

	source.updateData(*image);
	delete image;
	file = fopen(args->output_path, "wb");
	source.writePNG(file);
	fclose(file);
	delete args;
    return 0;
}
