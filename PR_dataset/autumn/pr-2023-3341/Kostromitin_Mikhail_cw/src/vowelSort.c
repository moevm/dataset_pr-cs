#include "vowelSort.h" 


void sortByNumOfVowel(Text* text)
{
    for (int i = 0; i < text->size; i++)
    {
        int words = countWords(text->sentences + i);
        wchar_t* arr[words];
        int maxLen = 0;
        int sizeOfArr = fillArr(text->sentences[i].sentence, arr, &maxLen, L", .\n\t");
        
        qsort(arr, sizeOfArr, sizeof(wchar_t*), vowelcmp);

        wchar_t* arrSep[words];
        int maxLenSep = 0;
        fillArr(text->sentences[i].sentence, arrSep, &maxLenSep, L"qwertyuiopasdfghjkl;'zxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMйцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮЁ!ё@#$^&*0123456789");

        wchar_t anotherCopy[text->sentences[i].sizeOfBuf];
        anotherCopy[0] = L'\0';
        
        for (int l = 0; l < words; l++)
        {
            wcscat(anotherCopy, arr[l]);
            wcscat(anotherCopy, arrSep[l]);
        }

        wcscpy(text->sentences[i].sentence, anotherCopy);

        for (int j = 0; j < sizeOfArr; j++)
        {
            free(arr[j]);
            free(arrSep[j]);
        }
    }
}


int vowelcmp(const void* a, const void* b)
{
    int counterFirst = 0, counterSecond = 0;
    wchar_t** first = (wchar_t**)a;
    wchar_t** second = (wchar_t**)b;

    for (int i = 0; i < wcslen(*first); i++)
    {
        if (wcschr(L"eyuioaуеыаоэяию", towlower((*first)[i]))) counterFirst++;
    }

    for (int j = 0; j < wcslen(*second); j++)
    {
        if (wcschr(L"eyuioaуеыаоэяию", towlower((*second)[j]))) counterSecond++;
    }

    return counterFirst - counterSecond;
}
