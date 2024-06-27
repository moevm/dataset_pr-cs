#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<locale.h>
#include<ctype.h>

#define BLOCK_SIZE 50
#define NUMBER_OF_SEPARATORS 3
#define END_OF_STRING '\0'
const char separators[] = {'.', ';', '?'};

int isNotEndOfSentence(char symbol)
{
	for(int i=0;i<NUMBER_OF_SEPARATORS;i++)
		if (symbol == separators[i])
			return 0;
	return 1;
}

char** input(int* numOfSentences)
{
	*numOfSentences = 0; 
	int curSize=BLOCK_SIZE - 1;
	char** text=(char**)malloc(sizeof(char*));
	char buf;
	do
	{
	    if(*numOfSentences!=0)
			text=(char**)realloc(text, (*numOfSentences+1)*sizeof(char*));
		text[*numOfSentences]=(char*)malloc(sizeof(char)*BLOCK_SIZE);
		curSize=BLOCK_SIZE-1;
		int i=0;
		bool isNewSentence=false;
		do
		{
			buf=getchar();
			if(buf!='\t' && buf!=' ' && buf!='\n')
				isNewSentence=true;
			if(i>curSize)
			{
				text[*numOfSentences] = (char*)realloc(text[*numOfSentences], curSize+BLOCK_SIZE);
				curSize+=BLOCK_SIZE;
			}
			if(isNewSentence && buf!='\n')
			{
				text[*numOfSentences][i]=buf;
				i++;
				text[*numOfSentences][i]=END_OF_STRING;
			}
		}
		while (isNotEndOfSentence(buf) && buf!='!');
		(*numOfSentences)++;
	}
	while(buf!='!');
	return text;
}

bool notEndOfWord(char symbol)
{
	if (symbol!=' ' && symbol!=',' && isNotEndOfSentence(symbol))
		return true;
	return false;
}

bool ifAddSentence(char** text, int sentenceIndex)
{
	bool haveSym=false, haveNum=false, newWord = true;
	for(int j=0; isNotEndOfSentence(text[sentenceIndex][j]);j++)
	{
		if (text[sentenceIndex][j]==' ' || text[sentenceIndex][j]==',')
		{
			haveNum=false;
			haveSym=false;
			newWord=true;
		}
		else
		{
			if (isdigit(text[sentenceIndex][j]) && !newWord && notEndOfWord(text[sentenceIndex][j+1]))
				haveNum=true;
			else                     
			if (!isdigit(text[sentenceIndex][j]))
				haveSym=true;
			newWord=false;
		}
		if (haveNum && haveSym)
			return false;
	}
	return true;
}

char** textReformation(char** text, int numOfSentences, int* fNumOfSentences)
{
	char** formatedText = (char**)malloc(sizeof(char*));
	*fNumOfSentences=1;
	for(int i=0; i<numOfSentences-1;i++)
	{
		if (ifAddSentence(text, i))
		{
			(*fNumOfSentences)++;
			formatedText=(char**)realloc(formatedText, sizeof(char*) * (*fNumOfSentences));
			formatedText[*fNumOfSentences-2]=text[i];
		}
	}
	formatedText[*fNumOfSentences - 1]=text[numOfSentences-1];
	return formatedText;
}

void output(char** formatedText, int numOfSentences, int fNumOfSentences)
{
	for(int i=0;i<fNumOfSentences;i++)
	{
		puts(formatedText[i]);
	}
	printf("Количество предложений до %d и количество предложений после %d", numOfSentences-1, fNumOfSentences-1);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int numOfSentences=0;
	char** text = input(&numOfSentences);
	int fNumOfSentences=0;
	char** formatedText=textReformation(text, numOfSentences, &fNumOfSentences);
	output(formatedText, numOfSentences, fNumOfSentences);
	return 0;
}