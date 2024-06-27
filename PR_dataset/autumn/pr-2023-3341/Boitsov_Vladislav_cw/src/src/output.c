#include<wchar.h>
#include<wctype.h>

#include"../headers/output.h"

void printSentence(struct Sentence* snt)
{
	wprintf(L"%ls\n", snt->content);
}

void printText(struct Text* txt)
{
	for(int i=0;i<txt->numOfSentences;i++)
		printSentence(&(txt->sentences[i]));
}

void printHelp() 
{
    wprintf(L"\nOptions:\n");
    wprintf(L"0 - Display text after primary mandatory processing\n");
    wprintf(L"1 - Display sentences that are anagrams of each other (case-insensitive)\n");
    wprintf(L"2 - Sort sentences by the number of uppercase letters\n");
    wprintf(L"3 - Replace vowels with the next two letters in the alphabet\n");
    wprintf(L"4 - Replace occurrences of one word with another (case-insensitive)\n");
    wprintf(L"5 - Display this help message\n");
}