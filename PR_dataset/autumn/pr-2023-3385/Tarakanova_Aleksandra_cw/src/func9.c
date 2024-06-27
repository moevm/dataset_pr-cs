#include "func9.h"
#include <stdio.h>
#include <wchar.h>

void func9(struct Text text){
	for(int i=0;i<text.size;i++){
		for(int j=0; j<text.p[i].len; j++){
			for(int k=0; k<text.p[i].p[j].len; k++){
				printf("%C", text.p[i].p[j].p[k]);
			}
			printf(" ");
			for(int k=0; k<text.p[i].p[j].len; k++){
				printf("%C", text.p[i].p[j].p[k]);
			}
			if(j!=text.p[i].len-1){
				printf(" ");
			}
		}
		printf(".\n");
	}
}
