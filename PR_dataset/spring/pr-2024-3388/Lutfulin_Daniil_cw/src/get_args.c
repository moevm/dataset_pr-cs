#include "get_args.h"


args_t get_args(int argc, char **argv){
    args_t args = {0,0,NULL,NULL,0,NULL,NULL,NULL,0,NULL,0,NULL,NULL,0,NULL,NULL,NULL,NULL,0};
    struct option long_opts[] = {
        { HELP_ARG, no_argument, NULL, SHORT_HELP_ARG},
        { INFO_ARG, no_argument, &args.info, 1},
        { ORNAMET_ARG, no_argument, &args.ornament, 1},
        { INPUT_ARG, required_argument, NULL, SHORT_INPUT_ARG},
        { OUTPUT_ARG, required_argument, NULL, SHORT_OUTPUT_ARG},
        { MIRROR_ARG, no_argument, NULL, SHORT_MIRROR_ARG},
        { AXIS_ARG, required_argument, NULL, LONG_OPT_ARG},
        { LEFT_UP_ARG, required_argument, NULL,LONG_OPT_ARG},
        { RIGHT_DOWN_ARG, required_argument, NULL,LONG_OPT_ARG},
        { COPY_ARG, no_argument, NULL,SHORT_COPY_ARG},
        { DEST_LEFT_UP_ARG, required_argument, NULL, LONG_OPT_ARG},
        { COLOR_REPLACE_ARG, no_argument, NULL, SHORT_COLOR_REPLACE_ARG},
        { OLD_COLOR_ARG, required_argument, NULL, LONG_OPT_ARG},
        { NEW_COLOR_ARG, required_argument, NULL, LONG_OPT_ARG}, 
        { SPLIT_ARG, no_argument, NULL, SHORT_SPLIT_ARG}, 
        { NUMBER_X_ARG, required_argument, NULL, LONG_OPT_ARG},
        { NUMBER_Y_ARG, required_argument, NULL, LONG_OPT_ARG},
        { THICKNESS_ARG, required_argument, NULL, LONG_OPT_ARG}, 
        { COLOR_ARG, required_argument, NULL, LONG_OPT_ARG},
        { 0, 0, 0, 0}};
    int opt;
    int long_index;
    opt = getopt_long(argc, argv, SHORT_OPTSTRING, long_opts, &long_index);
    while(opt != -1){
        // printf("!%d %c! %s\n",opt, opt, optarg);
        switch(opt){
            case NO_ARGUMENT_VALUE:{
                leave(NO_ARGUMENT_VALUE_ERROR, ARGUMENT_ERROR_CODE);
                break;
            }

            case UNKNOWN_ARGUMENT:{
                leave(UNKNOWN_ARGUMENT_ERROR, ARGUMENT_ERROR_CODE);
                break;
            }
            
            case SHORT_HELP_ARG:{
                print_help();
                exit(0);
                break;
            }

            case SHORT_INPUT_ARG:{
                args.input_file = strdup(optarg);
                break;
            }

            case SHORT_OUTPUT_ARG:{
                args.output_file = strdup(optarg);
                break;
            }

            case SHORT_MIRROR_ARG:{
                args.mirror = 1;
                break;
            }

            case SHORT_COPY_ARG:{
                args.copy = 1;
                break;
            }

            case SHORT_COLOR_REPLACE_ARG:{
                args.color_replace = 1;
                break;
            }
            
            case SHORT_SPLIT_ARG:{
                args.split = 1;
                break;
            }

            case LONG_OPT_ARG:{
                if (!strcmp(AXIS_ARG, long_opts[long_index].name)){
                    args.mirror_axis = strdup(optarg);
                    break;
                }

                if (!strcmp(LEFT_UP_ARG, long_opts[long_index].name)){
                    args.left_up = strdup(optarg);
                    break;
                }

                if (!strcmp(RIGHT_DOWN_ARG, long_opts[long_index].name)){
                    args.right_down = strdup(optarg);
                    break;
                }

                if (!strcmp(DEST_LEFT_UP_ARG, long_opts[long_index].name)){
                    args.dest_left_up = strdup(optarg);
                    break;
                }

                if (!strcmp(OLD_COLOR_ARG, long_opts[long_index].name)){
                    args.old_color = strdup(optarg);
                    break;
                }

                if (!strcmp(NEW_COLOR_ARG, long_opts[long_index].name)){
                    args.new_color = strdup(optarg);
                    break;
                }

                if (!strcmp(NUMBER_X_ARG, long_opts[long_index].name)){
                    args.number_x = strdup(optarg);
                    break;
                }

                if (!strcmp(NUMBER_Y_ARG, long_opts[long_index].name)){
                    args.number_y = strdup(optarg);
                    break;
                }
                
                if (!strcmp(THICKNESS_ARG, long_opts[long_index].name)){
                    args.thickness = strdup(optarg);
                    break;
                }

                if (!strcmp(COLOR_ARG, long_opts[long_index].name)){
                    args.color = strdup(optarg);
                    break;
                }


            }
        }
        opt = getopt_long(argc, argv, SHORT_OPTSTRING, long_opts, &long_index);
    }

    if(!args.input_file){
        if(optind < argc)
            args.input_file = strdup(argv[argc-1]);
        else
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }
    if(!args.output_file){
        args.output_file = strdup(DEFAULT_OUTPUT_FILE);
    }

    return args;
}

