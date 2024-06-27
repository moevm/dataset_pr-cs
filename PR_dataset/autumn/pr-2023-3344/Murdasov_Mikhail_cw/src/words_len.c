#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"
#include "print_func.h"


void words_len(struct Text* text) {
    struct Text words;
    words.sentences = (struct Sentence**)malloc(sizeof(struct Sentence*));
    if(words.sentences == NULL){
        print_error(L"Memory allocation error. (in function\"words_len\")");
    }
    words.len = 0;
    int ind = 0;

    for (int i = 0; i < text->len; i++) {
        wchar_t* sent = (wchar_t*)wcsdup(text->sentences[i]->sentence);
        if(sent == NULL){
            print_error(L"Memory allocation error. (in function\"words_len\")");
        }
        wchar_t* buffer;
        wchar_t* word = (wchar_t*)wcstok(sent, L" .,\f\r\n\t\v",&buffer);
        while (word != NULL) {
            words.sentences = (struct Sentence**)realloc(words.sentences, sizeof(struct Sentence*) * (ind + 1));
            if(words.sentences == NULL){
                print_error(L"Memory reallocation error. (in function\"words_len\")");
            }
            words.sentences[ind] = (struct Sentence*)malloc(sizeof(struct Sentence));
            if(words.sentences[ind] == NULL){
                print_error(L"Memory allocation error. (in function\"words_len\")");
            }
            words.sentences[ind]->sentence = (wchar_t*)wcsdup(word);
            if(words.sentences[ind]->sentence == NULL){
                print_error(L"Memory allocation error. (in function\"words_len\")");
            }
            ind++;
            word = (wchar_t*)wcstok(NULL, L" .,\f\r\n\t\v", &buffer);
        }
        free(sent);
        free(word);
        free(buffer);
    }

    int max_len = 0;
    for (int i = 0; i < ind; i++) {
        int len = wcslen(words.sentences[i]->sentence);
        if (len > max_len) {
            max_len = len;
        }
    }

    for (int len = 1; len <= max_len; len++) {
        int cnt = 0;
        int cnt_test = 0;
        for (int i = 0; i < ind; i++) {
            if (wcslen(words.sentences[i]->sentence) == len) {
                cnt_test++;
            }
        }
        if(cnt_test){
            wprintf(L"LEN = %d: (", len);
            for (int i = 0; i < ind; i++) {
                if (wcslen(words.sentences[i]->sentence) == len) {
                    wprintf(L"%ls, ", words.sentences[i]->sentence);
                    cnt++;
                }
            }
            wprintf(L"\b\b.)");
            wprintf(L" -- [%d pieces]\n", cnt);
        }
    }

    for (int i = 0; i < ind; i++) {
        free(words.sentences[i]->sentence);
        free(words.sentences[i]);
    }
    free(words.sentences);
}