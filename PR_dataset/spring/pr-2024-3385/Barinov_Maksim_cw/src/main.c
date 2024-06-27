#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <png.h>
#include <ctype.h>
#include <math.h>

typedef struct {
	unsigned int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_byte channels;

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_pointers;
} Png;

typedef struct {
	int leftup[2];
	int rightdown[2];
	char type[50];
	int side_size;
	int thickness;
	int color[3];
	int fill;
	int fillcolor[3];
	double alpha;
	int beta;
	int size;
} args;

void read_png_file(char* filename, Png *image) {
	int x, y;
	char header[8];
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		printf("Error in read_png_file function: cannot read file: [%s]\n", filename);
		exit(40);
	}
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8)) {
		printf("Error in read_png_file function: probably [%s] is not png\n", filename);
		exit(40);
	}
	image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!image->png_ptr) {
		printf("Error in read_png_file function: error in png structure\n");
		exit(40);
	}
	image->info_ptr = png_create_info_struct(image->png_ptr);
	if (!image->info_ptr) {
		printf("Error in read_png_file function: error in png info-structure\n");
		exit(40);
	}
	if (setjmp(png_jmpbuf(image->png_ptr))) {
		printf("Ошибка инициализации.\n");
		exit(40);
	}

	png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->channels = png_get_channels(image->png_ptr, image->info_ptr);
	png_read_update_info(image->png_ptr, image->info_ptr);

	image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; y++) {
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);

	if (image->color_type != PNG_COLOR_TYPE_RGB) {
        fclose(fp);
        fprintf(stderr, "The program supports working only with the PNG_COLOR_TYPE_RGB\n");
        exit(40);
    }
	png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
    fclose(fp);
}


void print_png_info(Png *img) {
    printf("Image Width: %d\n", img->width);
    printf("Image Height: %d\n", img->height);
    printf("Image Bit Depth: %d\n", img->bit_depth);
    printf("Image Channels: %d\n", img->channels);
    if (img->color_type == PNG_COLOR_TYPE_RGB) {
        printf("Image Colour Type: RGB\n");
    } else {
        printf("Image Colour Type: RGB_A\n");
    }
}


void write_png_file(char *filename, Png *image) {
	int x,y;
	FILE *fp = fopen(filename, "wb");
	if (!fp) {
        printf("Error in write_png_file function: file could not be opened.\n");
        exit(40);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr) {
        printf("Error in write_png_file function: png_create_write_struct failed.\n");
        exit(40);
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) {
        printf("Error in write_png_file function: png_create_info_struct failed.\n");
        exit(40);
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error in write_png_file function: error during init_io.\n");
        exit(40);
    }
    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        printf("Error in write_png_file function: error during writing header.\n");
        exit(40);
    }
	png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image->png_ptr, image->info_ptr);
    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        printf("Error in write_png_file function: error during writing bytes.\n");
        exit(40);
    }
    png_write_image(image->png_ptr, image->row_pointers);

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        fclose(fp);
        printf("Error in write_png_file function: error during writing end of file.\n");
        exit(40);
    }
    png_write_end(image->png_ptr, NULL);

	for (y = 0; y < image->height; y++)
		free(image->row_pointers[y]);
    free(image->row_pointers);
    fclose(fp);

}

