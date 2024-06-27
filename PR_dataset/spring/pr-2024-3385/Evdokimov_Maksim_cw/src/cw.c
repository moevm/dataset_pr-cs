#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <png.h>

typedef struct png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
} png;

typedef struct user_input {
	char mode; //default: ' '

	int color_r;
	int color_g;
	int color_b;

	int left_up_x;
	int left_up_y;
    int is_left_up_presented;

	int right_down_x;
	int right_down_y;
    int is_right_down_presented;




	int below;
	int above;
	int left;
	int right;

	char* in;
	char* out;
} user_input;

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int max(int a, int b) {
    if (a < b) {
        return b;
    }
    return a;
}

float min_f(float a, float b) {
    if (a < b) {
        return a;
    }
    return b;
}

float max_f(float a, float b) {
    if (a < b) {
        return b;
    }
    return a;
}

void printhelp() {
    printf("Supported flags:\n");

    printf("\t--help -h\n");
    printf("\t\tPrints all supported flags and arguments.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments: none\n");

    printf("\t--info -f\n");
    printf("\t\tPrints info about image.\n");
    printf("\t\tRequired flags:\n");
    printf("\t\t\t--input\n");
    printf("\t\tRequired arguments: none\n");

    printf("\t--input -i\n");
    printf("\t\tSets the name of input image file.\n");
    printf("\t\tNote: you can also set the input file by writing its name after all flags.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tFile name, string\n");

    printf("\t--output -o\n");
    printf("\t\tSets the name of output image file.\n");
    printf("\t\tNote: out.png by default.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tFile name, string\n");

    printf("\t--resize -s\n");
    printf("\t\tExpand image by adding pixels of selected color.\n");
    printf("\t\tRequired flags:\n");
    printf("\t\t\t--color\n");
    printf("\t\t\tAt least one from: --above --below --right --left\n");
    printf("\t\tRequired arguments: none\n");

    printf("\t--inverse -v\n");
    printf("\t\tInverse selected region of image.\n");
    printf("\t\tRequired flags:\n");
    printf("\t\t\t--left_up\n");
    printf("\t\t\t--right_down\n");
    printf("\t\tRequired arguments: none\n");

    printf("\t--gray -g\n");
    printf("\t\tTurn selected region of image into grayscale.\n");
    printf("\t\tRequired flags:\n");
    printf("\t\t\t--left_up\n");
    printf("\t\t\t--right_down\n");
    printf("\t\tRequired arguments: none\n");

    printf("\t--left_up -u\n");
    printf("\t\tUpper left bound of selection.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPosition, integer.integer\n");

    printf("\t--right_down -d\n");
    printf("\t\tBottom right bound of selection.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPosition, integer.integer\n");

    printf("\t--right -r\n");
    printf("\t\tNumber of pixels on the right.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPixels, integer\n");

    printf("\t--left -l\n");
    printf("\t\tNumber of pixels on the left.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPixels, integer\n");

    printf("\t--below -b\n");
    printf("\t\tNumber of pixels below.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPixels, integer\n");

    printf("\t--above -a\n");
    printf("\t\tNumber of pixels above.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tPixels, integer\n");

    printf("\t--color -c\n");
    printf("\t\tColor of added pixels.\n");
    printf("\t\tRequired flags: none\n");
    printf("\t\tRequired arguments:\n");
    printf("\t\t\tRGB color, integer.integer.integer\n");

}
void printInfo(png* image, user_input* in) {
    printf("Info:\n");
    printf("\tFile name: %s\n", in->in);
    printf("\tFile size: %dx%d\n", image->width, image->height);
    switch(image->color_type) {
        case PNG_COLOR_TYPE_GRAY:
            printf("\tFile color type: gray. Warn. This color type is unsupported.\n");
        break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            printf("\tFile color type: gray with alpha channel. Warn. This color type is unsupported.\n");
        break;
        case PNG_COLOR_TYPE_RGB:
            printf("\tFile color type: rgb\n");
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            printf("\tFile color type: rgb with alpha channel\n");
        break;
        default:
            printf("\tFile color type: unknown\n");
        break;
    }
    printf("\tFile bit depth: %d\n", image->bit_depth);
}

