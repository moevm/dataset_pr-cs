#ifndef stdio
#include <stdio.h>
#endif

#include "printduplicates.h"


void printduplicates(char ***sentences, size_t *cnt_sentences, int *N){
    for (size_t i = 0; i < *cnt_sentences; i++){
        for (int j = 0; j < *N; j++){
            for (size_t k = 0; (*sentences)[i][k] != '.'; k++){
                printf("%c", (*sentences)[i][k]);
            }
            if (j+1 < *N){
                printf(" ");
            }
            else{
                printf(".\n");
            }
        }
    }
}
