#include "functions.h"
#include "input.h"

void no_argschecker(char* arg, char* name){
    if(arg != NULL) {
        if(!strstr(arg,"--")){
            printf("%s doesn't have any arguments\n", name);
            exit(40);
        }
    }
}

void print_png_info(struct Png *image) {
    printf("image Width: %d\n", image->width);
    printf("image Height: %d\n", image->height);
    printf("image Bit Depth: %d\n", image->bit_depth);
    printf("image Number of passes: %d\n", image->number_of_passes);
    printf("image Channels: %d\n", image->channels);
    if (image->color_type == PNG_COLOR_TYPE_RGB) {
        printf("image Color Type: RGB\n");
    } else {
        printf("image Color Type: RGB_A\n");
    }
}

void fill_rect(struct Png *image, int x1, int y1, int x2, int y2, int* rgb) {
    if (x1 > x2 || y1 > y2 || x2 > (image->width - 1) || y2 > (image->height - 1)) return;
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) return;

    png_byte channels = image->channels;

    for (int y = y1; y <= y2; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = x1; x <= x2; x++) {
            png_byte *ptr = &(row[x * channels]);
            ptr[0] = rgb[0];
            ptr[1] = rgb[1];
            ptr[2] = rgb[2];
            if(channels == 4) ptr[3] = 255;
        }
    }
}

void create_border(struct Png *image, int x1, int y1, int x2, int y2, int* rgb, int thickness) {
    if (x1 > x2 || y1 > y2 || x2 > (image->width - 1) || y2 > (image->height - 1)) return;
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) return;
    if (thickness < 0) return;

    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;

    if ((thickness >= (width / 2)) || (thickness >= (height / 2))) {
        fill_rect(image, x1, y1, x2, y2, rgb);
        return;
    }

    fill_rect(image, x1, y1, x2, y1 + thickness - 1, rgb);
    fill_rect(image, x1, y2 - thickness + 1, x2, y2, rgb);
    fill_rect(image, x1, y1, x1 + thickness - 1, y2, rgb);
    fill_rect(image, x2 - thickness + 1, y1, x2, y2, rgb);
}

//проверяет формат x.y или rrr.ggg.bbb
int* check_str_format(char* str, int tok_num, struct Png *image) {
    char** char_res = malloc(sizeof(char*) * tok_num);
    int* res = malloc(sizeof(int) * tok_num);

    for (int j = 0; j < tok_num; j++) {
        char_res[j] = malloc(sizeof(char) * strlen(str) + 10);
    }

    char sep[1] = ".";
    char* istr;
    istr = strtok(str,sep);

    int i=0;
    while (istr != NULL)
   {
        strcpy(char_res[i], istr);
        if((tok_num == 3) && (strcmp(char_res[i], "0") != 0) && (!(atoi(char_res[i])))) {
            printf("The entered color name must be `rrr.ggg.bbb` format.");
            exit(40);
        }

        if((tok_num == 2) && (strcmp(char_res[i], "0") != 0) && (!(atoi(char_res[i])))) {
            printf("The entered coordinates must be `x.y` format.");
            exit(40);
        }

        istr = strtok (NULL,sep);
        i++;
        if(i == tok_num) break;
   }

    if ((i < tok_num) && (tok_num == 3)) {
        printf("The entered color name must be `rrr.ggg.bbb` format.");
        exit(40);
    }

    if ((i < tok_num) && (tok_num == 2)) {
        printf("The entered coordinates must be `x.y` format.");
        exit(40);
    }

    for (int j=0; j<i; j++) {
        if ((tok_num == 3) && (atoi(char_res[j]) < 0 || atoi(char_res[j]) > 255)) {
            printf("Error in check_str_format: incorrect color value.\n");
            exit(40);
        }

        if((tok_num == 2) && (atoi(char_res[j]) < 0 || atoi(char_res[0]) > image->width || atoi(char_res[1]) > image->height)) {
            printf("Error in check_str_format: incorrect coordinates value.\n");
            exit(40);
        }

        res[j] = atoi(char_res[j]);
    }

    for (int k=0; k < tok_num; k++) {
        free(char_res[k]);
    }
    free(char_res);

    return res;
}

