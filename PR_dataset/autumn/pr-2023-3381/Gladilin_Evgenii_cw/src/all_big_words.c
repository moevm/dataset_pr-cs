#include "all_big_words.h"

struct Sentence *make_big(struct Sentence *sentence, int max_len){
	struct Sentence *big_sentence = malloc(sizeof(struct Sentence));
	if(!big_sentence)
		fail(MEM_ERROR);
	big_sentence->str = malloc(sizeof(wchar_t));
	if(!big_sentence->str)
		fail(MEM_ERROR);
	int n = 0;
	int count = 1;
	int start_index = 0;
	int j = 0;
	wchar_t big_word[] = L"(большое слово)";
	for(int i = 0; i < sentence->len; i++){
		if(!(iswspace(sentence->str[i])) && (sentence->str[i] != L'.') && (sentence->str[i] != L',')){
			count = 1;
			start_index = i+1;
			while((!(iswspace(sentence->str[start_index]))) && (sentence->str[start_index] != L'.') && (sentence->str[start_index] != L',') && (start_index < sentence->len)){
				start_index++;
				count++;	
			}
			if(count>max_len){
				big_sentence->str = realloc(big_sentence->str,(n+2+wcslen(big_word))*sizeof(wchar_t));
				if(!big_sentence->str)
					fail(MEM_ERROR);
				for(int j = 0; j<wcslen(big_word);j++){
					big_sentence->str[n++] = big_word[j];
				}
				i = start_index-1;
			}else{
				big_sentence->str = realloc(big_sentence->str,(n+2+count)*sizeof(wchar_t));
				if(!big_sentence->str)
					fail(MEM_ERROR);
				for(j = i; j<start_index;j++){
					big_sentence->str[n++] = sentence->str[j];
					i++;
				}
				i--;
			}
		}else{
			big_sentence->str = realloc(big_sentence->str,(n+2)*sizeof(wchar_t));
			if(!big_sentence->str)
				fail(MEM_ERROR);
			big_sentence->str[n++] = sentence->str[i];
			
		}

	}
	big_sentence->str = realloc(big_sentence->str,(n+2)*sizeof(wchar_t));
	if(!big_sentence->str)
		fail(MEM_ERROR);
	big_sentence->str[n] = L'\0';
	big_sentence->len = n;
	return big_sentence;
}

struct Text big(struct Text text, int max_len){
	struct Text new_text;
	new_text.sents = malloc(sizeof(struct Sentence*));
        if(!new_text.sents)
                fail(MEM_ERROR);
        int n = 0;
        for(int i = 0; i < text.n; i++){
		if(make_big(text.sents[i],max_len)){
			new_text.sents = realloc(new_text.sents,(n+1)*sizeof(struct Sentence*));
			new_text.sents[n++] = make_big(text.sents[i],max_len);
		}
	}
	new_text.n = n;
	return new_text;
}

void all_big_words(struct Text text, int len){
	text_print(big(text, len));
	freeText(text);
}
