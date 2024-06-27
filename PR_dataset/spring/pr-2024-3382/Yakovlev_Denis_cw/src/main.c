#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#define PNG_DEBUG 3
#include <png.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* Tegs:
	#TODO - need to do
	#Dev - code that simplifies development
	#Exp - explanation a part of code
*/

// Structures:

typedef struct{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} Png;

struct option long_opt[] = {
	{"help", 0, NULL, 'h'},
	{"input", 1, NULL, 'i'},
    {"output", 1, NULL, 'o'},
    {"info", 0, NULL, 0},
    
    {"triangle", 0, NULL, 't'},
    {"biggest_rect", 0, NULL, 'r'},
	{"collage", 0, NULL, 'c'},
	
    {"points", 1, NULL, 'p'},
    {"thickness", 1, NULL, 1},
    {"color", 1, NULL, 2},
    {"fill", 0, NULL, 'f'},
    {"fill_color", 1, NULL, 3},
    {"old_color", 1, NULL, 4},
    {"new_color", 1, NULL, 5},
    {"number_y", 1, NULL, 'y'},
    {"number_x", 1, NULL, 'x'},
    
    {"circle_pixel", 0, NULL, '6'},
    {"circle_color", 1, NULL, '7'},
    {"size", 1, NULL, '8'},
    
    // #Dev: {"", , NULL, ''},
    {0, 0, 0, 0}
    /* #Exp 2 field:
    0 - no arg
    1 - required arg
    2 - optional arg
    */
};

// Functions:
void print_help();
void print_info(Png* image);
void write_png_file(char *file_name, Png *image);
void read_png_file(char *file_name, Png *image);
int check_to_make_c(int* num_x, int* num_y);
int check_to_make_r(int* old_col_r, int* old_col_g, int* old_col_b, int* new_col_r, int* new_col_g, int* new_col_b);
int check_to_make_t(int* t_x1, int* t_y1, int* t_x2, int* t_y2, int* t_x3, int* t_y3, int* thickness, int* t_col_r, int* t_col_g, int* t_col_b, int* is_fill, int* fill_col_r, int* fill_col_g, int* fill_col_b);
void do_c(Png *image, int* num_x, int* num_y);
void do_r(Png *image, int* old_col_r, int* old_col_g, int* old_col_b, int* new_col_r, int* new_col_g, int* new_col_b);
void do_t(Png *image, int* t_x1, int* t_y1, int* t_x2, int* t_y2, int* t_x3, int* t_y3, int* thickness, int* t_col_r, int* t_col_g, int* t_col_b, int* is_fill, int* fill_col_r, int* fill_col_g, int* fill_col_b);
void draw_line(Png *image, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b);
void draw_circle(Png *image, int x0, int y0, int rad, int r, int g, int b);
int check_pixel_in_img(Png *image, int x, int y);
void free_image_data(Png *img);
void fill_t(Png *image, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int f_col_r, int f_col_g, int f_col_b);
int check_filled_area(Png *image, int x1, int y1, int x2, int y2, int r, int g, int b);
int check_to_make_cir(int r1, int g1, int b1, int r, int r2, int g2, int b2);
void do_cir(Png* image, int r1, int g1, int b1, int r, int r2, int g2, int b2);
void free_img(Png* image);
void obv(Png* image, int r1, int g1, int b1, int r, int r2, int g2, int b2, int x0, int y0);