void replace_color(struct Png *image, char* new_color, char* old_color) {
    int* new_rgb = malloc(sizeof(int) * 3);
    new_rgb = check_str_format(new_color, 3, image);
    int* old_rgb = malloc(sizeof(int) * 3);
    old_rgb = check_str_format(old_color, 3, image);

    int f = 0;
    for (int x = 0; x < image->width; x++) {
        for (int y = 0; y < image->height; y++) {
            png_byte *ptr = &(image->row_pointers[y][x * image->channels]);
            for (int i = 0; i < image->channels; i++) {
                if (ptr[i] == old_rgb[i]) f++;
                else break;
            }
            if (f >= 3) {
                for (int j = 0; j < image->channels; j++) {
                    ptr[j] = new_rgb[j];
                }
            }
            f = 0;
        }
    }
}

void copy_img(struct Png *image, char* left_up, char* right_down, char* dest_left_up) {
    int* lu_coords = malloc(sizeof(int) * 2);
    lu_coords = check_str_format(left_up, 2, image);
    int* rd_coords = malloc(sizeof(int) * 2);
    rd_coords = check_str_format(right_down, 2, image);
    int* dlu_coords = malloc(sizeof(int) * 2);
    dlu_coords = check_str_format(dest_left_up, 2, image);

    int x1 = lu_coords[0];
    int y1 = lu_coords[1];
    int x2 = rd_coords[0];
    int y2 = rd_coords[1];
    int x3 = dlu_coords[0];
    int y3 = dlu_coords[1];

    if (x1 > x2 || y1 > y2) {
        printf("The entered coordinates do not form a rectangle.\n");
        exit(40);
    }

    int rect_width = x2 - x1 + 1;
    int rect_height = y2 - y1 + 1;
    png_byte channels = image->channels;

    png_bytep* rect = malloc(sizeof(png_byte*) * rect_height + 10);
    for (int i=0; i < rect_height; i++) {
        rect[i] = malloc(sizeof(png_byte) * rect_width * channels + 10);
        for (int j = 0; j < rect_width * channels; j++) {
            rect[i][j] = image->row_pointers[i + y1][j + x1 * channels];
        }
    }

    int rect_w_fin;
    if (rect_width > image->width - x3) rect_w_fin = image->width - x3;
    else rect_w_fin = rect_width;
    int rect_h_fin;
    if (rect_height > image->height - y3) rect_h_fin = image->height - y3;
    else rect_h_fin = rect_height;

    for (int x = 0; x < rect_w_fin * channels; x++) {
        for (int y = 0; y < rect_h_fin; y++) {
            image->row_pointers[y + y3][x + x3 * channels] = rect[y][x]; 
        }
    }
}

void create_rect_ornam(struct Png *image, char* color, char* thickness_str, char* count_str) {
    int* rgb = malloc(sizeof(int) * 3);
    rgb = check_str_format(color, 3, image);

    int thickness = atoi(thickness_str);
    if (thickness <= 0) {
        printf("--thickness argument must be > 0.\n");
        exit(40);
    }
    int count = atoi(count_str);
    if (count <= 0) {
        printf("--count argument must be > 0.\n");
        exit(40);
    }

    int width = image->width;
    int height = image->height;

    if ((thickness >= (width / 2)) || (thickness >= (height / 2))) {
        fill_rect(image, 0, 0, width - 1, height - 1, rgb);
        return;
    }
    while (((count * 2 - 1) * thickness > (width / 2)) || ((count * 2 - 1) * thickness > (height / 2))) {
        count--;
    }

    int x1 = 0;
    int y1 = 0;
    int x2 = width - 1;
    int y2 = height - 1;
    while (count != 0) {
        create_border(image, x1, y1, x2, y2, rgb, thickness);
        x1 = x1 + thickness * 2;
        y1 = y1 + thickness * 2;
        x2 = x2 - thickness * 2;
        y2 = y2 - thickness * 2;
        count--;
    }
}

