#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>

#include "structures.h"
#include "files_action.h"
#include "actions.h"
#include "input_hell.h"


int main(int argc, char *argv[]){
    const char *short_options = "i:o:h";
    Element *dict = malloc(sizeof(Element) * 200);
    int len_dict = 0;
    const struct option long_options[] = {
            {"input",            required_argument,     NULL, 'i'},
            {"output",           required_argument,     NULL, 'o'},
            {"info",             no_argument,           NULL, 1},
            {"help",             no_argument,           NULL, 'h'},
            {"squared_lines",    no_argument,           NULL, 0},
            {"side_size",        required_argument,     NULL, 0},
            {"left_up",          required_argument,     NULL, 0},
            {"right_down",       required_argument,     NULL, 0},
            {"rgbfilter",        no_argument,           NULL, 0},
            {"component_name",   required_argument,     NULL, 0},
            {"component_value",  required_argument,     NULL, 0},
            {"thickness",        required_argument,     NULL, 0},
            {"color",            required_argument,     NULL, 0},
            {"fill",             no_argument,           NULL, 0},
            {"fill_color",       required_argument,     NULL, 0},
            {"rotate",           no_argument,           NULL, 0},
            {"angle",            required_argument,     NULL, 0},
            {"contrast",         no_argument,     NULL, 0},
            {"alpha",            required_argument,     NULL, 0},
            {"beta",            required_argument,     NULL, 0},
            {NULL, 0,                                   NULL, 0}
    };

    int option;
    int option_index = 0;
    char *option_name;

    while ((option = getopt_long(argc, argv, short_options,
                                 long_options, &option_index)) != -1) {
        if (option == '?') {
            printf("unknown option - %s\n", argv[optind - 1]);
            continue;
        }
        option_name = strdup(long_options[option_index].name);
        if (optarg != NULL) {
            dict[len_dict].key = option_name;
            dict[len_dict++].value = optarg;
        } else {
            dict[len_dict].key = option_name;
            dict[len_dict++].value = "";
        }

    };
    int input_flag = 0;

    for (int i = 0; i < len_dict; i++) {
        if (strcmp("input", dict[i].key) == 0) {
            input_flag = 1;
        }
    }
    if (input_flag == 0) {
        if (optind < argc) {
            dict[len_dict].key = "input";
            dict[len_dict++].value = argv[argc - 1];
        }
    }

    run(dict, len_dict);
    free(dict);

    return 0;
}
