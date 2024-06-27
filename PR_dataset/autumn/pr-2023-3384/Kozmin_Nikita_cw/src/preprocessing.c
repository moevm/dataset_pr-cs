#ifndef stdlib
#include <stdlib.h>
#endif
#ifndef string
#include <string.h>
#endif
#ifndef ctype
#include <ctype.h>
#endif

#include "preprocessing.h"


size_t preprocessing(char ***sentences, size_t *cnt_sentences){
    char *fst = NULL;  // Первое предложение
    char *scd = NULL;  // Второе предложение
    size_t len_fst;
    size_t len_scd;

    // Проход по первым предложениям
    for (size_t i = 0; i < (*cnt_sentences)-1; i++){
        len_fst = strlen((*sentences)[i]);
        fst = realloc(fst, sizeof(char)*(len_fst + 1));
        for (size_t k=0; k < (len_fst+1); k++){
            fst[k] = tolower((*sentences)[i][k]);
        }

        // Проход по каждому второму предложению
        for (size_t j = i+1; j < (*cnt_sentences); j++){
            len_scd = strlen((*sentences)[j]);
            if (len_fst == len_scd){
                scd = realloc(scd, sizeof(char)*(len_scd + 1));
                for (size_t k=0; k < (len_scd+1); k++){
                    scd[k] = tolower((*sentences)[j][k]);
                }

                // Удаление второго предложения при равенстве с первым
                if (strcmp(fst, scd) == 0){
                    for (size_t k = j+1; k < (*cnt_sentences); k++){
                        (*sentences)[k-1] = (*sentences)[k];
                    }
                    (*cnt_sentences)--;
                    (*sentences) = realloc((*sentences), (*cnt_sentences)*sizeof(char*));
                }
            }
        }
    }
}
