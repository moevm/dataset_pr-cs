#include "del.h"
#include "struct.h"
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

int checksen(struct Sentence s1, struct Sentence s2){
	if(s1.len!=s2.len){
		return 0;
	}
	for(int i=0; i<s1.len; i++){
		if(wcscasecmp(s1.p[i].p,s2.p[i].p)){
			return 0;
		}	
	}
	return 1;	
}


struct Text delete(struct Text text){
	struct Text newtext;
	int n=30, k=0, b=1;
	newtext.p=(struct Sentence*)malloc(n*sizeof(struct Sentence));
	for(int i=0;i<(text.size-1);i++){
		for(int j=i+1;j<text.size;j++){
			if(checksen(text.p[i],text.p[j])){
				b=0;
			}
		}	
		if(b){
			newtext.p[k]=text.p[i];
			k++;
			if(k>=n){
				n+=30;
				newtext.p=(struct Sentence*)realloc(newtext.p,n*sizeof(struct Sentence));
			}	
		}
		b = 1;	
	
	}
	newtext.p[k]=text.p[text.size-1];
	k++;
	newtext.size = k;
	return newtext;	
}

