#include "../include/image_processing.h"

void process_file(Configs* config, Png* image){
	int flag = 1;
	if (config->input != NULL && config->info == 1){
		read_png_file(config->input, image);
		printf(INFO, image->height, image->width, image->color_type, image->bit_depth);
		for (int y = 0; y < image->height; y++)
        		free(image->row_pointers[y]);
    		free(image->row_pointers);
	}
	if (config->input != NULL && config->output != NULL){
		if ((config->rgbfilter)->n == 1){
			if ((config->rgbfilter)->component_name != ' ' && (config->rgbfilter)->component_value != 256){
				read_png_file(config->input, image);
				rgbfilter(image, (config->rgbfilter)->component_name, (config->rgbfilter)->component_value);
				write_png_file(config->output, image);
			} else flag = 0;
		}
		if ((config->squared_lines)->n == 1){
			if ((config->squared_lines)->coordinates != 0 && (config->squared_lines)->thickness_color != NULL && (config->squared_lines)->thickness != -1){
					read_png_file(config->input, image);
					squared_lines(config, image);
					write_png_file(config->output, image);
			} else flag = 0;
		}
		if ((config->rotate)->n == 1){
			if ((config->rotate)->coordinates!=0 && (config->rotate)->angle!=0){
				read_png_file(config->input, image);
				rotate(config, image);
				write_png_file(config->output, image);
			} else flag = 0;
		}
		if ((config->rhombus)->n == 1){
			if ((config->rhombus)->coordinates!=0 && (config->rhombus)->size!=-1 && (config->rhombus)->fill_color!=NULL){
				read_png_file(config->input, image);
				rhombus(config, image);
				write_png_file(config->output, image);
			} else flag = 0;
		}
	}
	if (!flag)
		raise_error(config, "there are not enough flags to set parameters\n", 42);
	free_memory(config);
}

int RGB_or_RGBA(Png *image){
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
    		return 3;
        }
        if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGBA){
        	return 4;
        }
}

void rgbfilter(Png *image, char component_name, int component_value) {
    int x,y,color;
    color = RGB_or_RGBA(image);
    for (y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * color]);
            switch(component_name){
            	case 'r':
            	    ptr[0] = component_value;
            	    break;
            	case 'g':
            	    ptr[1] = component_value;
            	    break;
            	case 'b':
            	    ptr[2] = component_value;
            	    break;
            } 
        }
    }
}

void set_pixel(Png* image, int y, int x, int num_color, Color* color){
	if (y < 0 || y >= image->height || x < 0 || x >= image->width)
		return;
	png_byte *row = image->row_pointers[y];
	png_byte *ptr = &(row[x * num_color]);
	ptr[0] = color->r;
	ptr[1] = color->g;
	ptr[2] = color->b;
}

void draw_line(Png* image, int left, int up, int right, int down, int thickness, Color* color, int num_color) {
    int deltaX = abs(right - left);
    int deltaY = abs(down - up);
    int signX = left < right ? 1 : -1;
    int signY = up < down ? 1 : -1;
    int error = deltaX - deltaY;
    
    while(1) 
   {
   	int rectX = left - thickness / 2;
        int rectY = up - thickness / 2;
        for (int y = rectY; y < rectY + thickness; y++) {
         	for (int x = rectX; x < rectX + thickness; x++) {
                    set_pixel(image, y, x, num_color, color);
                }
        }
        if (left == right && up == down) break;
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            left += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            up += signY;
        }
    }
}

void squared_lines(Configs* config, Png* image){
	int num_color = RGB_or_RGBA(image);
	int left = (config->squared_lines)->left;
	int up = (config->squared_lines)->up;
	int size = (config->squared_lines)->size;
	int thickness = (config->squared_lines)->thickness;
	if (thickness % 2==0) thickness--;
	
	if ((config->squared_lines)->fill_color != NULL){
		for (int y = up; y < up + size - 1; y++){
			for (int x = left; x < left+size-1; x++){
				set_pixel(image, y, x, num_color, (config->squared_lines)->fill_color);
			}
		}
	}
	
	draw_line(image, left, up, left+size-1, up, thickness, (config->squared_lines)->thickness_color, num_color);
	draw_line(image, left, up+size-1, left+size-1, up+size-1, thickness, (config->squared_lines)->thickness_color, num_color);
	draw_line(image, left, up, left, up+size-1, thickness, (config->squared_lines)->thickness_color, num_color);
	draw_line(image, left+size-1, up, left+size-1, up+size-1, thickness, (config->squared_lines)->thickness_color, num_color);
	draw_line(image, left, up, left+size-1, up+size-1, thickness, (config->squared_lines)->thickness_color, num_color);
	draw_line(image, left+size-1, up, left, up+size-1, thickness, (config->squared_lines)->thickness_color, num_color);
}

