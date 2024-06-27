#include "option.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("-h, -helh  Выводит справку.\n--info  Печатает информацию об изображении и завершает работу.\n-i, --input   Задаёт имя входного изображения.\n-o, --output  Задаёт имя выходного изображения.\n");
    printf("--color_replace  Заменяет все пиксели одного заданного цвета на другой цвет.");
    printf("Функционал определяется: \nЦвет, который требуется заменить. Флаг `--old_color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту.\n");
    printf("Цвет на который требуется заменить. Флаг `--new_color` (работает аналогично флагу `--old_color`)");
    printf("\n--component_max  Установить все компоненты пикселя как максимальную из них. Т.е. если пиксель имеет цвет (100, 150, 200), то после применения операции цвет будет (200, 200, 200).");
    exit(0);
}

char option(char **output,char **input,char **old_col,char **new_col,char **value, int argc, char *argv[]){
    char comand=0;
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 0},
        {"output", required_argument, NULL, 'o'},
        {"color_replace", no_argument, NULL, 0},
        {"old_color", required_argument, NULL, 0},
        {"new_color", required_argument, NULL, 0},
        {"component_max", no_argument, NULL, 0},
        {"input", required_argument, NULL, 'i'},
        {"gamma", no_argument, NULL, 0},
        {"value", required_argument, NULL, 0},
        {NULL, 0, NULL, 0}};
    int code;
    int option_index;
    while ((code = getopt_long(argc, argv, "ho:i:", long_options, &option_index)) != -1) {
        switch (code) {
            case 'h':
                help();
                exit(0);
                break;
            case 'o': {
                *output = optarg;
                break;
            };
            case 'i': {
                *input = optarg;
                break;
            };

            case 0: {
                const char *opt_name = long_options[option_index].name;
                if (strcmp(opt_name, "info") == 0) {
                    if (comand == 0)
                        comand = 'i';
                    else
                        exit(46);
                } else if (strcmp(opt_name, "color_replace") == 0) {
                    if (comand == 0)
                        comand = 'r';
                    else
                        exit(46);
                } else if (strcmp(opt_name, "component_max") == 0) {
                    if (comand == 0)
                        comand = 'm';
                    else
                        exit(46);
                } else if (strcmp(opt_name, "old_color") == 0) {
                    *old_col = optarg;
                } else if (strcmp(opt_name, "new_color") == 0) {
                    *new_col = optarg;
                } else if (strcmp(opt_name, "gamma") == 0) {
                    if (comand == 0)
                        comand = 'g';
                    else
                        exit(46);
                } else if (strcmp(opt_name, "value") == 0) {
                    *value = optarg;
                }
                break;
            }
            default: {
                exit(41);
                break;
            };
        };
    };
    if (*output == NULL)
        *output = "out.bmp";
    if (*input == NULL) {
        if (argc > optind && (optind + 1 == argc))
            *input = argv[optind];
        else if (argc >= optind) {
            printf("no file name entered\n");
            exit(41);
        }
    }
    if (strcmp(*output, *input) == 0) {
        exit(43);
    }
    if (comand == 0)
        help();
    return comand;
}

