#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "print_func.h"

wchar_t** delimiters(wchar_t* sent){
    wchar_t** delims = (wchar_t**)malloc(sizeof(wchar_t*));
    if (delims == NULL) {
        print_error(L"Memory allocation error. (in function\"delimiters\")");
    }
    int ind_delims = 0;
    for(int i = 0; i<wcslen(sent); i++){
        wchar_t* delim = (wchar_t*)malloc(sizeof(wchar_t));
        if (delim == NULL) {
            print_error(L"Memory allocation error. (in function\"delimiters\")");
        }
        int ind = 0;
        while(iswspace(sent[i]) || sent[i] == L',' || sent[i] == L' '){
            delim = (wchar_t*)realloc(delim, wcslen(delim)*sizeof(wchar_t) + sizeof(wchar_t)*10);
            if (delim == NULL) {
                print_error(L"Memory reallocation error. (in function\"delimiters\")");
            }
            delim[ind++] = sent[i++];
        }
        delim[ind] = L'\0';
        if(wcslen(delim) != 0){
            delims = (wchar_t**)realloc(delims, (ind_delims + 2)*sizeof(wchar_t*));
            if (delim == NULL) {
                print_error(L"Memory reallocation error. (in function\"delimiters\")");
            }
            delims[ind_delims++] = delim;
        }
    }
    return delims;
}

wchar_t* replace_spaces(struct Text* text, int i){
    wchar_t* result = (wchar_t*)malloc(1000*sizeof(wchar_t));
    if (result == NULL) {
        print_error(L"Memory allocation error. (in function\"delimiters\")");
    }
    wchar_t* str = (wchar_t*)wcsdup(text->sentences[i]->sentence);
    if (str == NULL) {
        print_error(L"Memory allocation error. (in function\"delimiters\")");
    }
    wchar_t* buffer;
    wchar_t* word = (wchar_t*)wcstok(str, L"\f\r\n\t\v ,",&buffer);
    wcscpy(result, word);
    wcscat(result, L" ");
    word = (wchar_t*)wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
    while(word != NULL){
        wcscat(result, word);
        wcscat(result, L" ");
        word = (wchar_t*)wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
    }
    result[wcslen(result)-1] = L'\0';
    return result;
}

void return_delimiters(struct Text* text_array, int i,wchar_t* sent, wchar_t** delims){
    wchar_t* sent_copy = (wchar_t*)wcsdup(sent);
    if (sent_copy == NULL) {
        print_error(L"Memory allocation error. (in function\"return_delimiters\")");
    }

    wchar_t* result = (wchar_t*)malloc(1000*sizeof(wchar_t));
    if (result == NULL) {
        print_error(L"Memory allocation error. (in function\"return_delimiters\")");
    }
    int len = 0;
    wchar_t* buffer;
    wchar_t* word = (wchar_t*)wcstok(sent_copy, L"\f\r\n\t\v ,",&buffer);
    if (word == NULL) {
        print_error(L"Memory allocation error. (in function\"return_delimiters\")");
    }
    wcscpy(result, word);
    len+=wcslen(word);
    word = (wchar_t*)wcstok(NULL, L"\f\r\n\t\v ,",&buffer);
    int ind_delim = 0;
    while(word != NULL){
            wcscat(result, delims[ind_delim]);
            wcscat(result, word);
            len+=wcslen(delims[ind_delim++]);
            len+=wcslen(word);
            word = (wchar_t*)wcstok(NULL, L"\f\r\n\t\v ,",&buffer);
    }
    result[len] = L'\0';
    wcscpy(text_array->sentences[i]->sentence,result);
    
    free(result);
    free(buffer);
    free(sent_copy);    
}

void shift_words_in_a_sentence(struct Text* text) {
    int N;
    wscanf(L"%d", &N);
    if(N < 0){
        print_error(L"Incorrect number of words.");
    }

    for(int num = 0; num < text->len; num++){
        wchar_t** delims = (wchar_t**)delimiters(text->sentences[num]->sentence);    
        wchar_t* main_sentence = (wchar_t*)replace_spaces(text,num);
        wchar_t* sentence = (wchar_t*)wcsdup(main_sentence);
        if (sentence == NULL) {
            print_error(L"Memory allocation error. (in function\"delimiters\")");
        }

        wchar_t* sentence_copy = (wchar_t*)wcsdup(main_sentence);
        if (sentence_copy == NULL) {
            print_error(L"Memory allocation error. (in function\"shift_words_in_a_sentence\")");
        }
    
        wchar_t* buffer;
        wchar_t* word = (wchar_t*)wcstok(sentence, L"\f\r\n\t\v ,", &buffer);
        int ind = 0;
        while(ind < N){
            main_sentence = (wchar_t*)realloc(main_sentence, (wcslen(main_sentence) + wcslen(word) + 100)*sizeof(wchar_t)); 
            if(main_sentence == NULL){
                print_error(L"Memory reallocation error. (in function\"shift_words_in_a_sentence\")");
            }

            wcscat(main_sentence, L" ");
            wcscat(main_sentence, word);
            ind++;

            memmove(main_sentence, main_sentence + wcslen(word) + 1, wcslen(main_sentence)*sizeof(wchar_t) - (wcslen(word) + 1)*sizeof(wchar_t));
            main_sentence[wcslen(main_sentence) - wcslen(word) - 1] = L'\0';
            word = (wchar_t*)wcstok(NULL, L"\f\r\n\t\v ,",&buffer);
            if(word == NULL){
                free(sentence);
                sentence = (wchar_t*)wcsdup(sentence_copy);

                if (sentence == NULL) {
                    print_error(L"Memory allocation error. (in function\"shift_words_in_a_sentence\")");
                }
                word = (wchar_t*)wcstok(sentence, L"\f\r\n\t\v ,",&buffer);
            }
        }
        
        return_delimiters(text, num, main_sentence, delims);
        
        free(delims);
        free(sentence);
        free(sentence_copy);
        free(main_sentence);
    }
}
