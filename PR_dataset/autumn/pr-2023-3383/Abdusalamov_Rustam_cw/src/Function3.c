#include "Common.h"
#include "Function3.h"
#include "FreeMemory.h"
char** Function3(char** text, int *sentences_count)
{
    char** NewText = (char**)malloc(*sentences_count * sizeof(char*));
    if (NewText == NULL)
        return NULL;
    int new_count = 0;
    for (int i = 0; i < *sentences_count; i++)
    {
        if (strlen(text[i]) <= 15)
        {
            NewText[new_count] = (char*)malloc(((strlen(text[i]) + 1)) * sizeof(char));
            if (NewText[new_count] == NULL) {
                FreeMemory(NewText, new_count);
                return NULL;
            }
            strcpy(NewText[new_count], text[i]);
            new_count++;
        }
    }
    if (new_count == 0)
    {
        free(text);
        *sentences_count = 0;
        return NULL;
    }
    NewText = realloc(NewText,sizeof(char*) * new_count);
    if (NewText == NULL)
        return NULL;
    FreeMemory(text,*sentences_count);
    *sentences_count = new_count;
    return NewText;
}
