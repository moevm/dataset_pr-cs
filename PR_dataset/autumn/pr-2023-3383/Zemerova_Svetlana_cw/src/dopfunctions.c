#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include "functions.h"
#include "input_output.h"

wchar_t* not_pun_sp(wchar_t* sent){
	wchar_t *str=(wchar_t*)malloc((wcslen(sent)+1)*sizeof(wchar_t));
	size_t j=0;
	for (size_t i=0; i<wcslen(sent); i++){
	if (iswalnum(sent[i])) str[j++]=towlower(sent[i]);
	}
	str[j]=L'\0';
	return str;
}

int anagramma(wchar_t* sent1, wchar_t* sent2, size_t len){
	wchar_t* str1=sent1;
	wchar_t* str2=sent2;
	qsort(str1, len, sizeof(wchar_t), comparator);
	qsort(str2, len, sizeof(wchar_t), comparator);
	for (size_t i=0; i<len; i++) if (str1[i]!=str2[i]) return 0;
	return 1;
}

void replacekiril(wchar_t symb, wchar_t* vow, size_t *j){
 if (symb == L'я') 
 {
      vow[(*j)++]=L'а';
      vow[(*j)++]=L'б';
 }
 else  if (symb  == L'Я')
 {
      vow[(*j)++]=L'А';
      vow[(*j)++]=L'Б';
 }
 else if (symb == L'ю') 
 {
      vow[(*j)++]=L'я';
      vow[(*j)++]=L'а';
 }
 else  if (symb  == L'Ю')
 {
      vow[(*j)++]=L'Я';
      vow[(*j)++]=L'А';
 }
 else if (symb==L'Е')  
 {
 	vow[(*j)++]=L'Ё'; 
 	vow[(*j)++]=L'Ж';
 }
 else if (symb==L'е')  
 {
 	vow[(*j)++]=L'ё';
 	vow[(*j)++]=L'ж';
 }
 else if (symb==L'Ё')  
 {
 	vow[(*j)++]=L'Ж'; 
 	vow[(*j)++]=L'З';
 }
 else if (symb==L'ё')  
 {
 	vow[(*j)++]=L'ж';
 	vow[(*j)++]=L'з';
 }
 else {
      vow[(*j)++]=symb+1;
      vow[(*j)++]=symb+2;
  }
}

void replacelatin(wchar_t symb, wchar_t* vow, size_t *j){
 if (symb == L'y') 
 {
      vow[(*j)++]=L'z';
      vow[(*j)++]=L'a';
 }
 else if (symb  == L'Y')
 {
      vow[(*j)++]=L'Z';
      vow[(*j)++]=L'A';
 }
 else
 {
      vow[(*j)++]=symb+1;
      vow[(*j)++]=symb+2;
  }
}

int compare(const void* a, const void* b){
	const Sentence** f=(const Sentence**)a;
	const Sentence** s=(const Sentence**)b;
	size_t kf=0;
	size_t ks=0;
	for (size_t i=0; i<wcslen((*f)->symbols); i++) if (iswupper((*f)->symbols[i])) kf++;
	for (size_t i=0; i<wcslen((*s)->symbols); i++) if (iswupper((*s)->symbols[i])) ks++;
	return kf-ks;
}

int comparator(const void *a, const void *b){
	const wchar_t * f=(const wchar_t*)a;
	const wchar_t * s=(const wchar_t*)b;
	return wcscmp(f,s);
}

int cmp(wchar_t * sent1, wchar_t * sent2, size_t len){
	for (size_t i=0; i<len; i++) if (towlower(sent1[i])!=towlower(sent2[i])) return 0;
	return 1;
}


