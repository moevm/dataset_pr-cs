#include"../headers/memfuncs.h"
#include<stdlib.h>
#include<assert.h>

void initText(struct Text* txt)//инициализация текста
{
	txt->sentences=(struct Sentence*)calloc(1, sizeof(struct Sentence));
	txt->sentences[0].content=(wchar_t*)calloc(BLOCK_SIZE, sizeof(wchar_t));
	txt->sentences[0].curSize=BLOCK_SIZE-1;
	txt->numOfSentences=1;
}

void initSentence(struct Sentence* snt)//инициализация предложения
{
	snt->content=(wchar_t*)calloc(BLOCK_SIZE, sizeof(wchar_t));
	snt->curSize=BLOCK_SIZE-1;
}

void addSentenceMemory(struct Sentence* snt)//добавление памяти к предложению
{
	snt->content=(wchar_t*)realloc(snt->content, sizeof(wchar_t)*(snt->curSize+BLOCK_SIZE));
	snt->curSize+=BLOCK_SIZE;
}

void addTextMemory(struct Text* txt)//добавление предложения в текст
{
	txt->sentences=(struct Sentence*)realloc(txt->sentences, sizeof(struct Sentence)*(txt->numOfSentences+1));
	txt->numOfSentences++;
	initSentence(&(txt->sentences[txt->numOfSentences-1]));
}

void freeSentence(struct Sentence* snt)
{
	free(snt->content);
}

void freeText(struct Text* txt)
{
	for(int i=0;i<txt->numOfSentences;i++)
	{
		freeSentence(&(txt->sentences[i]));
	}
	free(txt->sentences);
}