void create_circle_ornam(struct Png *image, char* color) {
    int* rgb = malloc(sizeof(int) * 3);
    rgb = check_str_format(color, 3, image);

    int rad; 
    int x0 = (int)(image->width / 2) + 1;
    int y0 = (int)(image->height / 2) + 1;
    if (image->width < image->height) {
        rad = (int)(image->width / 2);
    } else {
        rad = (int)(image->height / 2);
    }

    for (int y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            if ((pow(x - x0, 2) + pow(y - y0, 2)) > pow(rad, 2)) {
                png_byte *ptr = &(row[x * image->channels]); 
                ptr[0] = rgb[0];
                ptr[1] = rgb[1];
                ptr[2] = rgb[2];
                if (image->channels == 4) ptr[3] = 255;
            }
        }
    }
}

void create_semicircle (struct Png *image, int x0, int y0, int r1, int thickness, int* rgb) {
    if (thickness <= 0 || x0 < 0 || y0 < 0 || x0 >= image->width || y0 >= image->height) return;

    int x_min, x_max, y_min, y_max;
    int r2 = r1 + thickness;

    if (x0 - r2 + 1 >= 0) x_min = x0 - r2 + 1;
    else x_min = 0;
    if (x0 + r2 - 1 < image->width) x_max = x0 + r2 - 1;
    else x_max = image->width - 1;
    if (y0 - r2 + 1 >= 0) y_min = y0 - r2 + 1;
    else y_min = 0;
    if (y0 + r2 - 1 < image->height) y_max = y0 + r2 - 1;
    else y_max = image->height - 1;

    for (int y = y_min; y <= y_max; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = x_min; x <= x_max; x++) {
            if (((pow(x - x0, 2) + pow(y - y0, 2)) > pow(r1 + 2, 2)) && ((pow(x - x0, 2) + pow(y - y0, 2)) <= pow(r2 + 2, 2))) {
                png_byte *ptr = &(row[x * image->channels]); 
                ptr[0] = rgb[0];
                ptr[1] = rgb[1];
                ptr[2] = rgb[2];
                if (image->channels == 4) ptr[3] = 255;
            }
        }
    }
}

