#include "count_length_words.h"

void count_length_words(Text * text){
	wchar_t ** array_words = malloc(sizeof(wchar_t *)*SIZE_WORDS);
	size_t * count_words = malloc(sizeof(size_t)*SIZE_WORDS); 
	for (size_t i = 0; i < SIZE_WORDS; i++){
		array_words[i] = malloc(sizeof(wchar_t)*BUFFSIZE);
	}
	for (size_t i = 0; i < text->length;i++){
		wchar_t * context = NULL;
		wchar_t * current_word = wcstok(text->text[i]->sentence, SEPARATOR, &context);
		while(current_word != NULL){
			count_words[wcslen(current_word) - 1]++;
			array_words[wcslen(current_word) - 1] = wcscat(array_words[wcslen(current_word) - 1], current_word);
			array_words[wcslen(current_word) - 1] = wcscat(array_words[wcslen(current_word) - 1], L" ");
			current_word = wcstok(NULL, SEPARATOR, &context);
		}
	}
	for (size_t x = 0; x < SIZE_WORDS; x++){
		if (wcslen(array_words[x])){
			wprintf(L"Количество слов c длиной %ld:%ld ( %ls)\n", x+1,count_words[x], array_words[x]);
		}
	}
	for (size_t x = 0; x < SIZE_WORDS;x++){
		free(array_words[x]);
	}
	free(array_words);
	free(count_words);
}
