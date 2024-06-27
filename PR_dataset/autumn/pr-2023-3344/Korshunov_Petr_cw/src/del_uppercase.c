#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include "structs.h"

void delUpperCase(TEXT *text)
{
    setlocale(LC_ALL, "C");
    for (int i = 0; i < text->len; i++)
    {
        int len = 0;
        for (int j = 0; j < text->sents[i]->len; j++)
        {
            if (!iswupper(text->sents[i]->sent[j]))
            {
                text->sents[i]->sent[len++] = text->sents[i]->sent[j];
            }
        }
        text->sents[i]->sent[len] = L'\0';
        text->sents[i]->len = len;
    }
    return;
}