void create_semicir_ornam(struct Png *image, char* color, char* thickness_str, char* count_str) {
    int* rgb = malloc(sizeof(int) * 3);
    rgb = check_str_format(color, 3, image);

    int thickness = atoi(thickness_str);
    if (thickness <= 0) {
        printf("--thickness argument must be > 0.\n");
        exit(40);
    }
    int count = atoi(count_str);
    if (count <= 0) {
        printf("--count argument must be > 0.\n");
        exit(40);
    }
    if ((image->width < (count+1) * thickness) || (image->height < (count+1) * thickness)) {
        printf("Some arguments are incorrect.\n");
        exit(40);
    }
    thickness++;

    int d_x, r_x, d_y, r_y;
    if ((image->width - (count+1) * thickness) % count != 0) {
        d_x = (int)((image->width - (count+1) * thickness) / count) + 1;
    } else d_x = (int)((image->width - (count+1) * thickness) / count);
    r_x = (int)(d_x / 2);
    if(d_x % 2 == 1) r_x++;

    if ((image->height - (count+1) * thickness) % count != 0) {
        d_y = (int)((image->height - (count+1) * thickness) / count) + 1;
    } else d_y = (int)((image->height - (count+1) * thickness) / count);
    r_y = (int)(d_y / 2);
    if(d_y % 2 == 1) r_y++;

    int x_center = (int)(image->width / 2);
    int y_center = 0;
    if(count % 2 == 1) {
        //сверху
        create_semicircle(image, x_center, y_center, r_x, thickness, rgb);
        for (int i = 1; i <= (count-1) / 2; i++) {
            create_semicircle(image, x_center + i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
            create_semicircle(image, x_center - i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
        }

        //снизу
        y_center = image->height - 1;
        create_semicircle(image, x_center, y_center, r_x, thickness, rgb);
        for (int i = 1; i <= (count-1) / 2; i++) {
            create_semicircle(image, x_center + i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
            create_semicircle(image, x_center - i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
        }

        //слева
        y_center = (int)(image->height / 2);
        x_center = 0;
        create_semicircle(image, x_center, y_center, r_y, thickness, rgb);
        for (int i = 1; i <= (count-1) / 2; i++) {
            create_semicircle(image, x_center, y_center + i * (2 * r_y + thickness), r_y, thickness, rgb);
            create_semicircle(image, x_center, y_center - i * (2 * r_y + thickness), r_y, thickness, rgb);
        }

        //справа
        x_center = image->width - 1;
        create_semicircle(image, x_center, y_center, r_y, thickness, rgb);
        for (int i = 1; i <= (count-1) / 2; i++) {
            create_semicircle(image, x_center, y_center + i * (2 * r_y + thickness), r_y, thickness, rgb);
            create_semicircle(image, x_center, y_center - i * (2 * r_y + thickness), r_y, thickness, rgb);
        }
    }
    if (count % 2 == 0) {
        //сверху
        int del_x = (int)(r_x + thickness / 2);
        if (thickness % 2 != 0) del_x++;
        for (int i = 0; i <= count / 2; i++) {
            create_semicircle(image, x_center + del_x + i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
            create_semicircle(image, x_center - del_x - i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
        }

        //снизу
        y_center = image->height - 1;
        for (int i = 0; i <= count / 2; i++) {
            create_semicircle(image, x_center + del_x + i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
            create_semicircle(image, x_center - del_x - i * (2 * r_x + thickness), y_center, r_x, thickness, rgb);
        }

        //слева
        int del_y = (int)(r_y + thickness / 2);
        if (thickness % 2 != 0) del_y++;
        y_center = (int)(image->height / 2);
        x_center = 0;
        for (int i = 0; i <= count / 2; i++) {
            create_semicircle(image, x_center, y_center + del_y + i * (2 * r_y + thickness), r_y, thickness, rgb);
            create_semicircle(image, x_center, y_center - del_y - i * (2 * r_y + thickness), r_y, thickness, rgb);
        }

        //справа
        x_center = image->width - 1;
        for (int i = 0; i <= count / 2; i++) {
            create_semicircle(image, x_center, y_center + del_y + i * (2 * r_y + thickness), r_y, thickness, rgb);
            create_semicircle(image, x_center, y_center - del_y - i * (2 * r_y + thickness), r_y, thickness, rgb);
        }
    }
}

int compare_colors(png_byte* ptr, int* color) {
    if ((ptr[0] == color[0]) && (ptr[1] == color[1]) && (ptr[2] == color[2])) return 1;
    return 0;
}

int** free_border_data(struct Png *image, int* color) {
    int** free_border_data_array = (int**) malloc(sizeof(int*) * image->height + 10);
    for (int y = 0; y < image->height; y++) {
        free_border_data_array[y] = (int*) malloc(sizeof(int) * image->width + 10);
    }

    png_bytep* row_pointers = image->row_pointers;
    int channels = image->channels;

	for (int y = 0; y < image->height; y++)
	{
        png_byte *row = row_pointers[y];
		for (int x = 0; x < image->width; x++)
		{
            png_byte *ptr = &(row[x * channels]);
			if (compare_colors(ptr, color) == 1)
			{
				if ((y + 1 == image->height || y - 1 < 0) && (x + 1 == image->width || x - 1 < 0))
					free_border_data_array[y][x] = 5;
				else if (y + 1 == image->height || y - 1 < 0 || x + 1 == image->width || x - 1 < 0)
					free_border_data_array[y][x] = 3;
				if (y + 1 < image->height && compare_colors(&(row_pointers[y + 1][x * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && compare_colors(&(row_pointers[y - 1][x * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (x + 1 < image->width && compare_colors(&(row[(x + 1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (x - 1 >= 0 && compare_colors(&(row[(x - 1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (y + 1 < image->height && x + 1 < image->width && compare_colors(&(row_pointers[y + 1][(x+1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (y + 1 < image->height && x - 1 >= 0 && compare_colors(&(row_pointers[y + 1][(x-1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && x + 1 < image->width && compare_colors(&(row_pointers[y - 1][(x+1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && x - 1 >= 0 && compare_colors(&(row_pointers[y - 1][(x-1) * channels]), color) == 0)
					free_border_data_array[y][x] += 1;
			}
		}
	}
	return free_border_data_array;
}

void trace_rects(struct Png *image, char* color_ch, char* border_color_ch, char* thickness_str) {
    int* color = malloc(sizeof(int) * 3);
    color = check_str_format(color_ch, 3, image);
    int* border_color = malloc(sizeof(int) * 3);
    border_color = check_str_format(border_color_ch, 3, image);

    int thickness = atoi(thickness_str);
    if (thickness <= 0) {
        printf("--thickness argument must be > 0.\n");
        exit(40);
    }

    int** free_border_data_array = free_border_data(image, color);

    struct Coordinates** coords = malloc(sizeof(struct Coordinates*) * image->width * image->height);
    int coords_count = 0;
    png_bytep* row_pointers = image->row_pointers;
    int channels = image->channels;

    for (int y = 0; y < image->height; y++) {
        png_byte *row = row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * channels]);
            if (compare_colors(ptr, color) == 0) continue;
            struct Coordinates *c = malloc(sizeof(struct Coordinates));
            if (free_border_data_array[y][x] == 8) {
                c->x0 = x;
                c->x1 = x;
                c->y0 = y;
                c->y1 = y;
                coords[coords_count++] = c;
                continue;
            }
            if (free_border_data_array[y][x] == 7) {
				int flag = 0;
				for (int x1 = x + 1; x1 < image->width; x1++) {
					if (free_border_data_array[y][x1] != 6) {
						if (free_border_data_array[y][x1] != 7) break;
						c->x1 = x1;
						c->y0 = y;
						c->y1 = y;
						c->x0 = x;
						flag = 1;
					}
				}
				if (!flag)
					for (int y1 = y + 1; y1 < image->height; y1++) {
						if (free_border_data_array[y1][x] != 6) {
							if (free_border_data_array[y1][x] != 7) break;
							c->x1 = x;
							c->y0 = y;
							c->y1 = y1;
							c->x0 = x;
							flag = 1;
						}
					}
				if (flag == 1) coords[coords_count++] = c;
				else {
					free(c);
					continue;
				}
			}
            else if (free_border_data_array[y][x] == 5) {
				int flag = 1;
				for (int x1 = x + 1; x1 < image->width; x1++) {
					if (free_border_data_array[y][x1] != 3) {
						if (free_border_data_array[y][x1] == 5) {
							c->x1 = x1;
							c->x0 = x;
						}
						else flag = 0;
						break;
					}
				}
				for (int y1 = y + 1; y1 < image->height; y1++) {
					if (free_border_data_array[y1][x] != 3) {
						if (free_border_data_array[y1][x] == 5) {
							c->y1 = y1;
							c->y0 = y;
						}
						else flag = 0;
						break;
					}
				}
				if (c->y0 + 1 > c->y1 || c->x0 + 1 > c->x1) flag = 0;
				if (!flag) continue;
				for (int x1 = c->x0 + 1; x1 <= c->x1; x1++) {
					if (free_border_data_array[c->y1][x1] != 3) {
						if (free_border_data_array[c->y1][x1] != 5) flag = 0;
					}
				}
				for (int y1 = c->y0 + 1; y1 <= c->y1; y1++) {
					if (free_border_data_array[y1][c->x1] != 3) {
						if (free_border_data_array[y1][c->x1] != 5) flag = 0;
					}
				}
				if (!flag) continue;
				for (int y1 = c->y0 + 1; y1 < c->y1; y1++) {
					for (int x1 = c->x0 + 1; x1 < c->x1; x1++)
						if (free_border_data_array[y1][x1] != 0) {
							flag = 0;
							break;
						}
					if (!flag)
						break;
				}
				if (flag) coords[coords_count++] = c;
				else free(c);
				continue;
			}
        }
    }

    for (int i = 0; i < coords_count; i++) {
        struct Coordinates *c = coords[i];
        create_border(image, c->x0, c->y0, c->x1, c->y1, border_color, thickness);
        free(c);
    }
    free(coords);
    free(free_border_data_array);
}

void print_help(){
    printf("\nВспомогательные функции:\n\n\
            -h, -help - справка, которую вы видите сейчас\n\n\
            -info - подробная информация об изображении\n\n\
            -i, -input - задаёт имя входного изображения\n\n\
            -o, -output - задаёт имя выходного изображения\n\n");
    printf("Функции по обработке изображений:\n\n\
            --copy - копирование заданной области (координаты задаются в формате `x.y`)\n\
                --left_up - координаты левого верхнего угла области-источника\n\
                --right_down - координаты правого нижнего угла области-источника\n\
                --dest_left_up - координаты левого верхнего угла области-назначения\n\
            --color_replace - заменяет все пиксели одного заданного цвета на другой цвет\n\
                --old_color - цвет, который требуется заменить (задаётся строкой `rrr.ggg.bbb`)\n\
                --new_color - цвет, на который требуется заменить (задаётся строкой `rrr.ggg.bbb`)\n\
            --ornament - сделать рамку в виде узора\n\
                --pattern - узор (возможные значения: rectangle, circle, semicircles)\n\
                --color - цвет (задаётся строкой `rrr.ggg.bbb`)\n\
                --thickness - ширина\n\
                --count - количество\n\
            --filled_rects - поиск всех залитых прямоугольников заданного цвета\n\
                --color - цвет искомых прямоугольников (задаётся строкой `rrr.ggg.bbb`)\n\
                --border_color - цвет линии для обводки\n\
                --thickness - толщина линии для обводки\n");
}

void fill_circled(struct Png *image, int x1, int y1, int x2, int y2, int* rgb, int* exc_rgb) {
    if (x1 > x2 || y1 > y2 || x2 > (image->width - 1) || y2 > (image->height - 1)) return;
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) return;

    png_byte channels = image->channels;

    for (int y = y1; y <= y2; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = x1; x <= x2; x++) {
            png_byte *ptr = &(row[x * channels]);
            if (!compare_colors(ptr, exc_rgb)) {
                ptr[0] = rgb[0];
                ptr[1] = rgb[1];
                ptr[2] = rgb[2];
                if(channels == 4) ptr[3] = 255;
            }
        }
    }
}

void circle_pix(struct Png *image, char* circle_color_str, char* color_str, char* size_str) {
    int* circle_color = check_str_format(circle_color_str, 3, image);
    int* color = check_str_format(color_str, 3, image);
    int size = atoi(size_str);
    if (size < 1) {
        printf("The size is incorrect.\n");
        exit(40);
    }
    int x1, x2, y1, y2;

    for (int y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * image->channels]);
            if ((ptr[0] == color[0]) && (ptr[1] == color[1]) && (ptr[2] == color[2])) { 
                if (x - size < 0) x1 = 0;
                else x1 = x - size;
                if (x + size > image->width - 1) x2 = image->width - 1;
                else x2 = x + size;
                if (y - size < 0) y1 = 0;
                else y1 = y - size;
                if (y + size > image->height - 1) y2 = image->height - 1;
                else y2 = y + size;

                fill_circled(image, x1, y1, x2, y2, circle_color, color);
            }
        }
    }
}