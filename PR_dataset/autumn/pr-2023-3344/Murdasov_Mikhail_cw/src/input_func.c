#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"
#include "print_func.h"

int change_option(){
    int opt;
    wchar_t OPTION[1000];
    wscanf(L"%ls", OPTION);
    for(int i = 0; OPTION[i] != L'\0'; i++){
        if(!iswdigit(OPTION[i]) || iswspace(OPTION[i])){
            print_error(L"Invalid entry. Please enter a number, not text.");
        }
    }
    
    wchar_t* endprt;
    opt = wcstol(OPTION, &endprt, 10);

    return opt;
}

int repeat_sent_check(struct Text* text, struct Sentence* sent) {
    for (int i = 0; i < text->len; i++) {
        int j;
        for (j = 0; j < text->sentences[i]->len && j < sent->len; j++){
            wchar_t s1 = (wchar_t)text->sentences[i]->sentence[j];
            wchar_t s2 = (wchar_t)sent->sentence[j];
            if (towlower(s1) != towlower(s2)) {
                break;
            }
        }
        if (j == text->sentences[i]->len && j == sent->len){
            return 1;
        }
    }
    
    return 0;
}

void remove_first_space(wchar_t* sent){
    int len = wcslen(sent);
    for (int i = 0; i < len - 1; i++) {
        if (iswspace(sent[i])) {
            int j = i;
            while (sent[j] != '\0') {
                sent[j] = sent[j+1];
                j++;
            }
            len--;
            i--;
        }else{
            break;
        }
    }
}

int bad_sentence(wchar_t* sent){
    for(int i = 0; i<wcslen(sent); i++){
        if(!iswspace(sent[i])){
            if(sent[wcslen(sent)-1] != L'\n'){
                return 0;
            }else{
                print_error(L"Incorrect text input. The sentence must end with a period.");

            }
        }
    }
    return 1;
}

void text_processing(struct Text* text, struct Sentence string){
    wchar_t* buffer;
    wchar_t* token = (wchar_t*)wcstok(string.sentence, L".", &buffer);
   
    while(token != NULL){
        struct Sentence* sent = (struct Sentence*)malloc(sizeof(struct Sentence));
        if(sent == NULL){
            print_error(L"Memory allocation error. (in function\"input_text\")");
        }

        sent->sentence = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(token) + 1));
        if(sent->sentence == NULL){
            print_error(L"Memory allocation error. (in function\"input_text\")");
        }
        int bad = bad_sentence(token);
        remove_first_space(token);
        wcscpy(sent->sentence, token);
        sent->len = wcslen(token);

        text->sentences = (struct Sentence**)realloc(text->sentences, sizeof(struct Sentence*) * (text->len + 2));
        if(text->sentences == NULL){
            print_error(L"Memory reallocation error. (in function\"input_text\")");
        }

        if(bad == 0 && repeat_sent_check(text, sent) == 0){
            text->sentences[text->len] = sent;
            text->len++;
        }

        token = (wchar_t*)wcstok(NULL, L".", &buffer);

    }
    free(buffer);
}

void input_text(struct Text* text){
    text->sentences = (struct Sentence**)malloc(sizeof(struct Sentence*));
    text->len = 0;

    if(text->sentences == NULL){
        print_error(L"Memory allocation error. (in function\"input_text\")");
    }

    struct Sentence string;
    string.len = 0;
    string.sentence = (wchar_t*)malloc(sizeof(wchar_t));
    if(string.sentence == NULL){
        print_error(L"Memory allocation error. (in function\"input_text\")");
    }

    wchar_t symbol = getwchar();
    wchar_t prev_symbol = L' ';
    while(1){
        if (prev_symbol == L'\n' && symbol == L'\n'){
            break;
        }
        prev_symbol = symbol;
        string.sentence[string.len] = symbol;
        string.len++;
        string.sentence = (wchar_t*)realloc(string.sentence, sizeof(wchar_t) * (string.len + 2));
        if(string.sentence == NULL){
            print_error(L"Memory reallocation error. (in function\"input_text\")");
        }
        symbol = getwchar();
    }
    string.sentence[string.len] = L'\0';

    text_processing(text, string);
    
    if(text->len == 0){
        print_error(L"Incorrect text input.");
    }

    free(string.sentence);
}