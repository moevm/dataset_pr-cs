#ifndef TEXT_PROCESSING_H
#define TEXT_PROCESSING_H

#include "data.h"

int isCorrect(Text text);

int textEndIsSentenceEnd();

int sentenceEndCheck(Sentence sentence);

int isNotBlank(Sentence sentence);

Text basicFormatting(Text text);

Text preCheckFormatting(Text text);

void removeLeadSpaces(Sentence *sentence);

WordCount *countWords(Text text, size_t *resultSize);

Text sortByLatinCount(Text text);

Text replaceNotChars(Text text);

Text removeSentencesWithoutSpecial(Text text);

Text filterByString(Text text, wchar_t *src);

wchar_t **getWords(wchar_t *src, wchar_t *delims, size_t *nsize);

#endif
