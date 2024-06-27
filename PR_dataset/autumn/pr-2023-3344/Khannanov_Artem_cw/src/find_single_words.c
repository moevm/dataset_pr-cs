#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "structs.h"
#include "find_single_words.h"
#include "is_word_in_array.h"
#include "memory_error.h"


void find_single_words (struct Text text)
{
    setlocale(LC_ALL, "");

    int is_memory_ok = 1;

    wchar_t **words_array = (wchar_t **)malloc(sizeof(wchar_t *)); // Массив слов
    if (words_array == NULL) memory_error(is_memory_ok, L"find_single_words.c words_array");

    int *num_array = (int *)malloc(sizeof(int)); // Массив чисел (количество слов)
    if (num_array == NULL) memory_error(is_memory_ok, L"find_single_words.c num_array");

    int length = 0, pos;
    wchar_t **ptr = (wchar_t **)malloc(sizeof(wchar_t *)); // Указатель для работы wcstok
    if (ptr == NULL) memory_error(is_memory_ok, L"find_single_words.c ptr");

    for (size_t i = 0; i < text.count && is_memory_ok; i++)
    {
        wchar_t *word = wcstok(text.text[i].sentence, L" ,.\n\t", ptr); // Выделение слова из предложения

        while (word != NULL)
        {   
            // Проверка, находится ли слово в массиве, если да, то в числевом массиве прибавляется 1 к соотвветсвующей позиции
            if (is_word_in_array(words_array, length, word) == length)
            {
                words_array[length++] = word;
                num_array[length - 1] = 1;

                words_array = (wchar_t **)realloc(words_array, sizeof(wchar_t *) * (length + 1));
                if (words_array == NULL) memory_error(is_memory_ok, L"find_single_words.c words_array");

                num_array = (int *)realloc(num_array, sizeof(int) * (length + 1));
                if (num_array == NULL) memory_error(is_memory_ok, L"find_single_words.c num_array");
            }
            else {
                num_array[is_word_in_array(words_array, length, word)]++;
            }

            word = wcstok(NULL, L" ,.\n", ptr);
        }
    }

    for (size_t i = 0; i < length && is_memory_ok; i++)
    {
        if (num_array[i] == 1)
        {
            wprintf(L"%ls\n", words_array[i]);
        }
    }

    // Освобождение памяти
    if (is_memory_ok)
    {
        free(ptr);
        free(num_array);
        free(words_array);
    }
}