#ifndef stdio
#include <stdio.h>
#endif
#ifndef string
#include <string.h>
#endif

#include "siftedoutput.h"


void siftedoutput(char ***sentences, size_t *cnt_sentences){
    for (size_t i=0; i < *cnt_sentences; i++){
        if (strlen((*sentences)[i]) <= 15){
            printf("%s\n", (*sentences)[i]);
        }
    }
}
