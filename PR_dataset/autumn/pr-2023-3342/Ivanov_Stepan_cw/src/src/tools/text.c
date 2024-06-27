#include "tools/text.h"

Text_t *
init_text()
{
    Text_t *_text = (Text_t *)init_char_struct();

    _text->data = (Sentence_t **)malloc(_text->capacity * sizeof(Sentence_t *));
    _text->end = DEFAULT_TEXT_END;

    return _text;
}

void free_text(Text_t *_text)
{
    for (size_t i = 0; i < _text->len; i++)
        free_sentence(_text->data[i]);

    free_char_struct(
        (Char_struct *)_text);
}

Sentence_t *
get_sentence(Text_t *_text, Tsize_t i)
{
    return _text->data[i];
}

void _text_increase_capacity(Text_t *_text)
{
    _increase_capacity_char_struct(
        (Char_struct *)_text,
        sizeof(Sentence_t *));
}

Text_t *
add_sentence(Text_t *_text, Sentence_t *_sentence)
{
    if (_text->len + 1 >= _text->capacity)
        _text_increase_capacity(_text);

    _text->data[_text->len++] = _sentence;

    return _text;
}

Text_t *
delete_sentence(Text_t *_text, Tsize_t _i)
{
    Sentence_t *_sentence = get_sentence(_text, _i);

    if (_sentence->end == L'\n')
        get_sentence(_text, _i - 1)->end = L'\n';

    _text->capacity = --_text->len;
    Sentence_t **new_data = (Sentence_t **)malloc(_text->capacity * sizeof(Sentence_t *));

    for (size_t i = 0, j = 0; j < _text->capacity; ++i)
    {
        if (get_sentence(_text, i) == _sentence)
            continue;

        new_data[j++] = _text->data[i];
    }

    free(_text->data);
    _text->data = new_data;

    free_sentence(_sentence);

    return _text;
}
