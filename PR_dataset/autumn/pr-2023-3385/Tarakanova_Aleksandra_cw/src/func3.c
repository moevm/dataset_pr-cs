#include "func3.h"
#include "sio.h"
#include <stdlib.h>

int prlen(struct Sentence sen){
	int m = 1;
	for(int i = 0; i < sen.len; i++){
		m *= sen.p[i].len;
	}
	return m;
}


int cmp(const void* a, const void* b){
	struct Sentence* f = (struct Sentence*)a;
	struct Sentence* s = (struct Sentence*)b;
	if(prlen(*f) > prlen(*s)){
		return 1;
	}
	if(prlen(*f) < prlen(*s)){
		return -1;
	}
	return 0;
}
 

void func3(struct Text text){
	qsort(text.p, text.size, sizeof(struct Sentence), cmp);
	outtext(text);
}
