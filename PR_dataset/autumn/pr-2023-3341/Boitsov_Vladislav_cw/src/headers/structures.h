#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<wchar.h>

#define BLOCK_SIZE 50

struct Sentence
{
	wchar_t* content;
	int curSize;
};

struct Text
{
	struct Sentence* sentences;
	int numOfSentences;
};

#endif