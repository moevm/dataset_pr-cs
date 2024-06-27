#include "function9.h"

int is_word_can_make_from_start(wchar_t *str, Word *wrd){

    for (size_t i=0; i<wcslen(str); i++)
    {
        str[i] = towlower(str[i]);
    }
    for (size_t i=0; i<wrd->length; i++)
    {
        if (wcschr(str, towlower(wrd->chars[i]))==NULL)
        {
            return 0;
        }
    }
    return 1;
}

void print_function9(Text *txt, wchar_t *str)
{   
    for (size_t i = 0; i < (txt->length); i++)
    {
        for (size_t j = 0; j < ((txt->array_sentence)[i]->count_words); j++)
        {
            if (is_word_can_make_from_start(str, txt->array_sentence[i]->array_of_words[j]))
            {
                wprintf(L"%ls\n", txt->array_sentence[i]->array_of_words[j]->chars);
            }
        }
    }
}