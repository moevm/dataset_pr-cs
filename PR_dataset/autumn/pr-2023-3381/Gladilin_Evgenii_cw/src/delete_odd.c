#include "delete_odd.h"

int check_for_odd(struct Sentence *sentence){
	for(int i = 0; i<sentence->len;i++){
		if(wcschr(L"13579", sentence->str[i]) && sentence->str[i]!='\0')
			return 1;
	}
	return 0;
}

struct Text odd(struct Text text){
	struct Text new_text;
	new_text.sents = malloc(sizeof(struct Sentence*));
	if(!new_text.sents)
		fail(MEM_ERROR);
	int n = 0;
	for(int i = 0; i < text.n; i++){
		if(!check_for_odd(text.sents[i])){
			new_text.sents = realloc(new_text.sents, (n+1)*sizeof(struct Sentence*));
			if(!new_text.sents)
				fail(MEM_ERROR);
			new_text.sents[n++] = text.sents[i];
		}

	}
	new_text.n = n;
	return new_text;
}

void all_delete_odd(struct Text text){
	text_print(odd(text));
	freeText(text);
}

