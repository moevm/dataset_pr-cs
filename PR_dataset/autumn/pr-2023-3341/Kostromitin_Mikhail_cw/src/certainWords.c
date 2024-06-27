#include "certainWords.h"


void certainWords(Text* text, Sentence* firstString)
{
    for (int i = 0; i < text->size; i++)
    {
        int words = countWords(text->sentences + i);
        wchar_t* arr[words];
        int sizeOfArr = fillArr(text->sentences[i].sentence, arr, &words, L", .\n\t");

        int firstWords = countWords(firstString);
        wchar_t* anotherArr[firstWords];
        int sizeOfAnotherArr = fillArr(firstString->sentence, anotherArr, &firstWords, L", .\n\t");

        for (int j = 0; j < words; j++)
        {
            int flag = 0;

            for (int h = 0; h < firstWords; h++)
            {
                if (wcsnotregsenscmp(arr[j], anotherArr[h]))
                {
                    flag = 1;
                    break;
                }
            }

            if (!flag)
            {
                wcscpy(text->sentences[i].sentence, L"\0");
            }
        }

        for (int u = 0; u < sizeOfArr; u++) free(arr[u]);
        for (int t = 0; t < sizeOfAnotherArr; t++) free(anotherArr[t]);
    }

    deleteNullSent(text);
}
