#include "output_special_wchar.h"

int compare(const void * a, const void * b)
{
  return ( *(wchar_t*)b - *(wchar_t*)a );
}

void output_special_wchar(struct Text text)
{
    for(int i = 0; i < text.number_sentences; i++)
    {
        wchar_t* str_special_wchar = (wchar_t *)malloc(text.sents[i]->size*sizeof(wchar_t));
        if (!str_special_wchar)
        {
            wprintf(L"Error: не удалось выделить память для специальных символов.\n");
            break;
        }
        int number_special_wchar = 0;
        for(int j = 0; j < wcslen(text.sents[i]->str); j++)
        {
            if(iswpunct(text.sents[i]->str[j]))
            {
                str_special_wchar[number_special_wchar] = text.sents[i]->str[j];
                number_special_wchar++;
            }
        }
        wchar_t* temp_str = (wchar_t *)realloc(str_special_wchar, number_special_wchar*sizeof(wchar_t));
        if (!temp_str)
        {
            wprintf(L"Error: не удалось выделить дополнительную память для специальных символов.\n");
            break;
        }
        str_special_wchar = temp_str;
        qsort(str_special_wchar, number_special_wchar, sizeof(wchar_t), compare);
        for (int j = 0; j < number_special_wchar; j++)
            putwchar(str_special_wchar[j]);
        wprintf(L"\n");
        free(str_special_wchar);
    }
}
