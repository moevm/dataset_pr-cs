#include "replace_nums.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

const wchar_t *find_bin(wchar_t ch)
{
    switch (ch)
    {
    case L'0':
        return L"0";
    case L'1':
        return L"1";
    case L'2':
        return L"10";
    case L'3':
        return L"11";
    case L'4':
        return L"100";
    case L'5':
        return L"101";
    case L'6':
        return L"110";
    case L'7':
        return L"111";
    case L'8':
        return L"1000";
    case L'9':
        return L"1001";
    
    default:
        return L"";
    }
}

void replace_nums(Text *text)
{
    wchar_t *replacement = (wchar_t *)malloc(10 * sizeof(wchar_t));
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        for (int j = 0; j < sentence->len; j++)
        {
            wchar_t ch = sentence->chars[j];
            if (!iswdigit(ch))
                continue;
           
            swprintf(replacement, 10, L"%ls", find_bin(ch));

            j += replace_n_at_index_sentence(sentence, replacement, 1, j);
        }
    }
    free(replacement);
}
