#include "cyrillic.h"

bool is_cyrillic(wchar_t c){
    return ((L'а' <= towlower(c) && towlower(c) <= L'я') || towlower(c) == L'ё');
}

struct Dict* initial_cyrillic_dict(){
    struct Dict *dict = malloc(sizeof(struct Dict));
    if (dict == NULL) 
        panic(MEM_ERROR);

    dict->keys = CYRILLIC;
    wchar_t values[CYRILLIC_COUNT][TRANSLIT_LEN] = CYRILLIC_TRANSLIT;
    dict->values = malloc(sizeof(wchar_t*) * CYRILLIC_COUNT);
    if (dict->values == NULL)
        panic(MEM_ERROR);

    for (size_t i = 0; i < CYRILLIC_COUNT; i++) {
        dict->values[i] = wcsdup(values[i]);
        if (dict->values[i] == NULL)
            panic(MEM_ERROR);
    }
    
    return dict;
}

struct Sentence* translit_sentence(struct Sentence *sentence, struct Dict *dict){
    struct Sentence *new_sentence = malloc(sizeof(struct Sentence));
    if (new_sentence == NULL)
        panic(MEM_ERROR);

    new_sentence->last_index = -1;
    new_sentence->len = 0;
    new_sentence->data = NULL;

    size_t trans_index;

    for(size_t i = 0; sentence->data[i]; i++){
        if (is_cyrillic(sentence->data[i])){
            trans_index = find_value(sentence->data[i], dict, CYRILLIC_COUNT);
            for(size_t j = 0; dict->values[trans_index][j]; j++){
                new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
                if (new_sentence->data == NULL)
                    panic(MEM_ERROR);
                new_sentence->data[new_sentence->len++] = dict->values[trans_index][j];
            }
        }
        else{
            new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
            if (new_sentence->data == NULL)
                panic(MEM_ERROR);
            new_sentence->data[new_sentence->len++] = sentence->data[i];
        }
    }

    new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1) * sizeof(wchar_t));
    if (new_sentence->data == NULL)
        panic(MEM_ERROR);
    new_sentence->data[new_sentence->len++] = END_STR;
    return new_sentence;
}

struct Text* translit_text(struct Text *text, struct Dict *dict) {
    struct Text *new_text = malloc(sizeof(struct Text));
    if (new_text == NULL)
        panic(MEM_ERROR);
    new_text->len = 0;
    new_text->data = NULL;

    for (size_t i = 0; i < text->len; i++) {
        new_text->data = realloc(new_text->data, (new_text->len + 1) * sizeof(struct Sentence));
        if (new_text->data == NULL)
            panic(MEM_ERROR);
        new_text->data[new_text->len++] = translit_sentence(text->data[i], dict);
    }

    return new_text;
}
