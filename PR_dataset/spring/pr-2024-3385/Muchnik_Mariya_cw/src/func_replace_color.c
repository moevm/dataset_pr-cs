#include <regex.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structures.h"
#include "func_replace_color.h"
#include "error_handler.h"

#define RGBREG "^([0-9]+)\\.([0-9]{1,3})\\.([0-9]{1,3})$"

void replace_color(int argc, char** argv, Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    char* regexString = RGBREG;
    size_t maxGroup = 4;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
        print_error("Sorry, can't compile regular expression.\n", bmfh, bmif, arr);

    int c = 0;
    int option_index = 0;
    static struct option long_options[] = {
        {"old_color", 1, NULL, 'o'},
        {"new_color", 1, NULL, 'n'},
        {0, 0, 0, 0}
    };
    c = getopt_long(argc, argv, "o:n:", long_options, &option_index);

    Rgb old_color;
    Rgb new_color;

    int flag = 0;
    while (c != -1) {
        opterr = 0;
        switch(c) {
            case 'o':
                if(regexec(&regexCompiled, optarg, maxGroup, groupArray, 0)){
                    regfree(&regexCompiled);
                    print_error("Your old color must be a string in the format 'rrr.ggg.bbb'!\n", bmfh, bmif, NULL);
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
                old_color.r = rgb[0];
                old_color.g = rgb[1];
                old_color.b = rgb[2];
                flag += 1;
                break;
            case 'n':
                if(regexec(&regexCompiled, optarg, maxGroup, groupArray, 0)){
                    regfree(&regexCompiled);
                    print_error("Your new color must be a string in the format 'rrr.ggg.bbb'!\n", bmfh, bmif, arr);
                }

                unsigned short rgb_n[3]; 
                for (int i = 1; i < maxGroup; i++) {
                    char* tmp = (char*)malloc((groupArray[i].rm_eo - groupArray[i].rm_so + 1)*sizeof(char));
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) {
                        tmp[j-groupArray[i].rm_so] = optarg[j];
                    }
                    tmp[groupArray[i].rm_eo - groupArray[i].rm_so] = '\0';
                    if (atoi(tmp) < 0 || atoi(tmp) > 255) {
                        print_error("New color must be a sets of numbers from 0 to 255!\n", bmfh, bmif, arr);
                    }
                    rgb_n[i-1] = atoi(tmp);
                    free(tmp);
                }
                flag += 1;
                new_color.r = rgb_n[0];
                new_color.g = rgb_n[1];
                new_color.b = rgb_n[2];
                break; 
            default:
                if (strchr("phrfsio", optopt) != NULL) {
                    break;
                } else {
                regfree(&regexCompiled);
                print_error("Meet unknown argument for function replace_color.\n", bmfh, bmif, arr);
                }
        }
        if (flag == 2) {
            regfree(&regexCompiled);
            break;
        }
        c = getopt_long(argc, argv, "o:n:", long_options, &option_index);
    }
    if (flag < 2) 
        print_error("Not enought arguments for function replace_color!\n", bmfh, bmif, arr);

    unsigned int H = abs((int)bmif->height);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < bmif->width; j++) {
            if (((int)arr[i][j].r == old_color.r) && ((int)arr[i][j].g == old_color.g) && ((int)arr[i][j].b == old_color.b)) {
                arr[i][j].r = new_color.r;
                arr[i][j].g = new_color.g;
                arr[i][j].b = new_color.b; 
            }
        }
    }
}