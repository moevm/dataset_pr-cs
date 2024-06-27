#include "image.h"
#include <math.h>

void print_help(){
printf("Course work for option 4.10, created by Maksimova Ekaterina\n");
    puts(
        "Изображение должно быть в формате BMP\n"
        "По умолчанию последним аргументом утилите должно передаваться имя входного файла\n"
        "Команды:\n"
        "  -c, --color_replace - Заменяет все пиксели заданного цвета на другой цвет. Флаги: --old_color(цвет задаётся строкой `rrr.ggg.bbb`), --new_color\n"
        "  -r, --ornament - Сделать рамку в виде узора. Flags: --pattern(rectangle и circle,  semicircles), --color, --thickness, --color\n"
        "  -f, --filled_rects - Поиск всех залитых прямоугольников заданного цвета и их обводка. Flags: `--color, --border_color, --thickness\n"
        "  -h, --help - показать справку.\n"
		"  -d, --data	вывести информацию о входном изображении \n"
        "\n");

}

void change_color(Image* image, Rgb old_color, Rgb new_color){
	for(int x = 0; x < image->width; x++){
        for(int y = 0; y < image->height; y++){
        	if (cmp_color(image->pix[x][y], old_color))
            	set_pixel(image,x,y,new_color);
        }
    }
}

void blur_image(Image* image, int size) {
	Rgb **old = malloc(image->height * sizeof(Rgb*));
    for(int y = 0; y < image->height; y++){
        old[y] = malloc(image->width * sizeof(Rgb) );
        for(int x = 0; x < image->width; x++){
        	old[y][x] = image-> pix[x][y];
        	
        }
    }
    
	for(int x = 0; x < image->width; x++) {
        for(int y = 0; y < image->height; y++) {
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int e = 0;
        	for (int shift_x = (size - 1) / -2; shift_x <= (size - 1) / 2; shift_x++) {
        		for (int shift_y = (size - 1) / -2; shift_y <= (size - 1) / 2; shift_y++) {
        			Rgb current = get_color(old, x + shift_x, y + shift_y,
        			                        image->width, image->height, &e);
        			sum_r += current.r;
        			sum_g += current.g;
        			sum_b += current.b;
        		}
        	}
        	Rgb result = {round(sum_b / e), round(sum_g / e), round(sum_r / e)};
        	set_pixel(image, x, y, result);
        }
    }
}

void find_and_border_rectangle(Image* image, int thickness, Rgb color, Rgb border_color){
	int count;
    int** visited = malloc(sizeof(int*) * image->width);
    for (int i = 0; i < image->width; i++) {
        visited[i] = malloc(sizeof(int) * image->height);
        for (int j = 0; j < image->height; j++) {
            visited[i][j] = 0;
        }
    }
    for(int x=0;x<image->width-1;x++)
    {
        for(int y=0;y<image->height-1;y++)
        {
            if(cmp_color(image->pix[x][y], color) && visited[x][y] == 0)
            {
                int x_max=x;
                int y_max=y;
                while(x_max < image->width && cmp_color(image->pix[x_max][y], color)){
               		x_max++;
               		
                }
                while(cmp_color(image->pix[x][y_max], color) && y_max < image->height){
                    y_max++;
                }
                
               	
                if(cmp_color_on_area(image,x,y,x_max,y_max, color) == 1){
						count++;
                        border_rectangle(image, x-thickness, y-thickness, x_max+(thickness-1), y_max+(thickness-1), thickness, border_color);
                        for (int i = x; i < x_max; i++) {
							for (int j = y; j < y_max; j++) {
							    visited[i][j] = 1;
							}
						}
                }
            }
                
              
        }
    }
    if (count ==0)
    	fprintf(stderr, "no rectangles of the color");
    
}

void rectangle_ornament(Image* image, int ornament_count, Rgb color_values, int thickness){
    int x1, y1, x2, y2;
    x1 = 0;
    y1 = 0;
    x2 = image->width-1;
    y2 = image->height-1;
    for (int i = 0; i < ornament_count; i++){
        border_rectangle(image, x1, y1, x2, y2, thickness, color_values);
        x1 += thickness * 2;
        y1 += thickness * 2;
        x2 -= thickness * 2;
        y2 -= thickness * 2;

        /* Check if rectangles can fit */
        if (x1 >= x2 || y1 >= y2){
            printf("Warning: Rectangles that cannot fit will be skipped\n");
            break;
        }
    }
}

void circle_ornament(Image* image, Rgb color_values){
    int centerX = image->width / 2;
    int centerY = image->height / 2;
    int radius = (centerX < centerY) ? centerX : centerY;
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
            if (distance > radius) {
                set_pixel(image,x, y, color_values);
            }
        }
    }
}

void semicircles_ornament(Image* image, int thickness, int ornament_count, Rgb color){
    int radius_w = ceil((double)(image->width - ornament_count * thickness) / (2 * ornament_count));
    int radius_h = ceil((double)(image->height - ornament_count * thickness) / (2 * ornament_count));

    for (int index = 0; index < ornament_count; index++) {
        draw_circle(image, color, radius_w * (2 * index + 1) + thickness * index + thickness / 2, 0, thickness, radius_w);
        draw_circle(image, color, radius_w * (2 * index + 1) + thickness * index+ thickness / 2, image->height, thickness, radius_w);
        draw_circle(image, color, 0, radius_h * (2 * index + 1) + thickness * index+ thickness / 2, thickness, radius_h);
        draw_circle(image, color, image->width, radius_h * (2 * index + 1) + thickness * index+ thickness / 2, thickness, radius_h);
    }
}
