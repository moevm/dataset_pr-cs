#include "delete_sentences.h"

void delete_empty_sentences(struct Text* text)
{
    for(int i=0; i<text->number_sentences; i++)
    {
        if(text->sents[i]->str[0] == END_STRING)
        {
            for(int j = i + 1; j < text->number_sentences; j++)
            {
                if (text->sents[j]->str[0] != END_STRING)
                {
                    struct Sentence *buf = text->sents[i];
                    if (i == 0) text->sents[i] = text->sents[j];
                    text->sents[j] = buf;
                    j = text->number_sentences;
                }
            }
            if(text->sents[i]->str[0] == END_STRING)
            {
                text->number_sentences = i;
                struct Sentence** new_sents = (struct Sentence**)realloc(text->sents, text->number_sentences*sizeof(struct Sentence*));
                if(!new_sents)
                {
                    wprintf(L"Error: не удалось выделить память после удаления предложений.\n");
                    break;
                }
                text->sents = new_sents;
            }
        }
    }
}

void delete_sentences_with_odd_numbers(struct Text* text)
{
    for(int i = 0; i < text->number_sentences; i++)
    {
        for(int j = 0; j < wcslen(text->sents[i]->str); j++)
        {
            if (iswdigit(text->sents[i]->str[j]) && ((wint_t)text->sents[i]->str[j]) % 2 == 1)
            {
                text->sents[i]->str[0] = END_STRING;
                break;
            }
        }
    }
    delete_empty_sentences(text);
}