point_t get_coords_from_string(char* coords_arg){
    char coords_str[strlen(coords_arg)];
    strcpy(coords_str, coords_arg);
    size_t max_groups = REGEX_COORDS_GROUPS;
    regmatch_t group_array[max_groups];
    regex_t regex_compiled;
    if(regcomp(&regex_compiled, REGEX_COORDS, REG_EXTENDED))
        leave(REGEX_COMPILE_ERROR, REGEX_ERROR_CODE);

    if(regexec(&regex_compiled, coords_str, max_groups, group_array, 0))
        leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);

    coords_str[group_array[1].rm_eo] = STR_END;
    int x = atoi(coords_str + group_array[1].rm_so);
    int y = atoi(coords_str + group_array[2].rm_so);
    point_t coords = {x,y};
    regfree(&regex_compiled);
    return coords;
}

rgb_t get_color_from_string(char* color_arg){
    char color_str[strlen(color_arg)];
    strcpy(color_str, color_arg);
    size_t max_groups = REGEX_COLOR_GROUPS;
    regmatch_t group_array[max_groups];
    regex_t regex_compiled;

    if(regcomp(&regex_compiled, REGEX_COLOR, REG_EXTENDED))
        leave(REGEX_COMPILE_ERROR, REGEX_ERROR_CODE);

    if(regexec(&regex_compiled, color_str, max_groups, group_array, 0))
        leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);
    color_str[group_array[1].rm_eo] = STR_END;
    color_str[group_array[2].rm_eo] = STR_END;

    rgb_t color;
    color.r = (unsigned char)atoi(color_str + group_array[1].rm_so);
    color.g = (unsigned char)atoi(color_str + group_array[2].rm_so);
    color.b = (unsigned char)atoi(color_str + group_array[3].rm_so);
    regfree(&regex_compiled);
    return color;
}

int get_int_from_string(char* num_string){
    if(isdigit(num_string[0]) || num_string[0] == '-'){
        for(size_t i = 1; i < sizeof(num_string[0]); i++){
            if(!isdigit(num_string[i]))
                leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);
        }
    }else
        leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);
    int num = atoi(num_string);
    return num;
}


void check_args(args_t input_args){
    if(!strcmp(input_args.input_file, input_args.output_file))
        leave(SAME_FILENAME_ERROR, ARGUMENT_ERROR_CODE);

    if(input_args.mirror + input_args.copy + input_args.color_replace + input_args.split + input_args.info + input_args.ornament != 1)
        leave(MAIN_ARGS_NUMBER_ERROR, ARGUMENT_ERROR_CODE);

    if(input_args.mirror){
        if(!input_args.mirror_axis || !input_args.left_up || !input_args.right_down)
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }

    if(input_args.copy){
        if (!input_args.left_up || !input_args.right_down || !input_args.dest_left_up)
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }
    
    if(input_args.color_replace){
        if (!input_args.old_color || !input_args.new_color)
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }

    if(input_args.split){
        if (!input_args.number_x || !input_args.number_y || !input_args.thickness || !input_args.color)
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }

    if(input_args.ornament){
        if (!input_args.color || !input_args.thickness)
            leave(NOT_ALL_ARGUMENTS_ERROR, ARGUMENT_ERROR_CODE);
    }

}

pargs_t process_arguments(args_t input_args){
    check_args(input_args);
    pargs_t processed_args;
    processed_args.info = input_args.info;
    processed_args.input_file = input_args.input_file;
    processed_args.output_file = input_args.output_file;
    processed_args.mirror = input_args.mirror;
    processed_args.copy = input_args.copy;
    processed_args.color_replace = input_args.color_replace;
    processed_args.split = input_args.split;
    processed_args.ornament = input_args.ornament;

    if(input_args.mirror_axis){
        if(!strcmp(input_args.mirror_axis, "x") || !strcmp(input_args.mirror_axis, "y"))
            processed_args.mirror_axis = input_args.mirror_axis[0];
        else
            leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);
    }

    if(input_args.left_up && input_args.right_down){
        processed_args.left_up = get_coords_from_string(input_args.left_up);
        processed_args.right_down = get_coords_from_string(input_args.right_down);
    }

    if(input_args.dest_left_up)
        processed_args.dest_left_up = get_coords_from_string(input_args.dest_left_up);

    if(input_args.old_color && input_args.new_color){
        processed_args.old_color = get_color_from_string(input_args.old_color);
        processed_args.new_color = get_color_from_string(input_args.new_color);
    }

    if(input_args.number_x && input_args.number_y && input_args.thickness && input_args.color){
        int number_x = get_int_from_string(input_args.number_x);
        int number_y = get_int_from_string(input_args.number_y);
        int thickness_num = get_int_from_string(input_args.thickness);
        
        if(number_x < 2 || number_y < 2 || thickness_num < 0)
            leave(ARGUMENT_FORMAT_ERROR, ARGUMENT_ERROR_CODE);

        processed_args.number_x = (size_t)number_x;
        processed_args.number_y = (size_t)number_y;
        processed_args.thickness = (size_t)thickness_num;
        processed_args.color = get_color_from_string(input_args.color);
    }
    if (input_args.ornament){
        int thickness_num = get_int_from_string(input_args.thickness);
        processed_args.color = get_color_from_string(input_args.color);
        processed_args.thickness = (size_t)thickness_num;
    }
    return processed_args;
}
