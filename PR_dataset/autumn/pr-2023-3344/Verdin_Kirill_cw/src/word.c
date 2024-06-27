#include <stdio.h>
#include <stdlib.h>
#include "word.h"
#define MEMORY_STEP 8

void initial_word(Word *word)
{
    word->capacity_chars = MEMORY_STEP;
    word->length = 0;
    wchar_t *pointer = (wchar_t *)malloc(sizeof(wchar_t) * (word->capacity_chars));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под слово\n", stderr);
        exit(0);
    }
    pointer[0] = L'\0';
    word->chars = pointer;
}

Word *make_word()
{
    Word *pointer = (Word *)malloc(sizeof(Word));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно выделить память под слово\n", stderr);
        exit(0);
    }
    Word *chars = pointer;
    initial_word(chars);
    return chars;
}

void expand_word(Word *word)
{
    word->capacity_chars += MEMORY_STEP;
    wchar_t *pointer = (wchar_t *)realloc(word->chars, sizeof(wchar_t) * (word->capacity_chars));
    if (pointer == NULL)
    {
        fputws(L"Ошибка. Невозможно расширить память под слово\n", stderr);
        exit(0);
    }
    word->chars = pointer;
}

void free_word(Word *word)
{
    if (word)
    {
        if (word->chars)
        {
            free(word->chars);
        }
        free(word);
    }
}

int word_comparison(const Word *str1, const Word *str2)
{
    if (str1->length != str2->length)
    {
        return 1;
    }
    for (size_t i = 0; i < str1->length; i++)
    {
        int result = towlower(str1->chars[i]) - towlower(str2->chars[i]);
        if (result != 0 || !str1->chars[i])
            return result;
    }
    return 0;
}