#include "other_stuff.h"

wchar_t *get_value(struct Dictionary dict[], int size, wchar_t *key){
	for(int i = 0; i < size;i++){
		if(!wcscmp(dict[i].key, key))
			return dict[i].value;
	}
	return key;
}

void fail(wchar_t *message){
	wprintf(MEM_ERROR);
	exit(0);
}

void freeText(struct Text t){
	for(int i=0; i<t.n; i++){
		free(t.sents[i]->str);
		free(t.sents[i]);
	}
	free(t.sents);
}

void text_print(struct Text t){
        for(int i=0; i<t.n; i++){
		if(!wcsrchr(t.sents[i]->str,'\n'))
                	wprintf(L"%ls\n", t.sents[i]->str);
		else
			wprintf(L"%ls",t.sents[i]->str);
        }
}
