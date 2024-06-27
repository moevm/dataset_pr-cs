#include "check_args.h"
#include "stdio.h"

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

int check_natural_nums(args_t args){
    int first_condition = !args.triangle || check_for_regex(args.thickness, REGEX_NATURAL_NUM);
    int second_condition =!args.collage || 
    (check_for_regex(args.number_x, REGEX_NATURAL_NUM) && check_for_regex(args.number_y, REGEX_NATURAL_NUM));

    return first_condition && second_condition;
}

int check_coordinates(args_t args){
    return !args.triangle || check_for_regex(args.points, REGEX_TRIANGLE_POINTS);
}

int check_colors(args_t args){
    int first_condition = (!args.fill && !args.fill_color) || (!args.triangle) ||
    (args.fill && check_for_regex(args.fill_color, REGEX_COLOR));

    int second_condition = !args.triangle || check_for_regex(args.color, REGEX_COLOR);

    int third_condition = (!args.biggest_rect) ||
    (check_for_regex(args.old_color, REGEX_COLOR) && check_for_regex(args.new_color, REGEX_COLOR));

    return first_condition && second_condition && third_condition;
}

int check_args(args_t args){
    int answers = 0;
    int selected_functions_count = args.info_flag + args.triangle + args.biggest_rect + args.collage + args.gamma;

    if (selected_functions_count != 1)
        panic(SELECTED_FUNCTIONS_COUNT_ERROR);

    answers += !check_natural_nums(args);
    answers += !check_coordinates(args);
    answers += !check_colors(args);
    answers += !strcmp(args.input_file, args.output_file);

    if (answers)
        panic(ARG_VAL_ERROR);
}