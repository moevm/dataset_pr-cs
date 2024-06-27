#include "text_to_words.h"

text_t* text_to_words(text_t* text)
{
    size_t top_words = 0;
    sentence_t** words = (sentence_t**)malloc(sizeof(sentence_t*));
    if(words == NULL) printError(L"Failed to allocate memory for the words");
    words[top_words] = (sentence_t*)malloc(sizeof(sentence_t));
    if(words[top_words] == NULL) printError(L"Failed to allocate memory for the word");
    for(size_t i = 0; i < text->size; ++i){
        wchar_t* cur_sent = text->data[i]->data;
        wchar_t* pwc;
        wchar_t* pt;
        pwc = wcstok(cur_sent, L" ,;.!?", &pt);
        while(pwc != NULL){
            words[top_words]->size = wcslen(pwc);
            words[top_words++]->data = pwc;
            words = (sentence_t**)realloc(words, sizeof(sentence_t*) * (top_words + 1));
            if(words == NULL) printError(L"Failed to reallocate memory for the words");
            words[top_words] = (sentence_t*)malloc(sizeof(sentence_t));
            if(words[top_words] == NULL) printError(L"Failed to allocate memory for the word");
            pwc = wcstok(NULL, L" ,;.!?", &pt);
        }
    }
    text_t* result = (text_t*)malloc(sizeof(text_t));
    if(result == NULL) printError(L"Failed to allocate memory for the text_t* words");
    result->data = words;
    result->size = top_words;
    return result;
}
