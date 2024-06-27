#include "tools/word.h"

Word_t *
init_word()
{
    Word_t *_word = (Word_t *)init_char_struct();

    _word->data = (wchar_t *)malloc(_word->capacity * sizeof(wchar_t));
    *_word->data = DEFAULT_WORD_END;

    return _word;
}

void free_word(Word_t *_word)
{
    free_char_struct(
        (Char_struct *)_word);
}

Word_t *
copy_word(const Word_t *_example)
{
    Word_t *word = init_word();
    word->end = _example->end;

    add_str(word, _example->data);

    return word;
}

wchar_t
get_char(Word_t *_word, Wsize_t i)
{
    return _word->data[i];
}

void _word_increase_capacity(Word_t *_word)
{
    _increase_capacity_char_struct(
        (Char_struct *)_word,
        sizeof(wchar_t));
}

Word_t *
add_char(Word_t *_word, wchar_t ch)
{
    if (_word->len + 1 >= _word->capacity)
        _word_increase_capacity(_word);

    _word->data[_word->len] = ch;
    _word->data[++_word->len] = L'\0';

    return _word;
}

Word_t *
add_str(Word_t *_word, const wchar_t *str)
{
    for (; *str != L'\0'; ++str)
        add_char(_word, *str);

    return _word;
}

static inline bool
_compare_chars(wchar_t ch1, wchar_t ch2, bool _register)
{
    if (_register)
        return ch1 == ch2;

    return towlower(ch1) == towlower(ch2);
}

bool compare_words(Word_t *word1, Word_t *word2, bool _register)
{
    if (word1->len != word2->len)
        return false;

    for (size_t i = 0; i < word1->len; ++i)
        if (!_compare_chars(
                get_char(word1, i),
                get_char(word2, i),
                _register))
            return false;

    return true;
}

bool is_number(Word_t *word)
{
    for (size_t i = 0; i < word->len; ++i)
    {
        if (!iswdigit(get_char(word, i)))
            return false;
    }

    return true;
}
