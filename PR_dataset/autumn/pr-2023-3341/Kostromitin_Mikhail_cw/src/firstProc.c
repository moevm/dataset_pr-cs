#include "firstProc.h" 


void firstProc(Text* text)
{
    for (int i = 0; i < (text->size - 1); i++)
    {
        for (int j = i + 1; j < text->size; j++)
        {
            if (text->sentences[i].sentence[0] != L'\0' && wcsnotregsenscmp(text->sentences[i].sentence, text->sentences[j].sentence)) 
            {
                wcscpy(text->sentences[j].sentence, L"\0");
            }
        }
    }

    deleteNullSent(text);
}


int wcsnotregsenscmp(wchar_t* sent1, wchar_t* sent2)
{
    if (wcslen(sent1) == wcslen(sent2))
    {
        for (int i = 0; i < wcslen(sent1); i++)
        {
            if (towupper(sent1[i]) != towupper(sent2[i])) return 0;
        }
    } else
    {
        return 0;
    }

    return 1;
}