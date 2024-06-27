#include "repeatWords.h"


void numberOfRepeatWords(Text* text)
{
    for (int i = 0; i < text->size; i++)
    {
        int words = countWords(text->sentences + i);
        wchar_t copy[text->sentences[i].len];
        wcscpy(copy, text->sentences[i].sentence);

        wchar_t* ptr;
        int counter = 0;

        wchar_t* arr[words];
        wchar_t* buf = wcstok(copy, L", .\n\t", &ptr);

        while (buf)
        {
            arr[counter] = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(buf) + 1));
            wcscpy(arr[counter++], buf);
            buf = wcstok(NULL, L", .\n\t", &ptr);
        }

        int numOfRepeatWords = 0;
        int currNumOfRepearWords = 0;

        for (int k = 0; k < counter - 1; k++)
        {
            currNumOfRepearWords = 0;
            for (int l = k + 1; l < counter; l++)
            {
                if (wcscmp(arr[k], L"\0") && !wcscmp(arr[k], arr[l]))
                {
                    if (!currNumOfRepearWords) currNumOfRepearWords++;
                    currNumOfRepearWords++;
                    wcscpy(arr[l], L"\0");
                }
            }
            numOfRepeatWords += currNumOfRepearWords;
        }

        if (text->sentences[i].len + 36 >= text->sentences[i].sizeOfBuf)
        {
            text->sentences[i].sizeOfBuf += 37;
            wchar_t* buf1 = (wchar_t*)realloc(text->sentences[i].sentence, sizeof(wchar_t) * (text->sentences[i].sizeOfBuf));
            text->sentences[i].sentence = buf1;
        }

        wchar_t bufStr[12];
        swprintf(bufStr, 10,  L"%d", numOfRepeatWords);

        text->sentences[i].sentence[text->sentences[i].len - 1] = L'\0';
        wcscat(text->sentences[i].sentence, L" ");
        wcscat(text->sentences[i].sentence, L"Кол-во одинаковых слов: ");
        wcscat(text->sentences[i].sentence, bufStr);
        wcscat(text->sentences[i].sentence, L"\n");


        for (int j = 0; j < counter; j++) free(arr[j]);
    }
}
