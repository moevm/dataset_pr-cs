#include "double_word.h"

void double_word(struct Text text)
{
    wchar_t* word = (wchar_t *)malloc(100*sizeof(wchar_t));
    for(int i = 0; i < text.number_sentences; i++)
    {
        text.sents[i]->size *=2 ;
        wchar_t* str_res = (wchar_t *)malloc(text.sents[i]->size*sizeof(wchar_t));
        if(!str_res)
        {
            wprintf(L"Error: не удалось выделить память для дублирования слов.\n");
            break;
        }
        int word_length = 0, size = 0;
        for(int j = 0; j < wcslen(text.sents[i]->str); j++)
        {
            if (text.sents[i]->str[j] != L' ' && text.sents[i]->str[j] != L'.')
            {
                word[word_length] = text.sents[i]->str[j];
                word_length +=1;
            }
            else
            {
                for(int k = 0; k < word_length; k++)
                    str_res[size + k] = word[k];
                size+=word_length;
                str_res[size] = L' ';
                size++;
                for(int k = 0; k < word_length; k++)
                    str_res[size + k] = word[k];
                size+=word_length;
                str_res[size] = L' ';
                size++;
                word_length = 0;
            }
        }
        str_res[size - 1] = '.';
        str_res[size] = END_STRING;
        free(text.sents[i]->str);
        text.sents[i]->str = str_res;
    }
}
