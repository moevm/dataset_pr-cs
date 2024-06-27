#include "freememory.h"
void freememory(Text T){
	for(size_t i=0; i<T.teklen; i++){
	free(T.sent[i]->symbols);
	free(T.sent[i]);
	}
	free(T.sent);
}
