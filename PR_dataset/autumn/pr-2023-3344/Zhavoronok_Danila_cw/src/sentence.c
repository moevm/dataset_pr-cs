#include "sentence.h"
#include <stdlib.h>
#include <stdio.h>

void init_sentence(sentence *str)
{
    str->capacity = 16;
    str->length = 0;
    str->counter = 0;

    wchar_t *p = (wchar_t *)malloc(str->capacity * sizeof(wchar_t));
    if (!p)
    {
        fputws(L"Невозможно выделить память под текст предложения, ошибка.", stderr);
        exit(0);
    }
    p[0] = L'\0';
    str->text = p;
}

sentence *create_sentence()
{
    sentence *p = (sentence *)malloc(sizeof(sentence));
    if (!p)
    {
        fputws(L"Невозможно выделить память под предложениt, ошибка.", stderr);
        exit(0);
    }
    sentence *str = p;
    init_sentence(str);
    return str;
}

void free_sentence(sentence *str)
{
    // wprintf(L"Deleting >%ls< length: %d cap: %d\n", str->text, str->length, str->capacity);
    if (str)
    {
        if (str->text)
        {
            free(str->text);
        }

        free(str);
    }
}

void enlarge_sentence(sentence *str)
{
    str->capacity += (str->length - (str->capacity - 1)) + 16;

    wchar_t *p = (wchar_t *)realloc((str->text), str->capacity * sizeof(wchar_t));
    if (!p)
    {
        fputws(L"Невозможно увеличить предложение, ошибка.", stderr);
        exit(0);
    }
    str->text = p;

    // wprintf(L"%ls length: %d cap: %d\n", str->text, str->length, str->capacity);
}

void enlarge_sentence_if_needed(sentence *str)
{
    if (str->length >= str->capacity - 1)
        enlarge_sentence(str);
}

void append_wchar_to_sentence(sentence *str, wchar_t *ch)
{
    str->length += wcslen(ch);
    enlarge_sentence_if_needed(str);
    wcscat(str->text, ch);
}

void print_sentence(sentence *str)
{
    for (int i = 0; i < str->length; i++)
    {
        wprintf(L"%lc", str->text[i]);
    }
    // wprintf(L"%ls.\n", str->text);
    wprintf(L".\n");
}

int comp_sentences(sentence *a, sentence *b, int is_case_sensitive)
{
    return (is_case_sensitive ? wcscmp(a->text, b->text) : wcscasecmp(a->text, b->text)) == 0;
}
