#include "delete_two_language_sentences.h"

bool check_two_language_sentence(Sentence *sentence){
    wchar_t latin_alphabet[] = LATIN_CHARS;
    wchar_t cyrillic_alphabet[] = CYRILLIC_CHARS;
    bool is_latin = false, is_cyrillic = false;
    for (size_t i=0;i<sentence->len;i++){
        if (sentence->data[i] == L' ' || sentence->data[i] == L','){
            is_latin = false;
            is_cyrillic = false;
            continue;
        }
        if (wcschr(latin_alphabet, sentence->data[i]))
            is_latin = true;
        if (wcschr(cyrillic_alphabet, sentence->data[i])) 
            is_cyrillic = true;
        if (is_latin && is_cyrillic)
            return true;
    }
    return false;
}

Text *delete_two_language_sentences(Text* text){
    Text *new_text = (Text*)malloc(sizeof(Text));
    if (new_text == NULL)
        leave(MEM_ERROR);
    new_text->len = 0;
    new_text->data = (Sentence**)malloc(text->len * sizeof(Sentence*));
    if (new_text->data == NULL)
        leave(MEM_ERROR);
    for(size_t i = 0; i < text->len ;i++){
        if (!check_two_language_sentence(text->data[i])){
            new_text->data[new_text->len] = text->data[i];
            new_text->len++;
        }else{
            free(text->data[i]->data);
            free(text->data[i]);
        }
    }
    free(text);
    new_text->data = realloc(new_text->data, new_text->len * sizeof(Sentence*));
    if (new_text->data == NULL)
        leave(MEM_ERROR);
    return new_text;
}