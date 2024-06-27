#include "process_text.h"

void process_text(struct Text* text)
{
    if (text->sents)
    {
        for(int i = 0; i < text->number_sentences; i++)
        {
            for(int j = i + 1; j < text->number_sentences; j++)
            {
                if (text->sents[j]->str[0] != END_STRING && !wcscasecmp(text->sents[i]->str, text->sents[j]->str))
                    text->sents[j]->str[0] = END_STRING;
            }
        }
        delete_empty_sentences(text);
    }
}