int check_for_invalid_args(char** argv, int argc) {
    char* dict[] = {"--help", "-h", "--info", "-f", "--gray", "--resize", "--inverse", "-g", "-s", "-v"};
    int dict_c = 10;
    for (int i = 0; i < argc - 2; i++) {
        for (int j = 0; j < dict_c; j++) {
            if (!strcasecmp(argv[i], dict[j]) && argv[i+1][0] != '-') {
                printf("Warning. Arg %s for flag %s will be ignored.\n", argv[i+1], argv[i]);
            }
        }
    }
    return 0;
}

user_input* init_user_input() {
	user_input* to_init = malloc(sizeof(user_input));

	to_init->mode = ' ';

	to_init->color_r = -1;
	to_init->color_g = -1;
	to_init->color_b = -1;


	to_init->left_up_x = 0;
	to_init->left_up_y = 0;
    to_init->is_left_up_presented = 0;

	to_init->right_down_x = 0;
	to_init->right_down_y = 0;
	to_init->is_right_down_presented = 0;

	to_init->below = 0;
	to_init->above = 0;
	to_init->left  = 0;
	to_init->right = 0;

	return to_init;
}

int parseflags(user_input* input, int argc, char **argv) {

    check_for_invalid_args(argv, argc);

    if (argc == 1) {
        printf("Fatal. No file provided.\n");
        return 1;
	}

    input->in = argv[argc - 1];
	input->out = "out.png";

	const char* short_options = "vu:d:gsl:r:a:b:c:hfi:o:t";

	const struct option long_options[] = {
		{ "inverse", no_argument, NULL, 'v'},
		{ "left_up", required_argument, NULL, 'u' },
		{ "right_down", required_argument, NULL, 'd'},
        { "gray", no_argument, NULL, 'g'},
        { "resize", no_argument, NULL, 's'},
		{ "left", required_argument, NULL, 'l'},
		{ "right", required_argument, NULL, 'r'},
		{ "above", required_argument, NULL, 'a'},
		{ "below", required_argument, NULL, 'b'},
		{ "color", required_argument, NULL, 'c'},
		{ "help", no_argument, NULL, 'h'},
		{ "info", no_argument, NULL, 'f'},
		{ "input", required_argument, NULL, 'i'},
        { "output", required_argument, NULL, 'o'},
        { "hsv", no_argument, NULL, 't'},
		{ NULL, 0, NULL, 0}
	};
	int res = getopt_long(argc, argv, short_options, long_options, NULL);
	int x, y, z, tmp;
	while (res !=-1) {
		switch (res)
		{
		case 'i':
            if (optarg == NULL) {
				printf("Fatal. Flag %c expects a required argument.\n", res);
				return 1;
			}
			input->in = malloc(sizeof(char) * strlen(optarg));
			strcpy(input->in, optarg);
            break;
        case 'o':
            if (optarg == NULL) {
				printf("Fatal. Flag %c expects a required argument.\n", res);
				return 1;
			}
			input->out = malloc(sizeof(char) * strlen(optarg));
			strcpy(input->out, optarg);
            break;
        case 'f':
            if (optarg != NULL) {
				printf("Fatal. Flag %c takes no arguments.\n", res);
				return 1;
			}
			input->mode = 'f';
            break;
		case 'h':
            if (optarg != NULL) {
				printf("Fatal. Flag %c takes no arguments.\n", res);
				return 1;
			}
            input->mode = 'h';
            break;
		case 'v':
		case 'g':
		case 's':
		case 't':
            if (optarg != NULL) {
				printf("Fatal. Flag %c takes no arguments.\n", res);
				return 1;
			}

			if (input->mode == ' ') {
				input->mode = (char) res;
			}
			else {
				printf("Warning. Multiple modes selected, all of them will be ignored, except for first.\n");
			}
			break;

		case 'u':
		case 'd':

			if (optarg == NULL) {
				printf("Fatal. Flag %c expects a required argument.\n", res);
				return 1;
			}
			tmp = sscanf(optarg, "%d.%d", &x, &y);
			if (tmp != 2) {
				printf("Fatal. Flag %c expects a point (Ex: 50.50), got %s.\n", res, optarg);
				return 1;
			}
			if (res == 'u') {
				input->left_up_x = x;
				input->left_up_y = y;
				input->is_left_up_presented = 1;
			}
			else {
				input->right_down_x = x;
				input->right_down_y = y;
				input->is_right_down_presented = 1;
			}

			break;

		case 'c':
			if (optarg == NULL) {
				printf("Fatal. Flag %c expects a required argument.\n", res);
				return 1;
			}
			tmp = sscanf(optarg, "%d.%d.%d", &x, &y, &z);
			if (tmp != 3 || x < 0 || y < 0 || z < 0 || x > 255 || y > 255 || z > 255) {
				printf("Fatal. Flag %c expects a point: number.number.number where number is in [0;255], got %s.\n", res, optarg);
				return 1;
			}
			input->color_r = x;
			input->color_g = y;
			input->color_b = z;
		break;


		case 'l':
		case 'r':
		case 'a':
		case 'b':
			if (optarg == NULL) {
				printf("Fatal. Flag %c expects a required argument.\n", res);
				return 1;
			}
			tmp = sscanf(optarg, "%d", &x);
			if (tmp != 1) {
				printf("Fatal. Flag %c expects a number, got %s.\n", res, optarg);
				return 1;
			}
			if (res == 'l') {
				input->left = x;
			}
			if (res == 'r') {
				input->right = x;
			}
			if (res == 'a') {
				input->above = x;
			}
			if (res == 'b') {
				input->below = x;
			}

		break;

		default:
			printf("Fatal. Unsupported option given: %c.\n", res);
			return 1;
			break;
		}

		res = getopt_long(argc, argv, short_options, long_options, NULL);
	}

	return 0;
}

