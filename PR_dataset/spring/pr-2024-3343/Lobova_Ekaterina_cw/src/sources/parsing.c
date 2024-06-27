#include "../include/parsing.h"

int is_number(const char* str) {
    int len = strlen(str);
    if (str[0] == '-') len -=1;
    int has_digit = 0;
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            has_digit+= 1;
        }
        str++;
    }
    return has_digit == len;
}

void raise_error(Configs* config, char* message, int return_code){
	free_memory(config);
	fprintf(stderr, message, return_code);
	exit(return_code);
}

void init_configs(Configs* config){
	config->info = 0;
	config->input = NULL;
	
	config->squared_lines = (Squared_lines*)malloc(sizeof(Squared_lines));
	(config->squared_lines)->n = 0;
	(config->squared_lines)->coordinates = 0;
	(config->squared_lines)->left = 0;
	(config->squared_lines)->up = 0;
	(config->squared_lines)->size = -1;
	(config->squared_lines)->thickness = -1;
	(config->squared_lines)->thickness_color = NULL;
	(config->squared_lines)->fill = 0;
	(config->squared_lines)->fill_color = NULL;
	
	config->rgbfilter = (Rgbfilter*)malloc(sizeof(Rgbfilter));
	(config->rgbfilter)->n = 0;
	(config->rgbfilter)->component_name = ' ';
	(config->rgbfilter)->component_value = 256;
	
	config->rotate = (Rotate*)malloc(sizeof(Rotate));
	(config->rotate)->n = 0;
	(config->rotate)->coordinates = 0;
	(config->rotate)->left = 0;
	(config->rotate)->up = 0;
	(config->rotate)->right = 0;
	(config->rotate)->down = 0;
	(config->rotate)->angle = 0;
	
	config->rhombus = (Rhombus*)malloc(sizeof(Rhombus));
	(config->rhombus)->n = 0;
	(config->rhombus)->coordinates = 0;
	(config->rhombus)->size = -1;
	(config->rhombus)->left = 0;
	(config->rhombus)->up = 0;
	(config->rhombus)->fill_color = NULL;
	config->output = NULL;
	
}

void free_memory(Configs* config){
	if (config->input != NULL) free(config->input);
	if (config->output != NULL) free(config->output);
	if (config->rgbfilter != NULL) free(config->rgbfilter);
	if (config->squared_lines != NULL){
		if ((config->squared_lines)->thickness_color != NULL) free((config->squared_lines)->thickness_color);
		if ((config->squared_lines)->fill_color != NULL) free((config->squared_lines)->fill_color);
		free(config->squared_lines);
	} 
	if (config->rhombus != NULL) {
		if ((config->rhombus)->fill_color != NULL) free((config->rhombus)->fill_color);
		free(config->rhombus);
	}
	if (config->rotate != NULL) free(config->rotate);
}

void parsing_coordinates(const char* flag, Configs* config, const char* optarg){
	int x, y;
	if (sscanf(optarg, "%d.%d", &x, &y) != 2){
		raise_error(config, "incorrect form of agrumeng for flag\n", 41);
	} else {
		if (strcmp(flag, "left_up") == 0){
			(config->squared_lines)->coordinates = 1;
			(config->squared_lines)->left = x;
			(config->squared_lines)->up = y;
			(config->rotate)->left = x;
			(config->rotate)->up = y;
		} else {
			if (strcmp(flag, "right_down") == 0){
				(config->rotate)->coordinates = 1;
				(config->rotate)->right = x;
				(config->rotate)->down = y;
			} else {
				(config->rhombus)->coordinates = 1;
				(config->rhombus)->left = x;
				(config->rhombus)->up = y;
			}	
		}
	}	
}

void parsing_angle(Configs* config, const char* optarg){
	if (strcmp(optarg,"90") == 0 || strcmp(optarg,"180") == 0 || strcmp(optarg,"270") == 0){
		(config->rotate)->angle = atoi(optarg);
	} else {
		raise_error(config, "argument for --agngle must be one of 90, 180 or 270\n", 41);
	} 
}

void parsing_number(const char* flag, Configs* config, const char* optarg){
	if (is_number(optarg) && optarg[0]!='-'){
		if (strcmp(flag, "thickness")==0)
			(config->squared_lines)->thickness = atoi(optarg);
		else{
			if (strcmp(flag, "side_size")==0)
				(config->squared_lines)->size = atoi(optarg);
			else{
				(config->rhombus)->size = atoi(optarg);
			} 
		}
			
	} else{
		raise_error(config, "incorrect value of the argument\n", 41);
	}
}

void parsing_color(const char* flag, Configs* config, const char* optarg){
	int  r, g, b;
	if (sscanf(optarg, "%d.%d.%d", &r, &g, &b)!=3){
		raise_error(config, "incorrect form of agrument for flag\n", 41);
	} else {
		if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255){
			if (strcmp(flag, "color") == 0){
				(config->squared_lines)->thickness_color = (Color*)malloc(sizeof(Color));
				((config->squared_lines)->thickness_color)->r = r;
				((config->squared_lines)->thickness_color)->g = g;
				((config->squared_lines)->thickness_color)->b = b;
			} else {
				(config->squared_lines)->fill_color = (Color*)malloc(sizeof(Color));
				((config->squared_lines)->fill_color)->r = r;
				((config->squared_lines)->fill_color)->g = g;
				((config->squared_lines)->fill_color)->b = b;
				
				(config->rhombus)->fill_color = (Color*)malloc(sizeof(Color));
				((config->rhombus)->fill_color)->r = r;
				((config->rhombus)->fill_color)->g = g;
				((config->rhombus)->fill_color)->b = b;
			}
		} else {
			raise_error(config, "incorrect value of the color component\n", 41);
		}
	}
}

void parsing_component_name(Configs* config, const char* optarg){
	if (strcmp(optarg,"red") == 0 || strcmp(optarg ,"blue") == 0 || strcmp(optarg,"green") == 0){
		(config->rgbfilter)->component_name = optarg[0];
	}else{
		raise_error(config, "the argument of the component_name flag must have one of the following values: red, green, or blue\n", 41);
	}
}

void parsing_component_value(Configs* config, const char* optarg){
	if (is_number(optarg)){
		int num = atoi(optarg);
		if (num >= 0 && num <= 255){
			(config->rgbfilter)->component_value = num;
		}else{
			raise_error(config, "incorrect value of the color component\n", 41);
		}
	}else{
		raise_error(config, "incorrect value of the color component\n", 41);
	}
}
