#include "parser.h"


TaskConfig* init_config() {
    TaskConfig* config = malloc(sizeof(TaskConfig));
    config->task_flag = 0;
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
    { ARGNAME_COPY, no_argument, NULL, TASKCODE_COPY                },
    { ARGNAME_REPL, no_argument, NULL, TASKCODE_REPL                },
    { ARGNAME_ORNM, no_argument, NULL, TASKCODE_ORNM                },
    { ARGNAME_RECT, no_argument, NULL, TASKCODE_RECT                },
    { ARGNAME_OUTO, no_argument, NULL, TASKCODE_OUTO                },
    { ARGNAME_SRC_UP, required_argument, NULL, LONG_OPT_FLAG        },
    { ARGNAME_SRC_DOWN, required_argument, NULL, LONG_OPT_FLAG      },
    { ARGNAME_DEST_UP, required_argument, NULL, LONG_OPT_FLAG       },
    { ARGNAME_OLD_COLOR, required_argument, NULL, LONG_OPT_FLAG     },
    { ARGNAME_NEW_COLOR, required_argument, NULL, LONG_OPT_FLAG     },
    { ARGNAME_PATTERN, required_argument, NULL, LONG_OPT_FLAG       },
    { ARGNAME_COLOR, required_argument, NULL, LONG_OPT_FLAG         },
    { ARGNAME_BORDER_COLOR, required_argument, NULL, LONG_OPT_FLAG  },
    { ARGNAME_THICKNESS, required_argument, NULL, LONG_OPT_FLAG     },
    { ARGNAME_COUNT, required_argument, NULL, LONG_OPT_FLAG         },
    { NULL, no_argument, NULL, 0 }
};


TaskConfig* get_args(int argc, char **argv) {
    TaskConfig* config = init_config();
    
    int long_idx;
    int opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
    string** ptr = config->params;
    string* index;

    while (opt != -1) {
        string* value = str_from_buffer(optarg);
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
            case TASKCODE_COPY:
            case TASKCODE_REPL:
            case TASKCODE_ORNM:
            case TASKCODE_RECT:
            case TASKCODE_OUTO:
                config->task_flag |= opt;
                break;
            case ARGNAME_SHORT_INPUT:
                if (optarg) config->input_filename = value;
                break;
            case ARGNAME_SHORT_OUTPUT:
                if (optarg) config->output_filename = value;
                break;
            case LONG_OPT_FLAG:
                if (optarg) {
                    index = str_from_buffer(long_opts[long_idx].name);
                    ptr[hash(index)] = value;
                }
                break;
        }
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
    if (*result < 0)
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

    if (!IN_RANGE(stoi(elements[0]), 0, MAX_CHANNEL_VALUE) ||
        !IN_RANGE(stoi(elements[1]), 0, MAX_CHANNEL_VALUE) ||
        !IN_RANGE(stoi(elements[2]), 0, MAX_CHANNEL_VALUE)) {
            config->error_flag = FLAG_INVALID_ARGUMENT;
            return;
    }

    color->r = (uint8_t)stoi(elements[0]);
    color->g = (uint8_t)stoi(elements[1]);
    color->b = (uint8_t)stoi(elements[2]);

    cptr[hash(key)] = color;
}


void parse_copy(TaskConfig* config) {
    if (NO_REQUIRED_ARG(ARGNAME_SRC_UP)   ||
        NO_REQUIRED_ARG(ARGNAME_SRC_DOWN) ||
        NO_REQUIRED_ARG(ARGNAME_DEST_UP)) {
            config->error_flag |= FLAG_NO_REQUIRED_ARG;
            return;
    }
    parse_point(config, str_from_buffer(ARGNAME_SRC_UP));
    parse_point(config, str_from_buffer(ARGNAME_SRC_DOWN));
    parse_point(config, str_from_buffer(ARGNAME_DEST_UP));
}


void parse_repl(TaskConfig* config) {
    if (NO_REQUIRED_ARG(ARGNAME_OLD_COLOR) ||
        NO_REQUIRED_ARG(ARGNAME_NEW_COLOR)) {
            config->error_flag |= FLAG_NO_REQUIRED_ARG;
            return;
    }
    parse_color(config, str_from_buffer(ARGNAME_OLD_COLOR));
    parse_color(config, str_from_buffer(ARGNAME_NEW_COLOR));
}


void parse_ornm(TaskConfig* config) {
    if (NO_REQUIRED_ARG(ARGNAME_PATTERN)   ||
        NO_REQUIRED_ARG(ARGNAME_COLOR)     ||
        NO_REQUIRED_ARG(ARGNAME_THICKNESS) ||
        NO_REQUIRED_ARG(ARGNAME_COUNT)) {
            config->error_flag |= FLAG_NO_REQUIRED_ARG;
            return;
    }
    parse_color(config, str_from_buffer(ARGNAME_COLOR));
    parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
    parse_int16(config, str_from_buffer(ARGNAME_COUNT));
}


void parse_rect(TaskConfig* config) {
    if (NO_REQUIRED_ARG(ARGNAME_COLOR)        ||
        NO_REQUIRED_ARG(ARGNAME_BORDER_COLOR) ||
        NO_REQUIRED_ARG(ARGNAME_THICKNESS)) {
            config->error_flag |= FLAG_NO_REQUIRED_ARG;
            return;
    }
    parse_color(config, str_from_buffer(ARGNAME_COLOR));
    parse_color(config, str_from_buffer(ARGNAME_BORDER_COLOR));
    parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
}


void parse_outo(TaskConfig* config) {
    if (NO_REQUIRED_ARG(ARGNAME_COLOR) ||
        NO_REQUIRED_ARG(ARGNAME_THICKNESS)) {
            config->error_flag |= FLAG_NO_REQUIRED_ARG;
            return;
    }
    parse_color(config, str_from_buffer(ARGNAME_COLOR));
    parse_int16(config, str_from_buffer(ARGNAME_THICKNESS));
}


void parse_args(TaskConfig* config) {
    if (config->task_flag == TASKCODE_HELP ||
        config->task_flag == TASKCODE_INFO)
        return;

    string** ptr = config->params;
    if (equal(config->input_filename, 
              config->output_filename)) {
        config->error_flag |= FLAG_EQ_INPUT_OUTPUT;
        return;
    }

    switch (config->task_flag) {
        case TASKCODE_COPY: {
            parse_copy(config);
            break;
        }
        case TASKCODE_REPL: {
            parse_repl(config);
            break;
        }
        case TASKCODE_ORNM: {
            parse_ornm(config);
            break;
        }
        case TASKCODE_RECT: {
            parse_rect(config);
            break;
        }
        case TASKCODE_OUTO: {
            parse_outo(config);
            break;
        }
    }
}
