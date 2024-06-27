#ifndef stdio
#include <stdio.h>
#endif

#include "printtext.h"


void printtext(char ***sentences, size_t *cnt_sentences){
    for (size_t i = 0; i < (*cnt_sentences); i++){
        printf("%s\n", (*sentences)[i]);
    }
}