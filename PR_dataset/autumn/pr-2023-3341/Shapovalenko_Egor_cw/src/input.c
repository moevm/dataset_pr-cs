#include "input.h"

int input_command(int *command){
    wchar_t command_buffer[2];
    command_buffer[0] = getwchar();
	command_buffer[1] = getwchar();

    if(!iswdigit(command_buffer[0])) return 0;
	if(command_buffer[1] != L'\n') return 0;

    *command = (int)wcstol(command_buffer, NULL, 10);
    if(((*command < 0) || (*command > 5)) && (*command) != 9) return 0;
    
	return 1;
}

int input_text(wchar_t **text_buffer, int *len, int command){
	int allocated_memory = 1, used_memory = 0;
	*text_buffer = (wchar_t*)calloc(1, sizeof(wchar_t));

	if(*text_buffer == NULL) return 0;

	wchar_t wch = getwchar();
	int end_flag = 0, word_flag = 0;

	while((wch != L'\n') || (!end_flag)){
		(*text_buffer)[used_memory] = wch;
		used_memory++;

		if((used_memory) >= allocated_memory){
			allocated_memory *= 2;
			*text_buffer = (wchar_t*)realloc(*text_buffer, (allocated_memory + 1) * sizeof(wchar_t));
			if(*text_buffer == NULL) return 0;
		}

		if(wch == L'.') (*len)++;
		
		if(wch == L'\n'){
			end_flag = 1;
			if(command == 9 && !word_flag){
				word_flag = 1;
				(*text_buffer)[used_memory - 1] = L'.';
				(*len)++;
			}
		}
		else end_flag = 0;
			
		wch = getwchar();
	}

	return 1;
}