int main(int argc, char **argv){
    if (argc < 1){
        fprintf(stderr,"Error\n");
		return 0;
    }
    
    char *output_img = "out.png";
    char *input_img = "0";
	char *opt_str = "hi:o:0trcp:1:2:f3:4:5:y:x:67:8:";
	int opt_val = 0;
	int opt_index = 0;
	
	int make_t = 0, make_r = 0, make_c = 0, make_cir = 0;
	int t_x1 = -1, t_y1 = -1, t_x2 = -1, t_y2 = -1, t_x3 = -1, t_y3 = -1;
	int thickness = -1;
	int t_col_r = -1, t_col_g = -1, t_col_b = -1;
	int is_fill = 0;
	int fill_col_r = -1, fill_col_g = -1, fill_col_b = -1;
	int old_col_r = -1, old_col_g = -1, old_col_b = -1;
	int new_col_r = -1, new_col_g = -1, new_col_b = -1;
	int num_y = -1, num_x = -1;
	int need_info = 0;
	int need_help = 0;
	int size = -1, s_col_r = -1, s_col_g = -1, s_col_b = -1; 
	
	while((opt_val = getopt_long(argc, argv, opt_str, long_opt, &opt_index)) != -1){
		// #Dev: printf("%d %s\n",(char)opt_val, optarg);
		if (opt_val == 0 || opt_val == 'h' || opt_val == 'i' || opt_val == 'o'){
			switch (opt_val){
				case 0:
					need_info = 1;
					break;
				case 'h':
					need_help = 1;
					print_help();
					break;
				case 'i':
					input_img = optarg;
					break;
				case 'o':
					output_img = optarg;
					break;
			}
			continue;
		}
		if (opt_val == 't' || opt_val == 'r' || opt_val == 'c' || opt_val == '6'){
			/*if (make_c == 1){
				make_c = check_to_make_c(&num_x, &num_y);
			}
			if (make_r == 1){
				make_r = check_to_make_r(&old_col_r, &old_col_g, &old_col_b, &new_col_r, &new_col_g, &new_col_b);
			}
			if (make_t == 1){
				make_t = check_to_make_t(&t_x1, &t_y1, &t_x2, &t_y2, &t_x3, &t_y3, &thickness, &t_col_r, &t_col_g, &t_col_b, &is_fill, &fill_col_r, &fill_col_g, &fill_col_b);
			}*/
			switch (opt_val){
				case 't':
					if (make_t == 0){
						make_t = 1;
					} else{
						fprintf(stderr, "triangle already got\n");
					}
					break;
				case 'r':
					if (make_r == 0){
						make_r = 1;
					} else{
						fprintf(stderr, "biggest rect already got\n");
					}
					break;
				case 'c':
					if (make_c == 0){
						make_c = 1;
					} else{
						fprintf(stderr, "collage already got\n");
					}
					break;
				case '6':
					if (make_cir == 0){
						make_cir = 1;
					} else{
						fprintf(stderr, "circle already got\n");
					}
					break;
			}
			continue;
		}
		switch (opt_val){
			case 'p':
				if (t_x1 != -1 && t_y1 != -1 && t_x2 != -1 && t_y2 != -1 && t_x3 != -1 && t_y3 != -1){
					fprintf(stderr, "Cordinates already got: (%d, %d),(%d, %d),(%d, %d)\n", t_x1, t_y1, t_x2, t_y2, t_x3, t_y3);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									t_x1 = cnt;
									break;
								case 1:
									t_y1 = cnt;
									break;
								case 2:
									t_x2 = cnt;
									break;
								case 3:
									t_y2 = cnt;
									break;
								case 4:
									t_x3 = cnt;
									break;
								case 5:
									t_y3 = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong cordinates: %s\n", optarg);
							cnt = -1;
							break;
						}
						if (cord > 5){
							fprintf(stderr, "Too more cordinates\n");
							cnt = -1;
							break;
						}
						i++;
					}
					if (cord < 5){
						fprintf(stderr, "Not enought cordinates\n");
						cnt = -1;
						break;
					}
					if (cnt == -1){
						t_x1 = -1;
						t_y1 = -1;
						t_x2 = -1;
						t_y2 = -1;
						t_x3 = -1;
						t_y3 = -1;
					} else {
						t_y3 = cnt;
					}
				}
				break;
			case 1:
				if (thickness != -1){
					fprintf(stderr, "Thickness already got: %d\n", thickness);
				} else{
					int cnt = 0, i = 0;
					while (optarg[i] != '\000'){
						if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else{
							fprintf(stderr, "Wrong number of thickness: %s\n", optarg);
							cnt = -1;
							break;
						}
						i++;
					}
					thickness = cnt;
				}
				break;
			case 2:
				if (t_col_r != -1){
					fprintf(stderr, "Color already got: %d.%d.%d\n", t_col_r, t_col_g, t_col_b);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									t_col_r = cnt;
									break;
								case 1:
									t_col_g = cnt;
									break;
								case 2:
									t_col_b = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						if (cord > 2){
							fprintf(stderr, "Too more colors\n");
							exit(44);
							cnt = -1;
							break;
						}
						if (cnt > 255){
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						i++;
					}
					if (cnt == -1){
						t_col_r = -1;
						t_col_g = -1;
						t_col_b = -1;
					} else {
						t_col_b = cnt;
					}
				}
				break;
			case 'f':
				is_fill = 1;
				break;
			case 3:
				if (fill_col_r != -1){
					fprintf(stderr, "Color already got: %d.%d.%d\n", fill_col_r, fill_col_g, fill_col_b);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									fill_col_r = cnt;
									break;
								case 1:
									fill_col_g = cnt;
									break;
								case 2:
									fill_col_b = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						if (cord > 2){
							fprintf(stderr, "Too more colors\n");
							exit(44);
							cnt = -1;
							break;
						}
						if (cnt > 255){
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						i++;
					}
					if (cnt == -1 || cnt > 255){
						fill_col_r = -1;
						fill_col_g = -1;
						fill_col_b = -1;
					} else {
						fill_col_b = cnt;
					}
				}
				break;
			case 4:
				if (old_col_r != -1){
					fprintf(stderr, "Color already got: %d.%d.%d\n", old_col_r, old_col_g, old_col_b);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									old_col_r = cnt;
									break;
								case 1:
									old_col_g = cnt;
									break;
								case 2:
									old_col_b = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						if (cord > 2){
							fprintf(stderr, "Too more colors\n");
							exit(44);
							cnt = -1;
							break;
						}
						if (cnt > 255){
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						i++;
					}
					if (cnt == -1){
						old_col_r = -1;
						old_col_g = -1;
						old_col_b = -1;
					} else {
						old_col_b = cnt;
					}
				}
				break;
			case 5:
				if (new_col_r != -1){
					fprintf(stderr, "Color already got: %d.%d.%d\n", new_col_r, new_col_g, new_col_b);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									new_col_r = cnt;
									break;
								case 1:
									new_col_g = cnt;
									break;
								case 2:
									new_col_b = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						if (cord > 2){
							fprintf(stderr, "Too more colors\n");
							exit(44);
							cnt = -1;
							break;
						}
						if (cnt > 255){
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(44);
							cnt = -1;
							break;
						}
						i++;
					}
					if (cnt == -1){
						new_col_r = -1;
						new_col_g = -1;
						new_col_b = -1;
					} else {
						new_col_b = cnt;
					}
				}
				break;
			case 'y':
				if (num_y != -1){
					fprintf(stderr, "Number y already got: %d\n", num_y);
				} else{
					int cnt = 0, i = 0;
					while (optarg[i] != '\000'){
						if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else{
							fprintf(stderr, "Wrong number of number y: %s\n", optarg);
							cnt = -1;
							break;
						}
						i++;
					}
					num_y = cnt;
				}
				break;
			case 'x':
				if (num_x != -1){
					fprintf(stderr, "Number x already got: %d\n", num_x);
				} else{
					int cnt = 0, i = 0;
					while (optarg[i] != '\000'){
						if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else{
							fprintf(stderr, "Wrong number of number x: %s\n", optarg);
							cnt = -1;
							break;
						}
						i++;
					}
					num_x = cnt;
				}
				break;
			case '7':
				if (s_col_r != -1){
					fprintf(stderr, "Color already got: %d.%d.%d\n", s_col_r, s_col_g, s_col_b);
				} else{
					int cnt = 0, i = 0, cord = 0;
					while (optarg[i] != '\000'){
						if (optarg[i] == '.'){
							switch (cord){
								case 0:
									s_col_r = cnt;
									break;
								case 1:
									s_col_g = cnt;
									break;
								case 2:
									s_col_b = cnt;
									break;
							}
							cnt = 0;
							cord++;
						} else if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else {
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(46);
							cnt = -1;
							break;
						}
						if (cord > 2){
							fprintf(stderr, "Too more colors\n");
							exit(46);
							cnt = -1;
							break;
						}
						if (cnt > 255){
							fprintf(stderr, "Wrong color: %s\n", optarg);
							exit(46);
							cnt = -1;
							break;
						}
						i++;
					}
					if (cnt == -1){
						s_col_r = -1;
						s_col_g = -1;
						s_col_b = -1;
					} else {
						s_col_b = cnt;
					}
				}
				break;
			case '8':
				if (size != -1){
					fprintf(stderr, "Size already got: %d\n", size);
				} else{
					int cnt = 0, i = 0;
					while (optarg[i] != '\000'){
						if (isdigit(optarg[i])){
							cnt *= 10;
							cnt += (int)optarg[i] - 48;
						} else{
							fprintf(stderr, "Wrong number of size: %s\n", optarg);
							cnt = -1;
							break;
						}
						i++;
					}
					size = cnt;
				}
				break;
		}
	}
	
	if (make_c == 1){
		make_c = check_to_make_c(&num_x, &num_y);
	}
	if (make_r == 1){
		make_r = check_to_make_r(&old_col_r, &old_col_g, &old_col_b, &new_col_r, &new_col_g, &new_col_b);
	}
	if (make_t == 1){
		make_t = check_to_make_t(&t_x1, &t_y1, &t_x2, &t_y2, &t_x3, &t_y3, &thickness, &t_col_r, &t_col_g, &t_col_b, &is_fill, &fill_col_r, &fill_col_g, &fill_col_b);
	}
	if (make_cir == 1){
		make_cir = check_to_make_cir(t_col_r, t_col_g, t_col_b, size, s_col_r, s_col_g, s_col_b);
	}
	
	if (need_help == 1 && !strcmp(input_img, "0")){
		return 0;
	}
	
	if (!strcmp(input_img, output_img)){
		fprintf(stderr, "name of input file (image) = name of output file (image)\n");
		exit(46);
	}
	
	if (!strcmp(input_img, "0")){
		fprintf(stderr, "haven't name of input file (image)\n");
		exit(43);
	} else if (need_info == 1 || make_t == 2 || make_r == 2 || make_c == 2 || make_cir == 2){
		Png image;

		read_png_file(input_img, &image);
		
		if (need_info == 1){
			print_info(&image);
			free_img(&image);
			return 0;
		}
		
		if (make_r == 2){
			do_r(&image, &old_col_r, &old_col_g, &old_col_b, &new_col_r, &new_col_g, &new_col_b);
		} else if (make_t == 2){
			do_t(&image, &t_x1, &t_y1, &t_x2, &t_y2, &t_x3, &t_y3, &thickness, &t_col_r, &t_col_g, &t_col_b, &is_fill, &fill_col_r, &fill_col_g, &fill_col_b);
		} else if (make_c == 2){
			do_c(&image, &num_x, &num_y);
		} else if (make_cir == 2){
			do_cir(&image, t_col_r, t_col_g, t_col_b, size, s_col_r, s_col_g, s_col_b);
		}
		write_png_file(output_img, &image);
	}
	
    return 0;
}

