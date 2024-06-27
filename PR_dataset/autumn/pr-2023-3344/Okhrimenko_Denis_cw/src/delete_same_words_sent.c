#include "delete_same_words_sent.h"

//Удалить все предложения, которые начинаются и заканчиваются на одно и то же слово.
void delete_same_words_sent(text_t* text)
{
    for(size_t i = 0; i < text->size; ++i){
        wchar_t* first_word;
        wchar_t* last_word;
        wchar_t* cur_sent = (wchar_t*)malloc(sizeof(wchar_t) * (1 + text->data[i]->size));
        if(cur_sent == NULL) (L"Failed to allocate memory for the cur_sent [fn: delete_same_words_sent]");
        wcsncpy(cur_sent, text->data[i]->data, 1 + text->data[i]->size);
        wchar_t* pwc;
        wchar_t* pt;
        pwc = wcstok(cur_sent, L" ,;.", &pt);
        first_word = pwc;
        while(pwc != NULL){
            last_word = pwc;
            pwc = wcstok(NULL, L" ,;.", &pt);
        }
        if(!wcsncmp(first_word, last_word, wcslen(last_word))){
            text->size--;
            for(size_t j = i; j < text->size; ++j){
                text->data[j] = text->data[j + 1];
            }
            i--;
        }
        free(cur_sent);
    }
}
