#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "../include/create_new_sentences.h"

char** create_new_sentences(char** init_sentences, int* count, char* D) {
    char** sentences = (char**)malloc(sizeof(char*));
    int max_len = 0;
    int min_len = 0;
    if (*count % 2 != 0) {
        max_len = (*count / 2) + 1;
        min_len = (*count / 2) - 2;
    }
    else {
        max_len = (*count / 2);
        min_len = (*count / 2) - 1;
    }
    int new = 0;
    for (int i1 = 0, i2 = *count-1; (i1 < max_len && i2 > min_len); i1++, i2--) {
        char* sentence = (char*)malloc((strlen(D) + strlen(init_sentences[0]) + strlen(init_sentences[0]) + 1) * sizeof(char*));
        init_sentences[i1][strlen(init_sentences[i1]) - 1] = ' ';
        strcat(sentence, init_sentences[i1]);
        strcat(sentence, D);
        strcat(sentence, " ");
        strcat(sentence, init_sentences[i2]);
        if (sentence[strlen(sentence) - 1] != '.') {
            sentence[strlen(sentence) - 1] = '.';
        }
        sentences[new++] = sentence;
        sentences = realloc(sentences, (new + 1) * sizeof(char*));
    }
    
    *count = new;
    return sentences;
}