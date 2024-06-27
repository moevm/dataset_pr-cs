#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "structures.h"
#include "error_handler.h"

void extra(int argc, char** argv, Rgb** arr, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    int c = 0;
    int option_index = 0;
    static struct option long_options[] = {
        {"left_up", 1, NULL, 'u'},
        {"right_down", 1, NULL, 'd'},
        {0, 0, 0, 0}
    };
    c = getopt_long(argc, argv, "u:d:", long_options, &option_index);

    int up[] = {-1, -1};
    int down[] = {-1, -1};

    char* regexString = "^([0-9]+)\\.([0-9]+)$";
    size_t maxGroup = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
        print_error("Sorry, can't compile regular expression.\n", bmfh, bmif, arr);

    while (c != -1) {
        opterr = 0;
        switch(c) {
            case 'u':
                regexec(&regexCompiled, optarg, maxGroup, groupArray, 0);
                if(regexec(&regexCompiled, optarg, maxGroup, groupArray, 0)){
                    regfree(&regexCompiled);
                    print_error("Your up coordinats must be in format x.y!\n", bmfh, bmif, arr);
                }


                for (int i = 1; i < maxGroup; i++) {
                    char* tmp = (char*)malloc((groupArray[i].rm_eo - groupArray[i].rm_so + 1)*sizeof(char));
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) {
                        tmp[j-groupArray[i].rm_so] = optarg[j];
                    }
                    tmp[groupArray[i].rm_eo - groupArray[i].rm_so] = '\0';
                    if (atoi(tmp) < 0)
                        print_error("Must be more than 0!\n", bmfh, bmif, arr);
                    up[i-1] = atoi(tmp);
                    free(tmp);
                }
                break; 
            case 'd':
                if(regexec(&regexCompiled, optarg, maxGroup, groupArray, 0)){
                    regfree(&regexCompiled);
                    print_error("Your down coordinats must be in format x.y!\n", bmfh, bmif, arr);
                }

                for (int i = 1; i < maxGroup; i++) {
                    char* tmp = (char*)malloc((groupArray[i].rm_eo - groupArray[i].rm_so + 1)*sizeof(char));
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) {
                        tmp[j-groupArray[i].rm_so] = optarg[j];
                    }
                    tmp[groupArray[i].rm_eo - groupArray[i].rm_so] = '\0';
                    if (atoi(tmp) < 0) {
                        print_error("Must be more than 0!\n", bmfh, bmif, arr);
                    }
                    down[i-1] = atoi(tmp);
                    free(tmp);
                }
                break;
            default:
                if (strchr("phrfsio", optopt) != NULL) {
                    break;
                } else {
                    regfree(&regexCompiled);
                    print_error("Meet unknown argument for function replace_color.\n", bmfh, bmif, arr);
                }
        }

        if (up[1] != -1 && down[1] != -1) {
            regfree(&regexCompiled);
            break;
        }
        c = getopt_long(argc, argv, "u:d:", long_options, &option_index);
    }

    int W = (int)bmif->width;
    int H = abs((int)bmif->height);
    if (up[0] > W || down[0] > W) 
        print_error("Your x values must be less than width!\n", bmfh, bmif, arr);
    if (up[1] > H || down[1] > H) 
        print_error("Your y values must be less than height!\n", bmfh, bmif, arr);
    if (up[0] > down[0] || up[1] > down[1]) 
        print_error("Incorrect!\n", bmfh, bmif, arr);

    Rgb** seg = (Rgb**)malloc(H*sizeof(Rgb*));
    for (int i = up[1]; i < down[1]; i++) {
        seg[i-up[1]] = (Rgb*)malloc(W*sizeof(Rgb));
        for (int j = up[0]; j < down[0]; j++) {
            seg[i-up[1]][j-up[0]] = arr[H-i-1][j];
        }
    }

    int si = 0;
    for (int i = 0; i < H; i++) {
        int sj = 0;
        for (int j = 0; j < W; j++) {
            arr[H-i-1][j] = seg[si][sj++];
            if (sj == down[0] - up[0])
                sj = 0;
        }
        si++;
        if (si == down[1] - up[1])
            si = 0;
    }
}