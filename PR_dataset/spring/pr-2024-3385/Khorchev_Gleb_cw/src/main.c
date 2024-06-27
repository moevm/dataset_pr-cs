#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <regex.h>

#include "bmp_structs.h"
#include "define.h"

#include "function_1.h"
#include "function_2.h"
#include "function_3.h"
#include "function_9.h"
#include "help_functions.h"
#include "input_functions.h"
#include "input_processing.h"


int circle_flag = 0, rgbfilter_flag = 0, split_flag = 0, help_flag = 0, info_flag = 0, input_flag = 0, blur_flag = 0;

int main(int argc, char** argv)
{

    char* filename = (char*)malloc(sizeof(char)*BUFFER); 
    char* outputname = (char*)malloc(sizeof(char)*BUFFER);
    outputname = strcpy(outputname, "out.bmp");
    Rgb** pixels = NULL;
    BitmapFileHeader* bmfh = NULL;
    BitmapInfoHeader* bmif = NULL;

    static struct option long_options[] =
    {
    {"circle", no_argument,       &circle_flag, CIRLCE},
    {"rgbfilter",   no_argument,       &rgbfilter_flag, RGBFILTER},
    {"split", no_argument,       &split_flag, SPLIT},
    {"help",   no_argument,       &help_flag, HELP},
    {"info",  no_argument, &info_flag, INFO},
    {"blur", no_argument, &blur_flag, BLUR},

    {"center",     required_argument,       0, CENTER},
    {"radius",  required_argument,       0, RADIUS},
    {"thickness",  required_argument, 0, THICKNESS},
    {"color",  required_argument, 0, COLOR},
    {"fill",  no_argument, 0, FILL},
    {"fill_color",    required_argument, 0, FILL_COLOR},
    {"component_name",    required_argument, 0, COMPONENT_NAME},
    {"component_value",     required_argument,       0, COMPONENT_VALUE},
    {"number_x",  required_argument,       0, NUMBER_X},
    {"number_y",  required_argument, 0, NUMBER_Y},
    {"output",  required_argument, 0, OUTPUT_NAME},
    {"input",  required_argument, 0, INPUT_NAME},
    {"size", required_argument, 0, SIZE},
    {0, 0, 0, 0}
    };

    char short_options[] = "ha:r:t:c:fg:e:v:x:y:o:ip:"; 

    /* getopt_long stores the option index here. */
    int option_index = 0;

    int c;

    int x_coord, y_coord;
    int size;
    unsigned int radius, fill = 0, component_value, thickness, number_x, number_y;
    Rgb fill_color, color;
    char* component_name = (char*)malloc(sizeof(char)*BUFFER);

    while (1)
    {
        c = getopt_long(argc, argv, short_options, long_options, &option_index);

        if ( c == -1 )
            break;

        switch (c)
        {
        case 'h':
            help_flag = HELP;
            break;
        case 'a':
        case CENTER:
            process_center_input(optarg, &x_coord, &y_coord);
            break;
        case 'r':
        case RADIUS:
            if(!process_integer_input(optarg, &radius))
                short_error("Argument for --radius (-r) is not correct. Program will be stopped");
            break;
        case 't':
        case THICKNESS: 
            if(!process_integer_input(optarg, &thickness))
                short_error("Argument for --thickness (-t)  is not correct. Program will be stopped");   
            break;
        case 'c':
        case COLOR:
            process_color_input(optarg, &color, 1);    
            break;
        case 'f':
        case FILL:
            fill = 1;    
            break;
        case 'g':
        case FILL_COLOR:
            process_color_input(optarg, &fill_color, 0);      
            break;
        case 'e':
        case COMPONENT_NAME:
            process_component_name(optarg, component_name);    
            break;
        case 'v':
        case COMPONENT_VALUE:
            process_component_value(optarg, &component_value);    
            break;
        case 'x':
        case NUMBER_X:
            if(!process_integer_input(optarg, &number_x))
                short_error("Argument for --number_x (-x) is not correct. Program will be stopped");
            break;
        case 'y':
        case NUMBER_Y:
            if(!process_integer_input(optarg, &number_y))
                short_error("Argument for --numver_y (-y) is not correct. Program will be stopped");    
            break;
        case 'o':
        case OUTPUT_NAME:
            if (!process_file_name(optarg, outputname))
                short_error("Output file name is not correct. Program will be stopped");    
            break;
        case 'p':
        case INPUT_NAME:
            if (!process_file_name(optarg, filename))
                short_error("Input file name is not correct. Program will be stopped");
            input_flag = 1;    
            break;
        case SIZE:
            if(!process_integer_input(optarg, &size))
                short_error("Input file name is not correct. Program will be stopped");
            break;
        case 'i':
            info_flag = INFO;    
            break;
        default:
            break;
        }
        
    }

    if (help_flag)
    {
        print_help();
        return 0;
    }

    //check for input file that was put without flag --input (-p)
    if ( !input_flag ) check_for_inputfile(argc, argv, filename, optind);
    bmfh = (BitmapFileHeader*)malloc(sizeof(BitmapFileHeader));
    bmif = (BitmapInfoHeader*)malloc(sizeof(BitmapInfoHeader));

    pixels = read_bmp(filename, bmfh, bmif);
    
    if (info_flag)
    {
        print_info(bmfh, bmif);
    } else if (circle_flag)
    {
        pixels = function_1(pixels, bmfh, bmif, x_coord, y_coord, radius, thickness, color, fill, fill_color);
    } else if (rgbfilter_flag)
    {
        pixels = function_2(pixels, bmfh, bmif, component_name, component_value);   
    } else if (split_flag)
    {
        pixels = function_3(pixels, bmfh, bmif, number_x, number_y, thickness, color);
    } else if (blur_flag)
    {
        if ( size % 2 == 0) size++;
        int H = bmif->height;
        int W = bmif->width;
        unsigned int padding = (W * sizeof(Rgb)) % 4;
        if ( padding ) padding = 4 - padding;
        size_t total_size = W * sizeof(Rgb) + padding;
        Rgb** new_pixels = (Rgb**)malloc(H * sizeof(Rgb*));
        for(int i = 0; i < H; i++)
        {
            new_pixels[H-i-1] = (Rgb*)calloc(1, total_size);
        }
        new_pixels = function_9(new_pixels, pixels, bmfh, bmif, size);
        write_bmp(outputname, new_pixels, bmfh, bmif); 
    } else 
    {
        short_error("No key flags were input. Try --help (-h). Program will be stopped");
    }
    if (!blur_flag)
        write_bmp(outputname, pixels, bmfh, bmif);
    return 0;
}