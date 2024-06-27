#include <stdlib.h>
#include <wchar.h>
#include "structs.h"

void freeText(TEXT *t)
{
    for (int i = 0; i < t->len; i++)
    {
        free(t->sents[i]->sent);
        free(t->sents[i]);
    }
    free(t->sents);
    return;
}

void printText(TEXT *t)
{
    for (int i = 0; i < t->len; i++)
    {
        wprintf(L"%ls\n", t->sents[i]->sent);
    }
    return;
}