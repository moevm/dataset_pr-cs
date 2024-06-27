#include <stdlib.h>
#include "sorting.h"
#include "counting.h"
#include "log.h"
int compareSentences(const void *sentenceA, const void *sentenceB)
{
	return cyrillicCounter((const Sentence *)sentenceB) - cyrillicCounter((const Sentence *)sentenceA);
}

void sortTextByCyrillic(Text *text)
{
	qsort(text->sentences, text->num_sentences, sizeof(Sentence), compareSentences);
}