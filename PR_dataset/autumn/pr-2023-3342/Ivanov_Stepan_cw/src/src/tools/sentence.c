#include "tools/sentence.h"

Sentence_t *
init_sentence()
{
    Sentence_t *_sentence = (Sentence_t *)init_char_struct();

    _sentence->data = (Word_t **)malloc(_sentence->capacity * sizeof(Word_t *));
    _sentence->end = DEFAULT_SENTENCE_END;

    return _sentence;
}

void free_sentence(Sentence_t *_sentence)
{
    for (size_t i = 0; i < _sentence->len; i++)
        free_word(_sentence->data[i]);

    free_char_struct(
        (Char_struct *)_sentence);
}

Word_t *
get_word(Sentence_t *_sentence, Ssize_t i)
{
    return _sentence->data[i];
}

void _sentence_increase_capacity(Sentence_t *_sentence)
{
    _increase_capacity_char_struct(
        (Char_struct *)_sentence,
        sizeof(Word_t *));
}

Sentence_t *
add_word(Sentence_t *_sentence, Word_t *_word)
{
    if (_sentence->len + 1 >= _sentence->capacity)
        _sentence_increase_capacity(_sentence);

    _sentence->data[_sentence->len++] = _word;

    return _sentence;
}

bool compare_sentences(Sentence_t *sentence1, Sentence_t *sentence2, bool _register)
{
    if (sentence1->len != sentence2->len)
        return false;

    Word_t *word1, *word2;

    for (size_t i = 0; i < sentence1->len; ++i)
    {
        word1 = get_word(sentence1, i);
        word2 = get_word(sentence2, i);

        if (!compare_words(
                word1, word2,
                false))
            return false;

        if (word1->end != word2->end)
            return false;
    }

    return true;
}

Sentence_t *
delete_word(Sentence_t *_sentence, Ssize_t _i)
{
    Word_t *_word = get_word(_sentence, _i);

    if (_word->end == L'.')
        get_word(_sentence, _i - 1)->end = L'.';

    _sentence->capacity = --_sentence->len;
    Word_t **new_data = (Word_t **)malloc(_sentence->capacity * sizeof(Word_t *));

    for (size_t i = 0, j = 0; j < _sentence->capacity; ++i)
    {
        if (get_word(_sentence, i) == _word)
            continue;

        new_data[j++] = _sentence->data[i];
    }

    free(_sentence->data);
    _sentence->data = new_data;

    free_word(_word);

    return _sentence;
}