#include "transliteration.h"

wchar_t* resize_transletiration_sentence(wchar_t *str_transliteration, int* size)
{
    (*size) += MEM_STEP;
    wchar_t* temp_str = (wchar_t *)realloc(str_transliteration, (*size)*sizeof(wchar_t));
    if(!temp_str)
    {
        wprintf(L"Error: не удалось выделить дополнительную память для транслитерации предложения.\n");
        return NULL;
    }
    return temp_str;
}

void transliteration(struct Text text)
{
    wchar_t* transliteration_wchar = (wchar_t *)malloc(4*sizeof(wchar_t));
    if(!transliteration_wchar)
        wprintf(L"Error: не удалось выделить память для транслитерации символа.\n");
    else
    {
        for(int i = 0; i < text.number_sentences; i++)
        {
            wchar_t* str_transliteration = (wchar_t *)malloc(text.sents[i]->size*sizeof(wchar_t));
            if(!str_transliteration)
            {
                wprintf(L"Error: не удалось выделить память для транслитерации предложения.\n");
                break;
            }
            int number_wchar_in_str_transliteration = 0;
            for (int j = 0; j < wcslen(text.sents[i]->str); j++)
            {
                wchar_t wchar = towlower(text.sents[i]->str[j]);
                transliteration_wchar = dictionary_russian_alphabet(wchar);
                if(number_wchar_in_str_transliteration + wcslen(transliteration_wchar) >= text.sents[i]->size)
                    str_transliteration = resize_transletiration_sentence(str_transliteration, &text.sents[i]->size);
                for(int k = 0; k < wcslen(transliteration_wchar); k++)
                    str_transliteration[number_wchar_in_str_transliteration + k] = (transliteration_wchar[0] == '.') ? wchar : (iswupper(text.sents[i]->str[j]) ? towupper(transliteration_wchar[k]) : transliteration_wchar[k]);
                number_wchar_in_str_transliteration += wcslen(transliteration_wchar);
            }
            str_transliteration[number_wchar_in_str_transliteration] = END_STRING;
            free(text.sents[i]->str);
            text.sents[i]->str = str_transliteration;
        }
    }
}