int validate_input(user_input* input) {

	switch (input->mode)
	{
	case 'h':
	case 'f':
	case 't':
        return 0;
        break;
	case 's':
		if((input->above == 0 && input->below == 0 &&
		input->right == 0 && input->left == 0) || input->color_g == -1) {
			printf("Fatal. Not enough arguments for option %c. see -h. \n", input->mode);
			return 1;
		}
		break;

	case 'v':
	case 'g':
		if(input->is_left_up_presented == 0 || input->is_right_down_presented == 0) {
			printf("Fatal. Not enough arguments for option %c. see -h. \n", input->mode);
			return 1;
		}
		break;

	default:
		printf("Fatal. No mode presented for program to work with. see -h. \n");
		return 1;
		break;
	}
	return 0;
}

int read_png(char* file_name, png* image) {
	char header[8];
	FILE* fp = fopen(file_name, "rb");
	if (!fp) {
		printf("Fatal. No such file found: %s \n", file_name);
		return 1;
	}
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8)) {
		printf("Fatal. Provided file is not png format: %s (header: %s)\n", file_name, header);
		return 1;
	}
	image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        printf("Fatal. Error in png structure\n");
        return 1;
    }
    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Fatal. Error in png info-structure\n");
        return 1;
    }
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Fatal. Error. Something went wrong!\n");
        return 1;
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr,image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);

    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep)* image->height);
    for (int y = 0; y < image->height; y++){
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);

    // ---

    // ---
    png_destroy_read_struct(&image->png_ptr, &image->info_ptr, NULL);
    fclose(fp);
    return 0;
}

