#include "anagram_funct.h"

Text *find_anagrams(Text *source){
	Text *res = (Text*)calloc(1, sizeof(Text));
	Text *text = create_text_with_copyed_pointers(source);
	int **char_table = calc_char_table(text);
	for(int i = 0; i < text->size - 1; ++i)
		if(text->sentences[i]) {
			int is_not_was = 1; 
			for(int j = i + 1; j < text->size; ++j){
				if(text->sentences[j] && !(memcmp(char_table[i],char_table[j], sizeof(int) * SIZE_ALPHA))){
					if (is_not_was){
						is_not_was = 0;
						text_append(res, text->sentences[i]);
					}
					text_append(res, text->sentences[j]);
					text->sentences[j] = NULL;
				}
			}
		}
	free(text->sentences);
	free(text);
	for (int i = 0; i < source->size; ++i)
		free(char_table[i]);
	free(char_table);
	return res;
}

int **calc_char_table(Text *text){
	int **table = malloc(sizeof(int*) * text->size);
	Sentence **sentences = text->sentences;
	for (int i = 0; i < text->size; ++i)
		table[i] = calloc(SIZE_ALPHA, sizeof(int));
	
	for(int i = 0; i < text->size; ++i)
		for(int j = 0; j < sentences[i]->size; ++j){
			int k = number_char_in_table(sentences[i]->str[j]);
			if (k)
				++table[i][k];
		}
	
	return table;
}

int number_char_in_table(wchar_t ch){
	int res = 0;
	if (ch == L'ё' || ch == L'Ё')
		return SIZE_ALPHA - 1;
	ch = to_lower_ru_en(ch);
	if (ch >= L'0' && ch <= L'9')
		res = ch - L'0' + 1;
	else
	if (ch >= L'a' && ch <= L'z')
		res = ch - L'a' + 1;
	else
	if (ch >= L'а' && ch <= L'я')
		res = ch - L'а' + 1;
	return res;
}




