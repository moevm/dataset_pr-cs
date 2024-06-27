#include <getopt.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "structures.h"
#include "func_rgb_filter.h"
#include "error_handler.h"

void rgb_filter(int argc, char** argv, Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    int c = 0;
    int option_index = 0;
    static struct option long_options[] = {
        {"component_name", 1, NULL, 'n'},
        {"component_value", 1, NULL, 'v'},
        {0, 0, 0, 0}
    };
    c = getopt_long(argc, argv, "n:v:", long_options, &option_index);

    char name = '\0';
    int value = -1;
    optind = 1;
    while (c != -1) {
        opterr = 0;
        switch(c) {
            case 'n':
                if (strstr(optarg, "red"))
                    name = 'r'; 
                if (strstr(optarg, "green")) 
                    name = 'g';
                if (strstr(optarg, "blue"))
                    name = 'b';
                if (name == '0')
                    print_error("Your component name should have value equal to 'red', 'blue' or 'green'!\n", bmfh, bmif, NULL);
                break;
            case 'v':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i]))
                        print_error("Your component value should be a number from 0 to 255!\n", bmfh, bmif, NULL);
                }
                value = atoi(optarg);
                if (value < 0 || value > 255)
                    print_error("Your component value should be a number from 0 to 255!\n", bmfh, bmif, NULL);
                break;
            default:
                if (strchr("phrfsio", optopt) != NULL)
                    break;
                else
                    print_error("Meet unknown argument for function rgb_filter.\n", bmfh, bmif, arr);
        }
        if (name != '\0' && value != -1)
            break;
        c = getopt_long(argc, argv, "n:v:", long_options, &option_index);
    }
    if (name == '0') 
        print_error("Miss argument component_name for function rgbfilter.\n", bmfh, bmif, arr);
    if (value == -1) 
        print_error("Miss argument component_value for function rgbfilter.\n", bmfh, bmif, arr);

    unsigned int H = abs((int)bmif->height);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < bmif->width; j++) {
            switch (name) {
                case 'r':
                    arr[i][j].r = value;
                    break;
                case 'g':
                    arr[i][j].g = value;
                    break;
                case 'b':
                    arr[i][j].b = value;
                    break;
            }
        }
    }
}