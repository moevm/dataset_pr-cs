
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>
#include "structures.h"
#include "actions.h"
#include "files_action.h"
#include "checkers.h"

char *find_value(Element *dict, int len, char *key);
void check_output_and_input_match(char* input, char* output);
int check_extra_option(Element *dict, int len_dict);
void check_flags(Element *dict, int len_dict, int *input_flag, int *output_flag, int *info_flag, int *help_flag, int *squared_lines_flag, int *side_size_flag, int *left_up_flag, int *right_down_flag, int *rgbfilter_flag, int *component_name_flag, int *component_value_flag, int *thickness_flag, int *color_flag, int *fill_flag, int *fill_color_flag, int *rotate_flag, int *angle_flag, int *contr_f, int *alpha_f, int *betha_f);
char *find_main_option(Element *dict, int len_dict, int *input_flag, int *output_flag, int *info_flag, int *help_flag, int *
squared_lines_flag,int *side_size_flag, int *left_up_flag, int *right_down_flag, int *rgbfilter_flag, int
                       *component_name_flag, int *component_value_flag, int *thickness_flag, int *color_flag, int *fill_flag, int
                       *fill_color_flag, int *rotate_flag, int *angle_flag, int *contr_f, int *alpha_f, int *betha_f);
void run(Element *dict, int len_dict);