void read_png_file(char *file_name, Png *image){
    int x,y;
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        fprintf(stderr, "file could not be opened\n");
        exit(40);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        fprintf(stderr, "file is not recognized as a PNG\n");
        exit(40);
    }

    /* initialize stuff */
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        fprintf(stderr, "png_create_read_struct failed\n");
        exit(40);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
    	fprintf(stderr, "png_create_info_struct failed\n");
       	exit(40);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during init_io\n");
        exit(40);
    }
    png_infop end_info = png_create_info_struct(image->png_ptr);

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);
	
	if (image->color_type != PNG_COLOR_TYPE_RGB && image->color_type != PNG_COLOR_TYPE_RGBA){
        fprintf(stderr, "color_type of input file must be PNG_COLOR_TYPE_RGB or PNG_COLOR_TYPE_RGBA\n");
        exit(40);
    }
	
    /* read file */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during read_image\n");
        free_img(image);
        exit(40);
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    if (image->row_pointers == NULL){
    	fprintf(stderr, "error allocation (no memory)\n");
        free(image->row_pointers);
        exit(40);
    }
    for (y = 0; y < image->height; y++){
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
        if (image->row_pointers[y] == NULL){
			fprintf(stderr, "error allocation (no memory)\n");
        	free_img(image);
		    exit(40);
		}
	}
    png_read_image(image->png_ptr, image->row_pointers);
    png_read_end(image->png_ptr, end_info);
	png_destroy_read_struct(&image->png_ptr, &image->info_ptr, &end_info);
    fclose(fp);
}

