#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>
#include <math.h>
#include <getopt.h>

#define HELP_PATH "help.txt" 
#define STRING_BUFFER 1024

#define PARSING_COLOR_ERROR 41
#define READ_IMAGE_ERROR 42
#define WRITE_IMAGE_ERROR 43
#define INVALID_ARGUMENTS 44
#define UNKNOWN_ARGUMENTS 45
#define INPUT_AND_OUTPUT_PATH_CONFLICT 46



const char* short_opts = "ho:i:";

const struct option long_options[] = 
{
    {"help", 		no_argument, 		NULL, 	'h'},
    {"output", 		required_argument, 	NULL, 	'o'},
    {"input", 		required_argument, 	NULL, 	'i'},
    {"rgbfilter", 	no_argument, 		NULL, 	2001}, 	// codes 2xxx are for RGB_filter function flags
    {"component_name", 	required_argument, 	NULL, 	2002},
    {"component_value", required_argument, 	NULL, 	2003},
    {"circle", 		no_argument, 		NULL, 	3001}, 	// codes 3xxx are for draw_circle function flags
    {"center", 		required_argument, 	NULL, 	3002},
    {"radius", 		required_argument, 	NULL, 	3003},
    {"thickness", 	required_argument, 	NULL, 	3004},
    {"fill", 		no_argument, 		NULL, 	3005},
    {"split", 		no_argument, 		NULL, 	4001}, 	// codes 4xxx are for split function flags
    {"number_x", 	required_argument, 	NULL, 	4002},
    {"number_y", 	required_argument, 	NULL, 	4003},
    {"color", 		required_argument, 	NULL, 	5001}, 	// codes 5xxx are for getting color values
    {"fill_color", 	required_argument, 	NULL, 	5002},
    {"square_rhombus", 	no_argument, 		NULL, 	6001}, 	// codes 6xxx are for square_rhombus function flags
    {"upper_vertex", 	required_argument, 	NULL, 	6002},
    {"size", 		required_argument, 	NULL, 	6003},
    {NULL, 		0, 			NULL, 	0}	// for unknown flags	
};

struct Png
{
    int                pixel_size;
    int                number_of_passes;
    int                width;
    int                height;
    png_structp        png_ptr;
    png_infop          info_ptr;
    png_infop          end_info_ptr;
    png_byte           bit_depth;
    png_byte           color_type;
    png_byte           interlace_type;
    png_byte           compression_type;
    png_byte           filter_type;
    png_bytepp         row_pointers;
};

struct RGB_color
{
    png_byte red;
    png_byte green;
    png_byte blue;
    png_byte alpha;
};

void read_png(const char* path, struct Png *image)
{
    FILE *file_pic = fopen(path, "rb");


    if (!file_pic)
    {
        exit(READ_IMAGE_ERROR);
    }

    png_byte signature[8];
    fread(signature, sizeof(png_byte), 8, file_pic);
    if(png_sig_cmp(signature, 0, 8) != 0)
    {
        exit(READ_IMAGE_ERROR);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        fclose(file_pic);
        exit(READ_IMAGE_ERROR);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        png_destroy_read_struct(&image->png_ptr, NULL, NULL);
        fclose(file_pic);
        exit(READ_IMAGE_ERROR);
    }

    image->end_info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->end_info_ptr)
    {
        png_destroy_read_struct(&image->png_ptr, NULL, NULL);
        fclose(file_pic);
        exit(READ_IMAGE_ERROR);
    }
    
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_read_struct(&image->png_ptr, &image->info_ptr, &image->end_info_ptr);
        fclose(file_pic);
        exit(READ_IMAGE_ERROR);
    }

    png_init_io(image->png_ptr, file_pic);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);

    if(image->bit_depth == 16)
    {
        png_set_strip_16(image ->png_ptr);
    }

    if (image->bit_depth < 8) 
    {
        png_set_packing(image->png_ptr);
    }

    if(image -> color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(image -> png_ptr);
    }

    if(image -> color_type == PNG_COLOR_TYPE_GRAY && image -> bit_depth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(image -> png_ptr);
    }
    
    if(png_get_valid(image -> png_ptr, image -> info_ptr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(image -> png_ptr);
    }

    if(image -> color_type == PNG_COLOR_TYPE_RGB ||
         image -> color_type == PNG_COLOR_TYPE_GRAY ||
         image -> color_type == PNG_COLOR_TYPE_PALETTE)
    {
	png_set_filler(image -> png_ptr, 0xFF, PNG_FILLER_AFTER);
    }
    

    if(image -> color_type == PNG_COLOR_TYPE_GRAY ||
        image -> color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(image -> png_ptr);
    }
    
    if(image -> color_type == PNG_COLOR_TYPE_GRAY ||
        image -> color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(image -> png_ptr);
    }
    
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->interlace_type = png_get_interlace_type(image->png_ptr, image->info_ptr);
    image->filter_type = png_get_filter_type(image->png_ptr, image->info_ptr);
    image->compression_type = png_get_compression_type(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    image->pixel_size = 3;
    if(image->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        image->pixel_size = 4;
    }

    png_read_update_info(image->png_ptr, image->info_ptr);
    image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image->height);

    for (int y = 0; y < image->height; y++)
    {
        image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);
    png_read_end(image->png_ptr, image->info_ptr);
    png_destroy_read_struct(&image->png_ptr, &image->info_ptr,&image->end_info_ptr);
    fclose(file_pic);

    // puts("Read successful\n");
}

