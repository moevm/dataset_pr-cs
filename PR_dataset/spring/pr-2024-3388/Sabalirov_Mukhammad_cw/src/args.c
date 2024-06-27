#include "args.h"

char* get_optional_arg(char* arg){
	char* optional_arg;

	if (arg[0] != '='){
		return arg;
	}

	optional_arg = malloc(sizeof(char)*strlen(arg));
	sprintf(optional_arg, "%.*s", (int)(strlen(arg) - 1), arg + 1);
	
	return optional_arg;
}

void process_long_options(func_param_args_t* args, int code_of_arg, char* optarg){
	switch (code_of_arg){
		case AXIS_CODE:{
			args->axis = strdup(optarg);
			break;
		}

		case LEFT_UP_CODE:{
			args->left_up = strdup(optarg);
			break;
		}

		case RIGHT_DOWN_CODE:{
			args->right_down = strdup(optarg);
			break;
		}

		case CENTER_CODE:{
			args->center = strdup(optarg);
			break;
		}

		case RADIUS_CODE:{
			args->radius = strdup(optarg);
			break;
		}

		case THICKNESS_CODE:{
			args->thickness = strdup(optarg);
			break;
		}

		case COLOR_CODE:{
			args->color = strdup(optarg);
			break;
		}

		case FILL_COLOR_CODE:{
			args->fill_color = strdup(optarg);
			break;
		}

		default:
			break;
	}
}

func_param_args_t get_args(int argc, char *argv[]){
	if (argc == 1){
		panic(UNKNOWN_OPTION_OR_NO_REQUIRED_ARG_ERROR);
	}

    int opt;
	int option_index;

	int input_f = 0;

	int code_of_arg = 0;

	func_param_args_t args = {0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	char* input_file;
	char* output_file = strdup(DEFAULT_OUTPUT);

    const struct option long_options[] = {
		{ HELP_ARG, no_argument, NULL, SHORT_HELP_ARG },
		{ INPUT_ARG, required_argument, NULL, SHORT_INPUT_ARG },
		{ OUTPUT_ARG, required_argument, NULL, SHORT_OUTPUT_ARG },
		{ INFO_ARG, no_argument, &(args.info), 1},
		{ MIRROR_ARG, no_argument, &(args.mirror), 1},
		{ PENTAGRAM_ARG, no_argument, &(args.pentagram), 1},
		{ RECT_ARG, no_argument, &(args.rect), 1},
		{ HEXAGON_ARG, no_argument, &(args.hexagon), 1},
		{ FILL_ARG, no_argument, &(args.fill), 1},
		{ PAVING_ARG, no_argument, &(args.paving), 1},
		{ AXIS_ARG, required_argument, &code_of_arg, AXIS_CODE},
		{ LEFT_UP_ARG, required_argument, &code_of_arg, LEFT_UP_CODE},
		{ RIGHT_DOWN_ARG, required_argument, &code_of_arg, RIGHT_DOWN_CODE},
		{ CENTER_ARG, required_argument, &code_of_arg, CENTER_CODE},
		{ RADIUS_ARG, required_argument, &code_of_arg, RADIUS_CODE},
		{ THICKNESS_ARG, required_argument, &code_of_arg, THICKNESS_CODE},
		{ COLOR_ARG, required_argument, &code_of_arg, COLOR_CODE},
		{ FILL_COLOR_ARG, required_argument, &code_of_arg, FILL_COLOR_CODE},
		{ NULL, 0, NULL, 0 }
	};

	while ((opt=getopt_long(argc, argv, SHORT_OPTIONS, long_options, &option_index))!=-1){

		switch (opt){
			case UNKNOWN_OPTION_OR_NO_REQUIRED_ARG:{
				panic(UNKNOWN_OPTION_OR_NO_REQUIRED_ARG_ERROR);
				break;
			}
			
			case SHORT_HELP_ARG:{
				printf(HELP);
				exit(0);
				break;
			}

			case SHORT_INPUT_ARG:{
				if (optarg){
					input_f = 1;
					input_file = strdup(optarg);
				}
				break;
			}

			case SHORT_OUTPUT_ARG:{
				if (optarg){
					output_file = strdup(optarg);
				}
				break;
			}

			default:{
				break;
			}
		}
		process_long_options(&args, code_of_arg, optarg);
		code_of_arg = 0;
    }

	if (!input_f){
		if (optind < argc){
        	input_file = strdup(argv[argc-1]);
    	}
		else{
        	panic(UNKNOWN_OPTION_OR_NO_REQUIRED_ARG_ERROR);
    	}
	}

	args.input = input_file;
	args.output = output_file;

	validate_func_param_args(args);

	return args;
}