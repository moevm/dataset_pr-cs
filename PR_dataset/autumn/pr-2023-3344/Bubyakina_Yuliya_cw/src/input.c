#include "input.h"
#include "sentence.h"
#include "text.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

int skip_if_at_start(wchar_t ch, int len)
{
    if (len)
        return 0;
    return (ch == L' ' || ch == L'\t' || ch == L'\n' || ch == L',');
}

int already_in_text(Text *text, Sentence *sentence)
{
    for (int i = 0; i < text->len; i++)
    {
        if (wcscasecmp(text->sentences[i]->chars, sentence->chars) == 0)
            return 1;
    }
    return 0;
}

Text *input()
{
    Text *text = create_text();
    wchar_t *ch = (wchar_t *)malloc(sizeof(wchar_t));
    int number_of_slashn = 0;
    do
    {
        Sentence *new_sentence = create_sentence();
        number_of_slashn = 0;
        wchar_t prev = L' ';
        do
        {
            *ch = getwchar();
            if (*ch == L'\n')
            {
                number_of_slashn++;
            }
            else if (prev == L'\n')
            {
                number_of_slashn = 0;
            }
            prev = *ch;

            if (skip_if_at_start(*ch, new_sentence->len))
            {
                continue;
            }
            if (*ch != L'.')
            {
                push_sentence(new_sentence, ch);
            }
        } while (number_of_slashn != 2 && *ch != L'.');

        if (number_of_slashn == 2)
        {
            if (new_sentence->len)
                new_sentence->len -= 2;
            new_sentence->chars[new_sentence->len] = L'\0';
        }

        if (already_in_text(text, new_sentence) || new_sentence->len == 0)
        {
            free_sentence(new_sentence);
        }
        else
        {
            push_text(text, new_sentence);
        }

    } while (number_of_slashn != 2);
    free(ch);

    return text;
}
