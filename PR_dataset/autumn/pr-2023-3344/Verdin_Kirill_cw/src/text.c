#include <stdio.h>
#include <stdlib.h>
#include "text.h"

void initial_text(Text *txt)
{
    txt->capacity = 2;
    txt->length = 0;
    Sentence **pointer = (Sentence **)malloc(sizeof(Sentence *) * (txt->capacity));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под предложения текста.\n", stderr);
        exit(0);
    }
    txt->array_sentence = pointer;
}

void expand_text(Text *txt)
{
    txt->capacity += 1;
    Sentence **pointer = (Sentence **)realloc((txt->array_sentence), ((txt->capacity) * sizeof(Sentence *)));

    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозомжно расширить память под текст\n", stderr);
        exit(0);
    }
    txt->array_sentence = pointer;
}

Text *make_text()
{
    Text *pointer = (Text *)malloc(sizeof(Text));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под текст", stderr);
        exit(0);
    }
    Text *txt = pointer;
    initial_text(txt);
    return txt;
}

void print_text(Text *txt)
{   
    for (size_t i = 0; i < (txt->length); i++)
    {
        for (size_t j = 0; j < ((txt->array_sentence)[i]->count_words); j++)
        {
            wprintf(L"%ls", txt->array_sentence[i]->array_of_words[j]->chars);
            if (j < (txt->array_sentence[i]->count_sep))
            {
                wprintf(L"%ls", txt->array_sentence[i]->array_of_sep[j]->chars);
            }
        }
        wprintf(L".\n");
    }
}

void free_text(Text *txt)
{
    if (txt)
    {
        for (size_t i; i < txt->length; i++)
        {
            free_sentence(txt->array_sentence[i]);
        }
    }
    free(txt);
}