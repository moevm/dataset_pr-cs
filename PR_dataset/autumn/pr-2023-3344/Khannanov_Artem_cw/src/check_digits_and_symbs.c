#include <wctype.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "structs.h"
#include "check_digits_and_symbs.h"


int check_digits_and_symbs (struct Sentence sentence)
{
    setlocale(LC_ALL, "");

    int is_digit_in = 0, is_symb_in = 0;

    for (size_t i = 0; i < wcslen(sentence.sentence); i++)
    {
        if (iswdigit(sentence.sentence[i])) is_digit_in = 1;

        if (wcschr(L"#№", sentence.sentence[i]) != NULL) is_symb_in = 1;
    }

    return (is_symb_in <= is_digit_in);
}