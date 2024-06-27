#include "func4.h"
#include "sio.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

void func4(struct Text text){
	struct Text newtext;
	int n = 30;
	newtext.p = (struct Sentence*)malloc(n * sizeof(struct Sentence));
	newtext.size=0;
	for(int i=0; i<text.size;i++){
		int z=0, f=0;
		for(int j=0; j<text.p[i].len;j++){
			for(int k=0; k<text.p[i].p[j].len;k++){
				if(text.p[i].p[j].p[k]=='#' || text.p[i].p[j].p[k]==8470){
					z=1;
				}
				if(iswdigit(text.p[i].p[j].p[k])){
					f=1;
				}
			}	
		}
		if(z==0 || f==1){
			newtext.p[newtext.size]=text.p[i];
			newtext.size++;
			if(newtext.size==n){
				n+=10;
				newtext.p = (struct Sentence*)realloc(newtext.p,n * sizeof(struct Sentence));
	
			}
		}
	}
	outtext(newtext);
}
