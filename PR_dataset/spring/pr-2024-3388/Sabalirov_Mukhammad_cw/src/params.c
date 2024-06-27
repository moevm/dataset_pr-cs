#include "params.h"

regmatch_t* get_args_for_regex(char* str, char* regex_template){
	int regex_answer;
    regex_t regex;
    regmatch_t *match = malloc(CAPTURE_GROUP_COUNT*sizeof(regmatch_t));

	regex_answer = regcomp(&regex, regex_template, REG_EXTENDED);

	if (regex_answer){
        panic(REGCOMP_ERROR);
	}

    regex_answer = regexec(&regex, str, CAPTURE_GROUP_COUNT, match, 0);
	regfree(&regex);

    return match;
}

void set_axis(func_param_args_t args, func_params_t* params){
    if (args.axis){
        if (!strcmp(args.axis, AXIS_FIRST_VAL)){
            params->axis = X_AXIS_INT;
        }
        else{
            params->axis = Y_AXIS_INT;
        }
    }
    else{
        params->axis = NO_ARG;
    }
}

int get_nums_from_dot_format(char* str, int match_pos, char* regex_template){
    regmatch_t* match = get_args_for_regex(str, regex_template);
    char* buffer = malloc((strlen(str) + 1)*sizeof(char));
    int coord;
    sprintf(buffer, "%.*s", match[match_pos].rm_eo - match[match_pos].rm_so,
                            str + match[match_pos].rm_so);
    
    sscanf(buffer, "%d", &coord);
    free(buffer);

    return coord;
}

void set_coords(func_param_args_t args, func_params_t* params){
    if (args.mirror || args.rect || args.paving){
        params->left_up_x = get_nums_from_dot_format(args.left_up, X_MATCH_POS, REGEX_COORDS);
        params->left_up_y = get_nums_from_dot_format(args.left_up, Y_MATCH_POS, REGEX_COORDS);
        params->right_down_x = get_nums_from_dot_format(args.right_down, X_MATCH_POS, REGEX_COORDS);
        params->right_down_y = get_nums_from_dot_format(args.right_down, Y_MATCH_POS, REGEX_COORDS);
    }
    else{
        params->left_up_x = NO_ARG;
        params->left_up_y = NO_ARG;
        params->right_down_x = NO_ARG;
        params->right_down_y = NO_ARG;
    }

	if (args.pentagram || args.hexagon){
        params->center_x = get_nums_from_dot_format(args.center, X_MATCH_POS, REGEX_COORDS);
        params->center_y = get_nums_from_dot_format(args.center, Y_MATCH_POS, REGEX_COORDS);
    }
    else{
        params->center_x = NO_ARG;
        params->center_y = NO_ARG;
    }
		
}

void set_natural_num(func_param_args_t args, func_params_t* params){
    if (args.rect || args.pentagram || args.hexagon){
        sscanf(args.thickness, "%d", &(params->thickness));
    }
    else{
        params->thickness = NO_ARG;
    }

	if (args.pentagram || args.hexagon){
        sscanf(args.radius, "%d", &(params->radius));
    }
    else{
        params->radius = NO_ARG;
    }
}

void set_colors(func_param_args_t args, func_params_t* params){
    if (args.rect || args.pentagram || args.hexagon){
        params->color_r = get_nums_from_dot_format(args.color, R_MATCH_POS, REGEX_COLOR);
        params->color_g = get_nums_from_dot_format(args.color, G_MATCH_POS, REGEX_COLOR);
        params->color_b = get_nums_from_dot_format(args.color, B_MATCH_POS, REGEX_COLOR);
    }
    else{
        params->color_r = NO_ARG;
        params->color_g = NO_ARG;
        params->color_b = NO_ARG;
    }

    if ((args.rect || args.hexagon) && args.fill){
        params->fill_color_r = get_nums_from_dot_format(args.fill_color, R_MATCH_POS, REGEX_COLOR);
        params->fill_color_g = get_nums_from_dot_format(args.fill_color, G_MATCH_POS, REGEX_COLOR);
        params->fill_color_b = get_nums_from_dot_format(args.fill_color, B_MATCH_POS, REGEX_COLOR);
    }
    else{
        params->fill_color_r = NO_ARG;
        params->fill_color_g = NO_ARG;
        params->fill_color_b = NO_ARG;
    }
}

func_params_t* set_and_get_func_params(func_param_args_t args){
    func_params_t* params = malloc(sizeof(func_params_t));
	
    params->mirror = args.mirror;
    params->pentagram = args.pentagram;
    params->rect = args.rect;
    params->hexagon = args.hexagon;
    params->fill = args.fill;
    params->info = args.info;
    params->input = args.input;
    params->output = args.output;
    params->paving = args.paving;

    set_axis(args, params);
    set_coords(args, params);
    set_natural_num(args, params);
    set_colors(args, params);

    return params;
}