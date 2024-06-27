#include "action_selection.h"
#include "config_action_selection.h"
#include <stdio.h>


void action_selection(){
	size_t number_command;
	wscanf(L"%ld", &number_command);
	getwchar();
	if (number_command == NUMBER_HELP){
		help();
		exit(0);
	}else if(number_command == NUMBER_MOVE_WORDS){
		size_t count_inverse = 0;
		wscanf(L"%ld", &count_inverse);
		getwchar();
		Text *  text = read_text();
		move_words(text, count_inverse);
		free_memory(text);
	}else if (0 <= number_command && number_command < 5 && number_command != 1){
		Text *  text = read_text();
		switch (number_command){
			case NUMBER_TREATMENT_TEXT:
				output_text(text);
				free_memory(text);
				break;
			case NUMBER_UNIC_TEXT:
				set_unic(text);
				free_memory(text);
				break;
			case NUMBER_COUNT_LENGTH_WORDS:
				count_length_words(text);
				free_memory(text);
				break;
			case NUMBER_DELETE_UPPER:
				delete_last_upper_char(text);
				free_memory(text);
				break;
		}
	}else if(number_command == 9){
		Text * text = read_text();
		add_smile(text);
		free_memory(text);
	}else{
		failure(FAILURE_FUNCTION_NUMBER);
		exit(0);
	}
}
