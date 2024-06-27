#include "move_words.h"

void move_words(Text * text, size_t count_inverse){
	for (size_t i = 0; i < text->length; i++){
		size_t count_words = 0;
		wchar_t ** array_words = NULL;
		wchar_t * context = NULL;
		wchar_t * new_word = wcstok(text->text[i]->sentence,SEPARATOR, &context);
		while(new_word != NULL){
			array_words = realloc(array_words, sizeof(wchar_t*)*(count_words + 1));
			array_words[count_words] = malloc(sizeof(wchar_t)*(wcslen(new_word) + 1));
			array_words[count_words] = wcscpy(array_words[count_words], new_word);
			count_words++;
			new_word = wcstok(NULL, SEPARATOR, &context);
		}
		for (size_t x = 0; x < count_inverse; x++){
			for (size_t z = 0; z < count_words - 1;z++){
				wchar_t * temp = array_words[z];
				array_words[z] = array_words[z + 1];
				array_words[z + 1] = temp;
			}
		}
		for (size_t f = 0;f < count_words; f++){
			if (f < count_words - 1){
				wprintf(L"%ls ", array_words[f]);
			}else{
				wprintf(L"%ls.\n",array_words[f]);
			}
		}
		while (count_words != 0){
			free(array_words[--count_words]);
		}
		free(array_words);
	}	
}
