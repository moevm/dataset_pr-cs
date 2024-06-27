#include "maskOfSent.h"


void maskOfSent(Text* text)
{
    for (int i = 0; i < text->size; i++)
    {
        int words = countWords(text->sentences + i);
        int maxLen = 0;
        wchar_t* arr[words];
        int sizeOfArr = fillArr(text->sentences[i].sentence, arr, &maxLen, L", .\n\t");
        
        qsort(arr, sizeOfArr, sizeof(wchar_t*), cmp);

        wchar_t mask[maxLen + 1];
        int maskLen = 0;
        int flag = 0;

        switch(sizeOfArr)
        {
            case (0):
            {
                ;
            }
            case (1):
            {
                flag = 1;
                break;
            }
            case (2):
            {
                maskForTwoWords(mask, &maskLen, arr[0], arr[1]);
                break;
            }
            default:
            {
                maskForTwoWords(mask, &maskLen, arr[0], arr[1]);

                for (int h = 2; h < sizeOfArr; h++)
                {
                    for (int g = 0; g < maskLen; g++)
                    {
                        if (arr[h][g] != mask[g] && mask[g] != L'*') mask[g] = L'?';
                    }

                    if (wcslen(arr[h]) > maskLen && mask[maskLen - 1] != L'*') 
                    {
                        mask[maskLen++] = L'*';
                    }
                }
            }
        }
        if (flag) 
        {
            freeArr(arr, sizeOfArr);
            continue;
        }

        mask[maskLen] = L'\0';

        if (text->sentences[i].len + (15 + wcslen(mask)) >= text->sentences[i].sizeOfBuf)
        {
            text->sentences[i].sizeOfBuf = text->sentences[i].sizeOfBuf + 15 + wcslen(mask) + 1;
            wchar_t* buf1 = (wchar_t*)realloc(text->sentences[i].sentence, sizeof(wchar_t) * (text->sentences[i].sizeOfBuf));
            text->sentences[i].sentence = buf1;
        }
        text->sentences[i].sentence[text->sentences[i].len - 1] = L'\0';

        wcscat(text->sentences[i].sentence, L" Образец слов: ");
        wcscat(text->sentences[i].sentence, mask);
        wcscat(text->sentences[i].sentence, L"\n");

        freeArr(arr, sizeOfArr);
    }
}


void freeArr(wchar_t* arr[], int size)
{
    for (int j = 0; j < size; j++) 
        {
            free(arr[j]);
        }
}


void maskForTwoWords(wchar_t mask[], int* maskLen, wchar_t firstWord[], wchar_t secondWord[])
{
    for (int k = 0; k < wcslen(firstWord); k++)
    {
        if (firstWord[k] == secondWord[k]) mask[(*maskLen)++] = firstWord[k];
        else mask[(*maskLen)++] = L'?';
    }

    if (wcslen(firstWord) - wcslen(secondWord)) mask[(*maskLen)++] = L'*';
}


int cmp(const void* a, const void* b)
{
    wchar_t** first = (wchar_t**)a;
    wchar_t** second = (wchar_t**)b;
    return wcslen(*first) - wcslen(*second);
}