void write_png_file(const char* path, struct Png* image)
{
    FILE *file_pic = fopen(path, "w");
    if (!file_pic)
    {
        fclose(file_pic);
        exit(WRITE_IMAGE_ERROR);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr)
    {
        fclose(file_pic);
        exit(WRITE_IMAGE_ERROR);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr)
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(file_pic);
        exit(WRITE_IMAGE_ERROR);
    }

    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(file_pic);
        exit(WRITE_IMAGE_ERROR);
    }

    png_init_io(image->png_ptr, file_pic);

    png_set_IHDR(image->png_ptr, 
        image->info_ptr, 
        image->width, 
        image->height, 
        image->bit_depth, 
        image->color_type,
        image->interlace_type, 
        image->compression_type, 
        image->filter_type);

    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
        fclose(file_pic);
        exit(WRITE_IMAGE_ERROR);
    }

    png_write_image(image->png_ptr, image->row_pointers);
    png_write_end(image->png_ptr, NULL);
    png_destroy_write_struct(&image->png_ptr, &image->info_ptr);
    
    fclose(file_pic);
    
    // puts("Write successful\n");

}

void filter_RGB(char* component_name, int component_value, struct Png* image)
{
    int change_color = -1;

    if(strcmp(component_name, "green")==0)
    {
        change_color = 1;
    }
    if(strcmp(component_name, "blue")==0)
    {
        change_color = 2;
    }
    if(strcmp(component_name, "red")==0)
    {
        change_color = 0;
    }


    for(int y = 0; y < image->height; y++)
    {
        png_byte *row = image->row_pointers[y];
        for(int x = 0; x < image->width; x++)
        {
            png_byte *pix = &(row[x * image->pixel_size]);
            pix[change_color] = component_value;
        }
    }
}

void split(int number_x, int number_y, int thickness, struct RGB_color *color, struct Png* image)
{   
    // in case of user's stupidity
    if(number_x * thickness > image->height || number_y * thickness > image->width)
    {
        // puts("wow, you are really dumb");
        for(int y = 0; y < image->height; y++)
        {
            png_byte *row = image->row_pointers[y];
            for(int x = 0; x < image->width; x++)
            {
                row[x * image->pixel_size] = color->red;
                row[x * image->pixel_size + 1] = color->green; 
                row[x * image->pixel_size + 2] = color->blue; 
                
            }
        }
        return;
    }

    int up = thickness / 2;
    int step_y = image->height / number_x;
    int start_hor = step_y - up;
    
    //in case if thickness too big

    if(start_hor < 0)
    { 
        start_hor = 0;
    }

    int count_hor = 0;
    for(int y = start_hor; count_hor < number_x-1; y+=step_y)
    {
        for(int add_thicc = 0; add_thicc < thickness; add_thicc++)
        {
        
            if(y+add_thicc >= image->height)
            { //in case if thickness too big
                continue;
            }
            png_byte *row = image->row_pointers[y+add_thicc];
            for(int x = 0; x < image->width; x++)
            {
                png_byte *pix = &(row[x * image->pixel_size]);
                pix[0] = color->red;
                pix[1] = color->green;
                pix[2] = color->blue;
            }
        }
        count_hor++;
    }

    int left = thickness / 2;
    int step_x = image->width / number_y;
    int start_ver = step_x - left;

    if(start_ver < 0)
    {      // if too thicc  (‿!‿)  
        start_ver = 0;
    }
    
    for(int y = 0; y < image->height; y++)
    {
        int count_ver = 0;
        png_byte *row = image->row_pointers[y];
        for(int x = start_ver; count_ver < number_y - 1 ; x+=step_x)
        {
            for(int add_thicc = 0; add_thicc < thickness; add_thicc++)
            {
                if(x+add_thicc >= image->width)
                {
                    continue;       //if too thicc
                }
                png_byte *pix = &(row[(x+add_thicc) * image->pixel_size]);
                pix[0] = color->red;
                pix[1] = color->green;
                pix[2] = color->blue;
            }
            count_ver++;
        }
    }
}

