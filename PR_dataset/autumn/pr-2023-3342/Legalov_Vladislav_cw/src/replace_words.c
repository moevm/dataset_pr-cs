#include "replace_words.h"




int replace_words_in_text(Text *text){
	wchar_t* first, *second;
	if(get_words(text, &first, &second)){
		for (int i = 0; i < text->size; ++i)
			replace_words_in_sentence(text->sentences[i], first, second);
		free(first);
		free(second);
		return 1;
	}
	return 0;
}

void replace_words_in_sentence(Sentence* sentence, wchar_t *first, wchar_t *second){
	BreaksData* positions = find_strs(sentence, wcsdup(first), (int)wcslen(second) - (int)wcslen(first));
	insert_breaks(sentence, positions);
	for(int i = 0; i < positions->size; ++i)
		memcpy(sentence->str + positions->breaks_pos[i] + positions->size_breaks * i, second, wcslen(second) * sizeof(wchar_t));
	free_breaks_data(positions);
}

BreaksData* find_strs(Sentence* sentence, wchar_t *first, int size_breaks){
	wchar_t *source = wcsdup(sentence->str);
	int* res = malloc(sizeof(int) * sentence->size);
	int size = 0;
	int *pos = source - 1;
	int size_first = wcslen(first);
	for (int i = 0; i < sentence->size; ++i)
		source[i] = to_lower_ru_en(source[i]);
	for (int i = 0; i < size_first; ++i)
		first[i] = to_lower_ru_en(first[i]);
	while(pos = wcsstr(pos + 1, first)){
		int i = pos - source;
		if((i == 0 || source[i-1] == L' ') && ((i + size_first == sentence->size || source[i + size_first] == L' ' || source[i + size_first] == L',')))
			res[size++] = i;
	}
	free(source);
	free(first);
	return create_breaks_data(res, size, size_breaks);
}

int get_words(Text *text, wchar_t **first, wchar_t **second){
	wchar_t* str = wcsdup(text->sentences[0]->str);
	wchar_t* p;
	wchar_t* pwc = wcstok(str, L" ,", &p);
	*first = wcsdup(pwc);
	if (pwc = wcstok(NULL, L" ,", &p)){
		*second = wcsdup(pwc);
		free(str);
		return 1;
	}
	else if (text->size > 1){
		free(str);
		str = wcsdup(text->sentences[1]->str);
		pwc = wcstok(str, L" ,", &p);
		*second = wcsdup(pwc);
		free(str);
		return 1;
	}	
	free(str);
	free(*first);
	return 0;
}

