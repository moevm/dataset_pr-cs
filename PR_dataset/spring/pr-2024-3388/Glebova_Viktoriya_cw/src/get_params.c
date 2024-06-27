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
        sscanf(tmp, "%d", &(answer[i - 1]));
        free(tmp);
    }

    return answer;
}

params_t get_params(args_t args){
    params_t params;
    int* color = NULL;
    int* coords = NULL;

    params.input_file = args.input_file;
    params.output_file = args.output_file;
    params.info_flag = args.info_flag;
    params.circle = args.circle;
    params.rgb_filter = args.rgb_filter;
    params.split = args.split;
    params.fill = args.fill;
    params.gamma = args.gamma;
    
    if (args.circle || args.split){
        color = get_nums_from_regex(args.color, 3, REGEX_COLOR);

        params.thickness = atoi(args.thickness)/RADIUS_KOEFF;
        params.color = (rgb_t){color[0], color[1], color[2]};

        free(color);
        color = NULL;
    }

    if (args.circle){
        coords = get_nums_from_regex(args.center, 2, REGEX_COORDINATES);
        params.center = (coords_t){coords[0], coords[1]};
        if (args.fill){
            color = get_nums_from_regex(args.fill_color, 3, REGEX_COLOR);
            params.fill_color = (rgb_t){color[0], color[1], color[2]};
        }
        
        params.radius = atoi(args.radius);

        free(coords);
        free(color);
    }

    if (args.rgb_filter){
        params.component_name = args.component_name;
        params.component_value = atoi(args.component_value);
    }

    if (args.split){
        params.number_x = atoi(args.number_x);
        params.number_y = atoi(args.number_y);
    }
    if (args.gamma){
        params.value = atof(args.value);
        if (params.value <= 0){
            panic(ARG_VAL_ERROR);
        }
    }

    return params;
}