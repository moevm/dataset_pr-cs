#include "../include/sorting.h"

int compare(const void *a, const void *b)
{
  Sentence *aa = (Sentence *)a;
  Sentence *bb = (Sentence *)b;
  return aa->amofwords - bb->amofwords;
}

Text sort_sentences(Text text)
{
    qsort(text.sentences, text.size, sizeof(Sentence), compare);
    return text;
}
