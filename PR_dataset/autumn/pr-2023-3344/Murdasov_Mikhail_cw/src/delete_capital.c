#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "print_func.h"

void delete_capital(struct Text* text){
    
    for (int i = 0; i < text->len; i++) {
        wchar_t* sentence_copy = wcsdup(text->sentences[i]->sentence);
        if (sentence_copy == NULL){
            print_error(L"Memory allocation error. (in function \"delete_capital\")");
        }

        wchar_t* buffer;
        wchar_t* word = wcstok(sentence_copy, L" .,\f\r\n\t\v", &buffer);
        while (word != NULL) {
            int len = wcslen(word);
            if (iswupper(word[len - 1])) {
                wchar_t* found = wcsstr(text->sentences[i]->sentence, word);
                if (found != NULL) {
                    memmove(found, found + wcslen(word), sizeof(wchar_t) * (wcslen(found + wcslen(word)) + 1));
                    sentence_copy = text->sentences[i]->sentence;
                }
            }
            word = wcstok(NULL, L" .,\f\r\n\t\v", &buffer);
        }

        int void_sent = 1;
        if(wcslen(sentence_copy) != 0){
            for(int i = 0; i < wcslen(sentence_copy); i++){
                if(!iswspace(sentence_copy[i])){
                    void_sent = 0;
                    break;
                }
            }
        }
        if(wcslen(sentence_copy) == 0 || void_sent == 1){
            text->sentences[i]->sentence = NULL;
        }
        
    }
}
