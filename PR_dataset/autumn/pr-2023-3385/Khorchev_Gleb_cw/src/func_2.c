#include "struct.h"
#include <stdio.h>
#include <wchar.h>
#define RESET "\033[0m"
#define GREEN "\033[32m"

void pr_sec_w_in_f_sen(text text_exp)
{
     if ( text_exp.sentences[0]->word_count >= 2 )
     {
            wchar_t* key_word = text_exp.sentences[0]->words[1];
            for (size_t i=0; i < text_exp.lenght;i++)
            {
                size_t ind = 0;
                for(size_t j=0; j < text_exp.sentences[i]->word_count; j++)
                {
                    if ( wcslen(text_exp.sentences[i]->words[j]) == wcslen(key_word) )
                    {
                        if ( !wcsncmp(text_exp.sentences[i]->words[j], key_word, wcslen(key_word)-1))
                        {
                            ind = j;
                            break;
                        }
                    }
                }
                if (ind)
                {
                    for(size_t j=0; j< text_exp.sentences[i]->word_count; j++)
                    {
                        if ( j == ind )
                        {
                            for ( size_t k=0; k < wcslen(key_word); k++)
                            {
                                if ( k != wcslen(key_word) - 1 ) wprintf(GREEN L"%lc" RESET, key_word[k]);
                                else wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);
                            }
                        }
                        else wprintf(L"%ls", text_exp.sentences[i]->words[j]);
                    }
                    wprintf(L"\n");
                }
            }
         } else fwprintf(stderr, L"Error: fisrt sentence has less then 1 word");
}

