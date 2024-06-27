#include <stdlib.h>
#include <wchar.h>
#include "structures.h"
#include "get_second_word.h"
#include "get_separators.h"

#define SEP L" ,.\n\t"

void word_replacement(struct Text text) {
    wchar_t words[text.n][text.size];
    wchar_t *sentence = calloc(1, sizeof(wchar_t));
    for(int i = 0; i < text.n; i++) {
        sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
        wcscpy(words[i], get_second_word(sentence));
    }
    wchar_t *word;
    wchar_t *ptr;
    wchar_t **separators;
    for(int i = 0; i < text.n; i++){
        sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
        separators = get_separators(sentence);
        word = wcstok(text.sents[i]->str, SEP, &ptr);
        if(word != NULL) wprintf(L"%ls", word);
        wprintf(L"%ls", separators[0]);
        word = wcstok(NULL, SEP, &ptr);
        if((i==0)&&(word != NULL)){
            wprintf(L"%ls", words[text.n-1]);
            wprintf(L"%ls", separators[1]);
        }
        else{
            if(word != NULL){
                wprintf(L"%ls", words[i-1]);
                wprintf(L"%ls", separators[1]);
            }
        }
        int i = 2;
        while(1) {
            word = wcstok(NULL, SEP, &ptr);
            if(word == NULL) break;
            if(word != NULL){
                wprintf(L"%ls", word);
                wprintf(L"%ls", separators[i]);
                i++;
            }
        }
        wprintf(L"%c%c", L'.', L'\n');
    }
}