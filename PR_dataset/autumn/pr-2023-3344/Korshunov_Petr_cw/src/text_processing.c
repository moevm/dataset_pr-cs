#include <wchar.h>
#include <wctype.h>
#include "structs.h"

void delFirstSymbols(SNT *snt)
{
    wchar_t *temp = snt->sent;
    while (*temp && (iswspace(*temp)))
    {
        temp++;
    }
    wmemmove(snt->sent, temp, wcslen(temp) + 1);
    return;
}

int delRepeatingSents(SNT *temp, SNT **text, int len)
{
    for (int i = 0; i < len; i++)
    {
        int flag = 1;
        if (temp->len == text[i]->len)
        {
            for (int j = 0; j < temp->len; j++)
            {
                if (towlower(temp->sent[j]) != towlower(text[i]->sent[j]))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                return 0;
            }
        }
    }
    return 1;
}