#include "processing.h"

void input_output_flag_processing(int * input_output_flag, char * file_name, char * optarg){
	file_name = optarg;
	(*input_output_flag)++;
}

void check_action_flag(int * action_flag, int * was_input_action_flag){
	if (!(*action_flag)){
		*action_flag = 1;
		(*was_input_action_flag)++;
	}
}

void check_reading_single_param(int * result_assignment, char * optarg, int * params_flag, int * param){
	*result_assignment = sscanf(optarg, "%d", param);
	if (!(*result_assignment)){
		failure("Error input parram");
	}
	(*params_flag)++;
}

void check_reading_params_coords(int * result_assignment, char * optarg, int * params_flag, int * x, int * y){
	*result_assignment = sscanf(optarg, "%d.%d", x, y);
	if ((*result_assignment) != 2){
		failure("Error input parram");
	}
	(*params_flag)++;
}

void check_reading_params_color(int * result_assignment, char * optarg, int * params_flag, int * action_flag, int * red_comp, int * blue_comp, int * green_comp){
	*result_assignment = sscanf(optarg, "%d.%d.%d", red_comp, green_comp, blue_comp);
	if ((*result_assignment) != 3){
		failure("Error input parram");
	}
	(*params_flag)++;
	(*action_flag)++;
}

void processing_input_output(int argc, char ** argv, int * input_output_flag, char * file_name){
	if ((*input_output_flag) == 1){
		file_name = argv[argc-1];
		++(*input_output_flag);
	}
}

void processing_info_flag(int argc, char ** argv, int input_output_flag, char * file_name){
	if (input_output_flag == 0){
		file_name = argv[argc-1];
	}
	image_bmp * image = (image_bmp*)malloc(sizeof(image_bmp));
	if (!image) failure("Error to allocate memory"); 
	read_image_bmp(file_name, image);
	print_info_header(image->dheader);	
	exit(SUCESSFULL);
}

void processing_inverse_action(int inverse_flag, int inverse_params_flag, int * x_start, int * y_start, int * x_end, int * y_end, image_bmp * image){
	if (inverse_flag && inverse_params_flag == 2){
		check_coords(image, x_start, x_end, y_start, y_end);
		reverse_color(image, *x_start, *y_start, *x_end, *y_end);
	}else if (inverse_flag && inverse_params_flag != 2) failure("Input params!");
}

void processing_gray_action(int gray_flag, int gray_params_flag, int * x_start, int * y_start, int * x_end, int * y_end, image_bmp * image){
	if (gray_flag && gray_params_flag == 2){
		check_coords(image, x_start, x_end, y_start, y_end);
		gray_image(image, *x_start, *y_start, *x_end, *y_end);
	}else if (gray_flag && gray_params_flag != 2) failure("Input params!"); 
}

void processing_line_action(int line_flag, int line_flags, int * x_start_line, int * y_start_line, int * x_end_line, int * y_end_line, int red_comp, int green_comp, int blue_comp, int thickness, rgb color,image_bmp * image){
	if (line_flag && line_flags == 4){
		check_coords(image, x_start_line, x_end_line, y_start_line, y_end_line);
		check_line_metainfo(&color, red_comp, green_comp, blue_comp);
		if (thickness <= 0) failure("Bad thickness");
		draw_line(image, *x_start_line, *y_start_line, *x_end_line, *y_end_line, color, thickness);
	}else if (line_flag && line_flags != 4) failure("Input params!");
}

void processing_ramka_action(int ramka_flag, int color_flag, int red_comp, int green_comp, int blue_comp, rgb * color, int thickness, char * output_file_name, image_bmp * image){
	if (ramka_flag){
		if (!color_flag) failure("Input color");
		check_line_metainfo(color, red_comp, green_comp, blue_comp);
		if (thickness <= 0) failure("Bad thickness");
		draw_ramka(image, thickness, *color, output_file_name);
		exit(SUCESSFULL);
	}
}

void processing_resize_action(int resize_flag, int resize_flags, int color_flag,int up_resize, int down_resize, int right_resize, int left_resize, char * output_file_name, rgb * color, int red_comp, int green_comp, int blue_comp, image_bmp * image){
	if (resize_flag && resize_flags > 0){
		if (up_resize > 0 || down_resize > 0 || right_resize > 0 || left_resize > 0){
			if (!color_flag) failure("Input color");
			check_line_metainfo(color, red_comp, green_comp, blue_comp);
		}
		resize(image, left_resize, right_resize, up_resize, down_resize, output_file_name, *color);
	}else if (resize_flag && resize_flags == 0) failure("Input params!");
}

void initialization_longopts(struct option * longopts){
	struct option longoptions[] = {
	    {OPTION_INPUT},
	    {OPTION_OUTPUT},
	    {OPTION_INVERSE},
	    {OPTION_GRAY},
	    {OPTION_LINE},
	    {OPTION_RESIZE},
	    {OPTION_LEFT},
	    {OPTION_RIGHT},
	    {OPTION_ABOVE},
	    {OPTION_BELOW},
	    {OPTION_START},
	    {OPTION_END},
	    {OPTION_COLOR},
	    {OPTION_THICKNESS},
	    {OPTION_LEFT_UP},
	    {OPTION_RIGHT_DOWN},
	    {OPTION_HELP},
	    {OPTION_INFO},
	    {OPTION_RAMKA},
	    {OPTION_NULL}
	};
	longopts = longoptions;
}

