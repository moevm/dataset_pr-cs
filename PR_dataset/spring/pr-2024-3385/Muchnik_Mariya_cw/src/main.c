#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "structures.h"
#include "bmp_rw.h"
#include "print_info.h"
#include "error_handler.h"
#include "print_help.h"
#include "func_replace_color.h"
#include "func_rgb_filter.h"
#include "func_split.h"
#include "extra_func.h"

int main (int argc, char **argv) {
    char* file_name = NULL;
    char* output_file = (char*)malloc((strlen("out.bmp") + 1)*sizeof(char));
    strcpy(output_file, "out.bmp");
    output_file[strlen("out.bmp")] = '\0';
    Rgb** arr = NULL;
    BitmapFileHeader* bmfh = NULL;
    BitmapInfoHeader* bmif = NULL;
    
    int c = 0;
    int option_index = 0;
    static struct option long_options[] = {
        {"color_replace", 0, NULL, 'R'},
        {"rgbfilter", 0, NULL, 'F'},
        {"split", 0, NULL, 'S'},
        {"paving", 0, NULL, 'P'},
        {"info", 0, NULL, 'a'},
        {"input", 1, NULL, 'i'}, 
        {"output", 1, NULL, 'o'},
        {"help", 0, NULL, 'h'},
        {0, 0, 0, 0}
    };
    c = getopt_long(argc, argv, "i:o:hrfpsa", long_options, &option_index);
    
    if (c == -1) {
        print_help();
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--input") || !strcmp(argv[i], "-i")) {
            if (i == argc || argv[i+1][0] == '-')
                print_error("Functon input requires one required argument: input_file_name!\n", bmfh, bmif, arr);
            file_name = (char*)malloc((strlen(argv[i+1])+1)*sizeof(char));
            strcpy(file_name, argv[i+1]);
            file_name[strlen(argv[i+1])] = '\0';
            bmfh = malloc(sizeof(BitmapFileHeader));
            bmif = malloc(sizeof(BitmapInfoHeader));
            arr = read_bmp(file_name, bmfh, bmif);
            break;
        }
    }
    
    if (file_name == NULL) {
        int cmp1 = !strcmp(argv[argc-1], "-h");
        int cmp2 = !strcmp(argv[argc-1], "--help");
        if (!(argc == 1 || (argc == 2 && (cmp1 || cmp2)))) {
            if (strstr(argv[argc-1], ".") == NULL)
                print_error("Please, enter your filename as last argument.\n", NULL, NULL, NULL);
            file_name = (char*)malloc((strlen(argv[argc-1]) + 1)*sizeof(char));
            strcpy(file_name, argv[argc-1]);
            file_name[strlen(argv[argc-1])] = '\0';
            bmfh = malloc(sizeof(BitmapFileHeader));
            bmif = malloc(sizeof(BitmapInfoHeader));
            arr = read_bmp(file_name, bmfh, bmif);
        }
    }
    
    int mem = 1;
    while (c != -1) {
        opterr = 0;
        if (isupper(c))
            optind--;
        switch (c) {
            case 'r':
            case 'R':
                mem = optind;
                replace_color(argc, argv, arr, bmfh, bmif);
                optind = mem++;
                break;
            case 'f':
            case 'F':
                mem = optind;
                rgb_filter(argc, argv, arr, bmfh, bmif);
                optind = mem++;
                break;
            case 's':
            case 'S':
                mem = optind;
                split(argc, argv, arr, bmfh, bmif);
                optind = mem++;
                break;
            case 'p':
            case 'P':
                mem = optind;
                extra(argc, argv, arr, bmfh, bmif);
                optind = mem++;
                break;
            case 'a':
                print_info(bmif, bmfh);
                break;
            case 'h':
                print_help();
                break;
            case 'i':
                break;
            case 'o':
                if (optarg == NULL || optarg[0] == '-')
                    print_error("Functon output requires one required argument: output_file_name!\n", bmfh, bmif, arr);
                output_file = (char*)malloc((strlen(optarg)+1)*sizeof(char));
                strcpy(output_file, optarg);
                output_file[strlen(optarg)] = '\0';
                break;
            case '?':
                optind++;
                break;
        }
        c = getopt_long(argc, argv, "i:o:rfpsah", long_options, &option_index);
    }
    if (bmif) {
        unsigned int H = abs((int)bmif->height);
        write_bmp(output_file, arr, H, bmif->width, *bmfh, *bmif);
    }
    free(file_name);
    free(output_file);
    freeMemory(bmfh, bmif, arr);
    return 0;
}