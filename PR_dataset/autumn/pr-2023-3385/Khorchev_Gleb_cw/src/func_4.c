#include "help_functions.h"
#include <stdio.h>
#include "struct.h"
#include <wchar.h>
#include <stdlib.h>
#define BLOCK 10

text del_more_then_10_w(text text_exp)
{
    size_t Capacity = BLOCK*sizeof(sentence*), new_lenght = 0;
    sentence** new_sentences = (sentence**)malloc(Capacity);
    if ( new_sentences == NULL )
    {
        free(new_sentences);
        free_text(text_exp);
        fwprintf(stderr, L"Ошибка выделения памяти в функции 4");
        exit(0);
    }

    for (size_t i=0; i<text_exp.lenght; i++)
    {
        if ( (text_exp.sentences[i])->word_count < 11 ) new_sentences[new_lenght++] = text_exp.sentences[i];
        else free_sentence(text_exp.sentences[i]);
        if ( new_lenght*sizeof(sentence*) == Capacity-sizeof(sentence*))
        {
            Capacity += BLOCK*sizeof(sentence*);
            new_sentences = (sentence**)realloc(new_sentences, Capacity);

            if ( new_sentences == NULL )
            {
                free(new_sentences);
                free_text(text_exp);
                fwprintf(stderr, L"Ошибка выделения памяти в функции 4");
                exit(0);
            }
        }
    }
    text_exp.sentences = new_sentences;
    text_exp.lenght = new_lenght;
    return text_exp;
}