void rotate(Configs* config, Png* image){
	int num_color = RGB_or_RGBA(image);
	int left = (config->rotate)->left;
	int up = (config->rotate)->up;
	int right = (config->rotate)->right;
	int down = (config->rotate)->down;
	
	if (left < 0 || left > image->width || up < 0 || up > image->height || right < 0 || right > image->width || down < 0 || down > image->height){
		raise_error(config, "Rotation area is not on image.\n", 43);
	}
	
	int height_copy = down - up;
	int width_copy = right - left;
	//копирование области
	png_bytep *row_pointers_copy =  (png_bytep *) malloc(sizeof(png_bytep) * height_copy);
	for (int y = 0; y < height_copy; y++)
        	row_pointers_copy[y] = (png_byte *) malloc(sizeof(png_byte) * num_color * width_copy);
        
        for (int y = up; y < down; y++){
        	png_byte *row_copy = image->row_pointers[y];
        	for (int x = left; x < right; x++){
        		png_byte *ptr = &(row_copy[x * num_color]);
        		for (int i = 0; i < 3; i++){
        			row_pointers_copy[y - up][(x - left)*num_color + i] = ptr[i];
        		}
        	}
        }
        //поворот скопированной области
        int height_rotate, width_rotate;
        int count = 4 - (config->rotate)->angle / 90;
	for (int i = 1; i<=count; i++){
        	height_rotate = width_copy;
        	width_rotate = height_copy;
        	
        	png_bytep *row_pointers_rotate =  (png_bytep *) malloc(height_rotate * sizeof(png_bytep));
		for (int y = 0; y < height_rotate; y++)
        		row_pointers_rotate[y] = (png_byte *) malloc(num_color * width_rotate* sizeof(png_byte));
        		
        	for (int y = 0; y < height_copy; y++){
        		png_byte *row_copy = row_pointers_copy[y];
        		for (int x = 0; x < width_copy; x++){
        			png_byte *ptr = &(row_copy[x * num_color]);
        			for (int i = 0; i < 3; i++){
        				row_pointers_rotate[x][(width_rotate - 1 - y)*num_color + i] = ptr[i];
        			}
        		}
        	}
        	free(row_pointers_copy);
        	row_pointers_copy = row_pointers_rotate;
        	width_copy = width_rotate;
        	height_copy = height_rotate;
        
        }
        //вставка на исходное изображение
        int rotate_left = (left+right)/2 - width_rotate/2;
        int rotate_up = (up+down)/2 - height_rotate/2;
	Color color;
    	for (int y = rotate_up; y < rotate_up+height_rotate; y++){
    		for (int x = rotate_left; x < rotate_left + width_rotate; x++){
    			color.r = row_pointers_copy[y-rotate_up][(x-rotate_left)*num_color];
    			color.g = row_pointers_copy[y-rotate_up][(x-rotate_left)*num_color + 1];
    			color.b = row_pointers_copy[y-rotate_up][(x-rotate_left)*num_color + 2];
    			set_pixel(image, y, x, num_color, &color);
    		}
    	}
	free(row_pointers_copy);
}
void rhombus(Configs* config, Png* image){
	int num_color = RGB_or_RGBA(image);
	int left = (config->rhombus)->left;
	int up = (config->rhombus)->up;
	int size = (config->rhombus)->size;
	int half_height = (int)(size/sqrt(2));
	int width = 0;
	int x, y, y1;
	printf("%d\n", half_height);
	for (y = up; y < up + half_height; y++){
		for ( x = left - width; x <= left + width; x++){
			set_pixel(image, y, x, num_color, (config->rhombus)->fill_color);
		}
		width++;
	}
	for (y1 = y; y1 <= y + half_height; y1++){
		for ( x = left - width; x <= left + width; x++){
			set_pixel(image, y1, x, num_color, (config->rhombus)->fill_color);
		}
		width--;
	}
	printf("%d - %d\n", y, width);
}
