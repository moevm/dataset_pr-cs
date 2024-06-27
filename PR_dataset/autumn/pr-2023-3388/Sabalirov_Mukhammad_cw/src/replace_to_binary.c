#include "replace_to_binary.h"

struct Sentence* bin_sentence(struct Sentence *sentence){
    struct Dict dict;
    dict.keys = DIGITS;
    dict.values = (wchar_t *[])BIN_DIGITS;
    
    struct Sentence *new_sentence = malloc(sizeof(struct Sentence));
    if (new_sentence == NULL)
        panic(MEM_ERROR);
    
    new_sentence->len = 0;
    new_sentence->data = NULL;

    size_t bin_len, bin_index;
    for (size_t i = 0; i < sentence->len; i++){
        if (!iswdigit(sentence->data[i])){
            new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1)*sizeof(wchar_t));
            if (new_sentence->data == NULL)
                panic(MEM_ERROR);
            
            new_sentence->data[new_sentence->len++] = sentence->data[i];    
        }
        else{
            bin_index = find_value(sentence->data[i], &dict, DIGITS_COUNT);
            bin_len = wcslen(dict.values[bin_index]);
            for (size_t j = 0; j < bin_len; j++){
                new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1)*sizeof(wchar_t));
                if (new_sentence->data == NULL)
                panic(MEM_ERROR);
            
                new_sentence->data[new_sentence->len++] = dict.values[bin_index][j];  
            }
        }
    }
    new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1)*sizeof(wchar_t));
    if (new_sentence->data == NULL)
        panic(MEM_ERROR);
            
    new_sentence->data[new_sentence->len++] = END_STR;
    return new_sentence;  
}

struct Text* bin_text(struct Text *text){
    struct Text *new_text = malloc(sizeof(struct Text));
    if (new_text==NULL)
        panic(MEM_ERROR);
    new_text->len = 0;
    new_text->data = NULL;

    size_t i;
    for (i = 0; i < text->len; i++){
        struct Sentence *new_sentence = bin_sentence(text->data[i]);
        new_text->data = realloc(new_text->data, (new_text->len+1)*sizeof(struct Sentence*));
        if (new_text->data == NULL)
            panic(MEM_ERROR);
        
        new_text->data[new_text->len++] = new_sentence;
    }
    
    return new_text;
}