int write_png_file(char *file_name, png *image) {

     int x,y;
     FILE *fp = fopen(file_name, "wb");
     if (!fp){
        printf("Fatal. No such file found: %s \n", file_name);
        return 1;
     }
     image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
     if (!image->png_ptr){
        printf("Fatal. Error in png info-structure\n");
        return 1;
     }
     image->info_ptr = png_create_info_struct(image->png_ptr);
     if (!image->info_ptr){
        printf("Fatal. Error in png info-structure\n");
        return 1;
     }
     if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Fatal. Error. Something went wrong!\n");
        return 1;
     }
     png_init_io(image->png_ptr, fp);
     if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Fatal. Error in png sig\n");
        return 1;
     }
     png_set_IHDR(image->png_ptr, image->info_ptr, image->width,  image->height, image->bit_depth, image->color_type,
                  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
     png_write_info(image->png_ptr, image->info_ptr);
     if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Fatal. Error. Something went wrong!\n");
        return 1;
     }
     png_write_image(image->png_ptr, image->row_pointers);
     if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Fatal. Error. Something went wrong!\n");
        return 1;
     }
     png_write_end(image->png_ptr, NULL);
     for (y = 0; y < image->height; y++)
         free(image->row_pointers[y]);
      free(image->row_pointers);
      fclose(fp);
}

void normalize_input(user_input* in, png* image) {
    if (in->left_up_x < 0) {
        in->left_up_x = 0;
    }
    if (in->left_up_y < 0) {
        in->left_up_y = 0;
    }
    if (in->right_down_x < 0) {
        in->right_down_x = 0;
    }
    if (in->right_down_y < 0) {
        in->right_down_y = 0;
    }
    if (in->left_up_x >= image->width) {
        in->left_up_x = image->width;
    }
    if (in->left_up_y >= image->height) {
        in->left_up_y = image->height;
    }
    if (in->right_down_x >= image->width) {
        in->right_down_x = image->width;
    }
    if (in->right_down_y >= image->height) {
        in->right_down_y = image->height;
    }

}

int inverse(png* image, user_input* input) {
    normalize_input(input, image);
    int components;
    switch (image->color_type) {
        case PNG_COLOR_TYPE_RGB:
            components = 3;
        break;

        case PNG_COLOR_TYPE_RGBA:
            components = 4;
        break;

        default:
            printf("Fatal. Unsupported color type for provided PNG!\n");
            printf("Supported: RGB or RGBA\n");
            return 1;
        break;
    }

    if (input->right_down_x > image->width || input->right_down_y > image->height) {
        printf("Fatal. Wrong bounds! Note: top left pixel has coords (0, 0)\n");
        return 1;
    }

    int x, y;
    for (y = input->left_up_y; y < input->right_down_y; y++) {
        png_byte* p = image->row_pointers[y];
        for (x = input->left_up_x; x < input->right_down_x; x++) {
            png_byte* byte = &(p[x*components]);
            byte[0] = 255 - byte[0];
            byte[1] = 255 - byte[1];
            byte[2] = 255 - byte[2];
        }
    }
    return 0;
}

int gray(png* image, user_input* input) {
    normalize_input(input, image);
    int components;
    switch (image->color_type) {
        case PNG_COLOR_TYPE_RGB:
            components = 3;
        break;

        case PNG_COLOR_TYPE_RGBA:
            components = 4;
        break;

        default:
            printf("Fatal. Unsupported color type for provided PNG!\n");
            printf("Supported: RGB or RGBA\n");
            return 1;
        break;
    }
    int x, y;
    for (y = input->left_up_y; y < input->right_down_y; y++) {
        png_byte* p = image->row_pointers[y];
        for (x = input->left_up_x; x < input->right_down_x; x++) {
            png_byte* byte = &(p[x*components]);
            int b = round(0.299 * byte[0] + 0.587 * byte[1] + 0.114 * byte[2]);
            byte[0] = b;
            byte[1] = b;
            byte[2] = b;
        }
    }
    return 0;
}

