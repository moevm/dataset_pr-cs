#include "all_bin_text.h"

struct Sentence *make_bin(struct Sentence *sentence){
	struct Sentence *bin_sentence = malloc(sizeof(struct Sentence));
	if(!bin_sentence)
		fail(MEM_ERROR);
	bin_sentence->str = malloc(sizeof(wchar_t));
	if(!bin_sentence->str)
		fail(MEM_ERROR);
	int n = 0;
	wchar_t sym[2] = {0};
	wchar_t *binDict[10] = {L"0", L"1", L"10", L"11", L"100", L"101", L"110", L"111", L"1000", L"1001"};
	for(int i = 0; i < sentence->len; i++){
		if(iswdigit(sentence->str[i])){
	                sym[0] = sentence->str[i];
	                int bin_index = wcstol(sym, NULL, 10);
	                int bin_len = wcslen(binDict[bin_index]);
			bin_sentence->str = realloc(bin_sentence->str,(n+2+bin_index)*sizeof(wchar_t));
			if(!bin_sentence->str)
				fail(MEM_ERROR);
			for(int j = 0; j<bin_len;j++){
				bin_sentence->str[n++] = binDict[bin_index][j];
			}
		}else{
			bin_sentence->str = realloc(bin_sentence->str,(n+2)*sizeof(wchar_t));
			if(!bin_sentence->str)
				fail(MEM_ERROR);
			bin_sentence->str[n++] = sentence->str[i];
			
		}

	}
	bin_sentence->str = realloc(bin_sentence->str,(n+2)*sizeof(wchar_t));
	if(!bin_sentence->str)
		fail(MEM_ERROR);
	bin_sentence->str[n] = '\0';
	bin_sentence->len = n;
	return bin_sentence;
}

struct Text bin(struct Text text){
	struct Text new_text;
	new_text.sents = malloc(sizeof(struct Sentence*));
        if(!new_text.sents)
                fail(MEM_ERROR);
        int n = 0;
	for(int i = 0; i < text.n; i++){
		if(make_bin(text.sents[i])){
			new_text.sents = realloc(new_text.sents,(n+1)*sizeof(struct Sentence*));
			new_text.sents[n++] = make_bin(text.sents[i]);
		}
	}
	new_text.n = n;
	return new_text;
}

void all_bin_sym(struct Text text){
	text_print(bin(text));
	freeText(text);
}
