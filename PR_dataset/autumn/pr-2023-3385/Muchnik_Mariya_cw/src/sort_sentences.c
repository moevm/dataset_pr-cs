#include <wchar.h>
#include <stdlib.h>

#include "struct.h"

int codes_sum(struct Sentence* sentence){
	wchar_t* sent = sentence->ptr;
	int sum = 0;
	int idx = 0;
	int last_id = wcscspn(sent, L" ,.");
	while (idx < last_id){
		sum += (int)sent[idx++];
	}
	return sum;
}

int cmp(const void* a, const void* b){
	int x = codes_sum(*(struct Sentence**)a);
	int y = codes_sum(*(struct Sentence**)b);
	return x - y;
}

void sort_sentences(struct Text txt){
	qsort(txt.ptr, txt.len, sizeof(struct Sentence*), cmp);
}
