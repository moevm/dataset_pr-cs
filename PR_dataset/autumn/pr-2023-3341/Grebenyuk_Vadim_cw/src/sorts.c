#include "sorts.h"

#include <stdlib.h>

#include "util/vector.h"
#include "words.h"

int compare_avglen(const void* _first_word, const void* _second_word) {
    return ((*(String**)_first_word)->avglen > (*(String**)_second_word)->avglen) - ((*(String**)_first_word)->avglen < (*(String**)_second_word)->avglen);
}

int compare_len(const void* _first_str, const void* _second_str) {
    return ((*(String**)_first_str)->len < (*(String**)_second_str)->len) - ((*(String**)_first_str)->len > (*(String**)_second_str)->len);
}

// test error
int compare_word_count(const void* _first_str, const void* _second_str) {
    if ((*(String**)_first_str)->words == (*(String**)_second_str)->words)
        return ((*(String**)_first_str)->len > (*(String**)_second_str)->len) - ((*(String**)_first_str)->len < (*(String**)_second_str)->len);
    else
        return ((*(String**)_first_str)->words > (*(String**)_second_str)->words) - ((*(String**)_first_str)->words < (*(String**)_second_str)->words);
}

void sort_avgwordlen(Text* _text) {
    for (unsigned int i = 0; i < _text->len; i++) {
        Words* _tmp = from_string_with_sep(_text->body[i]);
        _text->body[i]->avglen = avg_len(_tmp);
        free_words(_tmp);
    }

    qsort(_text->body, _text->len, sizeof(String*), compare_avglen);
}

void sort_text_by_words(Text* _text) {
    qsort(_text->body, _text->len, sizeof(String*), compare_word_count);
}

void sort_text_all(Text* _text) {
    for (unsigned int i = 0; i < _text->len; i++)
        if (_text->body[i]->len != 0)
            sort_words(&_text->body[i]);
}

void sort_words(String** _str) {
    Words* _words = from_string_with_sep(*_str);
    qsort(_words->words->body, _words->words->len, sizeof(String*), compare_len);
    free(*_str);
    *_str = to_string(_words);
    free_words(_words);
}
