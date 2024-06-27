#include "args.h"

void process_long_args(char* optarg, struct option* long_opts, int long_idx, args_t* args){
    if (!optarg)
        return;

    if (!strcmp(VALUE_ARG, long_opts[long_idx].name)){
        args->value = strdup(optarg);
        return;
    }

    if (!strcmp(THICKNESS_ARG, long_opts[long_idx].name)){
        args->thickness = strdup(optarg);
        return;
    }

    if (!strcmp(RADIUS_ARG, long_opts[long_idx].name)){
        args->radius = strdup(optarg);
        return;
    }
    
    if (!strcmp(COMPONENT_NAME_ARG, long_opts[long_idx].name)){
        args->component_name = strdup(optarg);
        return;
    }
    
    if (!strcmp(COMPONENT_VALUE_ARG, long_opts[long_idx].name)){
        args->component_value = strdup(optarg);
        return;
    }

    if (!strcmp(NUMBER_X_ARG, long_opts[long_idx].name)){
        args->number_x = strdup(optarg);
        return;
    }

    if (!strcmp(NUMBER_Y_ARG, long_opts[long_idx].name)){
        args->number_y = strdup(optarg);
        return;
    }

    if (!strcmp(CENTER_ARG, long_opts[long_idx].name)){
        args->center = strdup(optarg);
        return;
    }

    if (!strcmp(COLOR_ARG, long_opts[long_idx].name)){
        args->color = strdup(optarg);
        return;
    }

    if (!strcmp(FILL_COLOR_ARG , long_opts[long_idx].name)){
        args->fill_color = strdup(optarg);
        return;
    }
}

args_t get_args(int argc, char* argv[]){
    args_t args = {0, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL};

    struct option long_opts[] = {
		{ INPUT_ARG, required_argument, NULL, SHORT_INPUT_ARG},
		{ OUTPUT_ARG, required_argument, NULL, SHORT_OUTPUT_ARG},
        { HELP_ARG, no_argument, NULL, SHORT_HELP_ARG},
		{ INFO_ARG, no_argument, &(args.info_flag), 1},
        { CIRCLE_ARG, no_argument, &(args.circle), 1},
        { RGB_FILTER, no_argument, &(args.rgb_filter), 1},
        { SPLIT_ARG, no_argument, &(args.split), 1},
        { FILL_ARG, no_argument, &(args.fill), 1},
        { CENTER_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { RADIUS_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { THICKNESS_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { FILL_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { COMPONENT_NAME_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { COMPONENT_VALUE_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { NUMBER_X_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { NUMBER_Y_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { VALUE_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { GAMMA_ARG, no_argument, &(args.gamma), 1},
        { NULL, 0, NULL, 0}
    };

    int long_idx;
    int opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);

    while (opt != -1){
        switch (opt){
            case NO_ARG_VAL:{
                panic(NO_ARG_VAL_ERROR);
                break;
            }

            case UNKNOWN_ARG:{
                panic(UNKNOWN_ARG_ERROR);
                break;
            }

            case SHORT_HELP_ARG:{
                printf(HELP);
                exit(0);
                break;
            }

            case SHORT_INPUT_ARG:{
                if (optarg)
                    args.input_file = strdup(optarg);
                break;
            }

            case SHORT_OUTPUT_ARG:{
                if (optarg)
                    args.output_file = strdup(optarg);
                break;
            }

            case LONG_OPT_FLAG: {
                process_long_args(optarg, long_opts, long_idx, &args);
            }

            default:{
                break;
            }
        }
        opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
    }
    
    if (!args.input_file){
		if (optind < argc)
        	args.input_file = strdup(argv[argc-1]);
		else
        	panic(NO_INPUT_FILE_ARG_ERROR);
	}

    if (!args.output_file)
        args.output_file = strdup(DEFAULT_OUTPUT_PNG);

    return args;
}

int check_for_regex(char* str, char* regex_template){
	int reg_ans;
    regex_t regex;

	if (!str)
		return 0;

	reg_ans = regcomp(&regex, regex_template, REG_EXTENDED);

	if (reg_ans)
        panic(REGCOMP_ERROR);
	
    reg_ans = regexec(&regex, str, 0, NULL, 0);
	regfree(&regex);

    return reg_ans != REG_NOMATCH;
}

int check_color(int optional, char* color){
    return !optional || check_for_regex(color, REGEX_COLOR);
}

void check_args(args_t args){
    int checks = 0;
    int comp_val;
    int main_func_count = args.info_flag + args.circle + args.rgb_filter + args.split + args.gamma;

    if (main_func_count != 1)
        panic(SELECTED_FUNCTIONS_COUNT_ERROR);

    if (args.circle || args.split){
        checks += !check_for_regex(args.thickness, REGEX_NATURAL_NUM);
        checks += !check_color(0, args.color);
    }

    if (args.circle){
        checks += !check_for_regex(args.center, REGEX_COORDINATES);
        checks += !check_for_regex(args.radius, REGEX_NATURAL_NUM);
        checks += !check_color(args.fill, args.fill_color);
    }

    if (args.rgb_filter){
        checks += !check_for_regex(args.component_name, REGEX_RGB_FILTER);
        checks += !check_for_regex(args.component_value, REGEX_NUM);
        comp_val = atoi(args.component_value);
        checks += !(comp_val >= 0 && comp_val <= MAX_COMPONENT_VAL);
    }

    if (args.split){
        checks += !(check_for_regex(args.number_x, REGEX_NUM) && atoi(args.number_x) > 1);
        checks += !(check_for_regex(args.number_y, REGEX_NUM) && atoi(args.number_y) > 1);
    }

    checks += !strcmp(args.input_file, args.output_file);

    if (checks)
        panic(ARG_VAL_ERROR);
}