void draw_circle(int x_center, int y_center, int radius, int thickness, int fill, 
struct RGB_color *line_color, struct RGB_color *fill_color, struct Png* image) 
{

    // if(x_center < 0 || x_center > image->width || y_center < 0 || y_center > image->height)
    // {
    //     exit(0);
    // }
        

    for(int y = 0; y < image->height; y++)
    {
        png_byte *row = image->row_pointers[y];
        for(int x = 0; x < image->width;  x++)
        {
            int fit_in = floor(sqrt(pow(x - x_center, 2)+pow(y - y_center, 2)));

            if(fit_in >= (radius - thickness/2) && fit_in <= (radius + thickness/2))
            {
                row[x * image->pixel_size] = line_color->red;
                row[x * image->pixel_size + 1] = line_color->green; 
                row[x * image->pixel_size + 2] = line_color->blue; 
            }
        }
    }

    if (fill)
    {
        for(int y = 0; y < image->height; y++)
        {
            png_byte *row = image->row_pointers[y];
            for(int x = 0; x < image->width;  x++)
            {
                int fit_in = floor(sqrt(pow(x - x_center, 2)+pow(y - y_center, 2)));
                if(fit_in < (radius - thickness/2))
                {
                    row[x * image->pixel_size] = fill_color->red;
                    row[x * image->pixel_size + 1] = fill_color->green; 
                    row[x * image->pixel_size + 2] = fill_color->blue; 
                }
            }
        }
    }
}

void draw_rhombus(int x_vertex, int y_vertex, int size, struct RGB_color* fill_color, struct Png* image)
{
    int diag = floor(sqrt(2*pow(size, 2)));

    int x_center = x_vertex;
    int y_center = y_vertex + (diag / 2);

    for(int y = 0; y < image->height; y++)
    {
        png_byte *row = image->row_pointers[y];
        for(int x = 0; x < image->width;  x++)
        {
            int fit_in = ((abs(x - x_center))) + ((abs(y - y_center)));
            if(fit_in <= diag/2)
            {
                row[x * image->pixel_size] = fill_color->red;
                row[x * image->pixel_size + 1] = fill_color->green; 
                row[x * image->pixel_size + 2] = fill_color->blue; 
            }
        }
    }


}

void help()
{
    FILE* help_info = fopen(HELP_PATH, "r");
    char info_string[STRING_BUFFER];
    while(fgets(info_string, STRING_BUFFER, help_info)!=NULL)
    {
    	printf("%s", info_string);
    }
    fclose(help_info);
}

struct RGB_color* parse_color(char* color_str)
{
    struct RGB_color *parsed_color = (struct RGB_color*)malloc(sizeof(struct RGB_color));
    char *tmp = strtok(color_str, ".");
    if(tmp==NULL)
    {
        exit(PARSING_COLOR_ERROR);
    }
    parsed_color->red = atoi(tmp);
    tmp = strtok(NULL, ".");
    if(tmp==NULL)
    {
        exit(PARSING_COLOR_ERROR);
    }
    parsed_color->green = atoi(tmp);
    tmp = strtok(NULL, ".");
    if(tmp==NULL)
    {
        exit(PARSING_COLOR_ERROR);
    }
    parsed_color->blue = atoi(tmp);
    parsed_color->alpha = 255;
    if(parsed_color->red > 255 || parsed_color->green > 255 || parsed_color->blue > 255)
    {
        exit(PARSING_COLOR_ERROR);
    }
    return parsed_color;
}


int check_valid_io(char* path_i, char* path_o)
{
    return strcmp(path_i, path_o);
}

int valid_filter(char* c_name, int c_value)
{
    if(c_name == NULL || c_value < 0 || c_value > 255 )
    {
    	return 0;
    }
    if (strcmp(c_name, "red")!=0 && strcmp(c_name, "green")!=0 && strcmp(c_name, "blue")!=0)
    {
        return 0;
    }
    return 1;
}

int valid_split(int num_x, int num_y, int thickness, struct RGB_color *color)
{
    if(num_x < 1 || num_y < 1 || thickness < 1)
    {
    	return 0;
    }
    return 1;
}

