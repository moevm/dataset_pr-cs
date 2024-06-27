#include "sentence.h"
#include <stdlib.h>
#include <stdio.h>

void initial_sentence(Sentence *str)
{
    str->capacity_sep = 2;
    str->count_sep = 0;
    str->capacity_words = 2;
    str->count_words = 0;
    Word **pointer_words = malloc((str->capacity_words) * sizeof(Word *));
    if (pointer_words == NULL)
    {
        fputws(L"Ошибка. Невозомжно выделить память под массив слов\n", stderr);
        exit(0);
    }
    str->array_of_words = pointer_words;
    Word **pointer_sep = malloc((str->capacity_sep) * sizeof(Word *));
    if (pointer_sep == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под массив разделителей\n", stderr);
        exit(0);
    }
    str->array_of_sep = pointer_sep;
}

Sentence *make_sentence()
{
    Sentence *pointer = (Sentence *)malloc(sizeof(Sentence));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под предложение\n", stderr);
        exit(0);
    }
    Sentence *str = pointer;
    initial_sentence(str);
    return str;
}

void expand_array_words(Sentence *str)
{
    str->capacity_words += 1;
    Word **pointer = (Word **)realloc(str->array_of_words, sizeof(Word *) * (str->capacity_words));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно расширить память под массив слов\n", stderr);
        exit(0);
    }
    str->array_of_words = pointer;
}

void expand_array_sep(Sentence *str)
{
    str->capacity_sep += 1;
    Word **pointer = (Word **)realloc(str->array_of_sep, sizeof(Word *) * (str->capacity_sep));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно расширить память под массив разделителей\n", stderr);
        exit(0);
    }
    str->array_of_sep = pointer;
}

int sentence_comparison(const Sentence *sent1, const Sentence *sent2)
{
    if (sent1->count_words != sent2->count_words)
        return 0;
    if (sent1->count_sep != sent2->count_sep)
        return 0;
    for (size_t i = 0; i < sent1->count_words; i++)
    {
        if (word_comparison(sent1->array_of_words[i], sent2->array_of_words[i]))
            return 0;
    }
    for (size_t i = 0; i < sent1->count_sep; i++)
    {
        if (word_comparison(sent1->array_of_sep[i], sent2->array_of_sep[i]))
            return 0;
    }
    return 1;
}

int sentence_is_in_text(Sentence **array_of_sentences, Sentence *sent, int countsents)
{
    if (countsents == 0)
        return 1;
    for (size_t i = 0; i < countsents; i++)
    {
        if ((sent->count_words) != (array_of_sentences[i]->count_words))
            continue;
        if ((sent->count_sep) != (array_of_sentences[i])->count_sep)
            continue;
        if (sentence_comparison(sent, array_of_sentences[i]))
            return 0;
    }
    return 1;
}

void free_sentence(Sentence *sent)
{
    if (sent)
    {
        for (size_t i; i < sent->count_words; i++)
        {
            free_word(sent->array_of_words[i]);
        }
        for (size_t i; i < sent->count_sep; i++)
        {
            free_word(sent->array_of_sep[i]);
        }
    }
    free(sent);
}