void print_help() {
	printf("Course work for option 4.16, created by Maksim Barinov.\n");
	printf("--square\n");
	printf("\tThe square is defined by:\n");
	printf("\tCoordinates of the upper-left corner. The flag is `--left_up', the value is set in the format `left.up`, where left is the x coordinate, up is the y coordinate\n");
	printf("\tThe size of the side.\n ");
	printf("\tThe `--side_size` flag. Accepts a number greater than 0 as input\n");
	printf("\tThe thickness of the lines. The `--thickness` flag. Accepts a number greater than 0 as input\n");
	printf("\tThe color of the lines. The `--color` flag (the color is set by the string `rrr.ggg.bbb`, where rrr/ggg/bbb are the numbers specifying the color component. example `--color 255.0.0` sets the red color)\n");
	printf("\tCan be filled in or not. The `--file` flag. It works as a binary value: there is no flag – false, there is a flag – true.\n");
	printf("\tThe color with which it is filled in, if the user has selected the filled one. The `--fill_color` flag (works similarly to the `--color` flag)\n");

	printf("--exchange\n");
	printf("\tThe rectangular area selected by the user is divided into 4 parts and these parts are swapped. The functionality is defined by:\n");
	printf("\tCoordinates of the upper-left corner of the area. The flag is `--left_up', the value is set in the format `left.up`, where left is the x coordinate, up is the y coordinate\n");
	printf("\tCoordinates of the lower-right corner of the area. The flag is `--right_down', the value is set in the format `right.down`, where right is the x coordinate, down is the y coordinate\n");
	printf("\tThe method of exchanging parts: 'in a circle', diagonally. Flag `--exchange_type', possible values: `clockwise`, `counterclockwise`, `diagonals`\n");

	printf("--freq_color\n");
	printf("\tFinds the most frequently encountered color and replaces it with another specified color.\n");
	printf("\tThe functionality is defined by:\n");
	printf("\the color in which to repaint the most common color.\n \tThe `--color` flag (the color is set by the string `rrr.ggg.bbb`, where rrr/ggg/bbb are the numbers specifying the color component. example `--color 255.0.0` sets the color red)\n");
}

int is_pixel_in_img(Png *img, int x, int y) {
    if (y >= 0 && y < img->height && x >= 0 && x < img->width) {
        return 1;
    }
    return 0;
}

void put_pixel(Png *img, int x, int y, int *color_arr) {
    if (!is_pixel_in_img(img, x, y)){
        return;
    }
    img->row_pointers[y][x * img->channels + 0] = color_arr[0];
    img->row_pointers[y][x * img->channels + 1] = color_arr[1];
    img->row_pointers[y][x * img->channels + 2] = color_arr[2];
}

void fill_circle(Png *img, int xc, int yc, int r, int *color_arr) {
    int min_x = xc - r, min_y = yc - r, max_x = xc + r, max_y = yc + r;
    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            if ((x - xc)*(x-xc) + (y - yc) *(y-yc) <= (r * r)) {
                put_pixel(img, x, y, color_arr);
            }
        }
    }
}

void draw_in_oct(Png *img, int xc, int yc, int x, int y, int *color_arr) {
    put_pixel(img,xc+x, yc+y, color_arr);
    put_pixel(img, xc-x, yc+y, color_arr);
    put_pixel(img, xc+x, yc-y, color_arr);
    put_pixel(img, xc-x, yc-y, color_arr);
    put_pixel(img, xc+y, yc+x, color_arr);
    put_pixel(img, xc-y, yc+x, color_arr);
    put_pixel(img, xc+y, yc-x, color_arr);
    put_pixel(img, xc-y, yc-x, color_arr);
}
void draw_filled_circle(Png *img, int xc, int yc, int r, int *color_arr) {  
    int x = 0, y = r, d = 3 - 2 * r;
    draw_in_oct(img, xc, yc, x, y, color_arr);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        draw_in_oct(img, xc, yc, x, y, color_arr);
    }
    fill_circle(img, xc, yc, r, color_arr);
}


void draw_line(Png *img, int x1, int y1, int x2, int y2, int *color_arr) {
    int dX = abs(x2 - x1), dY = abs(y2 - y1), signX = x1 < x2 ? 1 : -1, signY = y1 < y2 ? 1 : -1;
    int error = dX - dY;
    put_pixel(img, x2, y2, color_arr);
    while (x1 != x2 || y1 != y2) {
        put_pixel(img, x1, y1, color_arr);
        int error2 = error * 2;
        if (error2 > -dY) {
            error -= dY;
            x1 += signX;
        }
        if (error2 < dX) {
            error += dX;
            y1 += signY;
        }
    }
}

