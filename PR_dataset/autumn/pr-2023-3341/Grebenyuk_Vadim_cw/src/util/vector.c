#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "error.h"

String** last_string(Text* _text) {
    return &_text->body[_text->len - 1];
}

String* extend_string(String* _str) {
    String* _new_str = new_string(_str->allocated * 2);
    wmemcpy(_new_str->body, _str->body, _str->len);
    _new_str->len = _str->len;
    _new_str->words = _str->words;
    free(_str);
    return _new_str;
}

void clear(String** _str) {
    free(*_str);
    *_str = new_string(MIN_VECTOR_SIZE);
}

Text* extend_text(Text* _text) {
    Text* _new_text = new_text(_text->allocated * 2);
    memcpy(_new_text->body, _text->body, _text->len * sizeof(String*));
    _new_text->len = _text->len;
    free(_text);
    return _new_text;
}

String* new_string(unsigned int _size) {
    String* _new_str = calloc(sizeof(String) + _size * sizeof(wchar_t), 1);
    if (_new_str == NULL) {
        ERROR("Failed to allocate new string", 1);
        exit(0);  // fix warning
    }
    _new_str->allocated = _size;
    _new_str->len = 0;
    return _new_str;
}

Text* new_text(unsigned int _size) {
    Text* _new_text = calloc(sizeof(Text) + _size * sizeof(String*), 1);
    if (_new_text == NULL) {
        ERROR("Failed to allocate new text", 1);
        exit(0);  // fix linter warning
    }
    _new_text->allocated = _size;
    return _new_text;
}

void append_wchar(Text* _text, wchar_t _ch) {
    String** _last = last_string(_text);
    if ((*_last)->allocated == (*_last)->len + 1)
        *last_string(_text) = extend_string(*_last);
    (*_last)->body[(*_last)->len++] = _ch;
};

void append_new_string(Text** _text) {
    if ((*_text)->allocated == (*_text)->len)
        *_text = extend_text(*_text);
    (*_text)->len++;
    *last_string(*_text) = new_string(MIN_VECTOR_SIZE);
};

void free_text(Text* _text) {
    for (unsigned int i = 0; i < _text->len; i++)
        free(_text->body[i]);
    free(_text);
}
