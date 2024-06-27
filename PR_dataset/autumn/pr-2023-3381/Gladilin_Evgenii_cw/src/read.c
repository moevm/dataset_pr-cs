#include "read.h"

int check_for_duplicates(struct Sentence **text, struct Sentence *sentence, int n){
	int flag = 0;
	for(int i = 0; i < n; i++){
		int j = 0;
		while(text[i]->str[j] && sentence->str[j]){
			if(towlower(text[i]->str[j]) != towlower(sentence->str[j])){
				flag += 1;
				break;
			}
			j++;
		}
	}
	return flag==n;
}

struct Sentence *read_sentence(){
	wchar_t cur_sym = getwchar();
	struct Sentence *sentence = malloc(sizeof(struct Sentence));
	if(!sentence)
		fail(MEM_ERROR);
	sentence->str = malloc(sizeof(wchar_t));
	if(!sentence->str)
		fail(MEM_ERROR);
	int n = 0;
	while(cur_sym == '\t' || cur_sym == ' '){
		cur_sym = getwchar();
	}
	sentence->str[n++] = cur_sym;
	while(/*cur_sym!= L'\n' && */cur_sym != L'.'){
		if(sentence->str[n-1] && cur_sym == L'\n')
			break;
		if(cur_sym == WEOF)
			fail(INPUT_ERROR);
		sentence->str = realloc(sentence->str,(n+1)*sizeof(wchar_t));
		if(!sentence->str)
			fail(MEM_ERROR);
		cur_sym = getwchar();
		sentence->str[n++] = cur_sym;
	}
	sentence->str = realloc(sentence->str,(n+1)*sizeof(wchar_t));
	if(!sentence->str)
		fail(MEM_ERROR);
	sentence->str[n] = L'\0';
	sentence->len = n;
	return sentence;
}

struct Text read_text(){
	struct Text text;
	text.sents = malloc(sizeof(struct Sentence*));
	if(!text.sents)
		fail(MEM_ERROR);
	int n = 0;
	struct Sentence *buffer;
	int count = 0;
	while(count<2){
		buffer = read_sentence();
		if(buffer->str[0] == L'\n'){
			count++;
			free(buffer);
		}else{
			count = 0;
			text.sents = realloc(text.sents,(n+1)*sizeof(struct Sentence*));
			if(!text.sents)
				fail(MEM_ERROR);
			if(check_for_duplicates(text.sents,buffer,n) || n==0){
				text.sents[n++] = buffer;
			}
		}

	}
	text.n = n;
	return text;
}
