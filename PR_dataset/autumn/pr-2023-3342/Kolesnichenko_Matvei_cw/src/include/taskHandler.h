#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <wchar.h>
#include "structures.h"

void defenceTask();
void logEditedCertainWords(Text* text);
int findWideSubstringIndex(const wchar_t *wideStr, const wchar_t *subStr);
void logCertainSentences(Text text);
int sentenceCmp(const void* a, const void* b);
void sortSentencesByWords(Text* text);
void removeShortSentences(Text* text);
void checkMemory(void *ptr, const wchar_t *errorMessage);
void switchTasks(int task);

#endif