void write_png_file(char *file_name, Png *image){
    int x,y;
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        fprintf(stderr, "file could not be opened\n");
        free_img(image);
        exit(41);
    }

    /* initialize stuff */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        fprintf(stderr, "png_create_write_struct failed\n");
        free_img(image);
        exit(41);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
       	fprintf(stderr, "png_create_info_struct failed\n");
        free_img(image);
       	exit(41);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during init_io\n");
        free_img(image);
        exit(41);
    }

    png_init_io(image->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during writing header\n");
        free_img(image);
        exit(41);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during writing bytes\n");
        free_img(image);
        exit(41);
    }

    png_write_image(image->png_ptr, image->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        fprintf(stderr, "error during end of write\n");
        free_img(image);
        exit(41);
    }

    png_write_end(image->png_ptr, NULL);

    /* cleanup heap allocation */
    free_img(image);
	png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
    fclose(fp);
}

int check_to_make_c(int* num_x, int* num_y){
	//printf("Collage: x - %d, y - %d\n", *num_x, *num_y);
	if (*num_x > 0 && *num_y > 0){
		//printf("All good (collage)\n");
		return 2;
	} else{
		fprintf(stderr,"Haven't enought args\n");
		exit(45);
		*num_x = -1;
		*num_y = -1;
		return 0;
	}
}

int check_to_make_cir(int r1, int g1, int b1, int r, int r2, int g2, int b2){
	//printf("Rect:\n old color - %d.%d.%d\n new color - %d.%d.%d\n", *old_col_r, *old_col_g, *old_col_b, *new_col_r, *new_col_g, *new_col_b);
	if (r1 <= 255 && r1 >= 0 && g1 <= 255 && g1 >= 0 && b1 <= 255 && b1 >= 0 && r >= 0 && r2 <= 255 && r2 >= 0 && g2 <= 255 && g2 >= 0 && b2 <= 255 && b2 >= 0){
		//printf("All good (biggest_rect)\n");
		return 2;
	} else{
		//printf("Circle_pixel:\n");
		//printf(" color - %d.%d.%d\n", r1, g1, b1);
		//printf(" size - %d\n", r);
		//printf(" circle color - %d.%d.%d\n", r2, g2, b2);
		fprintf(stderr,"Haven't enought args\n");
		exit(45);
		return 0;
	}
}

