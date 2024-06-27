#include "free.h"

void free_dict(struct Dict *dict){
    for (size_t i = 0; i < CYRILLIC_COUNT; i++)
        free(dict->values[i]);
    free(dict->values);
    free(dict);
}

void free_text(struct Text *text){
    for (size_t i = 0; i < text->len; i++){
        free(text->data[i]->data);
        free(text->data[i]);
    }
    free(text);
}