#include "print_colourwords.h"



int is_digitsentence(wchar **sent, unsigned countwords)
{
    unsigned lenword = 0;
    for (int i = 0; i < countwords; i++)
    {
        lenword = wcslen(sent[i]);
        if (lenword % 2 != 0 && iswdigit(sent[i][lenword / 2])) return 1;
    }
    return 0;
}

void print_colourwords(Text *structure)
{
    unsigned lenword = 0;
    for (int i = 0; i < structure->countsents; i++)
    {
        if (is_digitsentence(structure->arrofsents[i]->arrofwords, structure->arrofsents[i]->countwords))
        {
            for (int k = 0; k < structure->arrofsents[i]->countwords-1; k++)
            {
                lenword = wcslen(structure->arrofsents[i]->arrofwords[k]);
                if (lenword % 2 != 0 && iswdigit(structure->arrofsents[i]->arrofwords[k][lenword / 2]))
                {
                    wprintf(L"\033[01;32m%ls\033[0m", structure->arrofsents[i]->arrofwords[k]);
                    if (structure->arrofsents[i]->arrofseps[k] == L'!')
                    {
                        wprintf(L", ");
                    }
                    else
                    {
                        wprintf(L"%lc", structure->arrofsents[i]->arrofseps[k]);
                    }
                }
                else
                {
                    wprintf(L"%ls", structure->arrofsents[i]->arrofwords[k]);
                    if (structure->arrofsents[i]->arrofseps[k] == '!')
                    {
                        wprintf(L", ");
                    }
                    else
                    {
                        wprintf(L"%lc", structure->arrofsents[i]->arrofseps[k]);
                    }
                }
            }
            lenword = wcslen(structure->arrofsents[i]->arrofwords[structure->arrofsents[i]->countwords-1]);
            if (lenword % 2 != 0 && iswdigit(structure->arrofsents[i]->arrofwords[structure->arrofsents[i]->countwords-1][lenword / 2]))
            {
                wprintf(L"\033[01;32m%ls.\n\033[0m", structure->arrofsents[i]->arrofwords[structure->arrofsents[i]->countwords-1]);
            }
            else
            {
                wprintf(L"%ls.\n", structure->arrofsents[i]->arrofwords[structure->arrofsents[i]->countwords-1]);
            }
        }
    }
}
