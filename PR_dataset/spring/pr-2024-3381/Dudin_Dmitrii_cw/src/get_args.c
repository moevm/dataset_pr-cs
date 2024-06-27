#include "get_args.h"

args_t get_args(int argc, char* argv[]){
    args_t args = {0, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL};

    struct option long_opts[] = {
		{ INPUT_ARG, required_argument, NULL, SHORT_INPUT_ARG},
		{ OUTPUT_ARG, required_argument, NULL, SHORT_OUTPUT_ARG},
        { HELP_ARG, no_argument, NULL, SHORT_HELP_ARG},
		{ INFO_ARG, no_argument, &(args.info_flag), 1},
        { TRIANGLE_ARG, no_argument, &(args.triangle), 1},
        { BIGGEST_RECT_ARG, no_argument, &(args.biggest_rect), 1},
        { COLLAGE_ARG, no_argument, &(args.collage), 1},
        { FILL_ARG, no_argument, &(args.fill), 1},
        { NUMBER_Y_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { NUMBER_X_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { THICKNESS_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { POINTS_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { OLD_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { NEW_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        { FILL_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
        {"value", required_argument, NULL, LONG_OPT_FLAG},
        {"gamma", no_argument, &(args.gamma), 1},
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
                if (!optarg)
                    break;

                if (!strcmp("value", long_opts[long_idx].name)){
                    args.value = strdup(optarg);
                    break;
                }

                if (!strcmp(NUMBER_X_ARG, long_opts[long_idx].name)){
                    args.number_x = strdup(optarg);
                    break;
                }

                if (!strcmp(NUMBER_Y_ARG, long_opts[long_idx].name)){
                    args.number_y = strdup(optarg);
                    break;
                }

                if (!strcmp(POINTS_ARG, long_opts[long_idx].name)){
                    args.points = strdup(optarg);
                    break;
                }
                
                if (!strcmp(THICKNESS_ARG, long_opts[long_idx].name)){
                    args.thickness = strdup(optarg);
                    break;
                }

                if (!strcmp(COLOR_ARG, long_opts[long_idx].name)){
                    args.color = strdup(optarg);
                    break;
                }

                if (!strcmp(FILL_COLOR_ARG, long_opts[long_idx].name)){
                    args.fill_color = strdup(optarg);
                    break;
                }

                if (!strcmp(OLD_COLOR_ARG, long_opts[long_idx].name)){
                    args.old_color = strdup(optarg);
                    break;
                }

                if (!strcmp(NEW_COLOR_ARG, long_opts[long_idx].name)){
                    args.new_color = strdup(optarg);
                    break;
                }
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
        args.output_file = strdup(DEFAULT_OUTPUT_BMP);

    return args;
}