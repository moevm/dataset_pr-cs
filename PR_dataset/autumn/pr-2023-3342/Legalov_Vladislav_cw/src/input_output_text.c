#include "input_output_text.h"

Text *input_text(){
	Text *text = (Text*)calloc(1, sizeof(Text));
	Sentence *sentence;
	while((sentence = read_sentence()) != NULL){
		text_append(text, sentence);
		text_delete_repeat(text);
	}
	return text;
}

Sentence *read_sentence(){
	static int was_end = 0;
	if (was_end){
		was_end = 0;
		return NULL;
	}
	size_t size = 0, capacity = BLOCK, count_upper = 0;
	wchar_t *str = (wchar_t*)malloc(BLOCK * sizeof(wchar_t));
	wchar_t ch = getwchar();
	wchar_t last_wchar = L'\0';
	while(isspace(ch) || ch == ',' || ch == '.') {
		if (ch == L'\n' && last_wchar == L'\n'){
			free(str);
			return NULL;
		}
		last_wchar = ch;
		ch = getwchar();
	}
	while(ch != '.'){
		if (size >= capacity - 1){
			capacity += BLOCK;
			str = (wchar_t*)realloc(str, capacity * sizeof(wchar_t));
		}
		last_wchar = ch;
		if ((ch == '\n') || (ch == L',' && str[size - 1] == L',') || (size > 1 && ch == L',' && str[size - 2] == L','))
			ch = L' ';
		if ((ch == L' ' || ch == L',') && str[size - 1] == L' ')
			--size;
		if (str[size - 1] == L',' && ch != L' ' && ch != L',')
			str[size - 1] = L' ';
		str[size++] = ch;
		if (is_alpha_upper_ru_en(ch)) ++count_upper;
		ch = getwchar();
		if (last_wchar == L'\n' && ch == L'\n'){
			--size;
			if (size == 0){
				free(str);
				return NULL;
			}
			was_end = 1;
			break;
		}
	}
	if (str[size-1] == L' ' || str[size-1] == L',')
		--size;
	str[size] = L'\0';
	Sentence *sentence = (Sentence*)malloc(sizeof(Sentence*));
	sentence->size = size;
	sentence->str = str;
	sentence->count_upper = count_upper;
	return sentence;
}

void print_text(Text *text){
	Sentence **sentences = text->sentences;
	for(int i = 0; i < text->size; ++i)
		if (sentences[i])
			wprintf(L"%ls.\n", sentences[i]->str);
}




