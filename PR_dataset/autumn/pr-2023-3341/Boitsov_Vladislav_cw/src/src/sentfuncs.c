#include"../headers/sentfuncs.h"
#include<stdlib.h>
#include<assert.h>

#define NUM_OF_ENGLISH_LETTERS 26
#define NUM_OF_RUSSIAN_LETTERS 32

const wchar_t vowels[] = L"АаЕеЁёИиОоУуЫыЭэЮюЯяAaEeIiOoUuYy";
const wchar_t separators[]=L" ,.";
struct Sentence sentToLower(struct Sentence snt)//перевод предложения в нижний регистр
{
	struct Sentence res;
	res.curSize = snt.curSize;
	res.content = (wchar_t*)calloc(snt.curSize+1, sizeof(wchar_t));
	assert(res.content!=NULL);
	for(int i=0; i<wcslen(snt.content)+1;i++)
	{
		res.content[i]=towlower(snt.content[i]);
	}
	res.content[wcslen(snt.content)]='\0';
	return res; 
}

void sentenceCopy(struct Sentence* dest, struct Sentence* src)//копирование предложения
{
	dest->content=(wchar_t*)calloc(src->curSize+1, sizeof(wchar_t));
	assert(dest->content!=NULL);
	wcscpy(dest->content, src->content);
	dest->curSize=src->curSize;
}

int charComparator(const void* firstSym, const void* secondSym)//сравнение символов
{
	wchar_t firstChar = *((wchar_t*)firstSym), secondChar=*((wchar_t*)secondSym);
	return (firstChar-secondChar);
}

wchar_t* getSentenceMask(struct Sentence snt)
{
	wchar_t* str = (wchar_t*)calloc((wcslen(snt.content)+1), sizeof(wchar_t));
	wcscpy(str, snt.content);
	int ind=0;
	for(int i=0; i<wcslen(snt.content);i++)
	{
		if(iswalnum(snt.content[i]))
		{
			str[ind++]=towlower(snt.content[i]);
		}
	}
	str[ind]=L'\0';
	qsort(str, wcslen(str), sizeof(wchar_t), charComparator);
	return str;
}

int isAnagramm(struct Sentence firstSnt, struct Sentence secondSnt)//проверка предложений на анаграмму
{
	wchar_t* firstStr=getSentenceMask(firstSnt);
	wchar_t* secondStr=getSentenceMask(secondSnt);
	int res=!(wcscmp(firstStr, secondStr));
	free(firstStr);
	free(secondStr);
	return res;
}

int upperSentComparator(const void* firstSnt, const void* secondSnt)//сравнение предложений по кол-ву заглавных букв
{
	wchar_t* firstStr = ((struct Sentence*)firstSnt)->content; 
	wchar_t* secondStr = ((struct Sentence*)secondSnt)->content;
	int firstNumOfUppers=0, secondNumOfUppers=0;
	for(int i=0;i<wcslen(firstStr);i++)
		if(iswalpha(firstStr[i]) && iswupper(firstStr[i]))
			firstNumOfUppers++;
	for(int i=0;i<wcslen(secondStr);i++)
		if(iswalpha(secondStr[i]) && iswupper(secondStr[i]))
			secondNumOfUppers++;
	return (firstNumOfUppers-secondNumOfUppers);
}

int isVowel(wchar_t letter)
{
	for(int i=0;i<wcslen(vowels);i++)
		if(letter==vowels[i])
			return 1;
	return 0;
}

void getNextLetters(wchar_t vowel, struct Sentence* snt)
{
	wchar_t* res=(wchar_t*)calloc(3, sizeof(wchar_t));
	res[2]='\0';
	if(vowel==L'ё')
		wcscpy(res, L"жз");
	else if(vowel ==L'Ё')
		wcscpy(res, L"ЖЗ");
	else if(vowel==L'Е')
		wcscpy(res, L"ЁЖ");
	else if(vowel==L'е')
		wcscpy(res, L"ёж");
	else
	{
		int alphabetSize = (towlower(vowel)>=L'a' && towlower(vowel)<=L'z') ? NUM_OF_ENGLISH_LETTERS : NUM_OF_RUSSIAN_LETTERS;
		res[0]=vowel+1;
		if(!((towlower(vowel+1)>=L'a' && towlower(vowel+1)<=L'z')||(towlower(vowel+1)>=L'а' && towlower(vowel+1)<=L'я')))
			res[0]-=alphabetSize;
		res[1]=vowel+2;
		if(!((towlower(vowel+2)>=L'a' && towlower(vowel+2)<=L'z')||(towlower(vowel+2)>=L'а' && towlower(vowel+2)<=L'я')))
			res[1]-=alphabetSize;
	}
	wcscat(snt->content, res);
	free(res);
}

wchar_t* wordToLower(wchar_t* word)
{
	wchar_t* res=(wchar_t*)calloc(wcslen(word)+1, sizeof(wchar_t));
	for(int i=0;i<wcslen(word);i++)
		res[i]=towlower(word[i]);
	res[wcslen(word)]=L'\0';
	return res;
}

int isSeparator(wchar_t sym)
{
	for(int i=0;i<wcslen(separators);i++)
		if(sym==separators[i])
			return 1;
	return 0;
}

int getLen(struct Sentence snt)
{
	return wcslen(snt.content)-1;
}



void getFirstTwoWords(struct Text* txt, wchar_t** key, wchar_t** word)
{
	int numOfWords=0;
	int memsize[2];
	for(int i=0;i<2;i++)
		memsize[i]=0;
	wchar_t** words=(wchar_t**)calloc(2, sizeof(wchar_t*));
	for(int i=0; i<2;i++)
	{
		memsize[i]=BLOCK_SIZE-1;
		words[i]=(wchar_t*)calloc(BLOCK_SIZE, sizeof(wchar_t));
	}
	for(int i=0;i<txt->numOfSentences && numOfWords<2; i++)
	{
		int ind=0;
		for(int j=0;j<wcslen(txt->sentences[i].content) && numOfWords<2;j++)
		{
			if(!isSeparator(txt->sentences[i].content[j]))
			{
				words[numOfWords][ind++]=txt->sentences[i].content[j];
				if(ind+2>=memsize[numOfWords])
				{
					words[numOfWords]=(wchar_t*)realloc(words[numOfWords], (memsize[numOfWords]+BLOCK_SIZE)*sizeof(wchar_t));
					memsize[numOfWords]+=BLOCK_SIZE;
				}
			}
			else
			{
				words[numOfWords][ind]=L'\0';
				numOfWords++;
				ind=0;
			}
		}
	}
	*key = (wchar_t*)calloc((wcslen(words[0]) + 1), sizeof(wchar_t));
    wcscpy(*key, words[0]);
    free(words[0]);
    *word = (wchar_t*)calloc((wcslen(words[1]) + 1), sizeof(wchar_t));
    wcscpy(*word, words[1]);
    free(words[1]);
    free(words);
}

