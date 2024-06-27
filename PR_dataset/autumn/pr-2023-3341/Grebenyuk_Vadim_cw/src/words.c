#include "words.h"

#include <stdlib.h>
#include <wchar.h>

#include "util/error.h"
#include "util/vector.h"

inline float avg_len(Words* _words);

Words* from_string_with_sep(String* _str) {
    static Words* _new_words;
    _new_words = calloc(1, sizeof(Words));
    if (_new_words == 0) {
        ERROR("Failed to allocate new words", 1);
        exit(0);  // fix warning
    }
    _new_words->words = new_text(_str->words + 1);
    _new_words->separators = new_text(_str->words + 1);
    _new_words->strlen = _str->len;

    int sep = 1;
    for (unsigned int i = 0; i < _str->len; i++) {
        switch (_str->body[i]) {
            case L' ':
            case L',':
            case L'.':
                if (sep != 1) {
                    append_new_string(&_new_words->separators);
                    sep = 1;
                }
                append_wchar(_new_words->separators, _str->body[i]);
                break;
            default:
                if (sep != 0) {
                    append_new_string(&_new_words->words);
                    sep = 0;
                }
                append_wchar(_new_words->words, _str->body[i]);
                break;
        }
    }
    return _new_words;
}

String* to_string(Words* _words) {
    static String* _new_string;
    _new_string = new_string(_words->strlen + 2);
    _new_string->len = _words->strlen;
    _new_string->words = _words->words->len;
    for (unsigned int i = 0; i < _words->words->len; i++) {
        wcscat(_new_string->body, _words->words->body[i]->body);
        wcscat(_new_string->body, _words->separators->body[i]->body);
    }
    return _new_string;
}

float avg_len(Words* _words) {
    float sum = 0;

    if (_words->words->len == 0)
        return 0;

    for (unsigned int i = 0; i < _words->words->len; i++)
        sum += _words->words->body[i]->len;

    return sum / _words->words->len;
}

void free_words(Words* _words) {
    free_text(_words->words);
    free_text(_words->separators);
    free(_words);
}
