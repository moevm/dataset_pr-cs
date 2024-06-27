#include "delete_sentences_with_odd_numbers.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_odd_numbers(Sentence *sentence)
{
    for (int i = 0; i < sentence->len; i++)
    {
        wchar_t ch = sentence->chars[i];
        if (!iswdigit(ch))
            continue;
        if ((ch - L'0') % 2 != 0)
            return 1;
    }
    return 0;
}

void delete_sentences_with_odd_numbers(Text *text)
{
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        if (!has_odd_numbers(sentence))
            continue;

        free_sentence(sentence);
        text->len--;

        memmove(text->sentences + i, text->sentences + i + 1, (text->len - i) * sizeof(Sentence *));
        i--;
    }
}
