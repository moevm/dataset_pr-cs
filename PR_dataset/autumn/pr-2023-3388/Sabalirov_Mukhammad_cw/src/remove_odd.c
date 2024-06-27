#include "remove_odd.h"

bool odd_in_sentence(struct Sentence *sentence){
    for (size_t i = 0; i < sentence->len; i++)
        if (wcschr(ODS, sentence->data[i]) && sentence->data[i] != END_STR)
            return true;
    return false;
}

struct Text* remove_odd_text(struct Text *text){
    struct Text *new_text = malloc(sizeof(struct Text));
    if (new_text == NULL)
        panic(MEM_ERROR);
    
    new_text->data = NULL;
    new_text->len = 0;

    for(size_t i = 0; i < text->len; i++){
        if(!odd_in_sentence(text->data[i])){
            new_text->data = realloc(new_text->data, (new_text->len+1)*sizeof(struct Sentence*));
            if (new_text->data == NULL)
                panic(MEM_ERROR);
            new_text->data[new_text->len++] = text->data[i];
        }
    }
    
    return new_text;
}

