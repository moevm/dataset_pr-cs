#include<string.h>
#include<wchar.h>
#include <locale.h>

#include "is_word_in_array.h"


int is_word_in_array(wchar_t **words_array, int lenght, wchar_t *word)
{
    setlocale(LC_ALL, "");

    for (size_t i = 0; i < lenght; i++)
    {   
        int max = wcslen(words_array[i]) > wcslen(word) ? wcslen(words_array[i]) : wcslen(word);

        if (wcsncmp(words_array[i], word, max) == 0)
        {
            return i;
        }
    }
    return lenght;
}