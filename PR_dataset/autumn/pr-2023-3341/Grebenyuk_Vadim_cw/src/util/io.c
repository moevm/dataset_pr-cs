#include "io.h"

#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

#include "config.h"
#include "vector.h"

void remove_duplicats(Text* _text);

void remove_whithout_dot(Text* _text);

Text* read_text() {
    Text* _text = new_text(MIN_VECTOR_SIZE);
    int newline = 0;
    int ended = 1;
    int word = 0;
    for (wchar_t ch = getwchar(); newline < 2; ch = getwchar()) {
        switch (ch) {
            case L'\n':
                newline++;
                if (!ended)
                    append_wchar(_text, L' ');
                break;
            case L'.':
                ended = 1;
                append_wchar(_text, ch);
            case L' ':
            case L',':
                word = 0;
                if (!ended)
                    append_wchar(_text, ch);
                break;
            default:
                if (ended)
                    append_new_string(&_text);
                if (!word) {
                    (*last_string(_text))->words++;
                    word = 1;
                }
                ended = 0;
                newline = 0;
                append_wchar(_text, ch);
                break;
        }
    }
    if (_text->len > 0) {
        remove_duplicats(_text);
        remove_whithout_dot(_text);
    }
    return _text;
}

void output_text(Text* _text) {
    for (unsigned int i = 0; i < _text->len; i++)
        if (_text->body[i]->len != 0)
            printf("%ls\n", _text->body[i]->body);
}

void remove_whithout_dot(Text* _text) {
    if (wcsstr((*last_string(_text))->body, L".") == 0)
        clear(last_string(_text));
};

void remove_duplicats(Text* _text) {
    for (unsigned int i = 0; i < _text->len - 1; i++)
        if (_text->body[i]->len != 0)
            for (unsigned int j = i + 1; j < _text->len; j++)
                if (wcscasecmp(_text->body[i]->body, _text->body[j]->body) == 0)
                    clear(&_text->body[j]);
};
