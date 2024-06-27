#include "special_symbol.h"

Sentence *replace_special_symbols(Sentence *sentence){
    Sentence *new_sentence = (Sentence*)malloc(sizeof(Sentence));
    if(new_sentence == NULL)
        leave(MEM_ERROR);
    new_sentence->data = (wchar_t*)malloc(sentence->len*sizeof(wchar_t));
    if(new_sentence->data == NULL)
        leave(MEM_ERROR);
    new_sentence->len = sentence->len; 
    wchar_t special[] = SPECIAL_SYMBOLS;
    wchar_t replace[] = REPLACE;
    size_t replace_len = wcslen(replace); 
    size_t new_i = 0; 

    for (size_t i = 0; i < sentence->len; i++){
        if (wcschr(special, sentence->data[i])){
            new_sentence->len += replace_len;
            new_sentence->data = realloc(new_sentence->data, (new_sentence->len*sizeof(wchar_t)));
            if(new_sentence->data == NULL)
                leave(MEM_ERROR);
            new_sentence->data[new_i] = SENT_END;
            new_sentence->data = wcscat(new_sentence->data, replace);
            new_i += replace_len;
        }else{
            new_sentence->data[new_i++] = sentence->data[i];
        }
    }
    return new_sentence;
}

void replace_special_in_text(Text *text){
    for(size_t i =0; i<(text->len);i++)
        text->data[i] = replace_special_symbols(text->data[i]);
}