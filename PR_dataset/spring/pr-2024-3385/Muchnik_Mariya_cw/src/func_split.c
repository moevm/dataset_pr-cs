#include <getopt.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <regex.h>

#include "structures.h"
#include "func_split.h"
#include "error_handler.h"

#define RGBREG "^([0-9]+)\\.([0-9]{1,3})\\.([0-9]{1,3})$"

void split(int argc, char** argv, Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    int c = 0;
    int option_index = 0;
    static struct option long_options[] = {
        {"number_x", 1, NULL, 'x'},
        {"number_y", 1, NULL, 'y'},
        {"thickness", 1, NULL, 't'},
        {"color", 1, NULL, 'c'},
        {0, 0, 0, 0}
    };
    c = getopt_long(argc, argv, "x:y:t:c:", long_options, &option_index);

    char* regexString = RGBREG;
    size_t maxGroup = 4;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];

    int num_x = -1;
    int num_y = -1;
    int t = -1;
    int flag = -1;
    Rgb color;
    while (c != -1) {
        opterr = 0;
        switch(c) {
            case 'x':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i]))
                        print_error("Your number_x value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                }
                num_x = atoi(optarg);
                if (num_x < 2)
                    print_error("Your number_x value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                break;
            case 'y':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i]))
                        print_error("Your number_y value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                }
                num_y = atoi(optarg);
                if (num_y < 2)
                    print_error("Your number_y value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                break;
            case 't':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i]))
                        print_error("Your thickness value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                }
                t = atoi(optarg);
                if (t < 1)
                    print_error("Your thickness value should be a number, bigger than 1!\n", bmfh, bmif, NULL);
                break;
            case 'c':
                if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
                    print_error("Sorry, can't compile regular expression.\n", bmfh, bmif, arr);

                if(regexec(&regexCompiled, optarg, maxGroup, groupArray, 0)){
                    regfree(&regexCompiled);
                    print_error("Your split color must be a string in the format 'rrr.ggg.bbb'!\n", bmfh, bmif, NULL);
                }

                unsigned short rgb[3]; 
                for (int i = 1; i < maxGroup; i++) {
                    char* tmp = (char*)malloc((groupArray[i].rm_eo - groupArray[i].rm_so + 1)*sizeof(char));
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) 
                        tmp[j-groupArray[i].rm_so] = optarg[j];
                    tmp[groupArray[i].rm_eo - groupArray[i].rm_so] = '\0';
                    if (atoi(tmp) < 0 || atoi(tmp) > 255) {
                        print_error("Old color must be a sets of number from 0 to 255!\n", bmfh, bmif, arr);
                    }
                    rgb[i-1] = atoi(tmp);
                    free(tmp);
                }
                color.r = rgb[0];
                color.g = rgb[1];
                color.b = rgb[2];
                regfree(&regexCompiled);
                flag = 1;
                break;
            default:
                if (strchr("phrfsio", optopt) != NULL)
                    break;
                else
                    print_error("Meet unknown argument for function split.\n", bmfh, bmif, arr);
        }
        if (num_x != -1 && num_y != -1 && t != -1 && flag != -1)
            break;
        c = getopt_long(argc, argv, "x:y:t:c:", long_options, &option_index);
    }
    if (num_x == -1) 
        print_error("Miss argument number_x for function split.\n", bmfh, bmif, arr);
    if (num_y == -1) 
        print_error("Miss argument number_y for function split.\n", bmfh, bmif, arr);
    if (t == -1) 
        print_error("Miss argument thickness for function split.\n", bmfh, bmif, arr);
    if (flag == -1) 
        print_error("Miss argument color for function split.\n", bmfh, bmif, arr);

    unsigned int H = abs((int)bmif->height);
    unsigned int W = bmif->width;
    int dist = (int)W/num_x + t;
    for (int x = 0; x < W; x+=dist) {
        for (int y = 0; y < H; y++) {
            for (int j = 0; j < t; j++) {
                if (H-y >= 0 && x-j >= 0 && x-j < W && H-y < H) {
                    arr[H-y][x-j].r = color.r;
                    arr[H-y][x-j].g = color.g;
                    arr[H-y][x-j].b = color.b;
                }
            }
        } 
    }

    dist = (int)H/num_y + t;
    for (int y = 0; y < H; y+=dist) {
        for (int x = 0; x < W; x++){
            for (int j = 0; j < t; j++) {
                if (H-y+j >= 0 && H-y+j < H){
                    arr[H-y+j][x].r = color.r;
                    arr[H-y+j][x].g = color.g;
                    arr[H-y+j][x].b = color.b;
                }
            }
        }
    }
}