void draw_thick_odd_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    draw_line(img, x1, y1, x2, y2, color_arr);
    if (thickness == 1) {
        return;
    }
    if (abs(y2 - y1) >= abs(x2 - x1)) {
        for (int i = 1; i <= (thickness - 1) / 2; i++) {
            draw_line(img, x1 + i, y1, x2 + i, y2, color_arr);
            draw_line(img, x1 - i, y1, x2 - i, y2, color_arr);
        }
    } else {
        for (int i = 1; i <= (thickness - 1) / 2; i++) {
            draw_line(img, x1, y1 + i, x2, y2 + i, color_arr);
            draw_line(img, x1, y1 - i, x2, y2 - i, color_arr);
        }
    }
}

void draw_thick_even_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    draw_thick_odd_line(img, x1, y1, x2, y2, thickness - 1, color_arr);
    if (abs(y2 - y1) >= abs(x2 - x1)) {
        draw_line(img, x1 + thickness / 2, y1, x2 + thickness / 2, y2, color_arr);
    } else {
        draw_line(img, x1, y1 + thickness / 2, x2, y2 + thickness / 2, color_arr);
    }
}

void draw_thick_line(Png* img, int x1, int y1, int x2, int y2, int thickness, int* color_arr) {
    if (thickness % 2 == 1) {
        draw_thick_odd_line(img, x1, y1, x2, y2, thickness, color_arr);
    } else {
        draw_thick_even_line(img, x1, y1, x2, y2, thickness, color_arr);
    }
}

void draw_square(Png *image, args *params) {
	int y0 = params->leftup[1];
	int x0 = params->leftup[0];
    if (params->color[0] > 255 || params->color[1] > 255 || params->color[2] > 255) {
        printf("Incorrectly set color ranges.\n");
        exit(40);
    }
	if (params->fill == 1) {
        if (params->fillcolor[0] > 255 || params->fillcolor[1] > 255 || params->fillcolor[2] > 255) {
            printf("Incorrectly set color ranges.\n");
            exit(40);
        }
        for (int y = y0; y < y0 + params->side_size; y++) {
            for (int x = x0; x < x0 + params->side_size; x++) {
				put_pixel(image, x, y, params->fillcolor);    
			}
        }
    }
	int w = params->thickness / 2;
	int x1 = params->leftup[0], y1 = params->leftup[1];
	int x2 = x1 + params->side_size, y2 = y1 + params->side_size;
	int x3 = x2, y3 = y1, x4 = x1, y4 = y2;
	draw_thick_line(image, x1,y1,x3,y3,params->thickness,params->color);
	draw_thick_line(image, x2,y2,x3,y3,params->thickness,params->color);
	draw_thick_line(image, x2,y2,x4,y4,params->thickness,params->color);
	draw_thick_line(image, x1,y1,x4,y4,params->thickness,params->color);

	if (params->thickness > 3) {
		draw_filled_circle(image, x1, y1, params->thickness / 2, params->color);
		draw_filled_circle(image, x2, y2, params->thickness / 2, params->color);
		draw_filled_circle(image, x3, y3, params->thickness / 2, params->color);
		draw_filled_circle(image, x4, y4, params->thickness / 2, params->color);
	}
} 

