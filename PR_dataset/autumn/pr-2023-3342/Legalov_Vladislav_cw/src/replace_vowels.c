#include "replace_vowels.h"



void replace_vowel_in_text(Text* text){
	for(int i = 0; i < text->size; ++i){
		replace_vowel_in_sentence(text->sentences[i]);
	}
}

void replace_vowel_in_sentence(Sentence* sentence){
	BreaksData* positions = find_vowel_pos(sentence);
	if (positions->breaks_pos){
		insert_breaks(sentence, positions);
		for (int i = 0; i < positions->size; ++i){
			int j = positions->breaks_pos[i] + i;
			get_next_alpha(sentence->str[j], &sentence->str[j], &sentence->str[j + 1]);
		}
	}
	free_breaks_data(positions);
}

BreaksData* find_vowel_pos(Sentence* sentence){
	static wchar_t vowels[] = L"аоуыэёюиеяaeyuioАОУЫЭЁЮИЕЯAEYUIO";
	BreaksData* positions = create_breaks_data(malloc(sizeof(int) * sentence->size), 0, 1);
	wchar_t* ptr = sentence->str - 1;
	while(ptr = wcspbrk(ptr + 1, vowels)){
		positions->breaks_pos[positions->size++] = ptr - sentence->str;
	}
	return positions;
}


