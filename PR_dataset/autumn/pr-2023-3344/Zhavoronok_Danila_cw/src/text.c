#include "text.h"
#include <stdlib.h>
#include <stdio.h>

void init_text(text *txt)
{
    txt->capacity = 2;
    txt->length = 0;
    sentence **p = (sentence **)malloc(txt->capacity * sizeof(sentence *));
    if (!p)
    {
        fputws(L"Невозможно выделить память под предложения текста, ошибка.", stderr);
        exit(0);
    }
    txt->sentences = p;
}

text *create_text()
{
    text *p = (text *)malloc(sizeof(text));
    if (!p)
    {
        fputws(L"Невозможно выделить память под текст, ошибка.", stderr);
        exit(0);
    }
    text *txt = p;
    init_text(txt);
    return txt;
}

void free_text(text *txt)
{
    // wprintf(L"Deleting >%ls< length: %d cap: %d\n", str->text, str->length, str->capacity);
    if (txt)
    {
        for (int i = 0; i < txt->length; i++)
        {
            free_sentence(txt->sentences[i]);
        }

        free(txt);
    }
}

void enlarge_text(text *txt)
{
    txt->capacity += 1;
    sentence **p = (sentence **)realloc((txt->sentences), txt->capacity * sizeof(sentence *));
    if (!p)
    {
        fputws(L"Невозможно выделить память под текст большего объема, ошибка.", stderr);
        exit(0);
    }
    txt->sentences = p;
}

void append_text(text *txt, sentence *str)
{
    txt->sentences[txt->length++] = str;
    if (txt->length >= txt->capacity - 1)
        enlarge_text(txt);
}

void print_text(text *txt)
{
    for (int i = 0; i < txt->length; i++)
    {
        print_sentence(txt->sentences[i]);
    }
}

sentence *find_sentence_in_text(text *txt, sentence *str, int is_case_sensitive)
{
    for (int i = 0; i < txt->length; i++)
    {
        if (comp_sentences(txt->sentences[i], str, is_case_sensitive))
            return txt->sentences[i];
    }
    return NULL;
}
