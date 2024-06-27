#include"../headers/textfuncs.h"
#include"../headers/structures.h"
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

extern const wchar_t vowels[];
extern const wchar_t separators[];

struct Text primaryProcessing(struct Text txt)//первичначя обработка
{
	struct Text res;
	res.sentences=(struct Sentence*)calloc(1, sizeof(struct Sentence));
	assert(res.sentences!=NULL);
	res.sentences->content=(wchar_t*)calloc((txt.sentences[0].curSize +1), sizeof(wchar_t));
	assert(res.sentences->content!=NULL);
	sentenceCopy(&res.sentences[0], &txt.sentences[0]);
	res.numOfSentences=1;
	for(int i=1; i<txt.numOfSentences;i++)
	{
		bool isEqual = false;
		for(int j=i-1;j>=0;j--)
		{
			if(!wcscmp(sentToLower(txt.sentences[i]).content, sentToLower(txt.sentences[j]).content))
			{
				isEqual=true;
				break;
			}
		}
		if(!isEqual)
		{
			res.sentences=(struct Sentence*)realloc(res.sentences, sizeof(struct Sentence)*(res.numOfSentences+1));
			assert(res.sentences!=NULL);
			sentenceCopy(&res.sentences[res.numOfSentences], &txt.sentences[i]);
			res.numOfSentences++;
		}
	}
	return res;
}

void printAllAnagramms(struct Text* txt)
{
	int* listOfSentences = (int*)calloc((txt->numOfSentences), sizeof(int));
	for(int i=0;i<txt->numOfSentences; i++)
	{
		for(int j=i+1;j<txt->numOfSentences;j++)
		{
			if(isAnagramm(txt->sentences[i], txt->sentences[j]))
			{
				listOfSentences[i]=1;
				listOfSentences[j]=1;
			}
		}
	}
	for(int i=0;i<txt->numOfSentences;i++)
		if(listOfSentences[i])
			printSentence(&(txt->sentences[i]));
	free(listOfSentences);
}

void sortByUpperLetters(struct Text* txt)//сортировка по кол-ву заглавных букв
{
	qsort(txt->sentences, txt->numOfSentences, sizeof(struct Sentence), upperSentComparator);
	printText(txt);
}

void replaceVowels(struct Text* txt)
{
	struct Text res;
	res.sentences = (struct Sentence*)calloc(txt->numOfSentences, sizeof(struct Sentence));
	res.numOfSentences=txt->numOfSentences;
	for(int i=0;i<txt->numOfSentences;i++)
	{
		res.sentences[i].content=(wchar_t*)calloc(txt->sentences[i].curSize+1, sizeof(wchar_t));
		res.sentences[i].curSize=txt->sentences[i].curSize;
		int n=0;
		for(int j=0;j<wcslen(txt->sentences[i].content);j++)
		{
			if(wcslen(res.sentences[i].content)+3>=res.sentences[i].curSize)
				addSentenceMemory(&(res.sentences[i]));
			if(isVowel(txt->sentences[i].content[j]))
			{
				getNextLetters(txt->sentences[i].content[j], &(res.sentences[i]));
				n+=2;
			}
			else
			{
				res.sentences[i].content[n]=txt->sentences[i].content[j];
				n++;
			}
		}
		res.sentences[i].content[n]=L'\0';
	}
	printText(&res);
	freeText(&res);
}

