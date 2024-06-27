#include "validate.h"

int validate_for_regex(char* str, char* regex_template){
	int regex_answer;
    regex_t regex;

	if (!str){
		return 0;
	}

	regex_answer = regcomp(&regex, regex_template, REG_EXTENDED);

	if (regex_answer){
        panic(REGCOMP_ERROR);
	}

    regex_answer = regexec(&regex, str, 0, NULL, 0);
	regfree(&regex);
    return regex_answer != REG_NOMATCH;

}

int validate_axis_arg(func_param_args_t args){
	return !args.mirror || !strcmp(args.axis, AXIS_FIRST_VAL) || !strcmp(args.axis, AXIS_SECOND_VAL);
}

int validate_coords_arg(func_param_args_t args){
	int first_condition = (!args.mirror && !args.rect && !args.paving) ||
		(validate_for_regex(args.left_up, REGEX_COORDS_CHECK) &&
		 validate_for_regex(args.right_down, REGEX_COORDS_CHECK));

	int second_condition = (!args.pentagram && !args.hexagon) ||
		validate_for_regex(args.center, REGEX_COORDS_CHECK);

	return first_condition && second_condition; 
}

int validate_natural_num_arg(func_param_args_t args){
	int first_condition = (!args.rect && !args.pentagram && !args.hexagon) ||
		validate_for_regex(args.thickness, REGEX_NATURAL_CHECK);
	
	int second_condition = (!args.pentagram && !args.hexagon) ||
		validate_for_regex(args.radius, REGEX_NATURAL_CHECK);

	return first_condition && second_condition;
}

int validate_color_arg(func_param_args_t args){
	int first_condition = (!args.rect && !args.pentagram && !args.hexagon) ||
		validate_for_regex(args.color, REGEX_COLOR_CHECK);

	int second_condition = (!args.fill && !args.fill_color) || (!args.rect && !args.hexagon) ||
		(args.fill && validate_for_regex(args.fill_color, REGEX_COLOR_CHECK));
	
	return first_condition && second_condition;
}

void validate_func_param_args(func_param_args_t args){
	int validate_answers = 0;
	int main_funcs = args.mirror + args.pentagram + args.rect + args.hexagon + args.info + args.paving;

	if (main_funcs != 1){
		panic(MAIN_FUNCTION_COUNT_ERROR);
	}

	validate_answers += !validate_axis_arg(args);
	validate_answers += !validate_coords_arg(args);
	validate_answers += !validate_natural_num_arg(args);
	validate_answers += !validate_color_arg(args);

	if (validate_answers){
		panic(ARG_FORMAT_ERROR);
	}
}