void freq_color(Png *image, args *params) {
	if (params->color[0] > 255 || params->color[1] > 255 || params->color[2] > 255) {
        printf("Incorrectly set color ranges.\n");
        exit(40);
    }
    int *** colors = calloc(256, sizeof(int**));
    for (int i = 0; i < 256; i++) {
        colors[i] = calloc(256, sizeof(int*));
        for (int j = 0; j < 256; j++) {
            colors[i][j] = calloc(256, sizeof(int));
        }
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            int a[3];
			a[0] = image->row_pointers[y][(x)*image->channels + 0];
			a[1] = image->row_pointers[y][(x)*image->channels + 1];
			a[2] = image->row_pointers[y][(x)*image->channels + 2];
			colors[a[0]][a[1]][a[2]]++;
        }
    }

    int freq = colors[0][0][0];
    int max_colors[] = {0,0,0};
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 256; k++) {
                if (colors[i][j][k] > freq) {
                    max_colors[0] = i;
                    max_colors[1] = j;
                    max_colors[2] = k;
                    freq = colors[i][j][k];
                }
            }
        }
    }

    for (int j = 0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
           	int a[3];
			a[0] = image->row_pointers[j][(i)*image->channels + 0];
			a[1] = image->row_pointers[j][(i)*image->channels + 1];
			a[2] = image->row_pointers[j][(i)*image->channels + 2];

            if (a[0] == max_colors[0] && a[1] == max_colors[1] && a[2] == max_colors[2]) {
                put_pixel(image, i, j, params->color);
            }
        }
    }

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            free(colors[i][j]);
        }
        free(colors[i]);
    }
    free(colors);
}

void change(Png *image, int x1, int y1, int x2, int y2, int h, int w) {
	for (int i = 0; i <  w; i++) {
		for (int j = 0; j <  h; j++) {
			int a[3];
			a[0] = image->row_pointers[y2 + j][(x2+ i)*image->channels + 0];
			a[1] = image->row_pointers[y2 + j][(x2 + i)*image->channels + 1];
			a[2] = image->row_pointers[y2 + j][(x2 + i)*image->channels + 2];

			int b[3];
			b[0] = image->row_pointers[y1 + j][(x1+ i)*image->channels + 0];
			b[1] = image->row_pointers[y1 + j][(x1 + i)*image->channels + 1];
			b[2] = image->row_pointers[y1 + j][(x1 + i)*image->channels + 2];
			put_pixel(image, x1+i, y1+j, a);
			put_pixel(image, x2 +i, y2+j, b);
		}
	}		
}

void swap(Png* img, int x1, int y1, int x2, int y2, char*  type) {
	if (x1 < 0 ||  x1 >= img->width || y1 < 0 || y1 >= img->height
        || x2 < 0 ||  x2 >= img->width || y2 < 0 || y2 >= img->height) {
        printf("Incorrect data has been entered: the coordinates must be within the image and be at least zero\n");
        exit(40);
    }
    if (x1 > x2 || y1 > y2) {
        printf("Incorrect data was entered: the x coordinates of the upper-left corner should be less than the coordinates of the lower-right corner.\n");
        exit(40);
    }
	int w = abs(x2 - x1) / 2;
	int h = abs(y2  - y1) / 2;
	int a2_x1 = x1+w, a2_y1 = y1, a3_x1 = x1, a3_y1 = y1 + h, a4_x1 = x1 + w, a4_y1 = y1 + h;
	if (!strcmp("clockwise", type)) {
		change(img, a2_x1, a2_y1, a4_x1, a4_y1, h,w); 
		change(img, x1, y1, a2_x1, a2_y1, h, w);
		change(img, x1,y1, a3_x1, a3_y1, h, w);
	} else if (!strcmp("counterclockwise", type)) {
		change(img, x1, y1, a3_x1, a3_y1, h, w);
		change(img, x1, y1, a2_x1, a2_y1, h, w);
		change(img, a2_x1, a2_y1, a4_x1, a4_y1, h, w);
	} else if (!strcmp("diagonals", type)) {
		change(img, x1, y1, a4_x1, a4_y1, h, w);
		change(img, a2_x1, a2_y1, a3_x1, a3_y1, h, w);
	}
}


int min(int a, int b) {
	if (a < b) return a;
	return b;
}
void contrast(Png* image, args *params) {
	for (int i = 0; i < image->width; i++) {
		for (int j = 0; j < image->height; j++) {
			int a[3];
			a[0] = min(255,(int)image->row_pointers[j][(i)*image->channels + 0] * params->alpha + params->beta);
			a[1] = min(255, (int)image->row_pointers[j][(i)*image->channels + 1] * params->alpha + params->beta);
			a[2] = min(255,(int)image->row_pointers[j][(i)*image->channels + 2] * params->alpha + params->beta);
			//printf("%d %d %d\n", a[0], a[1], a[2]);
			put_pixel(image, i, j, a);
		}
	}
}

