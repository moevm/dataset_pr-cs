#include <stdlib.h>
#include "structures.h"
#include "log.h"

void printText(Text *text)
{
    for (unsigned int i = 0; i < text->num_sentences; i++)
    {
#ifdef LOG_USE_COLOR
        logInfoDefault(L"\033[1;36mSentence №%d:\033[0m%ls", (i + 1), text->sentences[i].sentence);
#else
        logInfoDefault(L"%ls", text->sentences[i].sentence);
#endif
    }
}

void freeText(Text *text)
{
    for (unsigned int i = 0; i < text->num_sentences; i++)
    {
        free(text->sentences[i].sentence);
    }
    free(text->sentences);
    free(text);
}