void check_count_args(int argc){
	if (argc == 1){
		help_display();
		exit(SUCESSFULL);
	}
}

int processing(int argc, char ** argv){

	check_count_args(argc);

	char *opts = SHORT_OPTIONS;
	int longidx;
	   
	struct option * longopts = (struct option *)malloc(sizeof(struct option));
	initialization_longopts(longopts);
	   
	int option = getopt_long(argc, argv, opts, longopts, &longidx);

	char * file_name = (char*)malloc(sizeof(char)*SIZE_FILE_NAME);
	char * output_file_name = (char*)malloc(sizeof(char)*SIZE_FILE_NAME);

	rgb color = {0,0,0};

	int x_start = -1;
	int y_start = -1;
	int x_end = -1;
	int y_end = -1;

	int x_start_line = -1;
	int y_start_line = -1;
	int x_end_line = -1;
	int y_end_line = -1; 

	int right_resize = 0;
	int left_resize = 0;
	int up_resize = 0;
	int down_resize = 0;


	int red_component_color;
	int green_component_color;
	int blue_component_color;

	int thickness = 0;

	int inverse_flag = 0;
	int gray_flag = 0;
	int info_flag = 0;
	int line_flag = 0;
	int resize_flag = 0;

	int input_output_flag = 0;
	int was_input_action_flag = 0;

	int color_flag = 0;
	int result_assignment = 0;
	int inverse_and_gray_flags = 0;
	int line_flags = 0;
	int resize_flags = 0;
	int ramka_flag = 0;

	while(option != END_OPTIONS){
		switch(option){
			case 'i':{
				input_output_flag_processing(&input_output_flag, file_name, optarg);	
				break;
			}
			case 'o':{
				input_output_flag_processing(&input_output_flag, output_file_name, optarg);	
				break;
			}
			case 'r':{
				check_action_flag(&inverse_flag,&was_input_action_flag);
				break;
			}
			case 'z':{
				check_action_flag(&resize_flag,&was_input_action_flag);
				break;
			}
			case 'g':{
				check_action_flag(&gray_flag,&was_input_action_flag);
				break;
			}
			case 'n':{
				check_action_flag(&ramka_flag,&was_input_action_flag);
				break;
			}
			case 'I':{
				check_action_flag(&info_flag,&was_input_action_flag);
				break;
			}
			case 'l':{
				check_action_flag(&line_flag,&was_input_action_flag);
				break;
			}
			case 'h':{
				help_display();
				return SUCESSFULL;
			}
			case 'L':{
				check_reading_params_coords(&result_assignment,optarg,&inverse_and_gray_flags,&x_start, &y_start);
               break;
			}
			case 'R':{
				check_reading_params_coords(&result_assignment,optarg,&inverse_and_gray_flags,&x_end, &y_end);
	            break;
			}
			case 's':{
				check_reading_params_coords(&result_assignment,optarg,&inverse_and_gray_flags,&x_start_line, &y_start_line);
				break;
			}
			case 'e':{
				check_reading_params_coords(&result_assignment,optarg,&inverse_and_gray_flags,&x_end_line, &y_end_line);
				break;
			}
			case 'c':{
				check_reading_params_color(&result_assignment,optarg, &color_flag, &line_flags,&red_component_color,&blue_component_color,&green_component_color);
				break;
			}
			case 't':{
				check_reading_single_param(&result_assignment,optarg,&line_flags,&thickness);
				break;
			}
			case 'f':{
				check_reading_single_param(&result_assignment,optarg,&resize_flags,&left_resize);
				break;
			}
			case 'G':{
				check_reading_single_param(&result_assignment,optarg,&resize_flags,&right_resize);
				break;
			}
			case 'a':{
				check_reading_single_param(&result_assignment,optarg,&resize_flags,&up_resize);
				break;
			}
			case 'b':{
				check_reading_single_param(&result_assignment,optarg,&resize_flags,&down_resize);
				break;
			}
			case UNKNOWN_OPTION:{
				printf("Programm will skip non-existent args\n");
			}
		}
		option = getopt_long(argc, argv, opts, longopts, &longidx);	
	}

	processing_input_output(argc, argv, &input_output_flag, file_name);

	processing_info_flag(argc, argv, input_output_flag, file_name);

	if (input_output_flag != SUCESSFULLY_INPUT_OUTPUT) failure("Enter the name of the input file and output file");

	image_bmp * image = (image_bmp*)malloc(sizeof(image_bmp));

	if (!image) failure("Error to allocate memory"); 

	read_image_bmp(file_name, image);	

	processing_inverse_action(inverse_flag, inverse_and_gray_flags, &x_start, &y_start, &x_end, &y_end, image);

	processing_gray_action(gray_flag, inverse_and_gray_flags, &x_start, &y_start, &x_end, &y_end, image);

	processing_line_action(line_flag, line_flags, &x_start_line, &y_start_line, &x_end_line, &y_end_line, red_component_color, green_component_color, blue_component_color, thickness, color, image);

	processing_ramka_action(ramka_flag, color_flag, red_component_color, green_component_color, blue_component_color, &color, thickness, output_file_name, image);

	processing_resize_action(resize_flag, resize_flags, color_flag, up_resize, down_resize, right_resize, left_resize, output_file_name, &color, red_component_color, green_component_color, blue_component_color, image);

	if (was_input_action_flag && !resize_flag) save_bmp(output_file_name, *image);

	if (!was_input_action_flag) failure("You have not selected an image action");

	return SUCESSFULL;
}
