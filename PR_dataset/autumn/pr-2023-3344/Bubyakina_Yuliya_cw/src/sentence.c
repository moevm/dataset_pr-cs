#include "sentence.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Sentence *create_sentence()
{
    Sentence *sentence = (Sentence *)malloc(sizeof(Sentence));
    sentence->cap = 10;
    sentence->len = 0;
    sentence->chars = (wchar_t *)malloc(sentence->cap * sizeof(wchar_t));
    sentence->chars[0] = L'\0';
    return sentence;
}

void free_sentence(Sentence *sentence)
{
    free(sentence->chars);
    free(sentence);
}

void extend_sentence(Sentence *sentence)
{
    if (sentence->len < sentence->cap - 1)
        return;
    int diff = sentence->len - sentence->cap + 1;
    sentence->cap += diff + 10;
    sentence->chars = (wchar_t *)realloc((sentence->chars), sentence->cap * sizeof(wchar_t));
}

void push_sentence(Sentence *sentence, wchar_t *ch)
{
    sentence->len += wcslen(ch);
    extend_sentence(sentence);
    wcscat(sentence->chars, ch);
}

void print_sentence(Sentence *sentence)
{
    for (int i = 0; i < sentence->len; i++)
    {
        wprintf(L"%lc", sentence->chars[i]);
    }
    wprintf(L".\n");
}

int replace_n_at_index_sentence(Sentence *sentence, wchar_t *source, int n, int i)
{
    if (i >= sentence->len || n > sentence->len)
        return 0;
    int source_len = wcslen(source);
    int len_diff = source_len - n;

    sentence->len += len_diff;
    extend_sentence(sentence);

    int num_to_move = sentence->len - i - source_len;
    if (num_to_move > 0)
    {
        wmemmove(sentence->chars + i + source_len, sentence->chars + i + n, num_to_move);
    }
    wmemcpy(sentence->chars + i, source, source_len);

    return len_diff;
}