void replaceWordToKey(struct Text* txt)
{
    wchar_t* key;
    wchar_t* word;
    getFirstTwoWords(txt, &key, &word);
    if(!wcscmp(key, L"") || !wcscmp(word, L""))
    {
    	wprintf(L"Error: not enough words to complete exchange\n");
    	exit(0);
	}
    struct Text res;
    res.sentences = (struct Sentence*)calloc(txt->numOfSentences, sizeof(struct Sentence));
    res.numOfSentences = txt->numOfSentences;
    for (int i = 0; i < txt->numOfSentences; i++)
    {
        initSentence(&(res.sentences[i]));
        int ind1 = 0, ind2 = 0;
        while (ind1 < wcslen(txt->sentences[i].content))
        {
            int isWordMatch = 1;
            for (int j = 0; j < wcslen(key); j++)
            {
                if (towlower(txt->sentences[i].content[ind1 + j]) != towlower(key[j]))
                {
                    isWordMatch = 0;
                    break;
                }
        	}
        	if(ind1>0)
        		if(!isSeparator(txt->sentences[i].content[ind1-1]))
        			isWordMatch=0;
        	if(ind1<wcslen(txt->sentences[i].content))
        		if(!isSeparator(txt->sentences[i].content[ind1+wcslen(key)]))
        			isWordMatch=0;
            if (isWordMatch)
            {
                if (wcslen(word) + wcslen(res.sentences[i].content) + 2 >= res.sentences[i].curSize)
                    addSentenceMemory(&(res.sentences[i]));
                for (int j = 0; j < wcslen(word); j++)
                    res.sentences[i].content[ind2++] = word[j];
                ind1 += wcslen(key);
            }
            else
            {
                if (wcslen(res.sentences[i].content) + 2 >= res.sentences[i].curSize)
                    addSentenceMemory(&(res.sentences[i]));
                res.sentences[i].content[ind2++] = txt->sentences[i].content[ind1++];
            }
        }
        res.sentences[i].content[ind2] = L'\0';
    }
    printText(&res);
    freeText(&res);
}

void func9(struct Text* txt)
{
	struct Text res;
	res.sentences=(struct Sentence*)calloc(txt->numOfSentences, sizeof(struct Sentence));
	res.numOfSentences=txt->numOfSentences;
	int len=getLen(txt->sentences[0]);
	res.sentences[0].content=(wchar_t*)calloc(len+3, sizeof(wchar_t));
	sentenceCopy(&(res.sentences[0]), &(txt->sentences[0]));
	for(int i=1;i<txt->numOfSentences;i++)
	{
		initSentence(&(res.sentences[i]));
		int ind1=0;
		const wchar_t* rep=L"(большое слово)";
		int len1=0;
		int wbeg=0;
		for(int j=0;j<wcslen(txt->sentences[i].content);j++)
		{
			if(isSeparator(txt->sentences[i].content[j]))
			{
				if(len1>len)
				{
					while(res.sentences[i].curSize<=wcslen(res.sentences[i].content)+3+wcslen(rep))
						addSentenceMemory(&(res.sentences[i]));
					wcscat(res.sentences[i].content, rep);
				}
				else
				{
					while(res.sentences[i].curSize<=wcslen(res.sentences[i].content) + 10+ j-ind1)
							addSentenceMemory(&(res.sentences[i]));
					int yyy=ind1;
					for(int m=0;m<j-ind1;m++)
					{
						res.sentences[i].content[wcslen(res.sentences[i].content)]=txt->sentences[i].content[yyy++];
					}
				}
				res.sentences[i].content[wcslen(res.sentences[i].content)]=txt->sentences[i].content[j];
				len1=0;
				wbeg=0;
			}
			else
			{
				len1++;
				if(wbeg==0)
				{
					ind1=j;
				}
				wbeg=1;
			}

		}
		res.sentences[i].content[wcslen(res.sentences[i].content)-1]=L'\0';		
	}
	printText(&res);
	freeText(&res);
}

void menu()
{
	int option;
	if(!wscanf(L"%d", &option))
		wprintf(L"Error: invalid option number\n");
	else
	{
		struct Text txt;
		switch(option)
		{
			case 0: txt=getText();
				txt=primaryProcessing(txt);
				printText(&txt);
				freeText(&txt);
				break;
			case 1: txt=getText();
				txt=primaryProcessing(txt);
				printAllAnagramms(&txt);
				freeText(&txt);
				break;
			case 2: txt=getText();
				txt=primaryProcessing(txt);
				sortByUpperLetters(&txt);
				freeText(&txt);
				break;
			case 3: txt=getText();
				txt=primaryProcessing(txt);
				replaceVowels(&txt);
				freeText(&txt);
				break;
			case 4: txt=getText();
				txt=primaryProcessing(txt);
				replaceWordToKey(&txt);
				freeText(&txt);
				break;
			case 5: printHelp();
				break;
			case 9:
				txt=getText();
				txt=primaryProcessing(txt);
				func9(&txt);
				break;
			default: wprintf(L"Error: wrong option\n");
		}
	}
}
