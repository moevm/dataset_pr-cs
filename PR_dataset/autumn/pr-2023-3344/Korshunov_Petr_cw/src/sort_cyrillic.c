#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "structs.h"

int countCyrillicLetters(SNT *str)
{
    int count = 0;
    for (int i = 0; i < str->len; i++)
    {
        setlocale(LC_ALL, "");
        if (iswalnum(str->sent[i]))
        {
            count++;
        }
        setlocale(LC_ALL, "C");
        if (iswalnum(str->sent[i]))
        {
            count--;
        }
    }
    return count;
}

int cmp(const void *a, const void *b)
{
    return -(countCyrillicLetters(*(SNT **)a) - countCyrillicLetters(*(SNT **)b));
}