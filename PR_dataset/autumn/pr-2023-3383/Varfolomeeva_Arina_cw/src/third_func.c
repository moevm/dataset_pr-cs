#include "third_func.h"
#include "struct.h"

unsigned long calc_multip(wchar_t *str, size_t len) {
	wchar_t* ptr, *token;
	wchar_t* str_copy = malloc(sizeof(wchar_t) * (len+1));
	wcsncpy(str_copy, str, len);
	str_copy[len] = 0;
	
	unsigned long result = 1;
	token = wcstok(str_copy, L" ,.", &ptr); 
	while (token != NULL) {
		result *= wcslen(token);
		token = wcstok(NULL, L" ,.", &ptr);
	}
	return result;
}

int compare_multip(wchar_t *a, size_t len_a, wchar_t *b, size_t len_b) {
	unsigned long multip_a = calc_multip(a, len_a);
	unsigned long multip_b = calc_multip(b, len_b);
	return (multip_b < multip_a) - (multip_b > multip_a);
}

int compare(const void *a, const void *b) {
	Sentence* sentence_a = *(Sentence **)a;
	Sentence* sentence_b = *(Sentence **)b;
	return compare_multip(sentence_a->string, sentence_a->length, sentence_b->string, sentence_b->length);
}

Text third_func(Text txt){
	qsort(txt.text, txt.length, sizeof(Sentence *), compare);
	return txt;
}
