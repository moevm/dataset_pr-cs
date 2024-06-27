#include "capitalStart.h"

void capitalStart(Text* text)
{
    int flag = 1;

    for (int i = 0; i < text->size; i++)
    {
        flag = 1;
        for (int j = 0; j < text->sentences[i].len; j++)
        {
            if (iswspace(text->sentences[i].sentence[j]) || text->sentences[i].sentence[j] == L',') flag = 1;
            if (iswlower(text->sentences[i].sentence[j]) && flag == 1) 
            {
                wcscpy(text->sentences[i].sentence, L"\0");
                break;
            } else if (iswupper(text->sentences[i].sentence[j])) flag = 0;
        }
    }

    deleteNullSent(text);
}
