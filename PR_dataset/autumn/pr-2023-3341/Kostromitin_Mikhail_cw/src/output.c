#include "output.h" 


void output(Text* text)
{
    for (int i = 0; i < text->size; i++)
    {
        wprintf(L"%ls", text->sentences[i].sentence);
    }
}


void freeMem(Text** text)
{
    for (int i = 0; i < (*text)->size; i++)
    {
        free((*text)->sentences[i].sentence);
    }
    free((*text)->sentences);
    free(*text);
}
