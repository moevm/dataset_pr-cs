#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include "struct.h"
#include "help_functions.h"
#include <stdlib.h>
#define BLOCK 50

wchar_t*  read_word()
{
    size_t Capacity = BLOCK*sizeof(wchar_t), len=0, Flag = 0, Flag2 = 1;
    wchar_t* result = (wchar_t*)malloc(sizeof(wchar_t)*Capacity);

    if ( result == NULL )
    {
        free(result);
        fwprintf(stderr, L"Ошибка выделения памяти");
        exit(0);
    }

    wchar_t c = getwchar();
    while(1)
    {
        if (len == 0 && (iswblank(c) || c == L',')  && Flag2)
        {
            c = getwchar();
            continue;
        }
        else Flag2 = 0;
        if ( c == '.' || c == ' ' || c == ',' )
        {
            result[len++] = c;
            result[len] = '\0';
            break;
        }
        else
        {
            if ( c == '\n') Flag = 1;
            result[len++] = c;
            c = getwchar();
            if (c == '\n' && Flag )
            {
            result[len++] = c;
            result[len] = '\0';
            return result;
            }
            else Flag = 0;
            if ( len*sizeof(wchar_t) == Capacity - sizeof(wchar_t))
            {
                Capacity += BLOCK*sizeof(wchar_t);
                result = (wchar_t*)realloc(result, Capacity);

                if ( result == NULL )
                {
                    free(result);
                    fwprintf(stderr, L"Ошибка выделения памяти");
                    exit(0);
                }

            }
        }
    }
    return result;
}


sentence* read_sentence()
{
    size_t Capacity = BLOCK*sizeof(wchar_t*);
    sentence* new = (sentence*)malloc(sizeof(sentence));

    if ( new == NULL)
    {
        free(new);
        fwprintf(stderr, L"Ошибка выделения памяти");
        exit(0);
    }

    new->word_count = 0;
    new->lenght = 0;
    new->last_sentence = 0;
    new->words = (wchar_t**)malloc(sizeof(wchar_t*)*Capacity);

    if ( new->words == NULL)
    {
        free_sentence(new);
        fwprintf(stderr, L"Ошибка выделения памяти");
        exit(0);
    }

    wchar_t* word = read_word();
    while(1)
    {
        if ( word[wcslen(word)-1] == '.' )
        {
            new->words[new->word_count++] = word;
            new->lenght += wcslen(word);
            break;
        }
        else
        {
            if (word[wcslen(word)-1] == '\n' &&  word[wcslen(word)-2] == '\n')
            {
                new->last_sentence = 1;
                break;
            }
            new->words[new->word_count++] = word;
            new->lenght += wcslen(word);
            word = read_word();
            if ( new->word_count*sizeof(wchar_t*) == Capacity - sizeof(wchar_t*))
            {
                Capacity += BLOCK*sizeof(wchar_t*);
                new->words = (wchar_t**)realloc(new->words, Capacity);

                if ( new->words == NULL )
                {
                    free_sentence(new);
                    fwprintf(stderr, L"Ошибка выделения памяти");
                    exit(0);
                }

            }
        }
    }
    return new;
}


text read_text(){
    size_t Capacity = BLOCK*sizeof(sentence*);
    struct text new;
    new.lenght = 0;
    new.sentences = (sentence**)malloc(sizeof(sentence*)*Capacity);

    if ( new.sentences == NULL)
    {
        free(new.sentences);
        fwprintf(stderr, L"Ошибка выделения памяти");
        exit(0);
    }

    sentence* sentence_exp = read_sentence();
    while(1)
    {
        if ( sentence_exp->last_sentence )
        {
             new.sentences[new.lenght++] = sentence_exp;
             break;
        }
        else
        {

            size_t Flag = 1;
            for(size_t i=0; i<new.lenght;i++)
            {
                if ( sentence_exp->lenght == new.sentences[i]->lenght )
                {
                    if ( not_unique_sentence(sentence_exp, new.sentences[i]) )
                    {
                        Flag = 0;
                        free_sentence(sentence_exp);
                        break;
                    }
                }
            }
            if (Flag) new.sentences[new.lenght++] = sentence_exp;

            sentence_exp = read_sentence();

            if ( new.lenght*sizeof(sentence*) == Capacity - sizeof(sentence*))
            {
                Capacity += BLOCK*sizeof(sentence*);
                new.sentences = (sentence**)realloc(new.sentences, Capacity);

                if ( new.sentences == NULL )
                {
                    free_text(new);
                    fwprintf(stderr, L"Ошибка выделения памяти");
                    exit(0);
                }

            }
        }
    }
    return new;
}
