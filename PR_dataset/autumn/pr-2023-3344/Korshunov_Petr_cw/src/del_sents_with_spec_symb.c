#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void delSentsWithSpecSymbs(TEXT *text)
{
    for (int i = 0; i < text->len; i++)
    {
        if (wcspbrk(text->sents[i]->sent, L"№*$#@") != NULL)
        {
            free(text->sents[i]->sent);
            free(text->sents[i]);
            if (i != text->len - 1)
            {
                memmove(&text->sents[i], &text->sents[i + 1], (text->len - i - 1) * sizeof(SNT *));
            }
            text->len--;
            i--;
        }
    }
    return;
}