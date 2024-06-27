#include "draw_filled_circle.h"

void draw_filled_circle(image_bmp * image, int x_center, int y_center, int radius, rgb color){
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
	while (y >= x){
        set_pixel(image, x_center + x, y_center + y, color);
        set_pixel(image, x_center + x, y_center - y, color);
        set_pixel(image, x_center - x, y_center + y, color);
        set_pixel(image, x_center - x, y_center - y, color);
        set_pixel(image, x_center + y, y_center + x, color);
        set_pixel(image, x_center + y, y_center - x, color);
        set_pixel(image, x_center - y, y_center + x, color);
        set_pixel(image, x_center - y, y_center - x, color);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
 	}	
 	if (radius == 1 || radius == 0){
 		return;
 	}else{
   		draw_filled_circle(image, x_center, y_center, (radius/2), color);
	}
}