int resize(png* image, user_input* input) {



    int components;
    switch (image->color_type) {
        case PNG_COLOR_TYPE_RGB:
            components = 3;
        break;

        case PNG_COLOR_TYPE_RGBA:
            components = 4;
        break;

        default:
            printf("Fatal. Unsupported color type for provided PNG!\n");
            printf("Supported: RGB or RGBA\n");
            return 1;
        break;
    }

    int new_height = image->height + input->above + input->below;
    int new_width = image->width + input->left + input->right;
    png_bytep* new_pointers = malloc(sizeof(png_bytep) * new_height);

    for (int y = 0; y < new_height; y++){
        new_pointers[y] = (png_byte*)malloc(sizeof(png_bytep) * components * new_width);
        for (int x = 0; x < new_width; x++) {
            png_byte* byte = &(new_pointers[y][x*components]);
            byte[0] = input->color_r;
            byte[1] = input->color_g;
            byte[2] = input->color_b;
            if (components == 4) {
                byte[3] = 255;
            }
        }
    }
    for (int y = max(input->above, 0); y < min(image->height + input->above, new_height); y++) {
        for (int x = max(input->left, 0); x < min(image->width + input->left, new_width); x++) {
            png_byte* byte = &(new_pointers[y][x*components]);
            int old_x = x - input->left;
            int old_y = y - input->above;

            png_byte* source = &(image->row_pointers[old_y][old_x*components]);
            byte[0] = source[0];
            byte[1] = source[1];
            byte[2] = source[2];
            if (components == 4) {
                byte[3] = source[3];
            }
        }
    }


    for (int y = 0; y < image->height; y++)
         free(image->row_pointers[y]);
    free(image->row_pointers);

    image->height = new_height;
    image->width = new_width;
    image->row_pointers = new_pointers;
    return 0;
}

int hsv(png* image, user_input* input) {
    for (int y = 0; y < image->height; y++){
        for (int x = 0; x < image->width; x++) {
            png_byte* byte = &(image->row_pointers[y][x*3]);
            float h, s, v;
            float r, g, b;
            r = ((float)byte[0]) / 255.0;
            g = ((float)byte[1]) / 255.0;
            b = ((float)byte[2]) / 255.0;



            float ma = max_f(r, max_f(g, b));
            float mi = min_f(r, min_f(g, b));
            float delta = ma - mi;

            if (ma == mi) {
                h = 0;
            }
            if (r >= g && r >= b) {
                int tmp = (g-b)/delta;
                float rem = (g-b)/delta - tmp;
                h = 60 * ((tmp % 6) + rem);
            }
            if (g >= b && g >= r) {
                h = 60 * (((b-r)/delta) + 2);
            }
            if (b >= g && b >= r) {
                h = 60 * (((r-g)/delta) + 4);
            }
            if (ma == 0) {
                s = 0;
            }
            else {
                s = delta/ma;
            }
            v = ma;
            byte[2] = ((float)h / 359.0)*255;
            byte[1] = s * 255;
            byte[0] = v * 255;

        }
    }
    return 0;
}

int main (int argc, char **argv) {
    printf("Course work for option 4.17, created by Evdokimov Maksim.\n");

    if (argc == 1) {
        printf("No flags provided.\n");
        printhelp();
        return 0;
    }

	user_input* input = init_user_input();

	if (parseflags(input, argc, argv)) {
        free(input);
		return 40;
	}

	if (validate_input(input)) {
        free(input);
		return 40;
	}

	if(input->mode == 'h') {
        printhelp();
        free(input);
        return 0;
	}

	png* image = (png*) malloc(sizeof(png));
    if (read_png(input->in, image)) {
        free(input);
        return 40;
    }

    if (input->mode == 'f') {
        printInfo(image, input);
        free(input);
        return 0;
    }

    int rez = 40;
    switch (input->mode) {
        case 'v':
            rez = inverse(image, input);
        break;
        case 's':
            rez = resize(image, input);
        break;
        case 'g':
            rez = gray(image, input);
        break;
        case 't':
            rez = hsv(image, input);
    }
    write_png_file(input->out, image);

    free(input);
    return rez;
}

