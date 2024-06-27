#include "input_arguments.hpp"

arguments::arguments(){
	ishelp = false;
	isinfo = false;
	isfill = false;
	number = 0;
	x1 = -1;
	x2 = -1;
	y1 = -1;
	y2 = -1;
	length = 0;
	thickness = 0;
	type_exchange = 0;
	color[0] = -1;
	fill_color[0] = -1;
	input_path = NULL;
	output_path = strdup("out.png");
	if (output_path == NULL){
		std::cout <<  "Error: not enough memory\n";
		exit(48);
	}
}

arguments::~arguments(){
	if (input_path)
		free(input_path);
	if (output_path)
		free(output_path);
}

arguments *getarguments(int argc, char** argv){
	arguments *args = new arguments;
	if (args == NULL){
		std::cout <<  "Error: not enough memory\n";
		exit(48);
	}
	args->input_path = strdup(argv[argc - 1]);
	if (args->input_path == NULL){
		std::cout <<  "Error: not enough memory\n";
		exit(48);
	}
    const char* short_options = "hpSEFIl:r:s:t:c:C:fe:o:i:R";
	opterr = 0;
    const struct option long_options[] ={
			{"help", no_argument, NULL, 'h'},
			{"info", no_argument, NULL, 'p'},
			{"square", no_argument, NULL, 'S'},
			{"exchange", no_argument, NULL, 'E'},
			{"freq_color", no_argument, NULL, 'F'},
			{"inverse", no_argument, NULL, 'I'},
			{"left_up", required_argument, NULL, 'l'},
			{"right_down", required_argument, NULL, 'r'},
			{"side_size", required_argument, NULL, 's'},
			{"thickness", required_argument, NULL, 't'},
			{"color", required_argument, NULL, 'c'},
			{"fill_color", required_argument, NULL, 'C'},
			{"fill", no_argument, NULL, 'f'},
			{"exchange_type", required_argument, NULL, 'e' },
			{"output", required_argument, NULL, 'o' },
			{"input", required_argument, NULL, 'i' },
			{"rhombus", no_argument, NULL, 'R' },
			{NULL, 0, NULL, 0 }
    };
	int n, opt;
	while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
		switch (opt){
		case 'h': {
			args->ishelp = true;
			break;
		}
		case 'p': {
			args->isinfo = true;
			break;
		}
		case 'S': {
			if(args->number){
				std::cout << "More then one command entered\n";
				exit(41);
			}
			args->number = 1;
			break;
		}
		case 'E': {
			if(args->number){
				std::cout << "More then one command entered\n";
				exit(41);
			}
			args->number = 2;
			break;
		}
		case 'F': {
			if(args->number){
				std::cout << "More then one command entered\n";
				exit(41);
			}
			args->number = 3;
			break;
		}
		case 'I': {
			if(args->number){
				std::cout << "More then one command entered\n";
				exit(41);
			}
			args->number = 4;
			break;
		}
		case 'R': {
			if(args->number){
				std::cout << "More then one command entered\n";
				exit(41);
			}
			args->number = 5;
			break;
		}
		case 'l': {
			n = sscanf(optarg, "%d.%d", &args->x1, &args->y1);
			if (n != 2){
				std::cout << "Invalid point format\n";
				exit(41);
			}
			break;
		}
		case 'r': {
			n = sscanf(optarg, "%d.%d", &args->x2, &args->y2);
			if (n != 2){
				std::cout << "Invalid point format\n";
				exit(41);
			}
			break;
		}
		case 's': {
			n = sscanf(optarg, "%d", &args->length);
			if (n != 1 || args->length <= 0){
				std::cout << "Invalid side size format\n";
				exit(41);
			}
			if (args->length <= 0){
				std::cout << "Invalid side size value\n";
				exit(42);
			}
			break;
		}
		case 't': {
			n = sscanf(optarg, "%d", &args->thickness);
			if (n != 1){
				std::cout << "Invalid thickness format\n";
				exit(41);
			}
			if (args->thickness <= 0){
				std::cout << "Invalid thickness value\n";
				exit(42);
			}
		}
			break;
		case 'c': {
			n = sscanf(optarg, "%d.%d.%d", &args->color[0], &args->color[1], &args->color[2]);
			if (n != 3){
				std::cout << "Invalid color format\n";
				exit(41);
			}
			if(args->color[0] < 0 || args->color[0] > 255 || args->color[1] < 0 || args->color[1] > 255 || args->color[2] < 0 || args->color[2] > 255){
				std::cout << "Invalid color value\n";
				exit(42);
			}
			break;
		}
		case 'C': {
			n = sscanf(optarg, "%d.%d.%d", &args->fill_color[0], &args->fill_color[1], &args->fill_color[2]);
			if (n != 3){
				std::cout << "Invalid fill color format\n";
				exit(41);
			}
			if(args->fill_color[0] < 0 || args->fill_color[0] > 255 || args->fill_color[1] < 0 || args->fill_color[1] > 255 || args->fill_color[2] < 0 || args->fill_color[2] > 255){
				std::cout << "Invalid fill color value\n";
				exit(42);
			}
			break;
		}
		case 'f': {
			args->isfill = true;
			break;
		}
		case 'e': {
			if(strcmp(optarg, "clockwise") == 0)
				args->type_exchange = 1;
			else if(strcmp(optarg, "counterclockwise") == 0)
				args->type_exchange = 2;
			else if(strcmp(optarg, "diagonals") == 0)
				args->type_exchange = 3;
			else{
				std::cout << "Invalid exchange type\n";
				exit(42);
			}
			break;
		}
		case 'o': {
			free(args->output_path);
			args->output_path = strdup(optarg);
			if (args->output_path == NULL){
				std::cout <<  "Error: not enough memory\n";
				exit(48);
			}
			break;
		}
		case 'i': {
			free(args->input_path);
			args->input_path = strdup(optarg);
			if (args->input_path == NULL){
				std::cout <<  "Error: not enough memory\n";
				exit(48);
			}
			break;
		}
		default: {
			std::cout << "Unknown flag\n";
			exit(43);
		}
		}
	}

	if(!strcmp(args->input_path, args->output_path)){
		std::cout << "Input and output cannot have the same path\n";
		exit(49);
	}
	return args;
}
