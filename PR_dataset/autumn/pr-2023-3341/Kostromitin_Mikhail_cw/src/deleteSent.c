#include "deleteSent.h"

void deleteNullSent(Text* text)
{
    int newSize = 0;

    for (int i = 0; i < text->size; i++)
    {
        if (text->sentences[i].sentence[0] != L'\0') 
        {
            text->sentences[newSize++] = text->sentences[i];
        } else 
        {
            free(text->sentences[i].sentence);
        }
    }

    Sentence* buf = (Sentence*)realloc(text->sentences, sizeof(Sentence) * newSize);
    text->sentences = buf;

    text->size = newSize;
}

