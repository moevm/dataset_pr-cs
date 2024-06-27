#include "../include/splittedSentence.h"
#define SIZE_STEP 20
 
wchar_t** splitSentence(Sentence sentence, int* count) {
    int limit = SIZE_STEP;
    wchar_t** words = malloc(sizeof(wchar_t*)*SIZE_STEP);
    wchar_t* word;
    wchar_t* buffer;
    word = wcstok(sentence.words,L",  \t",&buffer);
 
    while(word != NULL) {
        if (wcslen(word) > 0){
            *count = *count + 1;
            if (*count >= limit - 1) {
                limit += SIZE_STEP;
                words = realloc(words,sizeof(wchar_t*)*limit);
            }
            words[*count-1] = word;
        }
        word = wcstok(NULL,L",  \t",&buffer);
    }
 
    return words;
}