int valid_circle(int radius, int thickness, int fill, struct RGB_color *color, struct RGB_color *color_f)
{
    if(radius < 1 || thickness < 1 || color == NULL)
    {
    	return 0;
    }
    if(fill && color_f == NULL)
    {
    	return 0;
    }
    // else if(color_f != NULL && fill == 0)
    // {
    //     return 0;
    // }
    return 1;
}

int valid_rhombus(int size)
{
    if(size < 1)
    {
        return 0;
    }
    return 1;
}

void handler(int argc, char* argv[])
{
    char path_input[100];
    char path_output[100];

    char *component_name;
    int component_value = -1;

    int center_x;
    int center_y;
    int radius = -1;
    int thickness= 0;
    int fill = 0;

    int vertex_x;
    int vertex_y;
    int size;

    struct RGB_color *color = NULL; 
    struct RGB_color *fill_color = NULL;

    int split_x = 0;
    int split_y = 0;

    struct Png image;

    int func_option = -1;
   

    int rez;
    int option_index;

    while ((rez = getopt_long(argc, argv, short_opts, long_options, &option_index)) != -1)
    {
        switch (rez)
        {
            case 'h':
                help();
                exit(0);
            case 'o':
                strncpy(path_output, optarg, strlen(optarg));
                path_output[strlen(optarg)] = '\0';  
                break;
            case 'i':
                strncpy(path_input, optarg, strlen(optarg));
                path_input[strlen(optarg)] = '\0';
                break;
            case 2001:
            {
                func_option = 1;
                break;
            }
            case 2002:
            {
                component_name = (char*)malloc(strlen(optarg) * sizeof(char));
                strncpy(component_name, optarg, strlen(optarg));
                component_name[strlen(optarg)] = '\0';
                break;
            }
            case 2003:
            {
                component_value = atoi(optarg);
                break;
            }
            case 3001:
            {
                func_option = 2;
                break;
            }
            case 3002:
            {
                char center_coords[10];
                strncpy(center_coords, optarg, strlen(optarg));
                char *tmp = strtok(center_coords, ".");
                center_x = atoi(tmp);
                tmp = strtok(NULL, ".");
                center_y = atoi(tmp);
                break;
            }
            case 3003:
            {
                radius = atoi(optarg);
                break;
            }
            case 3004:
            {
                thickness = atoi(optarg);
                break;
            }
            case 3005:
            {
                fill = 1;
                break;
            }
            case 5001:
            {
                color = parse_color(optarg);
                break;
            }
            case 5002:
            {
                fill_color = parse_color(optarg);
                break;
            }
            case 4001:
            {
                func_option = 3;
                break;
            }
            case 4002:
            {
                split_x = atoi(optarg);
                break;
            }
            case 4003:
            {
                split_y = atoi(optarg);
                break;
            }
            case 6001:
            {
                func_option = 4;
                break;
            }
            case 6002:
            {
                char vertex_coords[10];
                strncpy(vertex_coords, optarg, strlen(optarg));
                char *tmp = strtok(vertex_coords, ".");
                vertex_x = atoi(tmp);
                tmp = strtok(NULL, ".");
                vertex_y = atoi(tmp);
                break;
            }
            case 6003:
            {
                size = atoi(optarg);
                break;
            }
            
            case '?':
            {
                exit(UNKNOWN_ARGUMENTS);
            }

        }
    }

    if(check_valid_io(path_input, path_output) == 0)
    {
    	
        exit(INPUT_AND_OUTPUT_PATH_CONFLICT);
    }
    

    
    read_png(path_input, &image);

    switch (func_option)
    {
    case 1:
    	if(!valid_filter(component_name, component_value))
    	{
    	    exit(INVALID_ARGUMENTS);
    	}
        filter_RGB(component_name, component_value, &image);
        break;

    case 2:
    	if(!valid_circle(radius, thickness, fill, color, fill_color))
    	{
    	    exit(INVALID_ARGUMENTS);
    	}
        draw_circle(center_x, center_y, radius, thickness, fill, color, fill_color, &image);
        break;
    
    case 3:
        if(!valid_split(split_x, split_y, thickness, color))
        {
    	    exit(INVALID_ARGUMENTS);
    	}
        split(split_x, split_y, thickness, color, &image);
        break;
    case 4:
        if(!valid_rhombus(size))
        {
            exit(INVALID_ARGUMENTS);
        }
        draw_rhombus(vertex_x, vertex_y, size, fill_color, &image);
        break;
    
    default:
        break;
    }
    
    write_png_file(path_output, &image);
}


int main(int argc, char* argv[])
{   
    puts("Course work for option 4.23, created by ALexander Romanov");
    handler(argc, argv);
    return 0;
}
