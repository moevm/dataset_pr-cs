#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <stdbool.h>

#include "structures.h"
#include "delete_capital.h"
#include "input_func.h"
#include "print_func.h"
#include "shift_words.h"
#include "unique_symbols.h"
#include "words_len.h"

int word(){
    wchar_t firstword[5000];
    wscanf(L"%ls", &firstword);

    wchar_t* buffer;
    wchar_t* word = wcstok(firstword, L"\f\r\n\t\v ,", &buffer);
    int firstwrd = wcslen(word);

    word = wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
    if(word != NULL){
        print_error(L"Too many words. Print one word, please.");
    }

    return firstwrd;
}

void replace_big_words(struct Text* text, int firstsize){

    
    for(int i = 0; i < text->len; i++){
        wchar_t* result = malloc(sizeof(wchar_t));
        if(result == NULL){
            print_error(L"Memory allocate error (in function \"relace_big_words\").");
        }

        wchar_t* sent_copy = wcsdup(text->sentences[i]->sentence);
        if(sent_copy == NULL){
            print_error(L"Memory allocate error (in function \"relace_big_words\").");
        }

        wchar_t** delims = delimiters(sent_copy);
        wchar_t* buffer;
        wchar_t* word = wcstok(sent_copy, L"\f\r\n\t\v ,", &buffer);

        int ind = 0;
        int len = 0;
        if(wcslen(word) > firstsize){
            len+=wcslen(L"(большое слово)");
            result = realloc(result, sizeof(wchar_t)*(len+100));

            if(result == NULL){
                print_error(L"Memory reallocate error (in function \"relace_big_words\").");
            }

            wcscpy(result, L"(большое слово)");
            word = wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
        }else{
            len+=wcslen(word);
            result = realloc(result, sizeof(wchar_t)*(len+100));

            if(result == NULL){
                print_error(L"Memory reallocate error (in function \"relace_big_words\").");
            }

            wcscpy(result, word);
            word = wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
        }

        
        
        while(word != NULL){
            if(wcslen(word) > firstsize){
                len+=wcslen(delims[ind]);
                len+=wcslen(L"(большое слово)");
                result = realloc(result, sizeof(wchar_t)*(len+100));

                if(result == NULL){
                    print_error(L"Memory reallocate error (in function \"relace_big_words\").");
                }

                wcscat(result, delims[ind]);
                wcscat(result, L"(большое слово)");
                word = wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
                ind++;
            }else{
                len+=wcslen(word);
                len+=wcslen(delims[ind]);
                result = realloc(result, sizeof(wchar_t)*(len+100));

                if(result == NULL){
                    print_error(L"Memory reallocate error (in function \"relace_big_words\").");
                }

                wcscat(result, delims[ind]);
                wcscat(result, word);
                word = wcstok(NULL, L"\f\r\n\t\v ,", &buffer);
                ind++;
            }
        }
        
        free(text->sentences[i]->sentence);
        text->sentences[i]->sentence = result;

        free(sent_copy);
        free(buffer);
        free(word);
    }

}