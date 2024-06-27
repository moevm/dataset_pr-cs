#include <iostream>
#include <getopt.h>
#include "png_class.h"
#include "file_interactions.h"
#include "input_system.h"
using namespace std;






void print_help() {
    FILE *file = fopen("help", "rb");
    if (!file) {
        printf("Help_info_file is not found.\n");
        exit(9);
    }
    char ch = (char) fgetc(file);
    while (ch != EOF) {
        printf("%c", ch);
        ch = (char) fgetc(file);
    }
    fclose(file);
    
}


int main(int argc, char** argv) {
    Arguments* args = readArguments(argc, argv);

    if (args == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    if(args->is_help)
    {
        print_help();
        exit(0);
    }
    Png* image = read_png_file(args->input_img_path);

    if (image == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    if(args->is_info)
    {
        image->print_png_info();
        exit(0);
    }


    switch (args->opt_number)
    {
        case 1:
        {
            if ( args->thickness <= 0)
            {
                cout << "Invalid thickness value\n";
                exit(42);
            }
            image->draw_triangle(args->x0,args->y0,args->x1,args->y1,args->x2,args->y2,args->color,args->thickness,args->is_fill,args->fill_color);
            save_png_file(image,args->output_img_path);
            break;
        }
        case 2:
        {
            image->recolor_biggest_rect(args->old_color,args->new_color);
            save_png_file(image,args->output_img_path);
            break;
        }
        case 3:
        {
            if (args->number_x <= 0 || args->number_y <= 0)
            {
                cout << "Invalid number_x or number_y value\n";
                exit(41);
            }
            Png* collage = image->create_collage(args->number_x, args->number_y);
            if (collage == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }
            
            save_png_file(collage,args->output_img_path);
            delete collage;
            break;
        }
        case 4:
        {
            if (args->thickness <= 0)
            {
                cout << "Invalid thickness value\n";
                exit(42);
            }
            image->draw_line(args->x0,args->y0,args->x1,args->y1,args->color,args->thickness);
            save_png_file(image,args->output_img_path);
            break;
        }
        case 5:
        {
          
            image->rhombus(args->color);
            save_png_file(image,args->output_img_path);
            break;
        }
        default:
        {
            cout << "Choose option!\n";
            exit(43);
        }
    }

    
    delete image;
    delete args;
    cout << "Done!\n";
    return 0;
}