int check_to_make_r(int* old_col_r, int* old_col_g, int* old_col_b, int* new_col_r, int* new_col_g, int* new_col_b){
	//printf("Rect:\n old color - %d.%d.%d\n new color - %d.%d.%d\n", *old_col_r, *old_col_g, *old_col_b, *new_col_r, *new_col_g, *new_col_b);
	if (*old_col_r <= 255 && *old_col_r >= 0 && *old_col_g <= 255 && *old_col_g >= 0 && *old_col_b <= 255 && *old_col_b >= 0
	 && *new_col_r <= 255 && *new_col_r >= 0 && *new_col_g <= 255 && *new_col_g >= 0 && *new_col_b <= 255 && *new_col_b >= 0){
		//printf("All good (biggest_rect)\n");
		return 2;
	} else{
		fprintf(stderr,"Haven't enought args\n");
		exit(45);
		*old_col_r = -1;
		*old_col_g = -1;
		*old_col_b = -1;
		*new_col_r = -1;
		*new_col_g = -1;
		*new_col_b = -1;
		return 0;
	}
}

int check_to_make_t(int* t_x1, int* t_y1, int* t_x2, int* t_y2, int* t_x3, int* t_y3, int* thickness, int* t_col_r, int* t_col_g, int* t_col_b, int* is_fill, int* fill_col_r, int* fill_col_g, int* fill_col_b){
	//printf("Triangle:\n");
	//printf(" cords - (%d,%d);(%d,%d);(%d,%d)\n", *t_x1, *t_y1, *t_x2, *t_y2, *t_x3, *t_y3);
	//printf(" thickness - %d\n", *thickness);
	//printf(" line color - %d.%d.%d\n", *t_col_r, *t_col_g, *t_col_b);
	//printf(" filling - %d; fill color - %d.%d.%d\n", *is_fill, *fill_col_r, *fill_col_g, *fill_col_b);
	if(*is_fill == 1 && !(*fill_col_r <= 255 && *fill_col_r >= 0 && *fill_col_g <= 255 && *fill_col_g >= 0 && *fill_col_b <= 255 && *fill_col_b >= 0)){
		fprintf(stderr,"Haven't filling color\n");
	}
	if (*t_x1 >= 0 && *t_y1 >= 0 && *t_x2 >= 0 && *t_y2 >= 0 && *t_x3 >= 0 && *t_y3 >= 0 && *thickness > 0 &&
	 *t_col_r <= 255 && *t_col_r >= 0 && *t_col_g <= 255 && *t_col_g >= 0 && *t_col_b <= 255 && *t_col_b >= 0 &&
	 (*is_fill == 0 || (*is_fill == 1 && *fill_col_r <= 255 && *fill_col_r >= 0 && *fill_col_g <= 255 && *fill_col_g >= 0 && *fill_col_b <= 255 && *fill_col_b >= 0))){
	 	//printf("All good (triangle)\n");
		return 2;
	} else{
		fprintf(stderr,"Haven't enought args or some args is wrong\n");
		exit(45);
		*t_x1 = -1;
		*t_y1 = -1;
		*t_x2 = -1;
		*t_y2 = -1;
		*t_x3 = -1;
		*t_y3 = -1;
		*thickness = -1;
		*t_col_r = -1;
		*t_col_g = -1;
		*t_col_b = -1;
		*is_fill = 0;
		*fill_col_r = -1;
		*fill_col_g = -1;
		*fill_col_b = -1;
		return 0;
	}
}

void do_c(Png *image, int *num_x, int *num_y){
	image->width *= *num_x;
	image->height *= *num_y;
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
	image->row_pointers = (png_bytep*)realloc(image->row_pointers, sizeof(png_bytep) * image->height);
	if(image->row_pointers != NULL){ 
		for (int y = 0; y < image->height; y++){
			if(y < (int)(image->height/(*num_y))){
				image->row_pointers[y] = (png_byte*)realloc(image->row_pointers[y], image->width * cnt_px);
			} else{
				image->row_pointers[y] = (png_byte*)malloc(image->width * cnt_px);
			}
			if(image->row_pointers[y] != NULL){ 
				png_byte *row1 = image->row_pointers[y%(int)(image->height/(*num_y))];
				png_byte *row = image->row_pointers[y];
				for (int x = 0; x < image->width; x++){
					png_byte *ptr = &(row[x * cnt_px]);
					png_byte *ptr1 = &(row1[(x%(int)(image->width/(*num_x)))*cnt_px]);
					ptr[0] = ptr1[0];
					ptr[1] = ptr1[1];
					ptr[2] = ptr1[2];
					if (image->color_type == PNG_COLOR_TYPE_RGBA){
						ptr[3] = ptr1[3];
					}
				}
			} else{
		  		fprintf(stderr, "Error memory allocation\n");
		  		free_img(image);
		  		exit(42);
		  	}
	  	}
  	} else{
  		fprintf(stderr, "Error memory allocation\n");
  		free_img(image);
  		exit(42);
  	}
}

