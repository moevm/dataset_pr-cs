#include "repeat_sentences.h"
#include "text.h"
#include "sentence.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
void repeat_sentences(Text *text, int repeat)
{
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        for (int k=0; k < repeat - 1; k++)
        {
            for (int j = 0; j < sentence->len; j++)
            {
                wprintf(L"%lc", sentence->chars[j]);
            }
            wprintf(L" ");
        }
        for (int j = 0; j < sentence->len; j++)
        {
            wprintf(L"%lc", sentence->chars[j]);
        }
        wprintf(L".\n");
    }
}