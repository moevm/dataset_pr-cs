#include "free_memory.h"

void free_text(struct Text text)
{
    for(int i=0; i<text.number_sentences; i++)
    {
        free(text.sents[i]->str);
        free(text.sents[i]);
    }
    free(text.sents);
}
