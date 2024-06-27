#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "print_func.h"

void unique_symbols(struct Text* text){
    struct Sentence uni_sym;
    uni_sym.sentence = (wchar_t*)malloc(sizeof(wchar_t));
    if(uni_sym.sentence == NULL){
        print_error(L"Memory allocation error. (in function\"unique symbols\")");
    }
    uni_sym.len = 0;

    for(int k = 0; k < text->len; k++){
        for(int i = 0; i < text->sentences[k]->len; i++){
            int is_unique = 1;
            for(int j = 0; j < uni_sym.len; j++){
                if(text->sentences[k]->sentence[i] == uni_sym.sentence[j]){
                    is_unique = 0;
                    break;
                }
            }
            if(is_unique && iswalnum(text->sentences[k]->sentence[i])){
                uni_sym.sentence = (wchar_t*)realloc(uni_sym.sentence, sizeof(wchar_t) * (uni_sym.len + 1));
                if(uni_sym.sentence == NULL){
                    print_error(L"Memory reallocation error. (in function\"unique_symbols\")");
                }
                uni_sym.sentence[uni_sym.len++] = text->sentences[k]->sentence[i];
            }
        }
    }
    uni_sym.sentence[uni_sym.len] = L'\0';

    for(int i = 0; i < uni_sym.len; i++){
        wprintf(L"%lc ", uni_sym.sentence[i]);
    }
    wprintf(L"\n");

    free(uni_sym.sentence);
}