void do_r(Png *image, int *old_col_r, int *old_col_g, int *old_col_b, int *new_col_r, int *new_col_g, int *new_col_b){
	int max_area = 0;
    int max_x1, max_y1, max_x2, max_y2, xm, ym, cnt = 0;
    int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
    for (int y = 0; y < image->height; y++){
        for (int x = 0; x < image->width; x++){
            if ((&(image->row_pointers[y][x*cnt_px]))[0] == *old_col_r && (&(image->row_pointers[y][x*cnt_px]))[1] == *old_col_g && (&(image->row_pointers[y][x*cnt_px]))[2] == *old_col_b){
                xm = x;
                ym = y;
                while (ym < image->height && (&(image->row_pointers[ym][x*cnt_px]))[0] == *old_col_r && (&(image->row_pointers[ym][x*cnt_px]))[1] == *old_col_g &&
                	  (&(image->row_pointers[ym][x*cnt_px]))[2] == *old_col_b){
                    ym++;
                }
                while (xm < image->width && (&(image->row_pointers[y][xm*cnt_px]))[0] == *old_col_r && (&(image->row_pointers[y][xm*cnt_px]))[1] == *old_col_g && 
                	  (&(image->row_pointers[y][xm*cnt_px]))[2] == *old_col_b){
                    xm++;
                }
                ym--;
                xm--;
                int area = (xm - x + 1) * (ym - y + 1);
                if (area > max_area){
                    if (check_filled_area(image, x, y, xm, ym, *old_col_r, *old_col_g, *old_col_b)){
                        max_area = area;
                        max_x1 = x;
                        max_y1 = y;
                        max_x2 = xm;
                        max_y2 = ym;
                        cnt = 0;
                    }
                } else if (area == max_area){
                	cnt++;
                }
            }
        }
    }
    if (max_area != 0) {
    	for (int y = max_y1; y <= max_y2; y++){
		    png_byte *row = image->row_pointers[y];
		    for (int x = max_x1; x <= max_x2; x++){
		        png_byte *ptr = &(row[x * cnt_px]);
		    	ptr[0] = *new_col_r;
	        	ptr[1] = *new_col_g;
	        	ptr[2] = *new_col_b;
	        	if (image->color_type == PNG_COLOR_TYPE_RGBA){
	        		ptr[3] = 255;
	        	}
        	}
       	}
       	if (cnt != 0){
       		do_r(image, old_col_r, old_col_g, old_col_b, new_col_r, new_col_g, new_col_b);
       	}
    } else{
        fprintf(stderr, "There are no rectangles of the specified color in the image.\n");
    }
}

void do_t(Png *image, int* t_x1, int* t_y1, int* t_x2, int* t_y2, int* t_x3, int* t_y3, int* thickness, int* t_col_r, int* t_col_g, int* t_col_b, int* is_fill, int* fill_col_r, int* fill_col_g, int* fill_col_b){
	if (*is_fill == 1){
		fill_t(image, *t_x1, *t_y1, *t_x2, *t_y2, *t_x3, *t_y3, *thickness, *fill_col_r, *fill_col_g, *fill_col_b);
	}
	draw_line(image, *t_x1, *t_y1, *t_x2, *t_y2, *thickness, *t_col_r, *t_col_g, *t_col_b);
	draw_line(image, *t_x1, *t_y1, *t_x3, *t_y3, *thickness, *t_col_r, *t_col_g, *t_col_b);
	draw_line(image, *t_x3, *t_y3, *t_x2, *t_y2, *thickness, *t_col_r, *t_col_g, *t_col_b);
}

void draw_line(Png *image, int x1, int y1, int x2, int y2, int thickness, int r, int g, int b){
	int x, y;
	if (x1 == x2 && y1 == y2){
		draw_circle(image, x1, y1, thickness, r, g, b);
	}
	if (abs(x1-x2) >= abs(y1-y2)){
		for (int i = 0; i <= abs(x1 - x2); i++){
		 	if (x1 < x2){
				x = x1 + i;
				y = y1 + round((y2 - y1) * i/(x2 - x1));
			} else{
				x = x2 + i;
				y = y2 + round((y1 - y2) * i/(x1 - x2));
			}
			draw_circle(image, x, y, thickness, r, g, b);
		}
	} else{
		for (int i = 0; i <= abs(y1 - y2); i++){
		 	if (y1 < y2){
				y = y1 + i;
				x = x1 + round((x2 - x1) * i/(y2 - y1));
			} else{
				y = y2 + i;
				x = x2 + round((x1 - x2) * i/(y1 - y2));
			}
			draw_circle(image, x, y, thickness, r, g, b);
		}
	}
}

