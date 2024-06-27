#include "print_structure.h"


void print_structure(Text *structure)
{
    for (int i = 0; i < structure->countsents; i++)
    {
        if (structure->arrofsents[i]->arrofwords[0] == L"" && structure->arrofsents[i]->countwords == 1) continue;
        for (int j = 0; j < structure->arrofsents[i]->countwords-1; j++)
        {
            wprintf(L"%ls", structure->arrofsents[i]->arrofwords[j]);
            if (structure->arrofsents[i]->arrofseps[j] == L'!')
            {
                wprintf(L", ");
            }
            else
            {
                wprintf(L"%lc", structure->arrofsents[i]->arrofseps[j]);
            }
        }
        wprintf(L"%ls.\n", structure->arrofsents[i]->arrofwords[structure->arrofsents[i]->countwords-1]);
    }
}
