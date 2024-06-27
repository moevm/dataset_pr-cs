#include "parser.h"
#include <stdio.h>
#define MAX_COLOR_VALUE 255

TaskConfig* init_config() {
    TaskConfig* config = malloc(sizeof(TaskConfig));
    config->task_flag = 0;
    config->fill_flag = false;
    config->error_flag = 0;
    config->params = malloc(UINT8_MAX * sizeof(void*));
    memset(config->params, 0x00, UINT8_MAX * sizeof(void*));
    config->input_filename = NULL;
    config->output_filename = NULL;
    return config;
}


uint8_t hash(string* str) {
    uint8_t hval = (uint8_t)2166136261;
    for (size_t i = 0; i < str->size; i++)
        hval = (hval ^ str->data[i]) * HASH_PRIME;
    return hval;
}


uint8_t bitcount(uint8_t n) {
    n = COUNT(n, 0);
    n = COUNT(n, 1);
    n = COUNT(n, 2);
    return n;
}


bool check_param(TaskConfig* config, string* key) {
    string** ptr = config->params;
    return ptr[hash(key)] != NULL;
}


struct option long_opts[] = {
    { ARGNAME_INPUT, required_argument, NULL, ARGNAME_SHORT_INPUT   },
    { ARGNAME_OUTPUT, required_argument, NULL, ARGNAME_SHORT_OUTPUT },
    { ARGNAME_HELP, no_argument, NULL, ARGNAME_SHORT_HELP           },
    { ARGNAME_INFO, no_argument, NULL, TASKCODE_INFO                },
    { ARGNAME_CIRC, no_argument, NULL, TASKCODE_CIRC                },
    { ARGNAME_RGBF, no_argument, NULL, TASKCODE_RGBF                },
    { ARGNAME_SPLT, no_argument, NULL, TASKCODE_SPLT                },
    { ARGNAME_SQRL, no_argument, NULL, TASKCODE_SQRL                },
    { ARGNAME_RMBS, no_argument, NULL, TASKCODE_RMBS                },
    { ARGNAME_CENTER, required_argument, NULL, LONG_OPT_FLAG        },
    { ARGNAME_RADIUS, required_argument, NULL, LONG_OPT_FLAG        },
    { ARGNAME_FILL_COLOR, required_argument, NULL, LONG_OPT_FLAG    },
    { ARGNAME_FILL, no_argument, NULL, TASKCODE_FILL                },
    { ARGNAME_COLOR, required_argument, NULL, LONG_OPT_FLAG         },
    { ARGNAME_THICKNESS, required_argument, NULL, LONG_OPT_FLAG     },
    { ARGNAME_COLOR, required_argument, NULL, LONG_OPT_FLAG         },
    { ARGNAME_COMPNAME, required_argument, NULL, LONG_OPT_FLAG      },
    { ARGNAME_COMPVALUE, required_argument, NULL, LONG_OPT_FLAG     },
    { ARGNAME_NUMBERX, required_argument, NULL, LONG_OPT_FLAG       },
    { ARGNAME_NUMBERY, required_argument, NULL, LONG_OPT_FLAG       },
    { ARGNAME_LEFT_UP, required_argument, NULL, LONG_OPT_FLAG       },
    { ARGNAME_SIDE_SIZE, required_argument, NULL, LONG_OPT_FLAG     },
    { NULL, no_argument, NULL, 0 }
};

static void handle_option(TaskConfig *config, int opt, char *optarg, int long_idx, string** ptr, string* index) {
    char *value = optarg ? str_from_buffer(optarg) : NULL;
    char *index;

    switch (opt) {
        case UNKNOWN_ARG:
            config->error_flag |= FLAG_UNKNOWN_ARGUMENT;
            break;
        case NO_ARG_VAL:
            config->error_flag |= FLAG_NO_ARGUMENT_VALUE;
            break;
        case ARGNAME_SHORT_HELP:
            config->task_flag |= TASKCODE_HELP;
            break;
        case TASKCODE_INFO:
        case TASKCODE_CIRC:
        case TASKCODE_RGBF:
        case TASKCODE_SPLT:
        case TASKCODE_SQRL:
        case TASKCODE_RMBS:
            config->task_flag |= opt;
            break;
        case TASKCODE_FILL:
            config->fill_flag = true;
            break;
        case ARGNAME_SHORT_INPUT:
            if (value) config->input_filename = value;
            break;
        case ARGNAME_SHORT_OUTPUT:
            if (value) config->output_filename = value;
            break;
        case LONG_OPT_FLAG:
            if (value) {
                index = str_from_buffer(long_opts[long_idx].name);
                ptr[hash(index)] = value;
            }
            break;
        default:
            break;
    }
}

TaskConfig* get_args(int argc, char **argv) {
    TaskConfig* config = init_config();
    
    int long_idx;
    int opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
    string** ptr = config->params;
    string* index;

    while (opt != -1) {
        handle_option(config, opt, optarg, long_idx, ptr, index);
        opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
    }
    
    if (config->input_filename == NULL && config->task_flag != TASKCODE_HELP) {
		if (optind < argc)
        	config->input_filename = str_from_buffer(argv[argc-1]);
		else
        	config->error_flag |= FLAG_NO_INPUT_FILE;
	}

    if (config->output_filename == NULL)
        config->output_filename = str_from_buffer(DEFAULT_OUTPUT);

    uint8_t tasks_count = bitcount(config->task_flag);
    if (tasks_count == 0) config->error_flag |= FLAG_NO_COMMAND;
    else if (tasks_count > 1) config->error_flag |= FLAG_MANY_COMMAND;

    return config;
}


