#include "text_base_funct.h"

void text_append(Text *text, Sentence *sentence){
	if (text->sentences == NULL){
		text->sentences = (Sentence**)malloc(sizeof(Sentence*));
		text->size = 0;
		text->capacity = 1;
	}
	if (text->size >= text->capacity){
		text->capacity += BLOCK;
		text->sentences = (Sentence**)realloc(text->sentences, sizeof(Sentence*) * text->capacity);
	}
	if (text->sentences)
		text->sentences[text->size++] = sentence;
}

void text_delete_repeat(Text *text){
	Sentence *first_sentence = text->sentences[text->size - 1];
	for (int k = 0; k < text->size - 1; ++k){
		Sentence *second_sentence = text->sentences[k];
		if (first_sentence->size == second_sentence->size){
			int i = 0;
			wchar_t *first = first_sentence->str;
			wchar_t *second = second_sentence->str;
			while(check_wchars_equality(first[i], second[i]) && i < first_sentence->size) ++i;
			if (i >= first_sentence->size) {
				--(text->size);
				free_sentence(first_sentence);
				break;
			}
		}
	}
}

void free_sentence(Sentence *sentence){
	free(sentence->str);
	free(sentence);
}

void free_text(Text *text){
	for(int i = 0; i < text->size; ++i)
		if (text->sentences[i]) free_sentence(text->sentences[i]);
	free(text->sentences);
	free(text);
}

void sort_text(Text *text){
	qsort(text->sentences, text->size, sizeof(Sentence*), comparator_upper_alpha);
}

Text* create_text_with_copyed_pointers(Text* source){
	Text *res = (Text*)calloc(1, sizeof(Text));
	res->size = source->size;
	res->capacity = source->size;
	res->sentences = (Sentence**)malloc(sizeof(Sentence*) * res->size);
	memcpy(res->sentences, source->sentences, sizeof(Sentence*) * res->size);
	return res;
}

int comparator_upper_alpha(const void* first, const void* second){
	long int first_value = (*((Sentence**)first))->count_upper;
	long int second_value = (*((Sentence**)second))->count_upper;
	return (first_value - second_value);
}




