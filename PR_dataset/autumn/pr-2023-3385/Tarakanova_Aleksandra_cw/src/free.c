#include "free.h"
#include <stdlib.h>

void freetext(struct Text text){
	for(int i=0;i<text.size;i++){
		for(int j=0;j<text.p[i].len;j++){
			free(text.p[i].p[j].p);
		}
		free(text.p[i].p);
	}
	free(text.p);
}
