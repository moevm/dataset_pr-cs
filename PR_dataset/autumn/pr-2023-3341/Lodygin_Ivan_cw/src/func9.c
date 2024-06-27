#include <wctype.h>
#include <wchar.h>
#include <stdlib.h>
#include "structures.h"
#include "checking.h"

#define SEP L" ,.\n\t"

void func9(struct Text text, wchar_t first_word[]) {
	wchar_t *ptr;
	wchar_t *sentence = calloc(1, sizeof(wchar_t));
	wchar_t *word;
	for(int i = 0; i < text.n; i++){
		sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
		word = wcstok(sentence, SEP, &ptr);
		if((checking(word, first_word) == 1)&&(word != NULL)) wprintf(L"%ls\n", word);
		while(1) {
			word = wcstok(NULL, SEP, &ptr);
			if(word == NULL) break;
			if(checking(word, first_word) == 1) wprintf(L"%ls\n", word);
		}
	}
}