void num(Png *image, int x, int y, int s, int* res) {
	int cnt = 0;
	int w = (s- 1)/ 2;
	for (int i = x - w; i <= x + w; i++) {
		for (int j = y - w; j <= y + w; j++) {
			if (is_pixel_in_img(image, i, j)) {
				res[0] += image->row_pointers[j][(i)*image->channels + 0]; 
				res[1] += image->row_pointers[j][(i)*image->channels + 1]; 
				res[2] += image->row_pointers[j][(i)*image->channels + 2];
				cnt++;
			}	
		}
	}
	res[0] = res[0] / cnt;
	res [1] /= cnt;
	res[2] /= cnt;
}

void blur(Png* image, int s) {
	if (s % 2 == 0) s +=1;
	for (int i = 0; i < image->width; i++) {
		for (int j = 0; j < image->height; j++) {
			int res[3] = {0,0,0};
			num(image, i, j, s, res);
			//printf("%d %d %d\n", res[0], res[1], res[2]);
			put_pixel(image, i, j, res);
		}
	}
}

int main(int argc, char* argv[]) {
	struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"info", no_argument, NULL, 'f'},
		{"square", no_argument, NULL, 's'},
		{"fill", no_argument, NULL, 'F'},
		{"freq_color", no_argument, NULL, 'q'},
		{"exchange", no_argument, NULL, 'e'},
		{"input", required_argument, NULL, 'i'},
		{"output", required_argument, NULL, 'o'},
		{"left_up", required_argument, NULL, 'l'},
		{"side_size", required_argument, NULL, 'S'},
		{"thickness", required_argument, NULL, 't'},
		{"color", required_argument, NULL, 'c'},
		{"fill_color", required_argument, NULL, 'C'},
		{"right_down", required_argument, NULL, 'r'},
		{"exchange_type", required_argument, NULL, 'x'},
		{"contrast", no_argument, NULL, 'n'},
		{"alpha", required_argument, NULL, 'a'},
		{"beta", required_argument, NULL, 'b'},
		{"Test", no_argument, NULL, 'T'},
		{"blur", no_argument, NULL, 'u'},
		{"size", required_argument, NULL, 'z'},
		{0,0,0,0}
	};

	args params;
	params.leftup[0] = -1;
	params.leftup[1] = -1;
	params.rightdown[0] = -1;
	params.rightdown[1] = -1;
	params.side_size = -1;
	params.thickness = -1;
	params.color[0] = -1;
	params.color[1] = -1;
	params.color[2] = -1;
	params.fill = 0;
	params.fillcolor[0] = -1;
	params.fillcolor[1] = -1;
	params.fillcolor[2] = -1;
	params.alpha = -1;
	params.beta = -1;
	params.size = -1;

	int opt;
	char* optstring = "hfsFqe:i:o:l:S:t:c:C:r:x:na:b:Tuz:";
	int long_opt_index = 0;
	char input_file[255];
	char output_file[255];
	strcpy(output_file, "out.png");
	int f = 0, info_file_fl = 0;
	char key;
	opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);
	int x,y,cnt,cnt1,cur,r,g,b, s,t, x1,y1,x2,y2,r1,g1,b1,cur1;
	while (opt != -1) {
		switch (opt){
			case 'h':
				print_help();
				return 0;
			case 'o':
				strcpy(output_file, optarg);
				break;
			case 'i':
				strcpy(input_file, optarg);
				f = 1;
				break;
			case 'f':
				info_file_fl = 1;
				break;
			case 's':
					key = 's';
				break;
			case 'l':
				x = 0, y = 0;
				cnt = sscanf(optarg, "%d.%d", &x, &y);
				if (cnt != 2) {
					printf("Error: incorrect input left.up\n");
					exit(40);
				}
				params.leftup[0] = x;
				params.leftup[1] = y;
				break;
			case 'S':
				sscanf(optarg, "%d", &s);	
				if (s <= 0) {
					printf("Error: the value of side_size is less than 0\n");
					exit(40);
				}
				params.side_size = s;
				break;
			case 't':
				t = 0;
				sscanf(optarg, "%d", &t);
				if (t <= 0) {
					printf("Erorr: The line thickness must be greater than 0");
					exit(40);
				}
				params.thickness = t;
				break;
			case 'c':
				cur = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
				if (cur != 3 || r < 0 || g < 0 || b < 0) {
					printf("Erorr: incorrect input color");
					exit(40);
				}
				params.color[0] = r;
				params.color[1] = g;
				params.color[2] = b;
				break;
			case 'F':
				params.fill = 1;
				break;
			case 'C':
				cur1 = sscanf(optarg, "%d.%d.%d", &r1, &g1, &b1);
				if (cur1 != 3 || r1 < 0 || g1 < 0 || b1 < 0) {
					printf("Erorr: incorrect input color");
					exit(40);
				}
				params.fillcolor[0] = r1;
				params.fillcolor[1] = g1;
				params.fillcolor[2] = b1;
				break;
			case 'q':
				key = 'q';
				break;
			case 'r':
				x2 = 0, y2 = 0;
				cnt1 = sscanf(optarg, "%d.%d", &x2, &y2);
				if (cnt1 != 2) {
					printf("Error: incorrect input left.up\n");
					exit(40);
				}
				params.rightdown[0] = x2;
				params.rightdown[1] = y2;
				break;
			case 'e':
				key = 'e';
				break;
			case 'x':
				strcpy(params.type, optarg);
				break;
			case 'T':
				key = 'T';
				break;
			case 'n':
				key = 'n';
				break;
			case 'a':
				sscanf(optarg, "%lf", &params.alpha);	
				break;
			case 'b':
				sscanf(optarg, "%d", &params.beta);
				break;
			case 'u':
				key = 'u';
				break;
			case 'z':
				sscanf(optarg, "%d", &params.size);
				break;

		}
		opt = getopt_long(argc, argv, optstring, long_options, &long_opt_index);
	}
	if (!f)strcpy(input_file, argv[argc - 1]);
	Png *image = malloc(sizeof(Png));
	read_png_file(input_file, image);
	if (info_file_fl) print_png_info(image);

	switch(key) {
		case 's':
			if (params.leftup[0] == -1 || params.leftup[1] == -1 || params.side_size == -1 || params.thickness == -1 || params.color[0] == -1 || params.color[1] == -1 || params.color[2] == -1) {
				printf("Not enough arguments have been entered to draw a square.\n");
				exit(40);
			}
			draw_square(image, &params);
			break;
		case 'q':
			if (params.color[0] == -1 || params.color[1] == -1 || params.color[2] == -1) {
				printf("Не хватает аргументов для фукнции freq_color\n");
				exit(40);
			}
			freq_color(image, &params);
			break;
		case 'e':
			if (params.leftup[0] < 0 || params.leftup[1] <0 || params.rightdown[0] < 0 || params.rightdown[1] < 0) {
				printf("Not enough arguments have been entered to exchange.\n");
				exit(40);
			}
			swap(image, params.leftup[0], params.leftup[1], params.rightdown[0], params.rightdown[1], params.type);
			break;
		case 'n':
			if (params.alpha == -1 || params.beta == -1) {
				printf("Not enough arguments have been entered to contrast");
				exit(40);
			}
			contrast(image, &params);
			break;
		case 'u':
			if (params.size < 0) {
				exit(40);
			}
			blur(image, params.size);
			break;
		default:
            fprintf(stderr, "Arguments entered incorrectly.\n");
            exit(40);
	}
	write_png_file(output_file, image);
}
