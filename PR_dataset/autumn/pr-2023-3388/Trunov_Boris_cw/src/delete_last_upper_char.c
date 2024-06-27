#include "delete_last_upper_char.h"

void  delete_last_upper_char(Text * text){
	for (size_t i = 0; i < text->length; i++){
		wchar_t * context = NULL;
		wchar_t * word_from_str = text->text[i]->sentence;
		word_from_str =  wcstok(word_from_str, SEPARATOR, &context);
		int was_print = 0;
		while(word_from_str != NULL){
			if (!iswupper(word_from_str[wcslen(word_from_str) - 1])){
				wprintf(L"%ls", word_from_str);
				was_print = 1;
			}
			word_from_str = wcstok(NULL, SEPARATOR, &context);
			if (word_from_str != NULL && was_print == 1 && !iswupper(word_from_str[wcslen(word_from_str) - 1])){
				wprintf(L" ");
			}
		}
		if (was_print){
			wprintf(L".\n");
		}
		was_print = 0;
	}
}
