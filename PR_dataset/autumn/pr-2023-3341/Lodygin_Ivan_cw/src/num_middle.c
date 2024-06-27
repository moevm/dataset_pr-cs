#include <stdlib.h>
#include <wchar.h>
#include "structures.h"
#include "check_mid_num.h"
#include "get_separators.h"
#define SEP L" ,.\n\t"

void num_middle(struct Text text) {
    wchar_t *sentence = calloc(1, sizeof(wchar_t));
    int checkbox;
    int k;
    wchar_t *word;
    wchar_t **separators;
    wchar_t *ptr;
    for(int i = 0; i < text.n; i++){
        checkbox = 0;
        k=1;
        sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
        word = wcstok(sentence, SEP, &ptr);
        if(check_mid_num(word)) checkbox = 1;
        while(1) {
            word = wcstok(NULL, SEP, &ptr);
            if(word == NULL) break;
            if(check_mid_num(word)) checkbox = 1;
        }
        if(checkbox == 1) {
            sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
            wcscpy(sentence, text.sents[i]->str);
            separators = get_separators(sentence);
            word = wcstok(text.sents[i]->str, SEP, &ptr);
            if(word != NULL) {
                if(check_mid_num(word)) wprintf(L"\033[1;32m%ls\033[0m", word);
                else wprintf(L"%ls", word);
            }
            wprintf(L"%ls", separators[0]);
            while(1){
                word = wcstok(NULL, SEP, &ptr);
                if(word == NULL) break;
                if(check_mid_num(word)) wprintf(L"\033[1;32m%ls\033[0m", word);
                else wprintf(L"%ls", word);
                wprintf(L"%ls", separators[k]);
                k++;
            }
            wprintf(L"%c%c", L'.', L'\n');
        }
        }
}