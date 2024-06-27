#include "double.h"

struct Sentence* make_double_sentence(struct Sentence *sentence){
    struct Sentence *new_sentence = malloc(sizeof(struct Sentence));
    if (new_sentence==NULL)
        panic(MEM_ERROR);
    new_sentence->len = 0;
    new_sentence->data = NULL;
    wchar_t *new_str = malloc(sizeof(wchar_t)*(sentence->len-1));
    size_t k = 0;
    while (sentence->data[k] != L'.')
    {
        new_str[k] = sentence->data[k];
        k++;
    }
    new_str[k] = END_STR;
    wchar_t *buffer;
    wchar_t *token = wcstok(new_str, L" ", &buffer);
    while(token) {
        for (size_t j = 0; j < 2; j++){
            for (size_t i = 0; i < wcslen(token); i++){
                new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
                if (new_sentence->data == NULL)
                    panic(MEM_ERROR);
                new_sentence->data[new_sentence->len++] = token[i];
            }
        new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
        if (new_sentence->data == NULL)
            panic(MEM_ERROR);
        new_sentence->data[new_sentence->len++] = L' ';
        }
        token = wcstok(NULL, L" ", &buffer);
    }
    new_sentence->data[new_sentence->len-1] = L'.';
    new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
    if (new_sentence->data == NULL)
        panic(MEM_ERROR);
    new_sentence->data[new_sentence->len++] = END_STR;
    return new_sentence;
}

struct Text* make_double_text(struct Text *text){
    struct Text *new_text = malloc(sizeof(struct Text));
    if (new_text == NULL)
        panic(MEM_ERROR);
    new_text->len = 0;
    new_text->data = NULL;
    for (size_t i; i < text->len; i++){
        new_text->data = realloc(new_text->data, (new_text->len+1)*sizeof(struct Sentence*));
        if (new_text->data == NULL)
            panic(MEM_ERROR);
        new_text->data[new_text->len++] = make_double_sentence(text->data[i]);
    }
    return new_text;
}