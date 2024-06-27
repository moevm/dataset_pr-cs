#ifndef stdlib
#include <stdlib.h>
#endif

#include "freetext.h"


void freetext(char ***sentences, size_t *cnt_sentences){
    for (size_t i=0; i < *cnt_sentences; i++){
        free((*sentences)[i]);
    }
    free(*sentences);
}
