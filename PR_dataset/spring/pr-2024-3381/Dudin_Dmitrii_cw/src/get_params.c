#include "get_params.h"

regmatch_t* get_capture_groups(char* str, char* regex_template){
    int regex_answer;
    regex_t regex;
    regmatch_t *match = malloc(MAX_CAPTURE_GROUP*sizeof(regmatch_t));

	regex_answer = regcomp(&regex, regex_template, REG_EXTENDED);

	if (regex_answer)
        panic(REGCOMP_ERROR);

    regex_answer = regexec(&regex, str, MAX_CAPTURE_GROUP, match, 0);
	regfree(&regex);

    return match;
}

int* get_nums_from_regex(char* str, int count, char* regex_template){
    regmatch_t* match = get_capture_groups(str, regex_template);
    char* tmp;
    int* answer = malloc(count*sizeof(int));

    for (size_t i = 1; i <= count; i++){
        tmp = calloc(match[i].rm_eo - match[i].rm_so + 1, sizeof(char));
        if (!tmp)
            panic(ALLOC_ERROR);

        for (size_t j = match[i].rm_so; j <= match[i].rm_eo; j++)
            tmp[j - match[i].rm_so] = str[j];
        answer[i - 1] = atoi(tmp);
        free(tmp);
    }

    return answer;
}

void set_points(args_t args, params_t* params){
    int* coordinates = get_nums_from_regex(args.points, 6, REGEX_TRIANGLE_POINTS);

    for (size_t i = 0; i < 3; i++){
        (params->points)[i].x = coordinates[i*2];
        (params->points)[i].y = coordinates[i*2 + 1];
    }

    free(coordinates);
}

void set_rect_colors(args_t args, params_t* params){
    int* color = get_nums_from_regex(args.old_color, 3, REGEX_COLOR);

    params->old_color.r = color[0];
    params->old_color.g = color[1];
    params->old_color.b = color[2];

    color = get_nums_from_regex(args.new_color, 3, REGEX_COLOR);

    params->new_color.r = color[0];
    params->new_color.g = color[1];
    params->new_color.b = color[2];

    free(color);
}

void set_triangle_color(args_t args, params_t* params){
    int* color = get_nums_from_regex(args.color, 3, REGEX_COLOR);

    params->color.r = color[0];
    params->color.g = color[1];
    params->color.b = color[2];

    if (!args.fill){
        free(color);
        return;
    }

    color = get_nums_from_regex(args.fill_color, 3, REGEX_COLOR);

    params->fill_color.r = color[0];
    params->fill_color.g = color[1];
    params->fill_color.b = color[2];

    free(color);
}

params_t get_params(args_t args){
    params_t params;

    params.input_file = args.input_file;
    params.output_file = args.output_file;
    params.info_flag = args.info_flag;
    params.triangle = args.triangle;
    params.biggest_rect = args.biggest_rect;
    params.collage = args.collage;
    params.fill = args.fill;
    params.gamma = args.gamma;
    
    if (args.triangle){
        set_points(args, &params);
        set_triangle_color(args, &params);
        params.thickness = atoi(args.thickness);
    }

    if (args.biggest_rect)
        set_rect_colors(args, &params);

    if (args.collage){
        params.number_x = atoi(args.number_x);
        params.number_y = atoi(args.number_y);
    }

    if (args.gamma){
        params.value = atof(args.value);
        if (params.value <=0) {
            panic(NO_ARG_VAL_ERROR);
        }
    }

    return params;
}