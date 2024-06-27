#include "../include/main.h"

int main(int argc, char **argv) {
	printf(START_SENTENCE);
	Configs config;
	init_configs(&config);
	const char* shortOpts = "i:o:h!";
	const struct option longOpts[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "input", required_argument, NULL, 'i' },
		{ "output", required_argument, NULL, 'o' },
		{ "info", no_argument, NULL, '!'},
		{"squared_lines", no_argument, NULL, 0},
		{"rgbfilter",no_argument, NULL, 0},
		{"rotate", no_argument, NULL, 0},
		{"component_name", required_argument, NULL, 0},
		{"component_value", required_argument, NULL, 0},
		{"left_up", required_argument, NULL, 0},
		{"right_down", required_argument, NULL, 0},
		{"angle", required_argument, NULL, 0},
		{"side_size", required_argument, NULL, 0},
		{"thickness", required_argument, NULL, 0},
		{"color", required_argument, NULL, 0},
		{"fill", no_argument, NULL, 0},
		{"fill_color", required_argument, NULL, 0},
		{"square_rhombus", no_argument, NULL, 0},
		{"upper_vertex", required_argument, NULL, 0},
		{"size", required_argument, NULL, 0},
		{ NULL, 0, NULL, 0 }
	};
	int opt;
	int longIndex;
	struct Png image;
	while((opt = getopt_long(argc, argv, shortOpts, longOpts, &longIndex)) != -1){
		switch(opt){
			case 'i':
				if (config.input != NULL){
					free(config.input);
				}
				config.input = (char*)malloc((strlen(optarg)+1)*sizeof(char));
				strncpy(config.input, optarg, strlen(optarg));
				break;
			case 'o':
				if (config.output != NULL){
					free(config.output);
				}
				config.output = (char*)malloc((strlen(optarg)+1)*sizeof(char));
				strncpy(config.output, optarg, strlen(optarg));
				break;
			case 'h':
				printf(HELP);
				break;
			case '!':
				config.info = 1;
				break;	
			case '?':
				printf("found unknown option\n");
				free_memory(&config);
				return 0;
			case 0:
				if (longOpts[longIndex].name == "squared_lines"){
					(config.squared_lines)->n = 1;
				}
				if (longOpts[longIndex].name == "rgbfilter"){
					(config.rgbfilter)->n = 1;
				}
				if (longOpts[longIndex].name == "rotate"){
					(config.rotate)->n = 1; 
				}
				if (longOpts[longIndex].name == "square_rhombus"){
					(config.rhombus)->n = 1; 
				}
				if (longOpts[longIndex].name == "upper_vertex"){
					parsing_coordinates(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "size"){
					parsing_number(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "component_name"){
					parsing_component_name(&config, optarg);
				}
				if (longOpts[longIndex].name == "component_value"){
					parsing_component_value(&config, optarg);
				}
				if (longOpts[longIndex].name == "left_up"){
					parsing_coordinates(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "right_down"){
					parsing_coordinates(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "angle"){
					parsing_angle(&config, optarg);
				}
				if (longOpts[longIndex].name == "color" || longOpts[longIndex].name == "fill_color"){
					parsing_color(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "side_size"){
					parsing_number(longOpts[longIndex].name, &config, optarg);	
				}
				if (longOpts[longIndex].name == "thickness"){
					parsing_number(longOpts[longIndex].name, &config, optarg);
				}
				if (longOpts[longIndex].name == "fill"){
					(config.squared_lines)->fill = 1;
				}
				
		}
	}
	if (config.input == NULL && optind == argc - 1){
        	config.input = (char*)malloc((strlen(argv[argc - 1])+1)*sizeof(char));
  		strncpy(config.input, argv[argc - 1], strlen(argv[argc - 1]));
     	}
     	if (config.output == NULL){
     		config.output = (char*)malloc((strlen(DEFAULT_VALUE)+1)*sizeof(char));
     		strncpy(config.output, DEFAULT_VALUE, strlen(DEFAULT_VALUE));
     	} 
	process_file(&config, &image);
	return 0;
}
