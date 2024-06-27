#include "processing.h"

void free_memory(struct Text *text, int **time_and_sentence_num_array, int size){
	free(text->sentences);
	if(time_and_sentence_num_array != NULL){
		if(size > 0){
			for(int i = 0; i < size; i++){
			free(time_and_sentence_num_array[i]);
			}
		}
		else free(time_and_sentence_num_array[0]);
		
		free(time_and_sentence_num_array);
	}
}

int calculate_time(int *time_and_sentence_num, time_t program_start_time){
	struct tm * timeinfo;
	timeinfo = localtime(&program_start_time);

	int minutes_after_start = timeinfo->tm_hour * 60 + timeinfo->tm_min;
	int minutes_in_sentence = time_and_sentence_num[0] * 60 + time_and_sentence_num[1];

	if(minutes_after_start >= minutes_in_sentence) return (minutes_after_start - minutes_in_sentence);
	else return (minutes_after_start - minutes_in_sentence + 24 * 60);
}

void command_processing(int command, struct Text *text, time_t program_start_time){
	if(command == 1){
		int size = 0;
		int **time_and_sentence_num_arr = make_time_and_sentence_num_arr(text, &size);
		if(time_and_sentence_num_arr == NULL){
			print_error(1);
			return;
		}

		if(localtime(&program_start_time)->tm_min < 10) wprintf(L"Текущее время: \x1b[32m%d:0%d\x1b[0m\n", localtime(&program_start_time)->tm_hour, localtime(&program_start_time)->tm_min);
		else wprintf(L"Текущее время: \x1b[32m%d:%d\x1b[0m\n", localtime(&program_start_time)->tm_hour, localtime(&program_start_time)->tm_min);
		
		for(int i = 0; i < size; i++){
			print_time_and_sentence_num_arr(time_and_sentence_num_arr[i], calculate_time(time_and_sentence_num_arr[i], program_start_time));
		}

		free_memory(text, time_and_sentence_num_arr, size);
		return;
	}
	else if(command == 2){
		delete_uppercase_letters(text);
	}
	else if(command == 3){
		sort_by_cyrillic_symbol_count(text);
	}
	else if(command == 4){
		*text = delete_sentences_without_special_symbols(text);
		if(text->sentences == NULL){
			print_error(1);
			return;
		}
	}
	else if(command == 9){
		*text = replace_long_words(text);
		if(text->sentences == NULL){
			print_error(1);
			return;
		}
	}

	print_text(*text);
	free_memory(text, NULL, 0);
}

void initial_processing()
{
	int command, len = 0;
	wchar_t *text_buffer;

	if (!input_command(&command)){
		print_error(0);	//command error
		return;
	}

	if(command == 5){
		print_manual();
		return;
	}

	int text_input_result = input_text(&text_buffer, &len, command);
	if(!text_input_result){
		print_error(1);	//allocation error
		return;
	}

	struct Text text = split_text(text_buffer, len);
	if(text.sentences == NULL){
		print_error(1);
		return;
	}

	if(text.len == 0){
		free(text.sentences);
		print_error(2); //empty text
		return;
	}
	
	delete_extra_separators(&text);

	text = delete_repeating_sentences(&text);
	if(text.sentences == NULL){
		print_error(1);
		return;
	}

	time_t program_start_time = time(NULL);
	if(command == 0){
		print_text(text);
		free_memory(&text, NULL, 0);
	}
	else command_processing(command, &text, program_start_time);
}