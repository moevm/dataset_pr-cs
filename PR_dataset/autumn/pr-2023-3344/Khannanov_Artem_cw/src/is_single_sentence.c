#include <strings.h>
#include <string.h>
#include <wchar.h>

#include "is_single_sentence.h"
#include "structs.h"


int is_single_sentence (struct Text text, struct Sentence sentence)
{
    for (size_t i = 0; i < text.count; i++)
    {
        size_t mx = wcslen(text.text[i].sentence) > wcslen(sentence.sentence) ? wcslen(text.text[i].sentence) : wcslen(sentence.sentence);

        if (!wcsncasecmp(text.text[i].sentence, sentence.sentence, mx))
        {
            return 0;
        }
    }
    return 1;
}