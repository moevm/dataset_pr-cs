#include "replace_numbers.h"

wchar_t* replace_not_digit(wchar_t current_wchar_of_sentence)
{
    wchar_t* temp_bin_digit = (wchar_t *)malloc(2*sizeof(wchar_t));
    if(!temp_bin_digit)
    {
        wprintf(L"Error: не удалось выделить память для представления цифры в двоичном коде.\n");
        return NULL;
    }
    temp_bin_digit[0] = current_wchar_of_sentence;
    temp_bin_digit[1] = END_STRING;
    return temp_bin_digit;
}

wchar_t* resize_result_sentence(wchar_t *str_bin_numbers, int* size)
{
    (*size) += MEM_STEP;
    wchar_t* temp_str = (wchar_t *)realloc(str_bin_numbers, (*size)*sizeof(wchar_t));
    if(!temp_str)
    {
        wprintf(L"Error: не удалось выделить дополнительную память для предложения с заменёнными цифрами.\n");
        return NULL;
    }
    return temp_str;
}

void replace_numbers(struct Text text)
{
    wchar_t* bin_digit = (wchar_t *)malloc(5*sizeof(wchar_t));
    if(!bin_digit)
        wprintf(L"Error: не удалось выделить память для представления цифры в двоичном коде.\n");
    else
    {
        for(int i = 0; i < text.number_sentences; i++)
        {
            wchar_t* str_bin_numbers = (wchar_t *)malloc(text.sents[i]->size*sizeof(wchar_t));
            if(!str_bin_numbers)
            {
                wprintf(L"Error: не удалось выделить память для предложения с заменёнными цифрами.\n");
                break;
            }
            str_bin_numbers[0] = END_STRING;
            for(int j = 0; j < wcslen(text.sents[i]->str); j++)
            {
                bin_digit = iswdigit(text.sents[i]->str[j]) ? dictionary_digit(text.sents[i]->str[j]) : replace_not_digit(text.sents[i]->str[j]);
                if (wcslen(str_bin_numbers) + wcslen(bin_digit) >= text.sents[i]->size - 1)
                    str_bin_numbers = resize_result_sentence(str_bin_numbers, &text.sents[i]->size);
                wcscat(str_bin_numbers, bin_digit);
            }
            free(text.sents[i]->str);
            text.sents[i]->str = str_bin_numbers;
        }
    }
}
