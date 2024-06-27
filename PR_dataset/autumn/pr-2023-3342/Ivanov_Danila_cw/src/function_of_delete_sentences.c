#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "structs.h"

struct Text func_of_delete_sentences(struct Text text){
    const wchar_t* letters_rus = L"бвгджзйклмнпрстфхцчшщъьБВГДЖЗЙКЛМНПРСТФХЦЧШЩЪЬ";
    const wchar_t* letters_eng = L"bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    struct Text text_res;
    struct Sentence str;
    struct Sentence str_0;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        wchar_t* last_word = str.list_of_words[str.count_of_words - 1];
        if (wcslen(last_word) < 3 || !((wcschr(letters_rus, last_word[wcslen(last_word) - 1]) != NULL || wcschr(letters_eng, last_word[wcslen(last_word) - 1]) != NULL)  && 
        (wcschr(letters_rus, last_word[wcslen(last_word) - 2]) != NULL || wcschr(letters_eng, last_word[wcslen(last_word) - 2]) != NULL) && 
        (wcschr(letters_rus, last_word[wcslen(last_word) - 3]) != NULL || wcschr(letters_eng, last_word[wcslen(last_word) - 3]) != NULL))){
            text_res.list_of_sentences[index++] = str;
            text_res.list_of_sentences = realloc(text_res.list_of_sentences, (index + 1) * sizeof(struct Sentence));
        }
    }
    text_res.count_of_sentences = index;
    return text_res;
}
