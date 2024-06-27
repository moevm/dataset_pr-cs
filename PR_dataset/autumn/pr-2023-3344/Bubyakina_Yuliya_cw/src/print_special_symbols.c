#include "print_special_symbols.h"
#include <stdlib.h>
#include <string.h>

int codes_comp(wchar_t *a, wchar_t *b)
{
    return (*b) - (*a);
}

void print_special_symbols(Text *text)
{
    wchar_t *ch = (wchar_t *)malloc(2 * sizeof(wchar_t));
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        Sentence *symbols = create_sentence();

        for (int j = 0; j < sentence->len; j++)
        {
            swprintf(ch, 2, L"%lc", sentence->chars[j]);
            if (wcschr(L"№*$#@", *ch))
                push_sentence(symbols, ch);
        }

        if (symbols->len)
        {
            qsort(symbols->chars, symbols->len, sizeof(wchar_t), (int (*)(const void *, const void *))codes_comp);
            print_sentence(symbols);
        }
        else
        {
            wprintf(L"В предложении нет специальных символов.\n");
        }

        free_sentence(symbols);
    }
    free(ch);
}