void parse_int16(TaskConfig* config, string* key) {
    string** ptr = config->params;
    string* value = ptr[hash(key)];

    uint16_t** i16ptr = config->params;
    int16_t* result = malloc(sizeof(int16_t));

    if (!is_num(value))
        config->error_flag = FLAG_INVALID_ARGUMENT;

    *result = (uint16_t)stoi(value);
    if (*result <= 0)
        config->error_flag = FLAG_INVALID_ARGUMENT;

    i16ptr[hash(key)] = result;
}


void parse_point(TaskConfig* config, string* key) {
    string** ptr = config->params;
    string* value = ptr[hash(key)];

    Point** pptr = config->params;
    Point* point = malloc(sizeof(Point));

    size_t elements_count = 0;
    string** elements = split(value, str_from_char('.'), &elements_count);
    if ((elements_count != 2) || !is_num(elements[0]) || !is_num(elements[1])) {
        config->error_flag = FLAG_INVALID_ARGUMENT;
        return;
    }

    point->x = stoi(elements[0]);
    point->y = stoi(elements[1]);
    pptr[hash(key)] = point;
}


void parse_color(TaskConfig* config, string* key) {
    string** ptr = config->params;
    string* value = ptr[hash(key)];

    Color** cptr = config->params;
    Color* color = malloc(sizeof(Color));

    size_t elements_count = 0;
    string** elements = split(value, str_from_char('.'), &elements_count);
    if ((elements_count != 3) || !is_num(elements[0]) || !is_num(elements[1]) || !is_num(elements[2])) {
        config->error_flag = FLAG_INVALID_ARGUMENT;
        return;
    }

    if (!IN_RANGE(stoi(elements[0]), 0, MAX_COLOR_VALUE) ||
        !IN_RANGE(stoi(elements[1]), 0, MAX_COLOR_VALUE) ||
        !IN_RANGE(stoi(elements[2]), 0, MAX_COLOR_VALUE)) {
            config->error_flag = FLAG_INVALID_ARGUMENT;
            return;
    }

    color->r = (uint8_t)stoi(elements[0]);
    color->g = (uint8_t)stoi(elements[1]);
    color->b = (uint8_t)stoi(elements[2]);

    cptr[hash(key)] = color;
}


void parse_args(TaskConfig* config) {
    if (config->task_flag == TASKCODE_HELP ||
        config->task_flag == TASKCODE_INFO)
        return;

    if (equal(config->input_filename, 
              config->output_filename)) {
        config->error_flag |= FLAG_EQ_INPUT_OUTPUT;
        return;
    }

    switch (config->task_flag) {
    case TASKCODE_CIRC: {
        if (NO_REQUIRED_ARG(ARGNAME_CENTER)    ||
            NO_REQUIRED_ARG(ARGNAME_RADIUS)    ||
            NO_REQUIRED_ARG(ARGNAME_THICKNESS) ||
            NO_REQUIRED_ARG(ARGNAME_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
        }
        parse_point(config, str_from_buffer(ARGNAME_CENTER));
        parse_int16(config, str_from_buffer(ARGNAME_RADIUS));
        parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
        parse_color(config, str_from_buffer(ARGNAME_COLOR));

        if (config->fill_flag) {
            if (NO_REQUIRED_ARG(ARGNAME_FILL_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
            }
            parse_color(config, str_from_buffer(ARGNAME_FILL_COLOR));
        }
        break;
    }
    case TASKCODE_RGBF: {
        if (NO_REQUIRED_ARG(ARGNAME_COMPNAME) ||
            NO_REQUIRED_ARG(ARGNAME_COMPVALUE)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
        }
        parse_int16(config, str_from_buffer(ARGNAME_COMPVALUE));
        break;
    }
    case TASKCODE_SPLT: {
        if (NO_REQUIRED_ARG(ARGNAME_NUMBERX)   ||
            NO_REQUIRED_ARG(ARGNAME_NUMBERY)   ||
            NO_REQUIRED_ARG(ARGNAME_THICKNESS) ||
            NO_REQUIRED_ARG(ARGNAME_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
        }
        parse_int16(config, str_from_buffer(ARGNAME_NUMBERX));
        parse_int16(config, str_from_buffer(ARGNAME_NUMBERY));
        parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
        parse_color(config, str_from_buffer(ARGNAME_COLOR));
        break;
    }
    case TASKCODE_SQRL: {
        if (NO_REQUIRED_ARG(ARGNAME_LEFT_UP)   ||
            NO_REQUIRED_ARG(ARGNAME_SIDE_SIZE) ||
            NO_REQUIRED_ARG(ARGNAME_THICKNESS) ||
            NO_REQUIRED_ARG(ARGNAME_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
        }
        parse_point(config, str_from_buffer(ARGNAME_LEFT_UP));
        parse_int16(config, str_from_buffer(ARGNAME_SIDE_SIZE));
        parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
        parse_color(config, str_from_buffer(ARGNAME_COLOR));

        if (config->fill_flag) {
            if (NO_REQUIRED_ARG(ARGNAME_FILL_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
            }
            parse_color(config, str_from_buffer(ARGNAME_FILL_COLOR));
        }
        break;
    }
    case TASKCODE_RMBS: {
        if (NO_REQUIRED_ARG(ARGNAME_COLOR)) {
                config->error_flag |= FLAG_NO_REQUIRED_ARG;
                return;
        }
        parse_color(config, str_from_buffer(ARGNAME_COLOR));
        break;
    }
    }
}
