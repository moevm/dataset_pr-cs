#include <wchar.h>
#include <stdlib.h>
#include "help_functions.h"
#include "struct.h"
#include <stdio.h>

text change_tca_tcia(text text_exp){
    for(size_t i=0; i<text_exp.lenght;i++)
    {
        for(size_t j=0;j<text_exp.sentences[i]->word_count;j++)
        {
            if ( wcslen(text_exp.sentences[i]->words[j]) >= 5)
            {
                size_t len = wcslen(text_exp.sentences[i]->words[j]);
                if ( text_exp.sentences[i]->words[j][len-2] == L'я' && text_exp.sentences[i]->words[j][len-3] == L'с' && text_exp.sentences[i]->words[j][len-4] == L'ь' && text_exp.sentences[i]->words[j][len-5] == L'т' )
                {
                    text_exp.sentences[i]->words[j] = (wchar_t*)realloc(text_exp.sentences[i]->words[j], (len)*sizeof(wchar_t));

                    if ( text_exp.sentences[i]->words[j] == NULL )
                    {
                        free(text_exp.sentences[i]->words[j]);
                        free_text(text_exp);
                        fwprintf(stderr, L"Ошибка выделения памяти в функции 1");
                        exit(0);
                    }

                    text_exp.sentences[i]->words[j][len-2] = text_exp.sentences[i]->words[j][len-1];
                    text_exp.sentences[i]->words[j][len-3] = L'я';
                    text_exp.sentences[i]->words[j][len-4] = L'с';
                    text_exp.sentences[i]->words[j][len-1] = L'\0';
                    text_exp.sentences[i]->lenght -= 1;
                    continue;
                }
            }
            if ( wcslen(text_exp.sentences[i]->words[j]) >= 4)
            {
                size_t len = wcslen(text_exp.sentences[i]->words[j]);
                if ( text_exp.sentences[i]->words[j][len-2] == L'я' && text_exp.sentences[i]->words[j][len-3] == L'с' && text_exp.sentences[i]->words[j][len-4] == L'т' )
                {
                    text_exp.sentences[i]->words[j] = (wchar_t*)realloc(text_exp.sentences[i]->words[j], (len+2)*sizeof(wchar_t));

                    if ( text_exp.sentences[i]->words[j] == NULL )
                    {
                        free(text_exp.sentences[i]->words[j]);
                        free_text(text_exp);
                        fwprintf(stderr, L"Ошибка выделения памяти в функции 1");
                        exit(0);
                    }

                    text_exp.sentences[i]->words[j][len] = text_exp.sentences[i]->words[j][len-1];
                    text_exp.sentences[i]->words[j][len-3] = L'ь';
                    text_exp.sentences[i]->words[j][len-2] = L'с';
                    text_exp.sentences[i]->words[j][len-1] = L'я';
                    text_exp.sentences[i]->words[j][len+1] = L'\0';
                    text_exp.sentences[i]->lenght += 1;
                }
            }
        }
    }
    return text_exp;
}


