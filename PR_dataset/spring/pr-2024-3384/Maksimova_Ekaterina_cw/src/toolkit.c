#include "toolkit.h"
#include "input_output.h"

int cmp_color(Rgb first, Rgb second){
	if (first.r == second.r && first.g == second.g && first.b == second.b)
		return 1;
	return 0;
}

Rgb get_color(Rgb** image, int x, int y, int width, int height, int* count) {
	if ((0 > x) || (x >= width) ||
	    (0 > y) || (y >= height)) {
	    Rgb zero = {0, 0, 0};
	    return zero;
	}
	
	*count += 1;
	return image[y][x];
}

void set_pixel(Image* image, int x, int y, Rgb color){
	if (x >= 0 && y >=0 && x < image->width && y < image->height) 
    	image -> pix[x][y] = color;
}

void border_rectangle(Image* image, int start_x, int start_y, int end_x, int end_y, int thick, Rgb color){
    for(int x = start_x; x <= end_x; x++){
        for(int y = start_y; y <= start_y+thick; y++){
        	set_pixel(image,x,y,color);
        }

        for(int y = end_y-thick; y <= end_y; y++){
        	set_pixel(image,x,y,color);
        }
    }

    for(int y = start_y; y <= end_y; y++){
        for(int x = start_x; x <= start_x+thick; x++){
        	set_pixel(image,x,y,color);
        }

        for(int x = end_x-thick; x <= end_x; x++){
        	set_pixel(image,x,y,color);
        }
    }
}



int cmp_color_on_area(Image* image, int x1, int y1, int x2, int y2, Rgb old){
    for(int y=y1;y<y2;y++)
    {
        for(int x=x1;x<x2;x++)
        {
            if (cmp_color(image->pix[x][y], old) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void draw_circle(Image* image, Rgb color, int center_x, int center_y, int thickness,int radius){
	for (int x = center_x - radius - thickness; x <= center_x + radius + thickness; x++) {
        for (int y = center_y - radius - thickness; y <= center_y + radius + thickness; y++) {
        	double distance = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));
            if (distance > radius && distance < (radius + thickness))
                    set_pixel(image, x, y, color);
        }
    }
}

int get_number(char* ptr){
    for(int i = 0; i<strlen(ptr);i++){
        if(isdigit(ptr[i]) == 0){
        	fprintf(stderr, "error: value must me a non-negative digit");
            exit(40);
        }
    }
    int tmp = atoi(ptr);
    if(tmp>=0){
        return tmp;
    }else{
        fprintf(stderr, "error: value must me a non-negative digit");
        exit(40);
    }

}

Rgb get_color_arg(char* str){
	Rgb color;
	char* token = strtok(str, ".");
	int index = 0;
	while(token != NULL){
		int t = get_number(token);
		if (t>255){
			fprintf(stderr, "error: invalid color input");
			exit(40);
		}else{
			if (index == 0){
				color.r = t;
			}else if( index == 1){
				color.g = t;
			}else{
				color.b = t;
			}
			index++;
			token = strtok(NULL, ".");
		}
	}
	if (index > 3){
		fprintf(stderr, "error: invalid color input or RGBA");
		exit(40);
	}
	return color;
}