void draw_circle(Png *image, int x0, int y0, int rad, int r, int g, int b){
	int x, y;
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
    for (y = y0 - rad; y <= y0 + rad; y++){
        png_byte *row = image->row_pointers[y];
        for (x = x0 - rad; x <= x0 + rad; x++){
            png_byte *ptr = &(row[x * cnt_px]);
            if ((((x - x0)*(x - x0)+ (y - y0)*(y - y0)) <= (rad/2)*(rad/2)) && check_pixel_in_img(image, x, y) == 1){
	        	ptr[0] = r;
            	ptr[1] = g;
            	ptr[2] = b;
            	if (image->color_type == PNG_COLOR_TYPE_RGBA){
            		ptr[3] = 255;
	        	}
	        }
        }
  	}
}

int check_pixel_in_img(Png *image, int x, int y){
    if (x >= 0 && x < image->width && y >= 0 && y < image->height){
        return 1;
    }
    return 0;
}

void free_image_data(Png *img){
    for (int y = 0; y < img->height; y++) {
        free(img->row_pointers[y]);
    }
    free(img->row_pointers);
}

void fill_t(Png *image, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, int f_col_r, int f_col_g, int f_col_b){
	int x, y, x_min, x_avg, x_max, y_minx, y_avgx, y_maxx, y_min, y_max;
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
	if (x1 >= x2 && x1 >= x3){
		x_max = x1;
		y_maxx = y1;
		if (x2 >= x3){
			x_avg = x2;
			y_avgx = y2;
			x_min = x3;
			y_minx = y3;
		} else{
			x_avg = x3;
			y_avgx = y3;
			x_min = x2;
			y_minx = y2;
		}	
	} else if (x2 >= x1 && x2 >= x3){
		x_max = x2;
		y_maxx = y2;
		if (x1 >= x3){
			x_avg = x1;
			y_avgx = y1;
			x_min = x3;
			y_minx = y3;
		} else{
			x_avg = x3;
			y_avgx = y3;
			x_min = x1;
			y_minx = y1;
		}	
	} else{
		x_max = x3;
		y_maxx = y3;
		if (x1 >= x2){
			x_avg = x1;
			y_avgx = y1;
			x_min = x2;
			y_minx = y2;
		} else{
			x_avg = x2;
			y_avgx = y2;
			x_min = x1;
			y_minx = y1;
		}	
	}
	if (y1 >= y2 && y1 >= y3){
		y_max = y1;
		if (y2 >= y3){
			y_min = y3;
		} else{
			y_min = y2;
		}
	} else if (y2 >= y1 && y2 >= y3){
		y_max = y2;
		if (y1 >= y3){
			y_min = y3;
		} else{
			y_min = y1;
		}
	} else{
		y_max = y3;
		if (y1 >= y2){
			y_min = y2;
		} else{
			y_min = y1;
		}
	}
	if (x_min != x_max && y_min != y_max){
		for (y = y_min; y < y_max; y++){
			if (y < image->height){
				png_byte *row = image->row_pointers[y];
				for (int i = 0; i < x_max - x_min; i++){
					if (i + x_min < image->width){
						png_byte *ptr = &(row[(x_min + i) * cnt_px]);
						if (x_min == x_avg){
							if (y_minx > y_avgx){
								int temp = y_minx;
								y_minx = y_avgx;
								y_avgx = temp;
							}
							if (y > y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min)) && y < y_avgx + round(i * (y_maxx - y_avgx) / (x_max - x_min))){
								ptr[0] = f_col_r;
								ptr[1] = f_col_g;
								ptr[2] = f_col_b;
								if (image->color_type == PNG_COLOR_TYPE_RGBA){
									ptr[3] = 255;
								}
							}
						} else if (x_avg == x_max){
							if (y_avgx > y_maxx){
								int temp = y_maxx;
								y_maxx = y_avgx;
								y_avgx = temp;
							}
							if (y > y_minx + round(i * (y_avgx - y_minx) / (x_max - x_min)) && y < y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min))){
								ptr[0] = f_col_r;
								ptr[1] = f_col_g;
								ptr[2] = f_col_b;
								if (image->color_type == PNG_COLOR_TYPE_RGBA){
									ptr[3] = 255;
								}
							}
						} else if (y_avgx < y_maxx){
							if ((i <= x_avg - x_min && y > y_minx + round(i * (y_avgx - y_minx) / (x_avg - x_min)) &&
								y < y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min))) || 
								
								(i >  x_avg - x_min && y > y_avgx + round((i - x_avg + x_min) * (y_maxx - y_avgx) / (x_max - x_avg)) &&
								y < y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min)))){
								
								ptr[0] = f_col_r;
								ptr[1] = f_col_g;
								ptr[2] = f_col_b;
								if (image->color_type == PNG_COLOR_TYPE_RGBA){
									ptr[3] = 255;
								}
							}
						} else{
							if ((i <= x_avg - x_min && y < y_minx + round(i * (y_avgx - y_minx) / (x_avg - x_min)) &&
								y > y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min))) || 
								
								(i >  x_avg - x_min && y < y_avgx + round((i - x_avg + x_min) * (y_maxx - y_avgx) / (x_max - x_avg)) &&
								y > y_minx + round(i * (y_maxx - y_minx) / (x_max - x_min)))){
								ptr[0] = f_col_r;
								ptr[1] = f_col_g;
								ptr[2] = f_col_b;
								if (image->color_type == PNG_COLOR_TYPE_RGBA){
									ptr[3] = 255;
								}
							}
						}
					}
				}
			}
	  	}
  	}
}

