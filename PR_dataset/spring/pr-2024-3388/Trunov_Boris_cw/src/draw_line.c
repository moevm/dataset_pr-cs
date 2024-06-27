#include "draw_line.h"

#include <stdio.h>

void draw_line(image_bmp * image,int x_start, int y_start, int x_end, int y_end, rgb color, int thickness){
	--y_start;
	--x_end;
	int delta_x= abs(x_end - x_start);
    int delta_y = abs(y_end - y_start);
    int sign_x = x_start < x_end ? 1 : -1;
    int sign_y = y_start < y_end ? 1 : -1;
    int second_error;
    int first_error = delta_x - delta_y;
    while(x_start != x_end || y_start != y_end){
		if (thickness == 1){
		    set_pixel(image, x_start,y_start, color);
	    }else{
	 	   draw_filled_circle(image, x_start, y_start, thickness/2, color);
	 	}
        second_error = first_error * 2;
        if(second_error > -delta_y) {
            first_error -= delta_y;
            x_start += sign_x;
        }
        if(second_error < delta_x) {
            first_error += delta_x;
            y_start += sign_y;
        }
    }
}

