#include "all_special_sym.h"

int cmp(const void *a, const void *b){
	const int *f = (const int*) a;
    	const int *s = (const int*) b;
	if(*f<*s)
        	return 1;
    	if(*f>*s)
        	return -1;
    	return 0;
}

struct Sentence  *make_special(struct Sentence *sentence){
	struct Sentence *special_sentence;
	special_sentence = malloc(sizeof(struct Sentence));
	if(!special_sentence)
		fail(MEM_ERROR);
	special_sentence->str = malloc(sizeof(wchar_t));
	if(!special_sentence->str)
		fail(MEM_ERROR);
	int n = 0;
	int flag = 0;
	for(int i = 0; i<sentence->len;i++){
		if(iswpunct(sentence->str[i]) && sentence->str[i]!= L'\0' && sentence->str[i]!= L'.'){
			special_sentence->str = realloc(special_sentence->str,(n+1)*sizeof(wchar_t));
			if(!special_sentence->str)
				fail(MEM_ERROR);
			special_sentence->str[n++] = sentence->str[i];
		}
	}
	qsort(special_sentence->str, n, sizeof(wchar_t),cmp);
	special_sentence->str = realloc(special_sentence->str,(n+2)*sizeof(wchar_t));
	if(!special_sentence->str)
		fail(MEM_ERROR);
	special_sentence->str[n++] = '.';
	special_sentence->str[n] = '\0';
	special_sentence->len = n;
	return special_sentence;
}

struct Text special(struct Text text){
	struct Text new_text;
	new_text.sents = malloc(sizeof(struct Sentence*));
	if(!new_text.sents)
		fail(MEM_ERROR);
	int n = 0;
	for(int i = 0; i < text.n;i++){
		if(make_special(text.sents[i]))
			new_text.sents = realloc(new_text.sents,(n+1)*sizeof(struct Sentence*));
			if(!new_text.sents)
				fail(MEM_ERROR);
			new_text.sents[n++] = make_special(text.sents[i]);
	}
	new_text.n = n;
        return new_text;
}

void all_special_sym(struct Text text){
	text_print(special(text));
	freeText(text);
}
