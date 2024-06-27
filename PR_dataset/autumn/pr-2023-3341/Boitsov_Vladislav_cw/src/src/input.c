#include<wchar.h>
#include<wctype.h>
#include<stdbool.h>

#include"../headers/input.h"
#include"../headers/memfuncs.h"

struct Text getText()//считывание текста из stdin
{
	struct Text txt;
	initText(&txt);
	wchar_t buf;
	int notEndOfText=0;
	do
	{
		bool isNewSentence = false;
		int i=0;
		do
		{
			buf=getwchar();
			if (!iswspace(buf) && buf!=L'.' && buf!=L',')
				isNewSentence = true;
			if(buf==L'\n')
				notEndOfText++;
			else
				notEndOfText=0;
			if(isNewSentence)
			{
				if(i>=txt.sentences[txt.numOfSentences-1].curSize-2)
				{
					addSentenceMemory(&(txt.sentences[txt.numOfSentences-1]));
				}
				txt.sentences[txt.numOfSentences-1].content[i]=buf;
				txt.sentences[txt.numOfSentences-1].content[i+1]=L'\0';
				i++;
			}
		}
		while(buf!=L'.' && notEndOfText<2);
		if (notEndOfText<2)
			addTextMemory(&txt);
	}
	while(notEndOfText<2);
	txt.numOfSentences--;
	return txt;
}