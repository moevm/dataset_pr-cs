#include "special_symbols.h"

int cmp (const void *first, const void *second){
    const wchar_t *f = (const wchar_t*)(first);
    const wchar_t *s = (const wchar_t*)(second);
    if (*f > *s)
        return -1;
    if (*f < *s)
        return 1;
    return 0;
}

struct Sentence* special_sentence(struct Sentence *sentence){
    struct Sentence *new_sentence = malloc(sizeof(struct Sentence));
    if (new_sentence == NULL)
        panic(MEM_ERROR);

    new_sentence->data = NULL;
    new_sentence->len = 0;

    for (size_t i = 0; i < sentence->len; i++){
        if (wcschr(SYMBOLS, sentence->data[i]) && sentence->data[i] != END_STR){
            new_sentence->data = realloc(new_sentence->data, (new_sentence->len+1)*sizeof(wchar_t));
            if (new_sentence->data == NULL)
                panic(MEM_ERROR);
            new_sentence->data[new_sentence->len++] = sentence->data[i];
        }
    }

    if (new_sentence->len==0){
        free(new_sentence);
        return NULL;
    }

    qsort(new_sentence->data, new_sentence->len, sizeof(wchar_t), cmp);

    new_sentence->data = realloc(new_sentence->data, (new_sentence->len+2)*sizeof(wchar_t));
    if (new_sentence->data == NULL)
        panic(MEM_ERROR);

    new_sentence->data[new_sentence->len++] = L'.';
    new_sentence->data[new_sentence->len++] = END_STR;
    return new_sentence;
}

struct Text* special_text(struct Text *text){
    struct Text *new_text = malloc(sizeof(struct Text));
    if (new_text == NULL)
        panic(MEM_ERROR);
    
    new_text->data = NULL;
    new_text->len = 0;

    for (size_t i = 0; i < text->len; i++){
        struct Sentence *new_sentence = special_sentence(text->data[i]);
        if (new_sentence == NULL)
            continue;
        new_text->data = realloc(new_text->data, (new_text->len+1)*sizeof(struct Sentence*));
        if (new_text->data == NULL)
            panic(MEM_ERROR);
        new_text->data[new_text->len++] = new_sentence;
    }
    return new_text;
}