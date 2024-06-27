#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <stdlib.h>
#include "struct.h"

int not_unique_sentence(sentence* sen1, sentence* sen2)
{
    size_t len = sen1->lenght;
    wchar_t* str1 = (wchar_t*)calloc(len, sizeof(wchar_t*));

    if ( str1 == NULL)
    {
        free(str1);
        fwprintf(stderr, L"Ошибка выделения памяти в функции сравнения строк");
        exit(0);
    }

    wchar_t* str2 = (wchar_t*)calloc(len, sizeof(wchar_t*));

    if ( str2 == NULL)
    {
        free(str2);
        fwprintf(stderr, L"Ошибка выделения памяти в функции сравнения строк");
        exit(0);
    }

    for(size_t i=0; i < sen1->word_count;i++) wcscat(str1, sen1->words[i]);
    for(size_t j=0; j < sen2->word_count;j++) wcscat(str2, sen2->words[j]);
    for(size_t k=0; k<len;k++)
            {
                if ( towupper(str1[k]) != towupper(str2[k]) )
                {
                    free(str1);
                    free(str2);
                    return 0;
                }
            }
    free(str1);
    free(str2);
    return 1;
}

void free_sentence(sentence* sent)
{
    for(size_t i=0; i < sent->word_count; i++) free(sent->words[i]);
}

void free_text(text text_exp)
{
    for( size_t j=0; j < text_exp.lenght; j++) free_sentence(text_exp.sentences[j]);
}

int compare(const void* sent1, const void* sent2)
{
  if ( (*(sentence**)sent1)->word_count < (*(sentence**)sent2)->word_count ) return -1;
  if ( (*(sentence**)sent1)->word_count == (*(sentence**)sent2)->word_count ) return 0;
  if ( (*(sentence**)sent1)->word_count > (*(sentence**)sent2)->word_count ) return 1;
}

