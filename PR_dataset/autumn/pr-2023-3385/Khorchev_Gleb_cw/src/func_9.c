#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "struct.h"

size_t yea_it_is(wchar_t* word, wchar_t* keyword)
{
    if ( word[0] == L'\n')
    {
    for(size_t i=1; i < wcslen(word)-1; i++)
        {
            size_t Flag = 0;
            for(size_t j=0; j < wcslen(keyword); j++)
            {
                if ( towlower(word[i]) == towlower(keyword[j]) )
                {
                    Flag = 1;
                    break;
                }
            }
            if (!Flag ) return 0;
        }
        return 1;
    }
    else{
    for(size_t i=0; i < wcslen(word)-1; i++)
    {
        size_t Flag = 0;
        for(size_t j=0; j < wcslen(keyword); j++)
        {
            if ( towlower(word[i]) == towlower(keyword[j]) )
            {
                Flag = 1;
                break;
            }
        }
        if (!Flag ) return 0;
    }
    return 1;}
}



void f_9(text text_exp, wchar_t* keyword)
{
    for(size_t i=0; i < text_exp.lenght; i++)
    {
        for(size_t j = 0; j < text_exp.sentences[i]->word_count; j++)
        {
            if ( yea_it_is(text_exp.sentences[i]->words[j], keyword) )
            {
                for(size_t k=0; k < wcslen(text_exp.sentences[i]->words[j]) - 1; k++)
                {
                    if ( j == 0 && text_exp.sentences[i]->words[j][k] == L'\n' ) {}
                    else wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);
                }
                wprintf(L"\n");
            }
        }
    }
}
