#include "switch_first_word.h"


void switch_first_word(Text *structure)
{
    if ( structure->countsents == 1 && structure->arrofsents[0]->countwords == 1)
    {
        exit(0);
    }
    if ( structure->countsents == 1)
    {
        structure->arrofsents[0]->arrofwords[0] = L"";
    }
    else
    {

        for (int i = 1; i < structure->countsents; i++)
        {
            if (structure->arrofsents[i - 1]->arrofwords[1])
            {
                structure->arrofsents[i]->arrofwords[0] = structure->arrofsents[i - 1]->arrofwords[1];
            }
            else
            {
                structure->arrofsents[i]->arrofwords[0] = L"";
            }
        }
        if (structure->arrofsents[structure->countsents - 1]->arrofwords[1])
        {
            structure->arrofsents[0]->arrofwords[0] = structure->arrofsents[structure->countsents - 1]->arrofwords[1];
        }
        else
        {
            structure->arrofsents[0]->arrofwords[0] = L"";
        }
    }
}
