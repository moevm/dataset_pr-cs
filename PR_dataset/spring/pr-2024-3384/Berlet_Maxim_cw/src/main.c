#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <math.h>
#include <stdbool.h>
#include <getopt.h>
#include "signatures.h"
#include "structs.h"
#include "png_read_write.h"
#include "main_funcs.h"

int main(int argc, char* argv[]) {
    int opt;
    int option_index = 0;
    png_t* image = (png_t*)malloc(sizeof(png_t));

    char file_name[128] = "\0";
    char output_name[128] = "out.png";
    ipoint_t left_up, right_down, dest, center;
    float radius;
    color_t c, fc;
    int thickness;
    bool fill = false;
    int func_number = -1;
    int threshold = -1;
    while ((opt = getopt_long(argc, argv, all_funcs_short_opts, all_funcs, &option_index)) != -1) {
        switch(opt) {
            case 'R': {
                func_number = draw_rect;
                break;
            }
            case 'S': {
                func_number = draw_smooth_rect;
                break;
            }
            case 'B': {
                func_number = bin;
                break;
            }
            case 'C': {
                func_number = copy_area;
                break;
            }
            case 'H': {
                func_number = draw_hex;
                break;
            }
            case 'i': {
                sscanf(optarg, "%s", file_name);
                if(check_if_png(file_name)) {
                    read_png_file(file_name, image);
                }
                else {
                    fprintf(stderr, "not png\n");
                    exit(format_error);
                }
                if (!check_if_rgb(image)) {
                    fprintf(stderr, "not rgb\n");
                    exit(format_error);
                }
                break;
            }
            case 'u': {
                sscanf(optarg, "%d.%d", &left_up.x, &left_up.y);
                break;
            }
            case 'T': {
                sscanf(optarg, "%d", &threshold);
                if (threshold <= 0) {
                    fprintf(stderr, "negative threshold\n");
                    exit(wrong_value);
                }
                break;
            }
            case 'd': {
                sscanf(optarg, "%d.%d", &right_down.x, &right_down.y);
                break;
            }
            case 'p': {
                sscanf(optarg, "%d.%d", &dest.x, &dest.y);
                break;
            }
            case 'o': {
                sscanf(optarg, "%s", output_name);
                break;
            }
            case 'l': {
                sscanf(optarg, "%d.%d.%d", &fc.r, &fc.g, &fc.b);
                if(!check_colors(fc)) {
                    fprintf(stderr, "wrong colors\n");
                    exit(color_error);
                }
                break;
            }
            case 'f':{
                fill = true;
                break;
            }
            case 't': {
                if (atoi(optarg) < 500) {
                    sscanf(optarg, "%d", &thickness);
                    break;
                }
                else {
                    fprintf(stderr,  "too big thickness\n");
                    exit(thickness_error);
                }
            }
            case 'c':{
                sscanf(optarg, "%d.%d.%d", &c.r, &c.g, &c.b);
                if(!check_colors(c)) {
                    fprintf(stderr, "wrong colors\n");
                    exit(color_error);
                }
                break;
            }
            case 'O': {
                sscanf(optarg, "%d.%d", &center.x, &center.y);
                break;
            }
            case 'r': {
                sscanf(optarg, "%f", &radius);
                if (radius <= 0) {
                    fprintf(stderr, "wrong radius\n");
                    exit(wrong_value);
                }
                break;
            }
            case 'I': {
                puts("This is program info.\n"
                    "This program suports drawing rectangles, hexagones and copying area.\n"
                    "Only png with RGB is supported.\n"
                    "Also there is an extra function that can draw smooth rectangles!\n"
                    "(--smooth_rect ...)");
                return 0;
            }
            case 'h': {
                puts("Course work for option 4.21, created by Maxim Berlet");
                return 0;
            }
        }
    }

    switch(func_number) {
        case draw_rect: {
            if (fill == false) {
                draw_rectangle(image, left_up, right_down, c, c, thickness);
            }
            else if (fill == true) {
                draw_rectangle(image, left_up, right_down, c, fc, thickness);
            }
            write_png_file(output_name, image);
            break;
        }
        case draw_smooth_rect: {
            if (fill == false) {
                draw_smooth_rectangle(image, left_up, right_down, c, thickness);
            }
            else if (fill == true) {
                draw_filled_rectangle(image, left_up, right_down, c, fc, thickness);
            }
            write_png_file(output_name, image);
            break;
        }
        case draw_hex: {
            if (fill == false) {
                draw_hexagon(image, center, radius, c, thickness);
            }
            else if (fill == true) {
                draw_filled_hexagon(image, center, radius, c, fc, thickness);
            }
            write_png_file(output_name, image);
            break;
        }
        case copy_area: {
            copy(image, left_up, right_down, dest);
            write_png_file(output_name, image);
            break;
        }
        case bin: {
            binarization(image, threshold);
            write_png_file(output_name, image);
            break;
        }
        default: {
            fprintf(stderr, "No function called / called wrong function\n");
            exit(wrong_value);
        }
    }

    return 0;
}