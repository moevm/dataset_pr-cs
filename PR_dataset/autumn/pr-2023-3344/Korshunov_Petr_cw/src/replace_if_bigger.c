#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include "structs.h"

void replaceIfBigger(TEXT *text)
{
    wchar_t *pt;
    wchar_t *copy = malloc((text->sents[0]->len + 1) * sizeof(wchar_t));
    wcscpy(copy, text->sents[0]->sent);
    int word_len = wcslen(wcstok(copy, L"\n", &pt));
    wmemmove(text->sents[0]->sent, text->sents[0]->sent + word_len + 1, text->sents[0]->len);
    text->sents[0]->len = text->sents[0]->len - word_len - 1;
    wchar_t word_to_rep[] = L"(большое слово)";
    for (int i = 0; i < text->len; i++)
    {
        wchar_t *ptr;
        wchar_t *copy_str = malloc((text->sents[i]->len + 1) * sizeof(wchar_t));
        wchar_t *copy_str2 = malloc((text->sents[i]->len + 1) * sizeof(wchar_t) * 100);
        wcscpy(copy_str, text->sents[i]->sent);
        wchar_t *res = wcstok(copy_str, L" \t\n,.", &ptr);
        int length = 0;
        int len_fin = 0;
        while (res != NULL)
        {
            if (wcslen(res) > word_len)
            {
                wcscat(copy_str2, word_to_rep);
                len_fin += wcslen(word_to_rep);
            }
            else
            {
                wcscat(copy_str2, res);
                len_fin += wcslen(res);
            }
            length += wcslen(res);
            while (!iswalpha(text->sents[i]->sent[length]))
            {
                copy_str2[len_fin++] = text->sents[i]->sent[length++];
            }
            res = wcstok(NULL, L" \t\n,.", &ptr);
        }
        free(text->sents[i]->sent);
        text->sents[i]->sent = copy_str2;
        text->sents[i]->len = wcslen(copy_str2);
        text->sents[i]->len = sizeof(copy_str2);
    }
    return;
}