int check_filled_area(Png *image, int x1, int y1, int x2, int y2, int r, int g, int b){
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
    for (int y = y1; y <= y2; y++){
        for (int x = x1; x <= x2; x++){
            if (!((&(image->row_pointers[y][x*cnt_px]))[0] == r && (&(image->row_pointers[y][x*cnt_px]))[1] == g && (&(image->row_pointers[y][x*cnt_px]))[2] == b)){
                return 0;
            }
        }
    }
    return 1;
}

void print_help(){
	printf("Course work for option 4.19, created by Denis Yakovlev\n\n");
	printf("Triangle (--triangle (-t)):\n");
	printf(" --points (-p):      codrinates through a point (x1.y1.x2.y2.x3.y3)\n");
	printf(" --thickness:        radius of triangle sides\n");
	printf(" --color:            color of triangle sides (r.g.b)\n");
	printf(" --fill (-f):        the need to fill the triangle (true or false)\n");
	printf(" --fill_color:       fillind color (r.g.b), if --fill (-f) is true, else no need\n\n");
	printf("Biggest rectangular (--biggest_rect (-r)):\n");
	printf(" --old_color:        the desired color (r.g.b)\n");
	printf(" --new_color:        the color to be replaced with (r.g.b)\n\n");
	printf("Collage (--collage (-c)):\n");
	printf(" --number_x (-x):    the number of images by x\n");
	printf(" --number_y (-y):    the number of images by y\n\n");
	printf("Other flags:\n");
	printf(" --help (-h):        displays information about the program\n");
	printf(" --input (-i):       name of input file (image)\n");
	printf(" --output (-o):      name of output file (image)\n");
	printf(" --info:             displays information about the file (image)\n");
	//#Dev: printf("\n");
}

void print_info(Png* image){
	printf("Image info:\n");
	printf(" width:               %d\n", image->width);
	printf(" height:              %d\n", image->height);
	printf(" color_type:          %d\n", image->color_type);
	printf(" bit_depth:           %d\n", image->bit_depth);
	printf(" number_of_passes:    %d\n", image->number_of_passes);
}

void free_img(Png* image){
	for (int y = 0; y < image->height; y++){
        free(image->row_pointers[y]);
    }
    free(image->row_pointers);
}

void do_cir(Png* image, int r1, int g1, int b1, int r, int r2, int g2, int b2){
	int x, y;
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
    for (y = 0; y < image->height; y++){
        png_byte *row = image->row_pointers[y];
        for (x = 0; x < image->width; x++){
            png_byte *ptr = &(row[x * cnt_px]);
            if (ptr[0] == r1 && ptr[1] == g1 && ptr[2] == b1){
				obv(image, r1, g1, b1, r, r2, g2, b2, x, y);
	        }
        }
  	}
}

void obv(Png* image, int r1, int g1, int b1, int r, int r2, int g2, int b2, int x0, int y0){
	int x, y;
	int cnt_px;
	if (image->color_type == PNG_COLOR_TYPE_RGB){
		cnt_px = 3;
	} else{
		cnt_px = 4;
	}
    for (y = y0 - r; y <= y0 + r; y++){
        png_byte *row = image->row_pointers[y];
        for (x = x0 - r; x <= x0 + r; x++){
            png_byte *ptr = &(row[x * cnt_px]);
            if (check_pixel_in_img(image, x, y) == 1 && (ptr[0] != r1 || ptr[1] != g1 || ptr[2] != b1)){
	        	ptr[0] = r2;
            	ptr[1] = g2;
            	ptr[2] = b2;
	        }
        }
  	}
}




