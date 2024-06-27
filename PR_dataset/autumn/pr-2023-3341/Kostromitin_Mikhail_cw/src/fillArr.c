#include "fillArr.h"


int fillArr(wchar_t* string, wchar_t* arr[], int* maxLen, const wchar_t* sep)
{
    wchar_t copy[wcslen(string)];
    wcscpy(copy, string);

    wchar_t* ptr;
    int sizeOfArr = 0;

    wchar_t* buf = wcstok(copy, sep, &ptr);

    while (buf)
    {
        if (*maxLen < wcslen(buf)) *maxLen = wcslen(buf);
        arr[sizeOfArr] = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(buf) + 1));
        wcscpy(arr[sizeOfArr++], buf);
        buf = wcstok(NULL, sep, &ptr);
    }

    return sizeOfArr;
}
