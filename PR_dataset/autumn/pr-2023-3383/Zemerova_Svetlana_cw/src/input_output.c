#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include "functions.h"
#include "input_output.h"
#include "freememory.h"

Text input(){
	Sentence** memory_T;
	wchar_t* memory_sent;
	Text T;
	T.tlen=BLOCK;
	T.sent=(Sentence**)malloc(T.tlen*sizeof(Sentence*));
	for (size_t i=0; i<T.tlen; i++) T.sent[i]=(Sentence*)malloc(sizeof(Sentence));
	wchar_t c=getwchar();
	size_t deli;	
	size_t ind_sent=0;
	while(1){ 
		if (!iswspace(c) && c!=L'.' && c!=L','){
		if (ind_sent==T.tlen-1){	
			memory_T=(Sentence**)realloc(T.sent,(T.tlen+BLOCK)*sizeof(Sentence*));
			if (memory_T!=NULL){
			T.sent=memory_T;
			for (size_t i=T.tlen; i<T.tlen+BLOCK; i++) T.sent[i]=(Sentence*)malloc(sizeof(Sentence));
			T.tlen+=BLOCK;
			}
			else{
			freememory(T);
			wprintf(L"Error: ошибка выделения памяти.\n");
			wprintf(L"Завершение работы программы.\n");
			exit(0);
			}
		}
		T.sent[ind_sent]->symbols=(wchar_t*)malloc(STR_BLOCK*sizeof(wchar_t));
		T.sent[ind_sent]->count=STR_BLOCK;
		T.sent[ind_sent]->len=0;
		deli=ind_sent;
		while(1){
			if (c==L'\n'){
			wprintf(L"Error: Ошибка ввода текста.\n");
			wprintf(L"Завершение работы программы.\n");
			exit(0);
			}
			
			if (T.sent[ind_sent]->len==(T.sent[ind_sent]->count-1)){
				T.sent[ind_sent]->count+=STR_BLOCK;
				memory_sent=(wchar_t*)realloc(T.sent[ind_sent]->symbols,(T.sent[ind_sent]->count)*sizeof(wchar_t));
				if (memory_sent!=NULL) T.sent[ind_sent]->symbols=memory_sent;
				else{
				freememory(T);
				wprintf(L"Error: Ошибка выделения памяти.\n");
				wprintf(L"Завершение работы программы.\n");
				exit(0);
				}
			}
			
			T.sent[ind_sent]->symbols[T.sent[ind_sent]->len++]=c;

			if (c==L'.'){
			for (size_t j=0; j<ind_sent; j++){
				if (cmp(T.sent[ind_sent]->symbols,T.sent[j]->symbols,T.sent[ind_sent]->len)){
					deli=j;
					break;
					}
				}
				
			if (deli==ind_sent){
			T.sent[ind_sent]->symbols[T.sent[ind_sent]->len++]=L'\0';
			T.sent[ind_sent]->symbols=(wchar_t*)realloc(T.sent[ind_sent]->symbols, (T.sent[ind_sent]->len)*sizeof(wchar_t));
			ind_sent++;
			}
			else free(T.sent[ind_sent]->symbols);
			break;
			}
			c=getwchar();
		}
		c=getwchar();
		}
		
		else if (c==L'\n'){
			if ((c=getwchar())==L'\n'){
				for (size_t j=ind_sent; j<T.tlen; j++) free(T.sent[j]);
				T.sent=(Sentence**)realloc(T.sent,ind_sent*sizeof(Sentence*));
				T.teklen=ind_sent;
				break;
			}
			}
		else c=getwchar();
		}
	if (!T.teklen){
	wprintf(L"Error: Вы не ввели текст.\n");
	wprintf(L"Завершение работы программы.\n");
	exit(0);
	}
	return T;
}

void output(Text T, int number){
	switch(number){
			case 0:
				for (size_t i=0; i<T.teklen; i++) wprintf(L"%S\n", T.sent[i]->symbols);
				break;
	
			case 1:;
				size_t sovp=0;
				size_t* st=function1(T, &sovp);
				for (size_t j=1; j<=sovp; j++){
					for (size_t s=0; s<T.teklen; s++) if (st[s]==j) wprintf(L"%S\n", T.sent[s]->symbols);
				}
				free(st);
				break;
				
			case 2:
				function2(T);
				for (size_t i=0; i<T.teklen; i++) wprintf(L"%S\n", T.sent[i]->symbols);
				break;
	
			case 3:
				for (size_t i=0; i<T.teklen; i++) wprintf(L"%S\n", function3(T.sent[i]->symbols, T.sent[i]->len)); 
				break;
	
			case 4:;
				wchar_t* word=(wchar_t *)malloc(STR_BLOCK*10*sizeof(wchar_t));
				wchar_t* newword=(wchar_t *)malloc(STR_BLOCK*10*sizeof(wchar_t));
				input_word(word,newword);
				T=input();
				for (size_t i=0; i<T.teklen; i++) {
				wprintf(L"%S\n", function4(T.sent[i]->symbols, word, newword, wcslen(word), wcslen(newword)));
				free(T.sent[i]);
				}
				free(T.sent);
				break;
			case 9:	
				wprintf(L"%S\n",function9());
	}
	
}


