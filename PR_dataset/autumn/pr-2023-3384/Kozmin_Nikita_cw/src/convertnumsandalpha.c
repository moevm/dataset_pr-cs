#ifndef stddef
#include <stddef.h>
#endif
#ifndef ctype
#include <ctype.h>
#endif

#include "convertnumsandalpha.h"


void convertnumsandalpha(char ***sentences, size_t *cnt_sentences){
    for (size_t i=0; i < *cnt_sentences; i++){
        for (size_t j = 0; (*sentences)[i][j]; j++){
	    	if (isdigit((*sentences)[i][j])){
	    		(*sentences)[i][j] = 'D';
	    	}
            else{
                (*sentences)[i][j] = tolower((*sentences)[i][j]);
            }
	    }
    }
}
