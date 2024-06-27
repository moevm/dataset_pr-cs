#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include "functions.h"
#include "input_output.h"
#include "freememory.h"

//1 ФУНКЦИЯ
size_t * function1(Text T, size_t* sovp){
	wchar_t* sent1;
	wchar_t* sent2;
	size_t *sentences=(size_t*)calloc(T.teklen,sizeof(size_t*));
	for (size_t k=0; k<T.teklen-1; k++){
		sent1=not_pun_sp(T.sent[k]->symbols);
		(*sovp)++;
		for (size_t j=k+1; j<T.teklen; j++){
		sent2=not_pun_sp(T.sent[j]->symbols);
		if (wcslen(sent1)==wcslen(sent2) && anagramma(sent1,sent2,wcslen(sent1))){
			sentences[k]=*sovp; 
			sentences[j]=*sovp; 
		}
	}
	}
	return sentences;

}

//2 ФУНКЦИЯ
void function2(Text T){
	qsort(T.sent, T.teklen, sizeof(Sentence*), compare);
}
//3 ФУНКЦИЯ

wchar_t* function3(wchar_t *sent, size_t lens){
	wchar_t * vowels1=L"AEIOUYaeiouy";
	wchar_t * vowels2=L"АЕЁИОУЫЭЮЯаеёиоуыэюя";
	wchar_t * vow=(wchar_t*)malloc(lens*sizeof(wchar_t)*2);
	wchar_t * sentnew=(wchar_t *)malloc(lens*sizeof(wchar_t)*2+sizeof(wchar_t));;
	size_t j=0;
	size_t k=0;
	for (size_t i=0; i<lens; i++){
		if (wmemchr(vowels1, sent[i], 12)!=NULL){
			replacelatin(sent[i], vow,&j);
			sentnew[k++]=vow[j-2];
			sentnew[k++]=vow[j-1];
		}
		else if (wmemchr(vowels2, sent[i], 20)!=NULL){
			replacekiril(sent[i],vow,&j);
			sentnew[k++]=vow[j-2];
			sentnew[k++]=vow[j-1];
		}
		else sentnew[k++]=sent[i];
	}
	sentnew[k]=L'\0';
	free(vow);
	return sentnew;
}

//4 ФУНКЦИЯ	
void input_word(wchar_t* word, wchar_t* newword){
	size_t lenw=0;
	wchar_t c=getwchar();
	wchar_t* buffer=(wchar_t *)malloc(STR_BLOCK*10*sizeof(wchar_t));
	while((c=getwchar())!=L'\n') buffer[lenw++]=c;
	buffer[lenw]=L'\0';
	size_t fl=1;
	wchar_t* state;
	wchar_t* pch=wcstok(buffer, L" ,\t\n.", &state);
	while (pch!=NULL){
	if (fl){
	word=(wchar_t*)realloc(word,(wcslen(pch)+1)*sizeof(wchar_t));
	wmemmove(word, pch, wcslen(pch)+1);
	}
	else{
	newword=(wchar_t*)realloc(newword, (wcslen(pch)+1)*sizeof(wchar_t));
	wmemmove(newword, pch, wcslen(pch)+1);
	}
	fl-=1;
	pch=wcstok(NULL, L" ,\t\n.", &state);
	}
	free(buffer);
	if (fl!=-1){
	wprintf(L"Error: ошибка ввода слов.\n");
	wprintf(L"Завершение работы программы.\n");
	exit(0);
	}
}

wchar_t* function4(wchar_t* sent, wchar_t* word, wchar_t* newword, size_t len2, size_t len3){
	size_t len=wcslen(sent);
	size_t lenn=len;
	wchar_t sent_cpy[len+1];
	wcscpy(sent_cpy, sent);
	size_t j=0;
	for(size_t i=0; i<len; i++){
		if (cmp(&sent_cpy[i], word, len2)){
		lenn+=(len3-len2);
		sent=(wchar_t*)realloc(sent, sizeof(wchar_t)*(lenn+1));
		if (!sent){
		wprintf(L"Error: ошибка выделения памяти.\n");
		wprintf(L"Завершение работы программы.\n");
		exit(0);
		}
		wmemcpy(&sent[j], newword, len3);
		wmemcpy(&sent[j+len3], &sent_cpy[i+len2], len-i-len2+1);
		i+=len2-1;
		j+=len3;
		}
		else j++;
		}
	return sent;
}

//5 ФУНКЦИЯ
void function5(){
	wprintf(L"Справка о функциях, реализуемых программой.\n");
	wprintf(L"Функция 0: вывод текста после первичной обработки.\n");
	wprintf(L"Функция 1: вывод всех предложений, являющихся анаграммами друг для друга без учета регистра.\n");
	wprintf(L"Функция 2: сортировка предложений по количеству заглавных букв.\n");
	wprintf(L"Функция 3: замена каждой гласной буквы двумя другими буквами, идушими следующими по алфавиту.\n");
	wprintf(L"Функция 4: замена всех вхождений одного слова на другое. Оба слова вводит пользователь.\n");
}

wchar_t* function9(){
	size_t fl;
	size_t i=0;
	wchar_t* sent1=(wchar_t*)malloc(STR_BLOCK*10*sizeof(wchar_t));
	wchar_t* sent2=(wchar_t*)malloc(STR_BLOCK*10*sizeof(wchar_t));
	wchar_t c=getwchar();
	while ((c=getwchar())!=L'\n') sent1[i++]=c;
	sent1[i]=L'\0';
	i=0;
	while ((c=getwchar())!=L'\n') sent2[i++]=c;
	sent2[i]=L'\0';
	size_t len=wcslen(sent1);
	for(size_t i=0; i<len; i++){
		fl=1;
		for(size_t j=0; j<wcslen(sent2); j++){
		if (sent1[i+j]!=sent2[j]){
		fl=0;
		break;}
		}
		if (fl){
		wmemmove(&sent1[i], &sent1[i+wcslen(sent2)],len-(i-wcslen(sent2)));
		len-=wcslen(sent2);
		i+=wcslen(sent2)-1;
		}
		}
	return sent1;
}

