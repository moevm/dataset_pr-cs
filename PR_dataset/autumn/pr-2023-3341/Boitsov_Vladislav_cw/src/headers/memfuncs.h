#ifndef MEMFUNCS_H
#define MEMFUNCS_H
#include"structures.h"

void initSentence(struct Sentence* snt);
void initText(struct Text* txt);
void addSentenceMemory(struct Sentence* snt);
void addTextMemory(struct Text* txt);
void freeSentence(struct Sentence* snt);
void freeText(struct Text* txt);

#endif